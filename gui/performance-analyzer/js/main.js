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
    let minumumLineWidth = 4;

    const input = document.querySelector("input[type=file]");
    const refresh = document.getElementById("refresh");
    const select = document.getElementById("select-file");
    const sliderVZoom = document.getElementById("v-zoom");
    const divCanvas = document.getElementById("div-canvas");
    const legendTable = document.getElementById("table-legend");
    const expandCollapseButton = document.getElementById("expand-collapse-button");

    let addLabelToLegend = () => {
        let threadNames = Object.keys(measurements);
        let numOfThreads = threadNames.length;

        for (let threadNum = 0; threadNum < numOfThreads; threadNum++) {
            let threadID = threadNames[threadNum];
            let functions = Object.keys(measurements[threadID]);
            for (let functionNum = 0; functionNum < functions.length; functionNum++) {
                let functionName = functions[functionNum];
                let data = measurements[threadID][functionName].data;
                let color = measurements[threadID][functionName].color;
                let numOfCalls = measurements[threadID][functionName].numOfCalls;
                let totalExecutionTime = measurements[threadID][functionName].totalExecutionTime;
                let averageExecutionTime = Math.round(totalExecutionTime / numOfCalls);

                let labelRow = legendTable.insertRow();
                let threadIDCell = labelRow.insertCell();
                let labelCell = labelRow.insertCell();
                let numOfCallsCell = labelRow.insertCell();
                let averageExecutionTimeCell = labelRow.insertCell();
                let totalExecutionTimeCell = labelRow.insertCell();
                
                labelRow.style.backgroundColor = color;
                threadIDCell.innerHTML = threadID;
                labelCell.innerHTML = functionName;
                numOfCallsCell.innerHTML = numOfCalls;
                averageExecutionTimeCell.innerHTML = averageExecutionTime  + " ns";
                totalExecutionTimeCell.innerHTML = totalExecutionTime + " ns";
            }
        }
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

    expandThread = false;
    let draw = () => {
        let threadNames = Object.keys(measurements);
        let numOfThreads = threadNames.length;
        if (expandThread) {
            canvasHeight = (stepHeight * maxNumOfFunctions) + baselineOffset * (numOfThreads - 1) * stepHeight;
        } else {
            canvasHeight = stepHeight * numOfThreads + baselineOffset * (numOfThreads - 1) * stepHeight;
        }
        resizeCanvas();
        
        let baseline = 0;
        for (let threadNum = 0; threadNum < numOfThreads; threadNum++) {
            let threadID = threadNames[threadNum];
            let functions = Object.keys(measurements[threadID]);
            for (let functionNum = 0; functionNum < functions.length; functionNum++) {
                baseline ++;
                let functionName = functions[functionNum];
                let data = measurements[threadID][functionName].data;
                let color = measurements[threadID][functionName].color;
                let positionY = baseline * stepHeight;
                let height = stepHeight;

                for (let dataNum = 0; dataNum < data.length; dataNum++) {
                    let positionX = offsetLeft + (data[dataNum][0] - firstStep) * scaleX * stepLength;
                    let width = data[dataNum][1] * scaleX * stepLength;
                    if (positionX > canvas.width || (positionX + width) < 0) continue;
                    ctx.fillStyle = color;
                    ctx.fillRect(positionX, positionY, width, -height);
                    if (width < minumumLineWidth) continue;
                    ctx.fillStyle = "black";
                    ctx.save();
                    ctx.translate(positionX + width / 2, baseline * stepHeight)
                    ctx.rotate(-Math.PI/2);
                    ctx.fillText(functionName, 0, 0);
                    ctx.restore();
                }
                if (!expandThread) baseline --;
            }
            if (!expandThread) baseline ++;
            baseline += baselineOffset / 2;
            ctx.fillStyle = "black";
            ctx.fillText(threadID, 10, baseline * stepHeight - 10);
            ctx.moveTo(0, baseline * stepHeight);
            ctx.lineTo(canvas.width, baseline * stepHeight)
            ctx.stroke();
            baseline += baselineOffset / 2;
        }
    }

    let parseText = (text) => {
        measurements = {};
        legendTable.innerHTML = "<tr>" +
            "<td>Thread ID</td>" +
            "<td>Function name</td>" +
            "<td>Number of calls</td>" +
            "<td>Average execution time</td>" +
            "<td>Total execution time</td>" +
            "</tr>"
        let lines = text.split("\n");
        let threadID, functionName, startTimepoint, elapsedTime;
        maxNumOfFunctions = 0;
        for (let i = 0; i < lines.length; i++) {
            if (lines[i].split(":").length != 4) continue; // rough check if the line format is correct

            [threadID, functionName, startTimepoint, elapsedTime] = lines[i].split(":");

            if (measurements[threadID] == undefined) { // first time you see this thread?
                measurements[threadID] = {};
            }
            if (measurements[threadID][functionName] == undefined) { // first time you see this function?
                maxNumOfFunctions ++;
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
        let lastDuration = parseInt(elapsedTime);
        let totalDuration = lastStart + lastDuration;
        scaleX = (window.innerWidth - offsetLeft - offsetRight) / totalDuration;
        maxStep = lastStart;
        firstStep = Math.min(maxStep, firstStep); // adjust if current first step exceeds the max step admissible
        addLabelToLegend();
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
        stepLength = Math.max(stepLength * magnification, 0.01);
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

    expandCollapseButton.onclick = () => {
        expandThread = !expandThread;
        refreshCanvas();
    }

    canvas.onmouseup = function (evt) {
        drag = false;
        canvas.style.cursor = "default";
    }
}
