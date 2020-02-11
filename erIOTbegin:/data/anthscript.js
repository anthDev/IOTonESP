
        // fonction permettant de demander le uptime 
        function getUptime() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    // l'élement uptime de la page prend la valeur de la réponse
                    document.getElementById("uptime").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "getUptime", true);
            xhttp.send();
        }

        // demande du uptime toutes les 2 secondes
        setInterval(function() {

            getUptime();
            getDataTemp();
            getDataHum();
            getDataLum();

        }, 2000); // 2000 ms
        // fonction permettant de changer l'état de la LED
        // on envoie un requête GET setLED avec ledState=0 ou 1 en argument  
        function sendData(led) {
            var xhttp = new XMLHttpRequest(); //envois requete
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("ledState").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "setLED?ledState=" + led, true);
            xhttp.send();
        }

        function getDataTemp() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("dataTemp").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "getDataTemp", true);
            xhttp.send();

        }

        function getDataHum() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("dataHum").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "getDataHum", true);
            xhttp.send();

        }

        function getDataLum() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("dataLum").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "getDataLum", true);
            xhttp.send();

        }



type="text/javascript" src = "./Chart.min.js">
type="text/javascript" src="./jquery-1.11.1.min.js">
type="text/javascript">

var dataPoints = [] ; // le tableau des points du graphique format JSON :  [{x:1,y:0.4},{x:2,y:0.9},{x:4,y:1.2},....]

// fonction permettant de parser un fichier csv : une donnée de la forme x,y par ligne
function getDataPointsFromCSV(csv) {
            var  csvLines = points = [];
            csvLines = csv.split(/[\r?\n|\r|\n]+/);          // on récupère un tableau de lignes
                
            for (var i = 0; i < csvLines.length; i++)   // pour chaque ligne i
                if (csvLines[i].length > 0) {           //  non vide
                    points = csvLines[i].split(",");  //   points est un couple de données texte (string)
                    dataPoints.push({                 //   on met les points dans le tableau dataPoints en format JSON {x:v1,y:v2} 
                        x: parseFloat(points[0]),     //  axe du temps 0, lumière 1, temp 2, humidité 3
                        y: parseFloat(points[2])        //  axe lumière
                    });
                }
            console.log("loading :");
            console.log(dataPoints);
            return dataPoints ;  // on retourne le tableau de données 
}


// fonction qui génére  sur le contexte ctx un graphique avec les données dataPoints 
function drawGraph(ctx,dataPoints) {
           
           // définie le graphique qui va apparaître sur le contexte ctx
           // voir les différentes possibilités à : https://www.chartjs.org
           var myChart = new Chart(ctx, {
                        type: 'line',
                        data: {
                                datasets: [{
                                                label: 'Les capteurs',  // légende
                                                fill: false,    //essayez avec True !
                                                backgroundColor: 'rgba( 243, 156, 18 , 1)', //Dot marker color
                                                borderColor: 'rgba( 243, 156, 18 , 1)', //Graph Line Color
                                                data: dataPoints  // les données du graphique
                                           }]
                              },
                        options: {
                                responsive: true,
                                maintainAspectRatio: false,
                                scales: {
                                        xAxes: [{
                                                type: 'linear',
                                                position: 'bottom'
                                                }],
                                        yAxes: [{
                                                ticks: {
                                                beginAtZero:true //essayez avec False !
                                                        }
                                                }]
                                         }
                                 }
                       }); // fin new Chart
}


    // fonction exécutée au chargement de la page
    window.onload = function() {
        
    console.log("load");  // affiche dans la console du navigateur pour le débug
        // requette jquery : $.get() voir https://api.jquery.com/jquery.get/
        // demande le fichier local "ExampleData.csv" puis exécute la "function" avec les données reçues (data)
        // data contient le contenu du fichier demandé.
        $.get("./sensors.csv", function(data) {

           var filenameHtml = document.getElementById('filename'); // récupère l'élément html nomé filename
           filenameHtml.innerHTML += "sensors.csv";  // y ajoute le nom du fichier
           console.log("generating chart");
           // récupère le "contexte graphique" de l'élément html nomé Chart
           var ctx = document.getElementById("Chart").getContext('2d');
           // met en forme JSON les données pour le graphique
           dataPoints=getDataPointsFromCSV(data);
           // génère le graphique
           drawGraph(ctx,dataPoints);

               }// fin de function (associée à get)
                  );  // fin le la requette $.get

  } // fin de la function onload 