const algoEnvConv = {demiPlan: 0, jarvis:1, graham:2};

class EnveloppeConvexe{
	constructor(lesPoints, a){
		this.algo = a ?? algoEnvConv.jarvis;
		this.points = lesPoints;
		this.envconv = new Array();
		this.initEnvConv();
	}

	getElements() {
		let ec = new Array();
		for (let i = 0; i < this.envconv.length; i++) {
			ec.push(this.points[this.envconv[i]]);
		}
		return ec;
	}

	initEnvConv() {
		switch (this.algo) {
			case algoEnvConv.demiPlan:
				this.algoDemiPlan();
				break;
			case algoEnvConv.jarvis:
				this.algoJarvis();
				break;
			case algoEnvConv.graham:
				this.algoGraham();
				break;
			default:
				console.log("Warning: algorithm not defined");
				break;
		}
	}

	determinant(p1 , p2){
		return (p1.x * p2.y) - (p1.y * p2.x);
    }

    detSign(p1, p2){  
        return Math.sign(this.determinant(p1, p2));
    }

    tour(p1, p2, p3){
		let P0 = new Point(p2.x - p1.x, p2.y - p1.y);
		let P1 = new Point(p3.x - p1.x, p3.y - p1.y);
		return this.detSign(P0, P1);
    }

	minY(points) {
		let min = 0;
		for (let i = 1; i < points.length; i++) {
			if (points[i].y < points[min].y) {
				min = i;
			}
		}
		return min;
	}

	findNext(idx) {
		let next = (idx + 1) % this.points.length;
		for (let i = 0; i < this.points.length; i++) {
			if (this.tour(this.points[idx], this.points[next], this.points[i]) < 0) {
				next = i;
			}
		}
		console.log(next);
		return next;
	}

	findFirst(i,j){
		let k = 0;
		for(; k < this.points.length ; k++){
			if(k != i && k != j) break;
		}
		return k;
	}

	algoDemiPlan(){
		console.log("algo d'intersection des demi-plans");
		let res = new Array();
		let n = this.points.length;
		let current , previous;
		let i , j , k , f;
		let mc = false;

		for(let j = 0 ; j < n ; j++){
			for(let i = 0 ; i < j ; i++){
				mc = true;
				f = this.findFirst(i, j);
				previous = this.tour(this.points[i], this.points[j], this.points[f]);
				k = f + 1;
				do{
					if(k != i && k != j){
						current = this.tour(this.points[i], this.points[j], this.points[k]);
						if(current == 0){
							throw "3 points alignes";
						}
						else if(current != previous){
							mc = false;
						}
					}
					previous = current;
				}while(++k < n && mc);
				if(k == n && previous == current){
					if(current > 0) res.push([i, j]);
					else if(current < 0) res.push([j, i]);
					else throw "3 points alignes";
				}
			}
		}

		this.envconv = this.convertForEnVConv(res);
	}

	convertForEnVConv(res){
		let newArray = [res[0][0], res[0][1]];
		for(let i = 0 ; i < res.length ; i++){
			for(let j = 0 ; j < res.length ; j++){
				if ((newArray.at(-1) == res[j][0]) && (!newArray.includes(res[j][1]))){
					newArray.push(res[j][1]);
				}
			}
		}
		return newArray;
	}
	

	algoJarvis() {
		console.log("algo Jarvis");
		let min = this.minY(this.points);
		let res = [min];
		let current;
		let previous = min;
		do{

			current = this.findNext(previous);
			res.push(current);
			previous = current;

		}while(current != min);
		this.envconv = res;
	}

	algoGraham(){
		console.log("algo de Graham")
		//todo


	}

	//fonction à appeler pour afficher l'enveloppe convexe dans le canvas
	drawIn(displayer) {
		displayer.drawLineLoop(this.getElements(), ["#FA3", "#41566E", "#FA3" ], true);
	}
}

