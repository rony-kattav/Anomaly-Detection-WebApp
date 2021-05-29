
function display(response, anomalies){

    
    var text = ""
    text += "<body style=\"color: rgb(189, 86, 86); background-color: rgb(255, 255, 255);\">"
    text += "\n"
    // write the headline
    text += "<p><span style='font-family: \"Comic Sans MS\", sans-serif; color: rgb(71, 85, 119,1);'><strong><span style=\"font-size: 24px;\">Anomaly Report:</span></strong></span></p>"
    text += "\n"

  
    anomalies = JSON.parse(anomalies);

    var i=1;

    
    anomalyText = "anomaly number " + i;
    var anomaly = anomalies[anomalyText];

    while (anomaly != null){
        
        // write "anomaly number X:"
        text += "<p><strong><span style='font-family: \"Comic Sans MS\", sans-serif;  color: rgb(41, 105, 176);'>" + anomalyText + ":</span></strong></p>"
        text += "\n"
        // write the features and the time step
        text += "<p><span style='font-family: \"Comic Sans MS\", sans-serif;  color: rgb(61, 142, 185);'>features: " + anomaly["features"] +"<br>time step: "+ anomaly["timeStep"] + "</span></p>"
        text += "\n"
        i++;
        anomalyText = "anomaly number " + i;
        anomaly = anomalies[anomalyText];
    }
    text += "</body>"
    response.write(text);


}


module.exports.display = display
