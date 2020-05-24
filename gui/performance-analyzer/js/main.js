window.onload = main;

function main() {
    console.log("Welcome back!")
    let canvas = document.getElementById("canvas");
    const marginBottom = 40; // canvas distance from window top
    const offsetRight = 40
    const baselineOffset = 0.3;
    var frameHeight = 1;
    var translateX = 0;
    // var maxTranslateX = 10;
    var measurements = {}
    let scaleX = 1;
    let normalizationFactor;
    let expandThread = true;
    let maxNumOfFunctions = 0;
    let minimumLineWidth = 4;
    let totalDuration = 0;
    let lastDuration = 0;
    let minStep = 100;
    let maxStep = 500;
    let step = minStep;

    const input = document.querySelector("input[type=file]");
    const refresh = document.getElementById("refresh");
    const select = document.getElementById("select-file");
    const sliderVZoom = document.getElementById("v-zoom");
    const divCanvas = document.getElementById("div-canvas");
    const legendTable = document.getElementById("table-legend");
    const expandCollapseButton = document.getElementById("expand-collapse-button");
    const resetButton = document.getElementById("reset-button");
    const headerProjectTitle = document.getElementById("project-title");

    let ctx = canvas.getContext("2d");
    let canvasHeight = 20;
    frameHeight = parseInt(sliderVZoom.value);
    resizeCanvas();
    refreshCanvas();

    let makeReadableTimeLabel = (time) => {
        if (time >= 1000000000) {
            return Math.round(time / 1000000) / 1000 + " s";
        }
        else if (time >= 1000000) {
            return Math.round(time / 1000) / 1000 + " ms";
        }
        else if (time >= 1000) {
            return (time / 1000) + " us";
        }
        else {
            return time + " ns";
        }
    }

    let addLabelToLegend = () => {
        let threadNames = Object.keys(measurements);
        let numOfThreads = threadNames.length;
        for (let threadNum = 0; threadNum < numOfThreads; threadNum++) {
            let threadID = threadNames[threadNum];
            let functions = Object.keys(measurements[threadID]);
            for (let functionNum = 0; functionNum < functions.length; functionNum++) {
                let functionName = functions[functionNum];
                let color = measurements[threadID][functionName].color;
                let numOfCalls = measurements[threadID][functionName].numOfCalls;
                let totalExecutionTime = measurements[threadID][functionName].totalExecutionTime;
                let averageExecutionTime = Math.round(totalExecutionTime / numOfCalls);

                let tableRow = legendTable.insertRow();
                let threadIDCell = tableRow.insertCell();
                let labelCell = tableRow.insertCell();
                let numOfCallsCell = tableRow.insertCell();
                let averageExecutionTimeCell = tableRow.insertCell();
                let totalExecutionTimeCell = tableRow.insertCell();

                numOfCallsCell.style.textAlign = "right";
                totalExecutionTimeCell.style.textAlign = "right";
                averageExecutionTimeCell.style.textAlign = "right";

                tableRow.style.backgroundColor = color;
                threadIDCell.innerHTML = threadID;
                labelCell.innerHTML = functionName;
                numOfCallsCell.innerHTML = numOfCalls;
                averageExecutionTimeCell.innerHTML = makeReadableTimeLabel(averageExecutionTime);
                totalExecutionTimeCell.innerHTML = makeReadableTimeLabel(totalExecutionTime);
            }
        }
    }


    function refreshCanvas() {
        if (Object.keys(measurements).length == 0) return;
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        draw();
    }

    function adjustTranslateX() {
        normalizationFactor = (window.innerWidth - offsetRight) / totalDuration;
        // maxTranslateX = lastDuration * normalizationFactor;
        translateX = Math.min(translateX, (canvas.width) / 2 * (1 / scaleX + 1) - 10 / scaleX);
        translateX = Math.max(translateX, - (canvas.width) / 2 * (1 / scaleX + 1) + 10 / scaleX);
    }

    function resizeCanvas() {
        canvas.width = window.innerWidth - offsetRight;
        var rect = canvas.getBoundingClientRect();
        canvas.height = canvasHeight;
        divCanvas.style.maxHeight = (window.innerHeight - rect.top - marginBottom) + "px";
    }

    let dummyOption = new Option("no file loaded", 1);
    select.appendChild(dummyOption);
    let files = [];

    function getRandomColor() {
        var letters = "0123456789ABCDE";
        var color = "#";
        for (var i = 0; i < 4; i++) {
            color += letters[Math.floor(Math.random() * letters.length)];
        }
        color += "F06F"
        return color;
    }

    let transformX = (x) => {
        return (x * normalizationFactor - translateX - canvas.width / 2) * scaleX + canvas.width / 2;
    }

    let drawRuler = () => {
        function round_to_precision(x, precision) {
            return x - (x % precision);
        }
        ctx.strokeStyle = '#a0a0ff';
        ctx.fillStyle = "black";
        while ((step * normalizationFactor * scaleX) < minStep) {
            step *= 10;
        }
        while ((step * normalizationFactor * scaleX) > maxStep && step > 5) {
            step /= 10;
        }
        // get the first drawable element
        for (var pos = 0; pos < totalDuration; pos += step) {
            let transformedPos = transformX(pos);
            if (transformedPos < 0) {
                let actualZero = (translateX + canvas.width / 2 * (1 - 1 / scaleX)) / normalizationFactor;
                // console.log("actual zero " + actualZero);
                pos = round_to_precision(actualZero, step);
                // console.log("first element starts at position " + pos);
            }
            if (transformedPos > canvas.width) {
                // console.log("print interrupted at position " + pos);
                break;
            }
            // ticks
            ctx.fillRect(transformedPos - 1, 0, 2, 6);
            ctx.font = "12px Arial";
            let labelLocationY = 15;
            // labels
            if (step > 1000000) {
                ctx.fillText(pos / 1000000 + " ms", transformedPos, labelLocationY);
            }
            else if (step > 1000) {
                ctx.fillText(pos / 1000 + " us", transformedPos, labelLocationY);
            }
            else {
                ctx.fillText(pos + " ns", transformedPos, labelLocationY);
            }
            ctx.setLineDash([5, 7]);
            ctx.beginPath();
            ctx.moveTo(transformedPos, 0);
            ctx.lineTo(transformedPos, canvas.height);
            ctx.stroke();
            ctx.closePath();
        }
    }

    let draw = () => {
        let threadNames = Object.keys(measurements);
        let numOfThreads = threadNames.length;
        if (expandThread) {
            canvasHeight = (frameHeight * maxNumOfFunctions) + baselineOffset * (numOfThreads) * frameHeight;
        } else {
            canvasHeight = frameHeight * numOfThreads + baselineOffset * (numOfThreads) * frameHeight;
        }
        resizeCanvas();

        let baseline = baselineOffset / 2;
        for (let threadNum = 0; threadNum < numOfThreads; threadNum++) {
            let threadID = threadNames[threadNum];
            let functions = Object.keys(measurements[threadID]);
            for (let functionNum = 0; functionNum < functions.length; functionNum++) {
                baseline++;
                let functionName = functions[functionNum];
                let data = measurements[threadID][functionName].data;
                let color = measurements[threadID][functionName].color;
                let positionY = baseline * frameHeight;
                let height = frameHeight;

                for (let dataNum = 0; dataNum < data.length; dataNum++) {
                    let positionX = transformX(data[dataNum][0]);
                    let width = data[dataNum][1] * normalizationFactor * scaleX;
                    if (positionX > canvas.width || (positionX + width) < 0) continue;
                    ctx.fillStyle = color;
                    ctx.fillRect(positionX, positionY, width, -height);
                    // No label if the width is too small
                    if (width < minimumLineWidth) continue;
                    ctx.fillStyle = "black";
                    ctx.save();
                    ctx.translate(positionX + width / 2, baseline * frameHeight)
                    ctx.rotate(-Math.PI / 2);
                    ctx.font = "15px Times";
                    ctx.fillText(functionName, 0, 0);
                    ctx.restore();
                }
                if (!expandThread) baseline--;
            }
            if (!expandThread) baseline++;
            baseline += baselineOffset / 2;
            ctx.font = "20px monospace";
            ctx.fillStyle = "black";
            ctx.fillText("ID:" + threadID, 10, baseline * frameHeight / 2);
            ctx.moveTo(0, baseline * frameHeight);
            ctx.lineTo(canvas.width, baseline * frameHeight)
            ctx.stroke();
            baseline += baselineOffset / 2;
        }
        drawRuler();
    }

    let parseText = (text) => {
        measurements = {};
        legendTable.innerHTML = "<tr>" +
            "<td>Thread ID</td>" +
            "<td>Label</td>" +
            "<td># of calls</td>" +
            "<td>Average execution time</td>" +
            "<td>Total execution time</td>" +
            "</tr>"
        let lines = text.split("\n");
        let threadID, functionName, startTimepoint, elapsedTime;
        maxNumOfFunctions = 0;
        for (let i = 0; i < lines.length; i++) {
            if (lines[i].includes("Title:")) {
                parseTitle(lines[i]);
            }
            if (lines[i].split(":").length != 4) continue; // rough check if the line format is correct

            [threadID, functionName, startTimepoint, elapsedTime] = lines[i].split(":");

            if (measurements[threadID] == undefined) { // first time you see this thread?
                measurements[threadID] = {};
            }
            if (measurements[threadID][functionName] == undefined) { // first time you see this function?
                maxNumOfFunctions++;
                let color = getRandomColor()
                measurements[threadID][functionName] = {
                    data: [],
                    color: color,
                    totalExecutionTime: 0,
                    numOfCalls: 0
                };
            }
            measurements[threadID][functionName].data.push([parseInt(startTimepoint), parseInt(elapsedTime)]);
            measurements[threadID][functionName].totalExecutionTime += parseInt(elapsedTime);
            measurements[threadID][functionName].numOfCalls++;
        }
        let lastStart = parseInt(startTimepoint);
        lastDuration = parseInt(elapsedTime);
        totalDuration = lastStart + lastDuration;
        adjustTranslateX();
        addLabelToLegend();
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

    let parseTitle = (str) => {
        headerProjectTitle.innerHTML = str.split("Title:")[1];
    }

    let updateData = async () => {
        let result = await readFile("./data/" + files[select.selectedIndex].name);
        parseText(result);
    }


    window.onresize = function () {
        resizeCanvas();
        adjustTranslateX();
        refreshCanvas();
    }

    resetButton.onclick = function () {
        translateX = 0;
        scaleX = 1;
        sliderVZoom.value = 100;
        frameHeight = 100;
        refreshCanvas();
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

    sliderVZoom.oninput = function () {
        frameHeight = parseInt(this.value);
        resizeCanvas();
        refreshCanvas();
    }


    canvas.onmousewheel = function (e) {
        scaleX *= (Math.atan(e.deltaY / 1000) + Math.PI / 2) / Math.PI * 2;
        scaleX = Math.max(scaleX, 1);
        scaleX = Math.min(scaleX, canvas.width / normalizationFactor / 2);
        adjustTranslateX()
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
            translateX += dx / scaleX;
            adjustTranslateX()
            last_x = pos_x;
            refreshCanvas();
        }
        canvas.style.cursor = "grab";
    }

    expandCollapseButton.onclick = () => {
        expandThread = !expandThread;
        expandCollapseButton.value = expandThread ? "Collapse" : "Expand"
        refreshCanvas();
    }

    canvas.onmouseup = function (evt) {
        drag = false;
        canvas.style.cursor = "default";
    }
}
