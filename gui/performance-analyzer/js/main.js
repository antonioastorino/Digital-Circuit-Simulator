window.onload = main;

function main() {
    console.log("Welcome back!")
    let canvas = document.getElementById("canvas");
    const marginTop = 350; // canvas distance from window top
    const offsetLeft = 80;
    const offsetRight = 40
    const baselineOffset = 0.3;
    var stepLength = 1;
    var stepHeight = 50;
    var firstStep = 0;
    var maxStep = 0;
    var measurements = {}
    let scaleX;
    let expandThread = false;
    let maxNumOfFunctions = 0;

    const input = document.querySelector("input[type=file]");
    const refresh = document.getElementById("refresh");
    const select = document.getElementById("select-file");
    const reader = new FileReader;
    const sliderVZoom = document.getElementById("v-zoom");
    const divCanvas = document.getElementById("div-canvas");
    const divLegend = document.getElementById("div-legend");

    let addLabelToLegend = (label, color) => {
        let labelDiv = document.createElement("div");
        labelDiv.innerHTML = label;
        labelDiv.style.backgroundColor = color;
        divLegend.appendChild(labelDiv);
    }

    let ctx = canvas.getContext("2d");
    ctx.font = "14px Arial";

    let refreshCanvas = () => {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        if (Object.keys(measurements).length == 0) return;
        resizeCanvas();
        draw();
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

    let dummyOption = new Option("no file loaded", 1);
    select.appendChild(dummyOption);
    let files = [];

    function getRandomColor() {
        var letters = "0123456789ABCDEF";
        var color = "#";
        for (var i = 0; i < 4; i++) {
            color += letters[Math.floor(Math.random() * 16)];
        }
        color += "F7"
        return color;
    }

    expandThread = true;
    let draw = () => {
        let baseline = 0;
        let threadNames = Object.keys(measurements);
        let numOfThreads = threadNames.length;
        if (expandThread) {
            canvasHeight = (stepHeight * maxNumOfFunctions) + baselineOffset * (numOfThreads - 1) * stepHeight;
        } else {
            canvasHeight = stepHeight * numOfThreads + baselineOffset * (numOfThreads - 1) * stepHeight;
        }
        resizeCanvas();

        for (let threadNum = 0; threadNum < numOfThreads; threadNum++) {
            let threadName = threadNames[threadNum];
            let functions = Object.keys(measurements[threadName]);
            for (let functionNum = 0; functionNum < functions.length; functionNum++) {
                baseline ++;
                let functionName = functions[functionNum];
                let data = measurements[threadName][functionName].data;
                let color = measurements[threadName][functionName].color;
                let positionY = baseline * stepHeight;
                let height = stepHeight;
                for (let dataNum = 0; dataNum < data.length; dataNum++) {
                    let positionX = offsetLeft + (data[dataNum][0] - firstStep) * scaleX * stepLength;
                    let width = data[dataNum][1] * scaleX * stepLength;
                    if (positionX > canvas.width || positionX + width < offsetLeft) continue;
                    ctx.fillStyle = color;
                    ctx.fillRect(positionX, positionY, width, -height);
                    if (width < 10) continue;
                    ctx.fillStyle = "black";
                    ctx.save();
                    ctx.translate(positionX + width / 2, baseline * stepHeight)
                    ctx.rotate(-Math.PI/2);
                    ctx.fillText(functionName, 0, 0);
                    ctx.restore();
                }
            }
            ctx.fillStyle = "black";
            ctx.fillText(threadName, 10, baseline * stepHeight);
            baseline += baselineOffset;
        }
    }



    let parseText = (text) => {
        measurements = {};
        divLegend.innerHTML = "";
        let lines = text.split("\n");
        let threadID, functionName, startTimepoint, elapsedTime;
        maxNumOfFunctions = 0;
        for (let i = 0; i < lines.length; i++) {
            [threadID, functionName, startTimepoint, elapsedTime] = lines[i].split(":");
            if (measurements[threadID] == undefined) { // first time you see this thread?
                measurements[threadID] = {};
            }
            if (measurements[threadID][functionName] == undefined) { // first time you see this function?
                maxNumOfFunctions ++;
                let color = getRandomColor()
                addLabelToLegend(functionName, color);
                measurements[threadID][functionName] = {
                    data: [],
                    color: color
                };
            }
            measurements[threadID][functionName].data.push([parseInt(startTimepoint), parseInt(elapsedTime)]);
        }
        let lastStart = parseInt(startTimepoint);
        let lastDuration = parseInt(elapsedTime);
        let totalDuration = lastStart + lastDuration;
        scaleX = (window.innerWidth - offsetLeft) / totalDuration;
        maxStep = lastStart;
        firstStep = Math.min(maxStep, firstStep); // adjust if current first step exceeds the max step admissible
    }


    let read = (file, reader) => new Promise((resolve, reject) => {
        reader.onload = () => {
            reader.onload = reader.onerror = null;
            resolve(reader.result);
        }
        reader.onerror = reject;
        reader.readAsText(file);
    })

    let updateData = async () => {
        let result = await read(files[select.selectedIndex], reader);
        parseText(result);
    }


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
        if (files.length == 0) {
            select.appendChild(dummyOption);
            ctx.clearRect(0, 0, canvas.width, canvas.height);
            firstStep = 0;
            console.log("no profile loaded");
        }
        else {
            await updateData();
            refreshCanvas();
        }
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

    sliderVZoom.oninput = function () {
        stepHeight = parseInt(this.value);
        refreshCanvas();
    }

    canvas.onmousewheel = function (e) {
        let magnification = (Math.atan(e.deltaY / 1000) + Math.PI / 2) / Math.PI * 2;
        stepLength = Math.max(stepLength * magnification, 0.001);
        refreshCanvas();
    }

    let drag = false;
    let last_x;

    canvas.onmousedown = function (evt) {
        last_x = evt.clientX;
        if (drag == false) {
            canvas.style.cursor = "grab";
            drag = true;
        }
    }

    canvas.onmousemove = function (evt) {
        if (drag == true) {
            var pos_x = evt.clientX;
            var dx = last_x - pos_x;
            firstStep += dx / scaleX / stepLength;
            firstStep = Math.min(firstStep, maxStep);
            firstStep = Math.max(firstStep, - (canvas.width - 10));
            last_x = pos_x;
            refreshCanvas();
        }
        canvas.style.cursor = "grab";
    }

    canvas.onmouseup = function (evt) {
        drag = false;
        canvas.style.cursor = "default";
    }
}
