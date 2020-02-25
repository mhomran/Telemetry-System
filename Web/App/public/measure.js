var starting = 1;
var Speed = 0;
var Current = 0;
var offset = 0;
var interval;

var layout = {
  grid: {rows: 2, columns: 1, pattern: 'independent'},
};

document.addEventListener("DOMContentLoaded", event => 
{
var dbRef = firebase.database().ref().child('Measure/Speed');
dbRef.on('value', snap =>  {Speed = snap.val()});  

var dbRef2 = firebase.database().ref().child('Measure/Current');
dbRef2.on('value', snap => {Current = snap.val()});
}
);

document.addEventListener("DOMContentLoaded", event =>
{ 
Plotly.newPlot('chart',[{y:[Speed] , x:[0],name: 'Speed',type:'line'}, 
{y:[Current] , x:[0],xaxis: 'x2',yaxis: 'y2', name: 'Current',type:'line'}], layout);
});

function ButtonClicked()
{         
  if(document.getElementById("Button").value == "Stop") 
    {
      document.getElementById("Button").value= "Start";
      document.getElementById("Button").className = "StartBtn";
      clearInterval(interval); 
    }  
  else if(document.getElementById("Button").value= "Start") 
    {
      document.getElementById("Button").value= "Stop";
      document.getElementById("Button").className = "StopBtn";

      offset = performance.now();
      interval = setInterval(function()
      {
        var xAxis = (performance.now() - offset)/1000;
        Plotly.extendTraces('chart', {y:[[Speed],[Current]], x:[[xAxis],[xAxis]]}, [0,1])} 
            ,1);
    }    
} 

function SaveButtonClicked()
{
  Plotly.downloadImage('chart', {format: 'svg', width: 800, height: 600, filename: 'Speed&Current_graph'}); 
}