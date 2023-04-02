const express = require("express"); //Line 1
const fs = require('fs');
const app = express(); //Line 2

const port = process.env.PORT || 5000; //Line 3
// const PORT = process.env.PORT || 6000;
// const { SerialPort } = require('serialport')
// const sport = new SerialPort({path:'\\\\.\\COM6', baudRate: 9600, autoOpen:true });

// sport.on('data', (data) => {
//   console.log('Received data:', data.toString());
// });

// // handle errors
// sport.on('error', (err) => {
//   console.error('Error:', err);
// });
// sport.close();

const socketIo = require("socket.io");
const http = require("http");
const server = http.createServer(app);
const io = socketIo(server, {
  cors: {
    origin: "http://localhost:3000",
  },
});
io.on("connection", (socket) => {
  console.log("client connected: ", socket.id);

  socket.join("clock-room");

  socket.on("disconnect", (reason) => {
    console.log(reason);
  });
});
setInterval(() => {
  io.to("clock-room").emit("time", new Date());
}, 1000);
server.listen(port, (err) => {
  if (err) console.log(err);
  console.log("Server running on Port ", port);
});
// This displays message that the server running and listening to specified port
app.listen(5001, () => console.log(`Listening on port ${5001}`)); //Line 6

// create a GET route
app.get("/express_backend", (req, res) => {
  //Line 9
  res.send({ express: "YOUR EXPRESS BACKEND IS CONNECTED TO REACT" }); //Line 10
}); //Line 11

app.get("/exampleApi", (req, res) => {
  //Line 9
  const bar=req.query.data  // true
  // sport.write(bar);
 
  console.log('getting api call',bar)
  io.to("clock-room").emit("Event", bar);

  res.send({ express: bar }); //Line 10

}); //Line 11
app.get("/getVehicleStatus", (req, res) => {
  //Line 9
    var currentDate = new Date();
  console.log(currentDate.toISOString())
  const accident=req.query.accident  // true
  const rash = req.query.rash
  const location = req.query.location
  const severity = req.query.severity
  const id = req.query.id
  const falseAlarmTrigger = req.query.falseAlarmTrigger
  
 const data = {
accident:accident,
rash:rash,
location:location,
timestamp:currentDate.toISOString(),
severity:severity,
id:id,
falseAlarmTrigger:falseAlarmTrigger
}
  console.log('getting api call',data)
  io.to("clock-room").emit("Event", data);

  res.send({ express: data }); //Line 10

}); //Line 11

function updateJsonFile(newObject) {
  // Read the contents of the JSON file
  fs.readFile('./client/src/settings.json', 'utf-8', (err, data) => {
    if (err) throw err;

    // Parse the JSON data
    const json = JSON.parse(data);
    console.log("json data", json)
    // Add the new object to the JSON array
    json.data.push(newObject);

    // Write the updated JSON data back to the file
    fs.writeFile('./client/src/settings.json', JSON.stringify(json), 'utf-8', (err) => {
      if (err) throw err;
      console.log('The file has been updated!');
    });
  });
}



app.get("/signUp", (req, res) => {
  //Line 9
    var currentDate = new Date();
  console.log(currentDate.toISOString())
  const username=req.query.username  // true
  const password = req.query.password
// Example usage

const newObject = { userName: username, passWord: password };
updateJsonFile(newObject);


  res.send(" user created successfully Signin with Respective Username and Password"); //Line 10

}); //Line 11
