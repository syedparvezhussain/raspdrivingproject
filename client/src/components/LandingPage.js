
import { useEffect, useState } from "react"
import Login from "./Login"
import MainPage from "./MainPage"
export default function LandingPage({arrayOfMessages}){
    const [loggedIn, setLogin] = useState(false)
      const [data, setData] = useState([])
      useEffect(()=>{
setData(arrayOfMessages)
  },[arrayOfMessages])
    console.log("loggedin", arrayOfMessages)
    return(

    <div class="container">
        <h1>Accedent Safty Landing Page</h1>

{/* {arrayOfMessages.map((e)=>{return <div>
       accident <li>{e.accident}</li>
      rash driving <li> {e.rash}</li>
     location <li>{e.location}</li>
     time stamp <li>{e.timestamp}</li>
    severity <li>{e.severity}</li>
    id <li>{e.id}</li>
    falseAlarmTrigger <li>{e.falseAlarmTrigger}</li>
      </div>})} */}
{loggedIn && 
    <div>
        <button onClick={()=>setLogin(false)}>Logout</button>
        <MainPage arrayOfMessages={data}/>
    </div>}
{!loggedIn && 
    <Login handleLogin={(e)=>{setLogin(e)}} isLoggedin ={loggedIn}/>
    }
    </div>
 )
}