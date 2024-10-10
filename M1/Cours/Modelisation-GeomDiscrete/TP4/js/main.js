function initAndRender() {
    const canvas = document.getElementById("canvas"),
        displayer = new Displayer(canvas),
        colors = ["#FEE", "#FFF", "#41566E"],
        nbSommets = 25;
    let algo = getAlgo((document.querySelector("input[type=radio]:checked")).id);

    function getAlgo(id) {
        return (id == "ri0") ? algoEnvConv.demiPlan : (id == "ri1") ? algoEnvConv.jarvis : algoEnvConv.graham;
    }

    let points;
    points = (new Dataset()).initRandomPoints(nbSommets, canvas.width, canvas.height, "p");
    //points = (new Dataset()).initFixedPoints("p");	
    displayer.drawPoints(points, colors, false);
    
    function initAndDrawEnvConv() {
        let tour = 0;
        let envconv = new EnveloppeConvexe(points, algo);
        displayer.drawPoints(points, colors, false);
        envconv.drawIn(displayer);
        // for(let i = 0; i < points.length-2; i++){

        //     tour = envconv.tour(points[i], points[i+1], points[i+2]);

        //     if(tour > 0) displayer.setColors(["#F00", "#FFF", "#41566E"]);
        //     else if(tour < 0) displayer.setColors(["#0F0", "#FFF", "#41566E"]);
        //     else displayer.setColors(["#FFF", "#FFF", "#41566E"]);

        //     displayer.mDrawLine(points[i], points[i+1]);
        //     displayer.mDrawLine(points[i+1], points[i+2]);
        //     displayer.mDrawLine(points[i+2], points[i]);
        // }
    }

    document.getElementById("choixAlgo").addEventListener("click", function (e) {
        let id = e.target.id;
        algo = getAlgo(id);
        initAndRender();
    });
    document.getElementById("canvas").addEventListener("click", initAndRender);
    initAndDrawEnvConv();
}