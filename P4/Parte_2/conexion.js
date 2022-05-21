var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");
const { emit } = require("process");
var QRCode = require('qrcode')



var MongoClient = require('mongodb').MongoClient;
var MongoServer = require('mongodb').Server;
var mimeTypes = { "html": "text/html", "jpeg": "image/jpeg", "jpg": "image/jpeg", "png": "image/png", "js": "text/javascript", "css": "text/css", "swf": "application/x-shockwave-flash" };




var httpServer = http.createServer(
	function (request, response) {
		var uri = url.parse(request.url).pathname;
		if (uri == "/") uri = "/domotica.html";
		var fname = path.join(process.cwd(), uri);
		fs.exists(fname, function (exists) {
			if (exists) {
				fs.readFile(fname, function (err, data) {
					if (!err) {
						var extension = path.extname(fname).split(".")[1];
						var mimeType = mimeTypes[extension];
						response.writeHead(200, mimeType);
						response.write(data);
						response.end();
					}
					else {
						response.writeHead(200, { "Content-Type": "text/plain" });
						response.write('Error de lectura en el fichero: ' + uri);
						response.end();
					}
				});
			}
			else {
				console.log("Peticion invalida: " + uri);
				response.writeHead(200, { "Content-Type": "text/plain" });
				response.write('404 Not Found\n');
				response.end();
			}
		});
	}
);




var ventana = true, aire = true;
var temperatura = 23, luz = 100;
var temperatura_fija = 23;
const MAXIMA_TEMP = 50, MAXIMA_LUZ = 100, MINIMA_TEMP = -10;

var allClients = new Array();

MongoClient.connect("mongodb://localhost:27017/", { useUnifiedTopology: true }, function (err, db) {
	httpServer.listen(8080);
	var io = socketio(httpServer);
	let dbo = db.db("pruebaBaseDatos");

	let collectiontemps = dbo.collection("temps");
	let collectionluces = dbo.collection("luces");
	let collectionchat = dbo.collection("chat");
	let collectioncalendario = dbo.collection("calendario");

	//Verifica los fallos de la temperatura y de la luz. En el caso de que se produzcan, enviará un mensaje para cerrar la persiana.
	function verificarFallos() {
		if ((temperatura < MINIMA_TEMP || temperatura >= MAXIMA_TEMP) && luz > MAXIMA_LUZ) {
			ventana = false;
			io.sockets.emit('persiana', ventana);
			io.sockets.emit('alertaluz', false);
		}
	}

	//Alertas de temperatura y luz en el caso de que se excedan los límites
	function envioAlertaTemp() {
		var alerta = false;
		if (temperatura >= MAXIMA_TEMP-10 || temperatura <= MINIMA_TEMP+10) {
			alerta = true;
		}
		io.sockets.emit('alertatemp', alerta);
	}

	function envioAlertaLuz() {
		var alerta = false;
		if (luz >= MAXIMA_LUZ) {
			alerta = true;
		}
		io.sockets.emit('alertaluz', alerta);
	}


	function buscarTemps(){
		setTimeout(function () {
			collectiontemps.find().toArray(function (err, results) {
				if (err) {
					console.log("ERROR");
				}
				else {
					io.sockets.emit('envioHistoricoTemps', results);
				}

			});
		}, 500);
	}

	function buscarLuces(){
		setTimeout(function () {
			collectionluces.find().toArray(function (err, results) {
				if (err) {
					console.log("ERROR");
				}
				else {
					io.sockets.emit('envioHistoricoLuces', results);
				}

			});
		}, 500);
	}
	//Función que se repite cada 5 segundos. Irá actualizando la temperatura de forma automática como si fuese un simulador.
	setInterval(function () {
		if (aire) {
			if (temperatura < temperatura_fija) {
				temperatura += 1;
			}
			else if (temperatura > temperatura_fija) {
				temperatura -= 1;
			}
		}
		else if (!aire) {
			if(temperatura < MAXIMA_TEMP)
				temperatura += 1;
			else if(temperatura >= MAXIMA_TEMP){
				temperatura -= 1;
			}
		}
		var d = new Date();
		var t = d.getTime();
		io.sockets.emit('envioTemp', { temperatura, t });
		envioAlertaTemp();
	}, 5000);

	//Cuando se reciba una conexión nueva de un cliente
	io.sockets.on('connection',
		function (client) {

			//El servidor responde con un ack confirmando la recepción de la conexión
			client.emit('ack', "Conexión recibida. Te respondo.");

			//Cuando el servidor reciba un ack del cliente, significará que el cliente recibió el ack y ha informado de su conexión satisfactoria.
			//Por tanto, añadirá el nuevo cliente al vector de clientes disponibles y enviará dicho array a todos los clientes (para mostrar las conexiones posteriormente).
			client.on('ack', function (data) {
				console.log(data);
				allClients.push({ address: client.request.connection.remoteAddress, port: client.request.connection.remotePort });
				io.sockets.emit('all-connections', allClients);
			});

			//Cuando el servidor reciba un mensaje 'aire' significará que ha cambiado el estado del aire acondicionado en un cliente
			//y deberá ser cambiado en el propio servidor y en todos los demás clientes, por lo que enviará un mensaje 'aire' a todos ellos.
			client.on('aire', function (data) {
				aire = data.cambio;
				io.sockets.emit('aire', aire);
			});

			//Igual que el anterior pero con la persiana
			client.on('persiana', function (data) {
				ventana = data.cambio;
				io.sockets.emit('persiana', ventana);
			});

			//Cuando el servidor reciba un mensaje 'disconnect', busca cual de todos ha sido y 
			//lo saca de la lista. Entonces, envía de nuevo el vector a todos los clientes sin el que se ha desconectado.
			client.on('disconnect', function () {
				console.log("El cliente " + client.request.connection.remoteAddress + " se va a desconectar");
				var index = -1;
				for (var i = 0; i < allClients.length; i++) {
					if (allClients[i].address == client.request.connection.remoteAddress
						&& allClients[i].port == client.request.connection.remotePort) {
						index = i;
					}
				}

				if (index != -1) {
					allClients.splice(index, 1);
					io.sockets.emit('all-connections', allClients);
				} else {
					console.log("EL USUARIO NO SE HA ENCONTRADO!")
				}
				console.log('El usuario ' + client.request.connection.remoteAddress + ' se ha desconectado');
			});

			client.on('inicioHistoricos', function(){
				buscarTemps();
				buscarLuces();
			});
			//Cuando el servidor reciba un mensaje de 'envioTemp', significará que el cliente ha modificado el valor por teclado de la temperatura,
			//y por tanto actualizará su sensor, lo meterá en la base de datos y mandará el mensaje con el nuevo aire a todos los clientes para que modifiquen dicho valor, además del histórico
			//de temperaturas para que actualice dicho valor
			//Por último, enviará una alerta si la temperatura recibida supera cierto umbral.
			client.on('envioTemp', function (data) {
				temperatura = data.temperatura;
				if (collectiontemps != null) {
					collectiontemps.insertOne(data, { safe: true }, function (err, result) { });
					buscarTemps();

				}
				io.sockets.emit('envioTemp', data);

				envioAlertaTemp();
				verificarFallos();
			});

			//Igual pero con la luz
			client.on('envioLuz', function (data) {
				luz = data.luz;
				if (collectionluces != null) {
					collectionluces.insertOne(data, { safe: true }, function (err, result) { });
					buscarLuces();
				}
				io.sockets.emit('envioLuz', data);
				envioAlertaLuz();
				verificarFallos();

			});

			//El servidor al recibir un mensaje 'chat', inserta los datos en la colección y extrae todos los elementos de la colección, mandándolos a todos los clientes.
			client.on('chat', function (data) {
				var datos = { msg: data, client: client.request.connection.remotePort }
				if (collectionchat != null) {
					collectionchat.insertOne(datos);
					setTimeout(function () {

						collectionchat.find().toArray(function (err, results) {
							if (err) {
								console.log("ERROR");
							}
							else {
								io.sockets.emit('chat', results);
							}

						});
					}, 500);

				}
			});

			//El servidor al recibir un mensaje 'calendario', inserta los datos en la colección y extrae los datos que correspondan a ese único día.
			//Tras esto, envía los resultados de la búsqueda al cliente que envió el mensaje
			client.on('calendario', function (data) {
				var datos = { fecha: data.fecha, msg: data.mensaje }
				if (collectioncalendario != null) {
					collectioncalendario.insertOne(datos);
					setTimeout(function () {
						collectioncalendario.find({ fecha: datos.fecha }).toArray(function (err, results) {
							if (err) {
								console.log("ERROR");
							}
							else {
								client.emit('calendario', results);
							}

						});
					}, 500);

				}
			});

			//Realiza lo mismo que el anterior pero sin insertar datos.
			client.on('getEvento', function (data) {
				if (collectioncalendario != null) {
					collectioncalendario.find({ fecha: data }).toArray(function (err, results) {
						if (err) {
							console.log("ERROR");
						}
						else {
							client.emit('calendario', results);
						}

					});

				}

			});

			//Si recibe un mensaje 'qr', lo reenvía a todos los clientes
			client.on('qr', function (data) {
				io.sockets.emit('qr', data);
			})
		});
});







console.log("Servicio MongoDB iniciado");
