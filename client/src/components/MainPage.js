import React, { useEffect, useState } from "react";
import ReactTable from "react-table-v6";
import Table from "./Table";
import "react-table-v6/react-table.css";

const data1 = [
  {
    id: 1,
    timestamp: "2022-03-28T10:00:00.000Z",
    location: "123 Main St.",
    rashDriving: false,
    falseAlarmTrigger: false,
    accident: true,
    severity: "High",
  },
  {
    id: 2,
    timestamp: "2022-03-28T11:00:00.000Z",
    location: "456 Elm St.",
    rashDriving: true,
    falseAlarmTrigger: false,
    accident: false,
    severity: "Low",
  },
  {
    id: 3,
    timestamp: "2022-03-28T12:00:00.000Z",
    location: "789 Oak St.",
    rashDriving: false,
    falseAlarmTrigger: true,
    accident: false,
    severity: "Medium",
  },
];

const columns = [
  {
    Header: "Vehicle ID",
    accessor: "id",
  },
  {
    Header: "Timestamp",
    accessor: "timestamp",
  },
  {
    Header: "Location",
    accessor: "location",
  },
  {
    Header: "Rash Driving",
    accessor: "rashDriving",
      Cell: (row) => {
      return row.value ? <span className="indicator">&#x2714;</span> : <span className="indicator">&#x2718;</span>;;
    },
  },
  {
    Header: "False Alarm Trigger",
    accessor: "falseAlarmTrigger",
      Cell: (row) => {
      return row.value ? <span className="indicator">&#x2714;</span> :  <span className="indicator">&#x2718;</span>;;
    },
  },
  {
    Header: "Accident",
    accessor: "accident",
     Cell: (row) => {
      return row.value ? <span className="indicator">&#x2714;</span> :  <span className="indicator">&#x2718;</span>;;
    },
  },
  {
    Header: "Severity",
    accessor: "severity",
  },
];

const MainPage = ({arrayOfMessages}) => {
  const [activeTab, setActiveTab] = useState("Hospital");
  const [data, setData] = useState([])
  const loc = data && data[data.length-1]?.location
 
  useEffect(()=>{
setData(arrayOfMessages)
var settings = {
  "async": true,
  "crossDomain": true,
  "url": "https://www.fast2sms.com/dev/bulkV2?authorization=duFxn6XTr0wH7s8fKNU5kJqEA9GBoWOR1YMVhzgP4e2QmvCLZ3XiZc7G9OJWgFRx3QNLsCMuHUTze2VA&message=Rash driving detected mundu me driver ni jail lo vestam ;) &language=english&route=q&numbers=6303528748,8919266028,9440996839",
  "method": "GET"
}
 fetch(settings.url)
      .then(response => {
        return response.json()
      })
      .then(data => {
          console.log("responseComing after sensing sms",data);
      })

  },[arrayOfMessages, loc])

  const handleTabChange = (tabName) => {
    setActiveTab(tabName);
  };

  return (
    <div className="landing-page">
      <nav className="nav-options">
        {data && data[data.length-1]?.location}
        <button
          className={activeTab === "Hospital" ? "active" : ""}
          onClick={() => handleTabChange("Hospital")}
        >
          Hospital
        </button>
        <button
          className={activeTab === "Family" ? "active" : ""}
          onClick={() => handleTabChange("Family")}
        >
          Family
        </button>
        <button
          className={activeTab === "PoliceStation" ? "active" : ""}
          onClick={() => handleTabChange("PoliceStation")}
        >
          Police Station
        </button>
      </nav>
      <div className="main-area">
        {data.length? <Table data={data}  columns={columns}  />:null}
      
      </div>
    </div>
  );
};

export default MainPage;
