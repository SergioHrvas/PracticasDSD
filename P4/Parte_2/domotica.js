document.getElementById("AireAcon").addEventListener('click', function () { eventoAire() });
document.getElementById("Persiana").addEventListener('click', function () { eventoPersiana() });
document.getElementById("enviar1").addEventListener('click', function () { setTemperatura() });
document.getElementById("enviar2").addEventListener('click', function () { setLuz() });

var ventana = true, aire = true;
var temperatura = 23, luz = 100;

var serviceURL = document.URL;
var socket = io.connect(serviceURL);

function alertarTemp() {
    if (temperatura >= 40 || temperatura <= 0) {
        document.getElementsByClassName("alerta").item(0).innerHTML = "¡CUIDADO!";
        document.getElementById("Temperatura").setAttribute("style", "filter: grayscale(100%) brightness(40%) sepia(100%) hue-rotate(-50deg) saturate(600%) contrast(0.8);");

    }
    else {
        document.getElementsByClassName("alerta").item(0).innerHTML = "";
        document.getElementById("Temperatura").setAttribute("style", "filter: ;");
    }
}

function alertarLuz() {
    if (luz >= 100) {
        document.getElementsByClassName("alerta").item(1).innerHTML = "¡CUIDADO!";
        document.getElementById("Luminosidad").setAttribute("style", "filter: grayscale(100%) brightness(40%) sepia(100%) hue-rotate(-50deg) saturate(600%) contrast(0.8);");

    }
}

function eventoAire() {
    if (aire) {
        socket.emit('aire', { cambio: false });
        //      document.getElementById("tempsensor").innerHTML = temperatura;
        document.getElementById("AireAcon").setAttribute("style", "-webkit-filter:grayscale(100%)");
    }
    else {
        socket.emit('aire', { cambio: true });
        document.getElementById("AireAcon").setAttribute("style", "-webkit-filter:grayscale(0%)");

    }

}

function eventoPersiana() {
    if (!ventana) {
        socket.emit('persiana', { cambio: true });
        luz = 100;
        document.getElementById("luzsensor").innerHTML = luz + "%";
        document.getElementById("Persiana").setAttribute("style", "-webkit-filter:grayscale(0%)");

    }
    else {
        socket.emit('persiana', { cambio: false });
        luz = 0;
        document.getElementById("luzsensor").innerHTML = luz + "%";
        document.getElementById("Persiana").setAttribute("style", "-webkit-filter:grayscale(100%)");

    }
}

function convertirDia(dia){
    var semana = new Array(7);
    semana[0] = "Lunes";
    semana[1] = "Martes";
    semana[2] = "Miércoles";
    semana[3] = "Jueves";
    semana[4] = "Viernes";
    semana[5] = "Sábado";
    semana[6] = "Domingo";
    return semana[dia];
}

function convertirNumero(n){
    var resultado;
    if(n < 10 && n>=0){
        resultado = "0"+n;
    }
    else{
        resultado = n;
    }
    return resultado;
}
function setTemperatura() {
    var x = document.getElementById("temp").value;
    temperatura = parseInt(x);
    document.getElementById("tempsensor").innerHTML = temperatura;
    alertarTemp();
    
    var t = new Date();
    t = convertirDia(t.getDay())+ ", " + t.getDate() + " " + t.getMonth()  + " " + t.getFullYear()  + " | " + convertirNumero(t.getHours())  + ":" + convertirNumero(t.getMinutes())  + ":" + convertirNumero(t.getSeconds());
    socket.emit('nuevaTemp', { temperatura, t });
}

function setLuz() {
    var x = document.getElementById("luz").value;
    luz = parseInt(x);
    document.getElementById("luzsensor").innerHTML = x;
    alertarLuz();
}

function actualizarConexiones(usuarios) {
    var listContainer = document.getElementsByClassName('mensajes').item(2);
    listContainer.innerHTML = '';
    var listElement = document.createElement('ol');
    listContainer.appendChild(listElement);
    var num = usuarios.length;
    for (var i = 0; i < num; i++) {
        var listItem = document.createElement('li');
        listItem.innerHTML = usuarios[i].address + ":" + usuarios[i].port;
        listElement.appendChild(listItem);
    }
}


function actualizarHistorico(temperaturas) {
    var listContainer = document.getElementsByClassName('mensajes').item(0);
    listContainer.innerHTML = '';
    var listElement = document.createElement('ul');
    listContainer.appendChild(listElement);
    var num = temperaturas.length;
    for (var i = 0; i < num; i++) {
        var listItem = document.createElement('li');
        listItem.innerHTML = temperaturas[i].t + " - " + temperaturas[i].temperatura;
        listElement.appendChild(listItem);
    }
}


socket.on('ack', function (data) {
    console.log(data);
    socket.emit('ack', "Conexion establecida correctamente!")

    //socket.emit('obtener', { host: data.address });
});
socket.on('all-connections', function (data) {
    actualizarConexiones(data);
});

socket.on('disconnect', function () {
    //actualizarLista({});
});

socket.on('envioTemp', function (data) {
    temperatura = data.temperatura;
    document.getElementById("tempsensor").innerHTML = temperatura;
    alertarTemp();

});

socket.on('envioHistorico', function(data){
    console.log(data[0].temperatura);
    actualizarHistorico(data);

});

socket.on('persiana', function (data) {
    ventana = data;
    console.log(ventana);

    if (!ventana) {
        luz = 0;
        document.getElementById("Persiana").setAttribute("style", "-webkit-filter:grayscale(100%)");

    }
    else {
        luz = 100;
        document.getElementById("Persiana").setAttribute("style", "-webkit-filter:grayscale(0%)");

    }
    document.getElementById("luzsensor").innerHTML = luz + "%";

});

socket.on('aire', function (data) {
    aire = data;
    console.log(aire);
    if (aire) {
        //      document.getElementById("tempsensor").innerHTML = temperatura;
        document.getElementById("AireAcon").setAttribute("style", "-webkit-filter:grayscale(0%)");
    }
    else {
        document.getElementById("AireAcon").setAttribute("style", "-webkit-filter:grayscale(100%)");

    }
});


