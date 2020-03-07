var starting   = 1;
var Speed      = 0;
var Current    = 0;
var strtOffset = 0;
var xAxis      = 0;
var interval;

// for flask server
const baseAddress = "http://localhost:8081"


var layout = {
  title: 'Speed vs Current Graph',
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
      strtOffset = performance.now();
      document.getElementById("Button").value= "Stop";
      document.getElementById("Button").className = "StopBtn";
      interval = setInterval(function()
      {
        //Take the difference between clicking start and plotting data
        //, and add it to the last time you clicked stop
        xAxis += (performance.now() - strtOffset )/1000;

        Plotly.extendTraces('chart', {y:[[Speed],[Current]], x:[[xAxis],[xAxis]]}, [0,1])} 
            ,1);
    }    
} 

function SaveButtonClicked()
{
  //Plotly.downloadImage('chart', {format: 'svg', width: 800, height: 600, filename: 'Speed&Current_graph'}); 
  var chart = document.getElementById("chart");

  axios.post(baseAddress + "/writejsonfile", chart.data)
  .then(function (response) {
    console.log(response);
  });
}

function LoadButtonClicked()
{
  var chart = document.getElementById("chart");

  //get the data
  axios.get(baseAddress + "/readjsonfile")
  .then(function (response) {
    chart.data = response.data
    var x_temp = chart.data[0].x[chart.data[0].x.length - 1 ];

    //plot one point in the end of the of the graph to make plotly draw all the data
    Plotly.extendTraces('chart', {y:[[Speed],[Current]], x:[[x_temp],[x_temp]]}, [0,1]);
  });
}

