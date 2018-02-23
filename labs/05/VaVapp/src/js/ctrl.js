angular.module('vavapp', [])
  .controller('vavappCtrl',function($scope) {
    $scope.processNumber = 1;
    $scope.errortext = "";
    $scope.process = [];
     $scope.title = "Round-Robin";
    $scope.showResults = false;
    $scope.rrResults = false;

    $scope.clear = function(title){
      $scope.title = title;
      $scope.showResults = false;
      $scope.rrResults = false;
      $scope.process = [];
      $scope.processNumber = 1;
      $scope.errortext = "";
      $scope.quantum = "";
      $scope.contextSwitch = "";
    }

    $scope.playSound = function(){
      var sounds = [new Audio('audio/Vavapp.mp3'), new Audio('audio/Have Fun.mp3')];
      sounds[Math.round(Math.random())].play();
    }

    $scope.addProcess = function () {

      if($scope.addNewProcess==""){
         $scope.errortext ="You must insert some value.";
        return;
      }
      if(isNaN($scope.addNewProcess)){
         $scope.errortext = "You must insert a numeric value.";
         return;
      }

      var newProcess = {id:"P"+    $scope.processNumber, num:$scope.addNewProcess};
      $scope.process.push(newProcess);
      $scope.addNewProcess = "";
      $scope.errortext = "";
      $scope.processNumber++;
  }

  $scope.removeProcess = function (x) {
        $scope.processNumber--;
       $scope.process.splice(x, 1);
       $scope.errortext = "";
   }

   var drawGraph = function(id, width, color, init,end){
     var myEl = angular.element( document.querySelector( '#graph' ) );
     width = width * 30;
     myEl.append('<div class="block-cont"><div style="background:'+color+'; width:'+width+'px" class="graph-block"><p>'+id+'</p><div/><p class="tooltiptext left">'+init+'</p><p class="tooltiptext right">'+end+'</p><div>');
   }

   function eraseGraph() {
     angular.element( document.querySelector( '#graph' ) ).empty();

   }

   function random_color() {
     var color = 'rgb(' + (Math.floor(Math.random() * 256)) + ',' + (Math.floor(Math.random() * 256)) + ',' + (Math.floor(Math.random() * 256)) + ')';
    return color;
}

   $scope.roundRobin = function (){
      //$scope.showResults = false;
      eraseGraph();

     if($scope.process.length==0){
       $scope.errortext = "You must create process.";
       return;
     }

     if(isNaN($scope.quantum)){
       $scope.errortext = "You must insert a quantum.";
       return;
     }

     if(isNaN($scope.contextSwitch)){
       $scope.errortext = "You must insert a context switch value.";
       return;
     }

    var execution_time = 0;
    var context_switches = 0;
    $scope.errortext = "";

    var data = new google.visualization.DataTable();
    data.addColumn('string', 'Task ID');
    data.addColumn('string', 'Task Name');
    data.addColumn('string', 'Resource');
    data.addColumn('date', 'Start Date');
    data.addColumn('date', 'End Date');
    data.addColumn('number', 'Duration');
    data.addColumn('number', 'Percent Complete');
    data.addColumn('string', 'Dependencies');
    var options = {
      height:300,
      colors: ['#a4c662','#006e5e', '#42915f', '#093'],
      backgroundColor: {
        fill: "rgba(0,0,0,0)"
      },
      gantt: {
        trackHeight: 30,
        fill: 'rgba(0,0,0,0)',
        innerGridDarkTrack: {fill: 'rgba(0,0,0,0)'},
        innerGridHorizLine: {
          stroke: 'rgba(0,0,0,0)',
          fill: ' rgba(0,0,0,0)'
        },
        innerGridTrack:{
          fill: "#000"
        },
        shadowColor: 'rgba(0,0,0,0)',
        criticalPathStyle:{ stroke: '#a4c662'}
      },
      labelStyle: {
        fontSize: 14,
        color: 'white',
        background: "rgba(0,0,0,0)"
      }
    };


    var processes = [];
    var j;
    for(j =0; j<$scope.process.length; j++){
      processes[j]=$scope.process[j];
      processes[j].color = random_color();
    }
    var prevProcess = null;
    var i=0;
    while(i<processes.length){
      if(i>0){
        context_switches++;
        execution_time+=$scope.contextSwitch;
      }
      if (processes[i].num<=$scope.quantum){
        drawGraph(processes[i].id, eval(processes[i].num), processes[i].color,execution_time,execution_time+eval(processes[i].num));
        execution_time+=eval(processes[i].num);
      //  data.addRows([[processes[i].id, processes[i].id, processes[i].id, null, null,eval(processes[i].num)*100, 100, prevProcess]]);
      }
      else{
        drawGraph(processes[i].id, $scope.quantum, processes[i].color, execution_time,execution_time+$scope.quantum);
        execution_time+= ($scope.quantum);
    //      data.addRows([[processes[i].id, processes[i].id, processes[i].id, null, null, $scope.quantum*100, 100, prevProcess]]);
          processes.push({id:processes[i].id, num:(eval(processes[i].num)-$scope.quantum), color:processes[i].color});

      }
      prevProcess=processes[i].id;
      i++;
      }
  //    var chart = new google.visualization.Gantt(document.getElementById('chart_div'));
  //    chart.draw(data, options);
      $scope.turnaround = execution_time;
      $scope.avgTurnaroudTime = (execution_time / $scope.process.length).toFixed(2);
      $scope.contextSwitchNum = context_switches;
      $scope.rrResults=true;
     }



   $scope.fcfsAlg = function(){
     var partialturn = 0;
     var processes = $scope.process;
     var prevProcess = null;
     $scope.totalWaitTime = 0;
     $scope.rrResults = false;
     $scope.waitTime = 0;
     $scope.avgWaitTime = 0;
     $scope.turnaround = 0;
     $scope.avgTurnaroudTime = 0;
     $scope.throughput = 0;

     var data = new google.visualization.DataTable();
     data.addColumn('string', 'Task ID');
     data.addColumn('string', 'Task Name');
     data.addColumn('string', 'Resource');
     data.addColumn('date', 'Start Date');
     data.addColumn('date', 'End Date');
     data.addColumn('number', 'Duration');
     data.addColumn('number', 'Percent Complete');
     data.addColumn('string', 'Dependencies');
     var options = {
       height:400,
       colors: ['#a4c662','#006e5e', '#42915f', '#093'],
       backgroundColor: {
         fill: "rgba(0,0,0,0)"
       },
       gantt: {
         trackHeight: 30,
         fill: 'rgba(0,0,0,0)',
         innerGridDarkTrack: {fill: 'rgba(0,0,0,0)'},
         innerGridHorizLine: {
           stroke: 'rgba(0,0,0,0)',
           fill: ' rgba(0,0,0,0)'
         },
         innerGridTrack:{
           fill: "#000"
         },
         shadowColor: 'rgba(0,0,0,0)',
         criticalPathStyle:{ stroke: '#a4c662'}
       },
       labelStyle: {
         fontSize: 14,
         color: 'white',
         background: "rgba(0,0,0,0)"
       }
     };

     if($scope.process.length<1){
       $scope.errortext = "You must create a process.";
        $scope.showResults = false;
       return;
     }
     var prevProcess = null;
     for (var i = 0; i < $scope.process.length; i++) {
         $scope.totalWaitTime += partialturn;
         $scope.turnaround += (partialturn+eval($scope.process[i].num));
        data.addRows([[$scope.process[i].id, $scope.process[i].id, $scope.process[i].id, null, null, eval($scope.process[i].num)*100, 100, prevProcess]]);
         partialturn += eval($scope.process[i].num);
         prevProcess = $scope.process[i].id;
     }
     var chart = new google.visualization.Gantt(document.getElementById('fcfs_chart'));
     chart.draw(data, options);
     $scope.avgWaitTime = Math.floor($scope.totalWaitTime/$scope.process.length);
     $scope.avgTurnaroudTime = Math.floor($scope.turnaround/$scope.process.length);
     $scope.throughput = ($scope.process.length/ partialturn).toFixed(2);
     $scope.errortext = "";
     $scope.showResults = true;

   }
});

google.charts.load('current', {'packages':['gantt']});
google.charts.setOnLoadCallback(drawChart);
function drawChart() {}
