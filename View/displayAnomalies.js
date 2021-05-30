
function popup(response, message, color){
    popupColor = "#04AA6D";
    if((color > "green") - (color < "green") == 0 ){
        popupColor = "#04AA6D";
    }
    else if((color > "red") - (color < "red") == 0 ){
        popupColor = "#f44336";
    }
    var text = ""
    text += "<style>\n.alert {\nborder-radius: 25px;\npadding: 20px;\nbackground-color:";
    text +=  popupColor;
    text += ";\ncolor: white;font-family: \"Comic Sans MS\";\n}\n.closebtn {\nmargin-left: 15px;\ncolor: white;\nfont-weight: bold;\nfloat: right;\nfont-size: 30px;\nline-height: 20px;\ncursor: pointer;\ntransition: 0.3s;\n}\n.closebtn:hover {\ncolor: black;\n}\n</style>"
    text += "<div class=\"alert\"><span class=\"closebtn\" onclick=\"this.parentElement.style.display='none';\">&times;</span><strong>";
    text += message;
    text += "</div>";
    response.write(text);
}


function display(response, anomalies){

    
    var text = ""
    text += "<body style=\"color: rgb(189, 86, 86); background-color: background:rgb(248, 248, 255,.7);\">"
    text += "\n"
    // write the headline
    text += "<p style=\"text-align: center;\"><span style='font-family: \"Comic Sans MS\", sans-serif; text-align: center; color: rgb(71, 85, 119);'><strong><span style=\"font-size: 24px;\">Anomaly Report:</span></strong></span></p>"
    text += "\n"

  
    anomalies = JSON.parse(anomalies);

    var i=1;

    
    anomalyText = "anomaly number " + i;
    var anomaly = anomalies[anomalyText];

    while (anomaly != null){
        
        // write "anomaly number X:"
        text += "<p style=\"text-align: center;\"><strong><span style='font-family: \"Comic Sans MS\", sans-serif;  color: rgb(41, 105, 176);'>" + anomalyText + ":</span></strong></p>"
        text += "\n"
        // write the features and the time step
        text += "<p style=\"text-align: center;\"><span style='font-family: \"Comic Sans MS\", sans-serif;  color: rgb(61, 142, 185);'>features: " + anomaly["features"] +"<br>time step: "+ anomaly["timeStep"] + "</span></p>"
        text += "\n"
        i++;
        anomalyText = "anomaly number " + i;
        anomaly = anomalies[anomalyText];
    }
    text += "</body>"
    response.write(text);


}


module.exports.display = display
module.exports.popup = popup
