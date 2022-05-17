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
		io.sockets.emit('envioTemp',{temperatura,t});
	}
		, 5000);

	var dbo = db.db("pruebaBaseDatos");
	dbo.createCollection("test", function (err, collection) {
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
					console.log(allClients);

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
					if (collection != null) {
						collection.insertOne(data, { safe: true }, function (err, result) { });
					}
					io.sockets.emit('envioTemp', data);
				});
			});
	});
});






console.log("Servicio MongoDB iniciado");
