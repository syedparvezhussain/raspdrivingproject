import React, { useEffect, useState } from "react";
import "./App.css";

import { io } from "socket.io-client";


function App() {
const [data, setData] = useState("");
const [arrayOfMessages, setArrayOfMessages]= useState([])

  useEffect(() => {
    
    const socket = io("http://localhost:5000");
    socket.on("connect", () => console.log(socket.id));
    socket.on("connect_error", () => {
      setTimeout(() => socket.connect(), 5000);
    });
    socket.on("Event", (data) => {

    setData(data);
    const x= arrayOfMessages
    if(arrayOfMessages && arrayOfMessages.length !== 0 && arrayOfMessages[arrayOfMessages.length-1].location !== data.location){
x.push(data)
    }
    else if(arrayOfMessages.length===0){
      x.push(data)
    }
    
    setArrayOfMessages(x)
    }
      );
    socket.on("disconnect", () => setData("server disconnected"));
  }, []);


  return (
    <div>
      {/* <h1>http://10.42.171.70:5001/exampleApi?data={data}</h1> */}
      {arrayOfMessages.map((e)=>{return <div>
       accident <li>{e.accident}</li>
      rash driving <li> {e.rash}</li>
     location <li>{e.location}</li>
      </div>})}
      
    </div>
 
  );
}

export default App;
