// Node-RED function node contents. Change the array's contents as you see fit!

var msg2 = 
[
    ["Key 1", "Value 1"],
    ["Key 2", "Value 2"],
    ["Key 3", "Value 3"],
    ["Key 4", "Value 4"],
    ["Key 5", "Value 5"],
    ["Key 6", "Value 6"],
    ["Key 7", "Value 7"],

    position = 75
]

/*
// How my node works, using both strings for labels and context data for values.
var msg2 = 
[
    ["O-TEMP", flow.get("outsideTemperature").slice(0, -6) + ", " + flow.get("RoomTemperature").toString()],
    ["O-HUMI", flow.get("outsideHumidity") + ", " + flow.get("RoomHumidity").toString() + "%"],
    ["PRESS", flow.get("outsidePressure")],
    ["CAQI", flow.get("CAQI").toString()],
    ["PI-TEMP", flow.get("piTemperature")],
    ["B-TEMP", (flow.get("boilerLastCorrectValue") + 8).toString()],
    ["", ""], // unfortunately, you have to waste precious bandwidth sending nothing if you want to use less than seven key-value pairs.

    position = 50
]
*/


var jsonstring = JSON.stringify(msg2);
msg.payload = jsonstring;

return msg;