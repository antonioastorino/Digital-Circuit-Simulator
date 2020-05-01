window.onload = main;

function main() {
    console.log("Welcome back!")
    let canvas = document.getElementById("canvas");
    const marginTop = 350; // canvas distance from window top
    const offsetLeft = 80;
    const offsetTop = 40;
    const offsetRight = 40
    const baselineOffset = 1.3;
    var stepLength = 50;
    var stepHeight = 50;
    var firstStep = 0;
    var signals = {};
    var stepNumbers = [];

    const input = document.querySelector("input[type=file]");
    const refresh = document.getElementById("refresh");
    const select = document.getElementById("select-file");
    const reader = new FileReader;
    const sliderHZoom = document.getElementById("h-zoom");
    const sliderVZoom = document.getElementById("v-zoom");
    const sliderFirstStep = document.getElementById("first-step");
    const headerTestTitle = document.getElementById("test-title");
    const pError = document.getElementById("p-error");
    const divCanvas = document.getElementById("div-canvas");

    let refreshCanvas = () => {
        if (Object.keys(signals).length == 0) return;
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        resizeCanvas();
        drawGrid();
        drawSignals();
    }
    
    function resizeCanvas() {
        canvas.width = window.innerWidth - offsetRight;
        canvas.height = canvasHeight;
        divCanvas.style.maxHeight = window.innerHeight - marginTop + 40 + "px";
    }
    
    window.onresize = function () {
        resizeCanvas();
        refreshCanvas();
    }
    
    let canvasHeight = window.innerHeight - marginTop;
    resizeCanvas();
    refreshCanvas();

    let ctx = canvas.getContext("2d");
    ctx.font = "14px Arial";


    let dummyOption = new Option("no file loaded", 1);
    select.appendChild(dummyOption);
    let files = [];

    let drawLine = (baseline, stepNumber, currValue, prevValue) => {
        let locationY = (baseline - currValue) * stepHeight + offsetTop;
        if (currValue != prevValue) {
            ctx.lineTo(offsetLeft + (stepNumber - 1) * stepLength, locationY);
        }
        ctx.lineTo(offsetLeft + stepNumber * stepLength, locationY);
    }

    let drawSignals = () => {
        ctx.setLineDash([]);
        ctx.lineWidth = 2;
        let baseline = 1;
        Object.keys(signals).forEach(signalName => {
            let values = signals[signalName];
            ctx.beginPath();
            let prevVal = values[firstStep];
            ctx.moveTo(offsetLeft, (baseline - prevVal) * stepHeight + offsetTop);
            for (let k = 0; k < values.length - firstStep; k++) {
                drawLine(baseline, k, values[k + firstStep], prevVal);
                prevVal = values[k + firstStep];
            }
            ctx.stroke();
            ctx.closePath();
            baseline += baselineOffset;
        });
    }

    let drawGrid = () => {
        ctx.lineWidth = 1;
        let baseline = 1;
        let keys = Object.keys(signals);
        let numOfHorizontalLines = keys.length;
        let numOfVerticalLines = signals[keys[0]].length;
        canvasHeight = baseline * baselineOffset * stepHeight * numOfHorizontalLines + offsetTop;
        resizeCanvas();
        ctx.setLineDash([5, 7]);

        // draw horizontal lines and labels
        for (let lineNum = 0; lineNum < numOfHorizontalLines; lineNum++) {
            let positionY = baseline * stepHeight + offsetTop + 1;
            ctx.beginPath();
            ctx.moveTo(offsetLeft, positionY);
            ctx.lineTo(offsetLeft + (stepLength * (numOfVerticalLines - firstStep - 1)), positionY);
            ctx.stroke();
            ctx.closePath();
            ctx.fillText(keys[lineNum], 10, baseline * stepHeight + offsetTop + 1);
            baseline += baselineOffset;
        }
        baseline -= baselineOffset;
        // draw vertical lines and line number
        for (let lineNum = 0; lineNum < numOfVerticalLines - firstStep; lineNum++) {
            let positionX = offsetLeft + stepLength * lineNum;
            ctx.beginPath();
            ctx.moveTo(positionX, offsetTop);
            ctx.lineTo(positionX, baseline * stepHeight + offsetTop + 1);
            ctx.stroke();
            ctx.closePath();
            ctx.fillText(stepNumbers[lineNum + firstStep], stepLength * lineNum + offsetLeft, 30);
        }
    }

    let parseText = (text) => {
        pError.innerHTML = ""
        signals = {};
        stepNumbers = [];
        let parseKV = (kv) => {

            let binary = kv[1].split("b") // check if the value is binary and convert accordingly
            if (binary.length > 1) {
                let bits = binary[1].split("");
                for (let i = 0; i < bits.length; i++) {
                    if (signals[kv[0] + i] == undefined) {
                        signals[kv[0] + i] = [];
                    }
                    signals[kv[0] + i].push(parseInt(bits[bits.length - i - 1]));
                }
            }
            else {
                if (kv[0] == "STEP") {
                    stepNumbers.push(parseInt(kv[1]));
                } else {
                    if (signals[kv[0]] == undefined) {
                        signals[kv[0]] = [];
                    }
                    signals[kv[0]].push(parseInt(kv[1]));
                }
            }
        }

        let parseTitle = (str) => {
            headerTestTitle.innerHTML = str;
        }

        let parseError = (str) => {
            pError.innerHTML = str;
        }

        let lines = text.split("\n");
        for (let i = 0; i < lines.length; i++) {
            if (lines[i].includes("test")) {
                parseTitle(lines[i]);
            }
            if (lines[i].includes("ERROR:")) {
                parseError(lines[i]);
            }
            else if (lines[i].includes("STEP:")) {
                let pairs = lines[i].split(" ");
                for (let j = 0; j < pairs.length; j++) {
                    let pair = pairs[j];
                    if (pair != "") {
                        let kv = pair.split(":");
                        if (kv.length == 2) {
                            parseKV(kv);
                        }
                    }
                }
            }
        }
    }


    let readFile = async (filePath)  => {
        let xhttp = new XMLHttpRequest();
		return new Promise((resolve) => {
			xhttp.onreadystatechange = function () {
				if (xhttp.readyState != 4) return;
				if (xhttp.status >= 200 && xhttp.status < 300) {
					let text = xhttp.response;
					resolve(text);
				}
			};
			xhttp.open("GET", filePath, true);
			xhttp.responseType = "text";
			xhttp.send();
		});
    }

    let updateData = async () => {
        let result = await readFile("./assets/" + files[select.selectedIndex].name);
        parseText(result);
        try {
            let signalLength = Object.values(signals)[0].length;
            sliderFirstStep.setAttribute("max", Math.max(signalLength - 10, 0).toString())
            firstStep = parseInt(sliderFirstStep.value);
        } catch {
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            firstStep = 0;
            console.log("No signal loaded");
        }
    }


    input.onchange = async () => {
        if (input.files.length == 0) return;
        select.innerHTML = "";
        files.length = 0;
        for (const file of input.files) {
            const {
                name
            } = file;
            const option = new Option(name, files.length);
            files.push(file);
            select.appendChild(option);
        }
        await updateData();
        refreshCanvas();
    }

    select.onchange = async () => {
        await updateData();
        refreshCanvas();
    }

    refresh.onclick = async () => {
        if (files.length == 0) return;
        await updateData();
        refreshCanvas();
    }

    sliderHZoom.oninput = function () {
        stepLength = parseInt(this.value);
        refreshCanvas();
    }

    sliderVZoom.oninput = function () {
        stepHeight = parseInt(this.value);
        refreshCanvas();
    }

    sliderFirstStep.oninput = function () {
        firstStep = parseInt(this.value);
        refreshCanvas();
    }
}
