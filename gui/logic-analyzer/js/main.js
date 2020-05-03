window.onload = main;

function main() {
    console.log("Welcome back!")
    let canvas = document.getElementById("canvas");
    const marginBottom = 40; // canvas distance from window top
    const offsetLeft = 80;
    const offsetTop = 40;
    const offsetRight = 40
    const baselineOffset = 1.5;
    var stepLength = 50;
    var stepHeight = 40;
    var firstStep = 0;
    var signals = {};
    var stepNumbers = [];
    var hexadecimal = false; // means binary
    var result = "";

    const input = document.querySelector("input[type=file]");
    const refresh = document.getElementById("refresh");
    const select = document.getElementById("select-file");
    const sliderHZoom = document.getElementById("h-zoom");
    const sliderVZoom = document.getElementById("v-zoom");
    const sliderFirstStep = document.getElementById("first-step");
    const headerTestTitle = document.getElementById("test-title");
    const pError = document.getElementById("p-error");
    const divCanvas = document.getElementById("div-canvas");
    const binaryHexadecimalButton = document.getElementById("bin-hex-button");

    let refreshCanvas = () => {
        if (Object.keys(signals).length == 0) return;
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        resizeCanvas();
        drawGrid();
        drawSignals();
    }

    function resizeCanvas() {
        canvas.width = window.innerWidth - offsetRight;
        var rect = canvas.getBoundingClientRect();
        canvas.height = canvasHeight;
        divCanvas.style.maxHeight = (window.innerHeight - rect.top - marginBottom) + "px";
    }

    window.onresize = function () {
        resizeCanvas();
        refreshCanvas();
    }

    let canvasHeight = window.innerHeight - marginBottom;
    resizeCanvas();
    refreshCanvas();

    let ctx = canvas.getContext("2d");

    let dummyOption = new Option("no file loaded", 1);
    select.appendChild(dummyOption);
    let files = [];



    function binaryToHex(s) {
        let lookUpTable = {
            "0000": '0',
            "0001": '1',
            "0010": '2',
            "0011": '3',
            "0100": '4',
            "0101": '5',
            "0110": '6',
            "0111": '7',
            "1000": '8',
            "1001": '9',
            "1010": 'A',
            "1011": 'B',
            "1100": 'C',
            "1101": 'D',
            "1110": 'E',
            "1111": 'F',
        }
        if (s.length % 4) return "number of bits not a multiple of 4"
        let hex = "";
        let splitS = s.match(/.{1,4}/g);
        for (let j = 0; j < splitS.length; j++) {
            hex += lookUpTable[splitS[j]];
        }
        return hex;
    }


    let drawLine = (baseline, stepNumber, currValue, prevValue) => {
        let locationY = (baseline - currValue) * stepHeight + offsetTop;
        if (currValue != prevValue) {
            ctx.lineTo(offsetLeft + (stepNumber - 1) * stepLength + 2, locationY);
        }
        ctx.lineTo(offsetLeft + stepNumber * stepLength - 2, locationY);
    }

    let printLabel = (baseline, stepNumber, text) => {
        let locationY = (baseline - 1 / 2) * stepHeight + offsetTop;
        ctx.font = "14px Verdana";
        ctx.fillStyle = "#0505f0";
        ctx.fillText("0x" + binaryToHex(text), offsetLeft + stepNumber * stepLength + 2, locationY + 5);
    }

    let drawSignals = () => {
        ctx.setLineDash([]);
        ctx.strokeStyle = '#020228';
        ctx.lineWidth = 2;
        let baseline = 1;
        Object.keys(signals).forEach(signalName => {
            let values = signals[signalName];
            let prevVal;
            if (values[firstStep].length > 1) {
                for (var startLevel of [true, false]) {
                    prevVal = values[firstStep];
                    let level = startLevel // start drawing from high
                    let prevLevel = startLevel // start drawing from high
                    printLabel(baseline, 0, values[firstStep + 1]);
                    ctx.beginPath();
                    ctx.moveTo(offsetLeft, (baseline - (level ? 1 : 0)) * stepHeight + offsetTop);
                    for (let k = 0; k < values.length - firstStep; k++) {
                        if (values[k + firstStep] != prevVal) {
                            level = !level;
                            printLabel(baseline, k - 1, values[k + firstStep]);
                        }
                        drawLine(baseline, k, level ? 1 : 0, prevLevel ? 1 : 0);
                        prevVal = values[k + firstStep];
                        prevLevel = level;
                    }
                    ctx.stroke();
                    ctx.closePath();
                }
                baseline += baselineOffset;
            }
            else {
                prevVal = values[firstStep];
                ctx.beginPath();
                ctx.moveTo(offsetLeft, (baseline - prevVal) * stepHeight + offsetTop);
                for (let k = 0; k < values.length - firstStep; k++) {
                    drawLine(baseline, k, values[k + firstStep], prevVal);
                    prevVal = values[k + firstStep];
                }
                ctx.stroke();
                ctx.closePath();
                baseline += baselineOffset;
            }
        });
    }

    let drawGrid = () => {
        ctx.lineWidth = 0.5;
        let baseline = 1;
        let keys = Object.keys(signals);
        let numOfHorizontalLines = keys.length;
        let numOfVerticalLines = signals[keys[0]].length;
        canvasHeight = baseline * baselineOffset * stepHeight * numOfHorizontalLines + offsetTop;
        resizeCanvas();
        ctx.setLineDash([2, 10]);

        // draw horizontal lines and labels
        for (let lineNum = 0; lineNum < numOfHorizontalLines; lineNum++) {
            let positionY = baseline * stepHeight + offsetTop;
            ctx.beginPath();
            ctx.strokeStyle = '#a0a0ff';
            ctx.moveTo(offsetLeft, positionY);
            ctx.lineTo(offsetLeft + (stepLength * (numOfVerticalLines - firstStep - 1)), positionY);
            ctx.stroke();
            ctx.closePath();
            ctx.font = "12px Verdana";
            ctx.fillStyle = "#333333";
            ctx.fillText(keys[lineNum], 10, (baseline - 1 / 2) * stepHeight + offsetTop + 6);
            baseline += baselineOffset;
        }
        baseline -= baselineOffset;
        // draw vertical lines and line number
        for (let lineNum = 0; lineNum < numOfVerticalLines - firstStep; lineNum++) {
            let positionX = offsetLeft + stepLength * lineNum;
            ctx.beginPath();
            ctx.moveTo(positionX, offsetTop);
            ctx.lineTo(positionX, baseline * stepHeight + offsetTop);
            ctx.stroke();
            ctx.closePath();
            if (stepLength > 20 || (lineNum % 2) == 0) {
                if (stepLength > 10 || (lineNum % 4) == 0) {
                    if (stepLength > 5 || (lineNum % 8) == 0) {
                        if (stepLength > 2 || (lineNum % 24) == 0) {
                            ctx.font = "12px Verdana";
                            ctx.fillStyle = "#000000";
                            ctx.fillText(stepNumbers[lineNum + firstStep], stepLength * lineNum + offsetLeft, 30);
                        }
                    }
                }
            }
        }
    }

    let parseText = () => {
        pError.innerHTML = ""
        signals = {};
        stepNumbers = [];
        let parseKV = (kv) => {

            let binary = kv[1].split("b") // check if the value is binary and convert accordingly
            if (binary.length > 1) {

                if (!hexadecimal || binary[1].length % 4 != 0) {  // binary representation (one line per bit)
                    let bits = binary[1].split("");
                    for (let i = 0; i < bits.length; i++) {
                        if (signals[kv[0] + i] == undefined) {
                            signals[kv[0] + i] = [];
                        }
                        signals[kv[0] + i].push(parseInt(bits[bits.length - i - 1]));
                    }
                }
                else { // store as it is for later hexadecimal conversion
                    if (signals[kv[0]] == undefined) {
                        signals[kv[0]] = [];
                    }
                    signals[kv[0]].push(binary[1]);
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

        let lines = result.split("\n");
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


    let readFile = async (filePath) => {
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
        result = await readFile("./assets/" + files[select.selectedIndex].name);
        parseText();
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

    binaryHexadecimalButton.onclick = () => {
        hexadecimal = !hexadecimal;
        binaryHexadecimalButton.value = hexadecimal ? "Go binary" : "Go hexadecimal";
        parseText();
        refreshCanvas();
    }
}
