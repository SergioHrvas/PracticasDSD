document.getElementById("AireAcon").addEventListener('click', function () { eventoAire() });
document.getElementById("Persiana").addEventListener('click', function () { eventoPersiana() });
document.getElementById("enviar1").addEventListener('click', function () { setTemperatura() });
document.getElementById("enviar2").addEventListener('click', function () { setLuz() });



var ventana = false, aire = false;
var temperatura = 40, luz = 0;
setInterval(function(){
            if (temperatura > 5 && !aire) {
                temperatura -= 1;
                document.getElementById("tempsensor").innerHTML = temperatura;
            }
            if (luz <= 100 && !ventana) {

                luz += 0.5;
                document.getElementById("luzsensor").innerHTML = luz;

            }
    }
, 10000);


function eventoAire(){
    if(aire){
        aire = false;
        document.getElementById("tempsensor").innerHTML = temperatura;
        document.getElementById("AireAcon").setAttribute("style", "-webkit-filter:grayscale(0%)");
    }
    else{
        aire = true;
        document.getElementById("AireAcon").setAttribute("style", "-webkit-filter:grayscale(100%)");

    }
}

function eventoPersiana(){
    if(!ventana){
        ventana = true;
        luz = 0;
        document.getElementById("luzsensor").innerHTML = luz;
        document.getElementById("Persiana").setAttribute("style", "-webkit-filter:grayscale(100%)");

    }
    else{
        ventana = false;
        document.getElementById("Persiana").setAttribute("style", "-webkit-filter:grayscale(0%)");

    }
}

function setTemperatura(){
    var x = document.getElementById("temp").value;
    document.getElementById("tempsensor").innerHTML=x;
}

function setLuz(){
    var x = document.getElementById("luz").value;
    document.getElementById("luzsensor").innerHTML=x;
}
var serviceURL = document.URL;
var socket = io.connect(serviceURL);


socket.on('my-address', function (data) {
    var d = new Date();
    socket.emit('poner', { host: data.host, port: data.port, time: d });
    socket.emit('obtener', { host: data.address });
});
socket.on('obtener', function (data) {
    // actualizarLista(data);
});
socket.on('disconnect', function () {
    //actualizarLista({});
});

