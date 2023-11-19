server = require("http").Server();
var socketIO = require("socket.io");
var io = socketIO.listen(server);

clients = [];

io.sockets.on("connection", function (socket) {
  clients.push(socket.id);

  socket.emit("player", clients.length);

  socket.on("disconnect", function () {
    console.log("user disconnected");
    clients.splice(clients.indexOf(socket.id), 1);
  });

  socket.on("player-move", function (data) {
    socket.broadcast.emit("player-move", data);
  });

  socket.on("pause", function (data) {
    socket.broadcast.emit("pause", data);
  });

  socket.on("resume", function (data) {
    socket.broadcast.emit("resume", data);
  });
});

server.listen(3000);
