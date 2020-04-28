window.onload = main;
window.onresize = resizeCanvas
let canvas = document.getElementById("canvas");
const marginTop = 100; // canvas distance from window top
function main() {
  console.log("Welcome back!")
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight - marginTop;
  let ctx = canvas.getContext("2d");
  
  
  const input = document.querySelector("input[type=file]");
  const refresh = document.getElementById("refresh");
  const select = document.querySelector("select");
  const reader = new FileReader;
  
  let files = [];
  let data = [];
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
    files.length = data.length = 0;
    for (const file of input.files) {
      const {
        name
      } = file;
      const option = new Option(name, files.length);
      files.push(file);
      select.appendChild(option);
      let result = await read(file, reader);
      data.push(result);
    }
  }
  
  refresh.onclick = async () => {
    let text = data[0];
    let lines = text.split('\n');
    let result = await read(files[0], reader);
    console.log(result)
  }
}
function resizeCanvas() {
  canvas.width = window.innerWidth;
  canvas.height = window.innerHeight - marginTop;
}