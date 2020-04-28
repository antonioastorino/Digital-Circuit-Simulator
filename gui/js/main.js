window.onload = main;
window.onresize = resizeCanvas
let canvas = document.getElementById("canvas");
const marginTop = 280; // canvas distance from window top
var stepLength = 50;
var stepHeight = 50;
var firstStep = 0;
const offsetLeft = 80;
const offsetTop = 40;
var signals = {};


function main() {
    console.log("Welcome back!")
    canvas.width = window.innerWidth - 20;
    canvas.height = window.innerHeight - marginTop;
    let ctx = canvas.getContext("2d");
    ctx.font = "14px Arial";

    const input = document.querySelector("input[type=file]");
    const refresh = document.getElementById("refresh");
    const select = document.querySelector("select");
    const reader = new FileReader;

    const sliderHZoom = document.getElementById("h-zoom");
    const sliderVZoom = document.getElementById("v-zoom");
    const sliderFirstStep = document.getElementById("first-step");
    const spanFirstStep = document.getElementById("span-first-step");

    let dummyOption = new Option("Load files", 1);
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
            baseline += 1.3;
        });
    }

    let drawGrid = () => {
        ctx.setLineDash([5, 7]);
        ctx.lineWidth = 1;
        let baseline = 1;
        let keys = Object.keys(signals);
        let numOfHorizontalLines = keys.length;
        let numOfVerticalLines = signals[keys[0]].length;
        // draw horizontal lines and labels
        for (let lineNum = 0; lineNum < numOfHorizontalLines; lineNum++) {
            let positionY = baseline * stepHeight + offsetTop + 1;
            ctx.beginPath();
            ctx.moveTo(offsetLeft, positionY);
            ctx.lineTo(offsetLeft + (stepLength * (numOfVerticalLines - firstStep - 1)), positionY);
            ctx.stroke();
            ctx.closePath();
            ctx.fillText(keys[lineNum],10, baseline * stepHeight + offsetTop + 1);
            baseline += 1.3;
        }
        baseline -= 1.3;
        // draw vertical lines
        for (let lineNum = 0; lineNum < numOfVerticalLines - firstStep; lineNum++) {
            let positionX = offsetLeft + stepLength * lineNum;
            ctx.beginPath();
            ctx.moveTo(positionX, offsetTop);
            ctx.lineTo(positionX, baseline * stepHeight + offsetTop + 1);
            ctx.stroke();
            ctx.closePath();
        }
    } 

    let parseText = (text) => {
        signals = {};
        let parseKV = (kv) => {
            let binary = kv[1].split("b") // check if the value is binary and convert accordingly
            if (binary.length > 1) {
                let bits = binary[1].split("");
                for (let i = 0; i < bits.length; i++) {
                    if (signals[kv[0] + i] == undefined) {
                        signals[kv[0] + i] = [];
                    }
                    signals[kv[0] + i].push(parseInt(bits[i]));
                }
                console.log(binary[1]);
            }
            else {
                if (signals[kv[0]] == undefined) {
                    signals[kv[0]] = [];
                }
                signals[kv[0]].push(parseInt(kv[1]));
            }
        }

        let lines = text.split("\n");
        for (let i = 0; i < lines.length; i++) {
            if (lines[i].includes("STEP:")) {
                let pairs = lines[i].split(" ");
                for (let j = 0; j < pairs.length; j++) {
                    let pair = pairs[j];
                    if (pair != "") {
                        let kv = pair.split(":");
                        if (kv.length == 2 && kv[0] != "STEP") {
                            parseKV(kv);
                        }
                    }
                }
            }
        }
        return signals;
    }


    let read = (file, reader) => new Promise((resolve, reject) => {
        reader.onload = () => {
            reader.onload = reader.onerror = null;
            resolve(reader.result);
        }
        reader.onerror = reject;
        reader.readAsText(file);
    })

    input.onchange = async () => {
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
    }

    let refreshCanvas = () => {
        if (Object.keys(signals).length == 0) return;
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        drawGrid();
        drawSignals();
    }
    
    refresh.onclick = async () => {
        if (files.length == 0) return;
        let result = await read(files[select.selectedIndex], reader);
        signals = parseText(result);
        let signalLength = Object.values(signals)[0].length;
        sliderFirstStep.setAttribute("max", Math.max(signalLength - 10, 0).toString())
        refreshCanvas();
    }

    sliderHZoom.oninput = function() {
        stepLength = parseInt(this.value);
        refreshCanvas();
    }

    sliderVZoom.oninput = function() {
        stepHeight = parseInt(this.value);
        refreshCanvas();
    }

    sliderFirstStep.oninput = function() {
        firstStep = parseInt(this.value);
        spanFirstStep.innerText = firstStep;
        refreshCanvas();
    }
}

function resizeCanvas() {
    canvas.width = window.innerWidth - 20;
    canvas.height = window.innerHeight - marginTop;
}