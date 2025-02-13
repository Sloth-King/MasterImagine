class Animation {
    id = 0;
    step = 0;
    start = 0;
    previousTimeStep = 0;

    constructor(maxStep = 24, animationDuration = 1000) {
        this.animationDuration = animationDuration;
        this.frameDuration = animationDuration / maxStep;
        this.maxStep = maxStep;
    }

    run() { 
        this.start = Date.now();
        
        if (this.firstStep !== undefined)
            this.firstStep(this.start);

        this.id = window.requestAnimationFrame(t => {
            
            this.animate(t);
        });
    }

    animate(t) {
        let delta = t - this.previousTimeStep;

        if (this.step < this.maxStep) {          
            if (delta >= this.frameDuration) {
                this.nextStep(t);              
                this.step++;
                this.previousTimeStep = t;
            }
            this.id = window.requestAnimationFrame(t => this.animate(t));
         } else {
            if (this.lastStep !== undefined) this.lastStep(Date.now());
            window.cancelAnimationFrame(this.id);
            this.duration = (Date.now() - this.start)/1000;
            console.log("Animation terminee (" + this.duration + " secondes) ");
       }
    }

    test() {
        console.log("Test");
    }
}


