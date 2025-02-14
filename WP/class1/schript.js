document.write("<h1>Hello World</h1>")
document.body.style.backgroundColor = 'lightblue';
document.write("<p style='text-decoration:underline;'>This is a paragraph</p>")
document.createElement("button");
document.write("<button id='butt'>Click me</button>");
document.createElement("h1");
document.write("<h1 id='11' style='color:red;'></h1>");
function alertlol() {
    alert("lol")
}
window.onload = function() {
    const x = document.getElementById("11");
    if (x) {
        x.style.color = "red";
        x.style.fontSize = "50px";
        x.textContent = "This is a heading";
        const xx= document.getElementById("butt");
        xx.onclick = function() {
            if (x.style.color === "red") {
                x.style.color = "blue";
                x.style.fontSize = "20px";
                x.textContent = "This is not a heading";
            }
            else if (x.style.color === "blue"){
                x.style.color = "green";
                x.style.fontSize = "30px";
                x.textContent = "This is a heading";
            }
            else if (x.style.color === "green"){
                let y =  prompt("Enter a text");
                if(y===""||y===null||!isNaN(y)){
                    alert("Invalid only strings allowed");
                    x.style.color = "green";
                    x.style.fontSize = "30px";
                    x.textContent = "This is a heading";
                }
                else{
                    x.style.color = "yellow";
                    x.style.fontSize = "40px";
                    x.textContent = y;
                }
                
            }
            else if (x.style.color === "yellow"){
                x.style.color = "red";
                x.style.fontSize = "50px";
                x.textContent = "This is a heading";
            }
        }
    }
}