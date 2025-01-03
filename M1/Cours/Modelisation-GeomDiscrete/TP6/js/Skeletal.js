
class CMove {
    sens = Sens.forward;
    force = 11;
}

//déplacement simple ou déplacement de type snake
class SnakeMove extends CMove {
    initMove(p_e , p_previousLocation , p_node , d){
        this.displayer = d;
        let delta = new Coord2D(p_e.offsetX - p_previousLocation.x, p_e.offsetY - p_previousLocation.y);
        p_node.moveOnCanvas(delta, d);

        this.recursiveMove(p_node , d);
    }

    recursiveMove(p_node , d){
        let edges = p_node.getEdges(this.sens);
        for(let edge of edges){
            let nextNode = edge.to;
            let delta = new Coord2D(p_node.cc.x - nextNode.cc.x , p_node.cc.y - nextNode.cc.y );
            let distance = delta.norme();
            delta.setLength(this.force);

            if(distance > edge.initialLength){
                nextNode.moveOnCanvas(delta , d);
                this.recursiveMove(nextNode , d);
            }
        }
    }
}

//déplacement rigide
class BlocMove extends CMove {
    initMove(p_e , p_previousLocation , p_node , d){
        this.displayer = d;
        let delta = new Coord2D(p_e.offsetX - p_previousLocation.x, p_e.offsetY - p_previousLocation.y);
        p_node.moveOnCanvas(delta, d);

        this.recursiveMove(p_node , delta , d);
    }

    recursiveMove(p_node , delta , d){
        let edges = p_node.getEdges(this.sens);
        for(let edge of edges){
            let nextNode = edge.to;
            nextNode.moveOnCanvas(delta , d);
            this.recursiveMove(nextNode , delta , d);
        }
    }
}

//rotation
class AngleMove extends CMove {}

class Node {
    cm; //coordonnées dans le modèle
    cc; //coordonnées canvas
    edges;

    constructor(c) {
        this.cm = new Coord2D(c.x, c.y, c.label);
        this.edges = new Array();
    }

    toString() {
        return this.cm.toString() + " (" + this.length + ")";
    }

    moveOnCanvas(delta, d) {
        this.cc.plus(delta);
        this.needsUpdate = { ro: true, alpha: true };
    }

    drawIn(displayer) {
        displayer.mDrawNode(this);
    }

    getEdges(sens) {
        let that = this;
        if (sens === Sens.forward)
            return this.edges.filter(b => b.from === that);
        else
            return this.edges.filter(b => b.to === that);
    }

    getCoordCopy(fromModel) {
        if (fromModel)
            return this.cm.copy();
        if (this.cc) return this.cc.copy();
        return undefined;
    }

    getCoordShared(fromModel) {
        if (fromModel)
            return this.cm;
        if (this.cc) return this.cc;
        return undefined;
    }
    updateModelFromCanvas(displayer) {
        this.cm = displayer.p2m(this.cc);
    }

}

class Edge {
    needsUpdate;

    //from et to sont des Nodes, ils référencent donc les coordonnées modèles 
    //et les coordonnées écran pour chaque articulation
    from;
    to;

    //le longueur dans le canvas, initialisée après le premier dessin et avant toute interaction
    initialLength;

    // ro et alpha sont les coordonnées polaires du vecteur fromto.
    ro;
    alpha;

    constructor(from, to) {
        this.from = from;
        this.to = to;
        this.needsUpdate = { ro: true, alpha: true };
        this.from.edges.push(this);
        this.to.edges.push(this);
    }

    changeAlpha(up) {
        this.updateAlphaIfNeeded();
        if (up)
            this.alpha += 0.1;
        else
            this.alpha -= 0.1;
    }

    updateAlphaIfNeeded() {
        if (this.needsUpdate.alpha) {
            let v = this.getVector(true);
            this.needsUpdate.alpha = false;
            this.alpha = v.alpha();
        }
    }
    updateRoIfNeeded() {
        if (this.needsUpdate.ro) {
            let v = this.getVector(true);
            this.needsUpdate.ro = false;
            this.ro = v.norme();
        }

    }

    getVector(fromModel) {
        let a = this.from.getCoordCopy(fromModel), b = this.to.getCoordCopy(fromModel);
        return Coord2D.vecteur(a, b);
    }

    computeLength() {
        this.initialLength = this.getVector(false).norme();
    }

    updateEdgeCoordFromModel() {
        this.updateAlphaIfNeeded();
        this.updateRoIfNeeded();
    }

    getRo() {
        this.updateRoIfNeeded();
        return this.ro;
    }

    getAlpha() {
        this.updateAlphaIfNeeded();
        return this.alpha;
    }

    drawIn(displayer) {
        displayer.drawEdge(this);
    }
}

class Squelette {
    nodes;
    edges;
    static id;
    frames;

    constructor(name) {
        this.name = name;
        this.forward = true;
        this.nodes = new Array();
        this.edges = new Array();
        this.initModel();
        this.neverDrawnBefore = true;
        this.frames = new Array();
        this.keys = new Array();
        this.animation = new Animation();
        this.savedFrames = new Array();
    }

    saveKeyFrame() {
        const keyframe = {
            nodes: this.nodes.map(node => ({
                x: node.cc.x,
                y: node.cc.y,
            })),
            edges: this.edges.map(edge => ({
                from: this.nodes.indexOf(edge.from),
                to: this.nodes.indexOf(edge.to),
            }))
        };
        this.keys.push(keyframe);
    }

    interpolateFrames(key1, key2, t) {
        console.log("Interpolating frames between key1 and key2");
        const num_frames = this.animation.maxStep;
        const frames_to_interpolate = num_frames / (this.keys.length - 1);

        for (let i = 0; i < frames_to_interpolate; i++) {
            let frame = {
                nodes: key1.nodes.map((node, index) => ({
                    x: node.x + (key2.nodes[index].x - node.x) * (i / frames_to_interpolate),
                    y: node.y + (key2.nodes[index].y - node.y) * (i / frames_to_interpolate),
                })),
                edges: key1.edges.map(edge => ({
                    from: edge.from,
                    to: edge.to,
                }))
            };
            this.frames.push(frame);
        }
    }

    initAnim() {
        const keys = this.keys;
        this.frames = [];

        for (let i = 0; i < keys.length - 1; i++) {
            this.interpolateFrames(keys[i], keys[i + 1], this.animation.maxStep);
        }
    }

    updateSkeleton(frame) {
        this.nodes.forEach((node, index) => {
            node.cc.x = frame.nodes[index].x;
            node.cc.y = frame.nodes[index].y;
        });

        this.edges.forEach((edge, index) => {
            edge.from = this.nodes[frame.edges[index].from];
            edge.to = this.nodes[frame.edges[index].to];
        });
    }

    saveAnimation() {
        this.initAnim();
        console.log("frames", this.frames.length);
        this.savedFrames = this.frames;
        console.log("savedFrames", this.savedFrames.length);
        console.log("Animation saved.");
    }

    //forward = false pour backward
    changeDirection(forward) {
        this.forward = forward;
    }

    reset() {
        this.forward = true;
        this.nodes = new Array();
        this.edges = new Array();
        this.initModel();
        this.neverDrawnBefore = true;
        this.frames = new Array();
        this.keys = new Array();
        this.animation = new Animation();
        this.savedFrames = new Array();  
    }


    getModelBox() {
        let minx = this.nodes[0].cm.x, miny = this.nodes[0].cm.y, maxx = minx, maxy = miny;
        for (let p of this.nodes) {
            if (p.cm.x < minx) minx = p.cm.x; if (p.cm.y < miny) miny = p.cm.y;
            if (p.cm.x > maxx) maxx = p.cm.x; if (p.cm.y > maxy) maxy = p.cm.y;
        }
        return { minX: minx, maxX: maxx, minY: miny, maxY: maxy };
    }

    //dessin à partir du modèle
    draw(displayer, colors, incrementalDrawing) {
        displayer.setOptions(undefined, incrementalDrawing);
        let initInitialLength = false;
        if (this.neverDrawnBefore) {
            this.nodes.forEach(ce => ce.drawIn(displayer));
            this.neverDrawnBefore = false;
            initInitialLength = true;
        }
        this.edges.forEach(e => e.drawIn(displayer));
        this.nodes.forEach(ce => ce.drawIn(displayer));
        if (initInitialLength)
            this.edges.forEach(e => e.computeLength());
    }

    updateModelCoords(displayer) {
        this.nodes.forEach(n => n.updateModelFromCanvas(displayer));
        this.edges.forEach(e => e.updateEdgeCoordFromModel());
    }

    createNodesFromArrays(ox, oy, lx, ly, label) {
        let that = this, c;
        ly.forEach(
            (li, i) => {
                c = new Coord2D(ox + lx[i], oy + li, "" + Squelette.id);
                Squelette.id++;
                that.nodes.push(new Node(c));
            });
    }

    createEdges(i, j) {
        let l;
        for (let k = i; k < j - 1; k++) {
            this.edges.push(new Edge(this.nodes[k], this.nodes[k + 1]));
            l = k + 1;
        }
    }
    addEdge(i, j) {
        this.edges.push(new Edge(this.nodes[i], this.nodes[j]));
    }

    initModel() {
        this.margX = 1; this.margY = 1;
        let x1 = this.margX + 1, x0 = this.margX;
        let lx, ly;
        let i = this.nodes.length, j;
        Squelette.id = 0;
        //tronc
        x0 = x1 - 1;
        lx = [x1, x1, x1, x1, x1, x1, x1, x1];
        ly = [4.5, 4.8, 5.1, 5.4, 5.75, 6.1, 6.5, 6.8];
        i = this.nodes.length;
        this.createNodesFromArrays(this.margX, this.margY, lx, ly, "t");
        j = this.nodes.length;
        let neck = j - 1;
        this.createEdges(i, j);


        //right leg
        x0 = x1 - 0.75;
        lx = [x0, x0, x0, x0 - 0.2, x0 - 0.3];
        ly = [4, 2.25, 0.4, 0.3, 0.25];
        i = this.nodes.length;
        this.createNodesFromArrays(this.margX, this.margY, lx, ly, "rl");
        j = this.nodes.length;
        this.createEdges(i, j);
        this.addEdge(0, i);

        //left leg
        x0 = x1 + 0.75;
        lx = [x0, x0, x0, x0 + 0.2, x0 + 0.3];
        ly = [4, 2.25, 0.4, 0.3, 0.25];
        i = this.nodes.length;
        this.createNodesFromArrays(this.margX, this.margY, lx, ly, "ll");
        j = this.nodes.length;
        this.createEdges(i, j);
        this.addEdge(0, i);


        //left arm
        x0 = x1 + 1;
        lx = [x0, x0 + 0.5, x0 + .8, x0 + .9, x0 + .8];
        ly = [6.5, 5, 3.6, 3.5, 3.3];
        i = this.nodes.length;
        this.createNodesFromArrays(this.margX, this.margY, lx, ly, "la");
        j = this.nodes.length;
        this.createEdges(i, j);
        this.addEdge(neck, i);

        //right arm
        x0 = x1 - 1;
        lx = [x0, x0 - 0.5, x0 - .8, x0 - .9, x0 - .8];
        ly = [6.5, 5, 3.6, 3.5, 3.3];
        i = this.nodes.length;
        this.createNodesFromArrays(this.margX, this.margY, lx, ly, "ra");
        j = this.nodes.length;
        this.createEdges(i, j);
        this.addEdge(neck, i);

        //mouth+nose
        lx = [x1, x1];
        ly = [7.3, 7.5];
        i = this.nodes.length;
        this.createNodesFromArrays(this.margX, this.margY, lx, ly, "");
        j = this.nodes.length;
        this.createEdges(i, j);
        this.addEdge(neck, i);

        //eyes
        lx = [x1 + 0.4];
        ly = [7.8];
        let nose = this.nodes.length - 1;
        this.createNodesFromArrays(this.margX, this.margY, lx, ly, "le");
        j = this.nodes.length;
        this.addEdge(nose, j - 1);
        lx = [x1 - 0.4];
        ly = [7.8];
        this.createNodesFromArrays(this.margX, this.margY, lx, ly, "re");
        j = this.nodes.length;
        this.addEdge(nose, j - 1);
    }

    pick(p_displayer, p_e) {
        let selection = this.nodes.filter(ce => p_displayer.intersect(ce, { x: p_e.offsetX, y: p_e.offsetY }));
        let s = selection.length > 0 ? selection[0] : undefined; //todo : à affiner au besoin pour gérer superpositions, pour le moment fait l'hypothèse qu'il n'y en a pas et/ou retourne le premier élément trouvé, ie le dernier affiché...
        return s;
    }
}