var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");
const { emit } = require("process");

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


var allClients = new Array();

MongoClient.connect("mongodb://localhost:27017/", { useUnifiedTopology: true }, function (err, db) {
	httpServer.listen(8080);
	var io = socketio(httpServer);
	let dbo = db.db("pruebaBaseDatos");

	let collectiontemps = dbo.collection("temps");
	let collectionluces = dbo.collection("luces");
	let collectionchat = dbo.collection("chat");
	let collectioncalendario = dbo.collection("calendario");

	function verificarFallos() {
		if ((temperatura < -10 || temperatura >= 50) && luz > 100) {
			ventana = false;
			io.sockets.emit('persiana', ventana);
			io.sockets.emit('alertaluz', false);

		}
	}

	function envioAlertaTemp() {
		var alerta = false;
		if (temperatura >= 40 || temperatura <= 0) {
			alerta = true;
		}

		io.sockets.emit('alertatemp', alerta);

	}

	setInterval(function () {
		if (aire) {
			if (temperatura < temperatura_fija) {
				temperatura += 1;
			}
			else if (temperatura > temperatura_fija) {
				temperatura -= 1;
			}
		}
		else if (temperatura < 50 && !aire) {
			temperatura += 1;

		}
		var d = new Date();
		var t = d.getTime();
		io.sockets.emit('envioTemp', { temperatura, t });
		envioAlertaTemp();
	}
		, 5000);



	setTimeout(function () {
	}, 5000);
	io.sockets.on('connection',
		function (client) {
			client.emit('ack', "Conexión recibida. Te respondo.");

			client.on('ack', function (data) {
				console.log(data);
				allClients.push({ address: client.request.connection.remoteAddress, port: client.request.connection.remotePort });
				io.sockets.emit('all-connections', allClients);
			});

			client.on('aire', function (data) {
				console.log(`Aire: ${data.cambio}`);
				aire = data.cambio;
				io.sockets.emit('aire', aire);
			});

			client.on('persiana', function (data) {
				console.log(`Persiana: ${data.cambio}`);
				ventana = data.cambio;
				io.sockets.emit('persiana', ventana);
			});

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

			client.on('nuevaTemp', function (data) {
				temperatura = data.temperatura;
				if (collectiontemps != null) {
					collectiontemps.insertOne(data, { safe: true }, function (err, result) { });
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
				io.sockets.emit('envioTemp', data);

				envioAlertaTemp();
				verificarFallos();
			});

			client.on('nuevaLuz', function (data) {
				luz = data.luz;
				if (collectionluces != null) {
					collectionluces.insertOne(data, { safe: true }, function (err, result) { });
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
				io.sockets.emit('envioLuz', data);
				var alerta = false;
				if (luz >= 100) {
					alerta = true;
				}
				io.sockets.emit('alertaluz', alerta);
				verificarFallos();

			});


			client.on('chat', function (data) {
				var datos = { msg: data, client: client.request.connection.remotePort }
				if (collectionchat != null) {
					collectionchat.insertOne(datos);
					setTimeout(function () {
						console.log("I am the third log after 5 seconds");

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

		});
});







console.log("Servicio MongoDB iniciado");
