document.getElementById("AireAcon").addEventListener('click', function () { eventoAire() });
document.getElementById("Persiana").addEventListener('click', function () { eventoPersiana() });
document.getElementById("enviar1").addEventListener('click', function () { setTemperatura() });
document.getElementById("enviar2").addEventListener('click', function () { setLuz() });
document.getElementById("enviarmensaje").addEventListener('click', function () { enviarMensaje(document.getElementById("mensaje")); });
document.getElementById("mensaje").addEventListener("keyup", function () { evaluarComentario(this, document.getElementById("contadormensaje")) });

document.getElementById("enviarnota").addEventListener('click', function () { enviarMensaje(document.getElementById("nota")); });
document.getElementById("nota").addEventListener("keyup", function () { evaluarComentario(this, document.getElementById("contadornota")) });

document.getElementById("flechaizq").addEventListener('click', function () { izquierda(); });
document.getElementById("flechader").addEventListener("click", function () { derecha(); });


document.addEventListener('DOMContentLoaded', function () { pintarMeses() });

let longitudmax = 1000, longitudrestante = 1000;
var ventana = true, aire = true;
var temperatura = 23, luz = 100;
const meses = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
var fecha = new Date();

var diaSeleccionado, mesSeleccionado, añoSeleccionado;
var serviceURL = document.URL;
var socket = io.connect(serviceURL);

contar(document.getElementById("enviarmensaje"), document.getElementById("contadormensaje"));
contar(document.getElementById("enviarnota"), document.getElementById("contadornota"));

setInterval(function () {
    scroll()
}, 100);

const monthNames = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];
const mesesNombres = ["Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"];

function derecha(){
    fecha.setMonth(fecha.getMonth()+1)

    pintarMeses();
}

function izquierda(){
    fecha.setMonth((fecha.getMonth()-1)%12)

    pintarMeses();
}

function pintarMeses() {
    var mes = document.getElementById("mes");
    document.getElementById("fechamensaje").innerHTML=mesesNombres[fecha.getMonth()]+"/"+fecha.getFullYear();
    mes.innerHTML = "";
    mes.style.display = "grid";
    mes.style.gridTemplateColumns = "repeat(7,1fr)";
    var nummes = fecha.getMonth();
    var primerdia = new Date(monthNames[nummes] + " 01, " + fecha.getFullYear() + " 00:00:01");

    mesSeleccionado = nummes;
    añoSeleccionado = fecha.getFullYear();

    var dia = (primerdia.getDay() + 6) % 7;
    var diasmes = meses[nummes] + dia;


    var contador = 1;
    for (var d = 0; d < diasmes; d++) {
        var diaelement = document.createElement("div");
        diaelement.style.display = "grid";
        diaelement.style.cursor = "pointer";
        diaelement.className = "dia";

        if (d < dia) {
            diaelement.innerHTML = " - ";
        }
        else {
            diaelement.innerHTML = contador;
            contador++;
            diaelement.addEventListener('click', function () { mostrarform(this.innerHTML) });

        }
        mes.appendChild(diaelement);
    }
}


function mostrarform(dia) {
    diaSeleccionado = parseInt(dia);
    document.getElementById("cajamensajes").style.display = "initial";
    fecha = diaSeleccionado + "/" + mesesNombres[mesSeleccionado] + "/" + añoSeleccionado;
    document.getElementById("fecha").innerHTML = fecha;
    var a = document.getElementById("fecha").innerHTML;
    socket.emit('getEvento', fecha);
}

function evaluarComentario(elemento, contador) {
    censurar(elemento);
    contar(elemento, contador);
}
function alertarTemp(alerta) {
    if (alerta) {
        document.getElementsByClassName("alerta").item(0).innerHTML = "¡CUIDADO!";
        document.getElementById("Temperatura").setAttribute("style", "filter: grayscale(100%) brightness(40%) sepia(100%) hue-rotate(-50deg) saturate(600%) contrast(0.8);");

    }
    else {
        document.getElementsByClassName("alerta").item(0).innerHTML = "";
        document.getElementById("Temperatura").setAttribute("style", "filter: ;");
    }
}

function alertarLuz(alerta) {
    if (alerta) {
        document.getElementsByClassName("alerta").item(1).innerHTML = "¡CUIDADO!";
        document.getElementById("Luminosidad").setAttribute("style", "filter: grayscale(100%) brightness(40%) sepia(100%) hue-rotate(-50deg) saturate(600%) contrast(0.8);");

    }
    else {
        document.getElementsByClassName("alerta").item(1).innerHTML = "";
        document.getElementById("Luminosidad").setAttribute("style", "filter: ;");
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

function convertirDia(dia) {
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

function convertirNumero(n) {
    var resultado;
    if (n < 10 && n >= 0) {
        resultado = "0" + n;
    }
    else {
        resultado = n;
    }
    return resultado;
}
function setTemperatura() {
    var x = document.getElementById("temp").value;
    temperatura = parseInt(x);
    //    document.getElementById("tempsensor").innerHTML = temperatura;

    var t = new Date();
    t = convertirDia(t.getDay()) + ", " + t.getDate() + "/" + t.getMonth() + "/" + t.getFullYear() + " | " + convertirNumero(t.getHours()) + ":" + convertirNumero(t.getMinutes()) + ":" + convertirNumero(t.getSeconds());
    socket.emit('nuevaTemp', { temperatura, t });
}

function setLuz() {
    var x = document.getElementById("luz").value;
    luz = parseInt(x);

    var t = new Date();
    t = convertirDia(t.getDay()) + ", " + t.getDate() + "/" + t.getMonth() + "/" + t.getFullYear() + " | " + convertirNumero(t.getHours()) + ":" + convertirNumero(t.getMinutes()) + ":" + convertirNumero(t.getSeconds());
    socket.emit('nuevaLuz', { luz, t });
}

function actualizarConexiones(usuarios) {
    var listContainer = document.getElementsByClassName('mensajes').item(1);
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


function actualizarHistoricoTemps(temperaturas) {
    var listContainer = document.getElementsByClassName('historicopar').item(0);
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


function actualizarHistoricoLuces(luces) {

    var listContainer = document.getElementsByClassName('historicopar').item(1);
    listContainer.innerHTML = '';
    var listElement = document.createElement('ul');
    listContainer.appendChild(listElement);
    var num = luces.length;
    for (var i = 0; i < num; i++) {
        var listItem = document.createElement('li');
        listItem.innerHTML = luces[i].t + " - " + luces[i].luz;
        listElement.appendChild(listItem);
    }
}

function actualizarChat(datos) {
    var listContainer = document.getElementsByClassName('mensajes').item(0);
    listContainer.innerHTML = '';
    var num = datos.length;
    for (var i = 0; i < num; i++) {
        var listItem = document.createElement('div');
        listItem.innerHTML = datos[i].msg + " - " + datos[i].client;
        listContainer.appendChild(listItem);
    }
}

function actualizarCalendario(datos) {
    var listContainer = document.getElementsByClassName('mensajes').item(3);
    var fecha = document.getElementById('fecha');
    listContainer.innerHTML = "";
    listContainer.appendChild(fecha);

    var num = datos.length;
    for (var i = 0; i < num; i++) {
        var listItem = document.createElement('div');
        listItem.innerHTML = datos[i].msg;
        listContainer.appendChild(listItem);
    }
}
//Contamos los caractéres
function contar(elemento, contador) {
    comentario = elemento.value;
    longitudrestante = longitudmax - comentario.length;
    contador.innerHTML = longitudrestante;

    if (longitudrestante > 200) {
        contador.style.backgroundColor = "#98ff8f";
        contador.style.color = "#085d00";
    }
    else if (longitudrestante > 50) {
        contador.style.backgroundColor = "#ffc67e";
        contador.style.color = "#d84e00";
    }
    else {
        contador.style.backgroundColor = "#ff6969";
        contador.style.color = "#b50000";
    }
    return false;
}

function censurar(elemento) {
    comentario = elemento.value;

    let censuradas = [];
    censuradas.push("xbox", "playsation", "mierda", "coño", "steam", "polla", "puta", "puto", "maricon", "cabron");
    for (let i = 0; i < censuradas.length; i++) {
        let indice = comentario.indexOf(censuradas[i]);
        if (indice != -1) {
            comentario = comentario.replace(censuradas[i], '****');
            elemento.value = comentario;
        }
    }
    return false;
}

function revisarMensaje(mensaje) {
    if (mensaje.length == 0 || mensaje.length > longitudmax) {
        return false;
    }
    else {
        return true;
    }
}


function enviarMensaje(elemento) {
    var mensaje = elemento.value;
    if (revisarMensaje(mensaje)) {
        if(elemento.id == "mensaje"){
            socket.emit('chat', mensaje);
        }
        else if(elemento.id == "nota"){
            var fecha = diaSeleccionado + "/" + mesesNombres[mesSeleccionado] + "/" + añoSeleccionado;
            socket.emit('calendario', {mensaje,fecha});
        }
    }

}

function scroll() {
    var element = document.getElementsByClassName("mensajes").item(0);
    element.scrollTop = element.scrollHeight;
}


function enviarEventoDia() {
    socket.emit
}

socket.on('ack', function (data) {
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

});

socket.on('envioLuz', function (data) {
    luz = data.luz;
    document.getElementById("luzsensor").innerHTML = luz + "%";

});


socket.on('envioHistoricoTemps', function (data) {
    actualizarHistoricoTemps(data);

});


socket.on('envioHistoricoLuces', function (data) {
    actualizarHistoricoLuces(data);

});

socket.on('persiana', function (data) {
    ventana = data;
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
    if (aire) {
        //      document.getElementById("tempsensor").innerHTML = temperatura;
        document.getElementById("AireAcon").setAttribute("style", "-webkit-filter:grayscale(0%)");
    }
    else {
        document.getElementById("AireAcon").setAttribute("style", "-webkit-filter:grayscale(100%)");

    }
});


socket.on('chat', function (data) {
    actualizarChat(data);
});

socket.on('calendario', function (data) {
    actualizarCalendario(data);
});


socket.on('alertatemp', function (data) {
    alertarTemp(data);
});

socket.on('alertaluz', function (data) {
    alertarLuz(data);
});
