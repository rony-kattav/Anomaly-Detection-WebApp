

function detect(detector_type, regfile, anomalyfile){

    const TSModule = require('bindings')('AnomalyDetector');

    let anomalies = TSModule.detect(detector_type,regfile,anomalyfile);
    // if no anomalies were detected or the detector type was invalid,
    // the return value will be an empty string.
    var lines;
    if(anomalies.length <1){
        lines=[];
    }
    else{
        lines = anomalies.match(/^.*((\r\n|\n|\r)|$)/gm);
    }
    return writeJSON(lines);
    
}


module.exports.detect = detect


function writeJSON(lines){
    
    linesLen = lines.length;
    if(linesLen<1){
        text = '{}';
    }
    else {
        anomaliesLen=linesLen -1;

        var i;
        text = '{';
        
        for (i = 0; i < anomaliesLen-1; i++) {
            var splitLine = lines[i].split(",");
            var feat = splitLine[0];
            var time = splitLine[1];
        
            text += '"anomaly number ';
            text += i+1;
            text += '":{'
            text += '"timeStep":';
            text += time;
            text +=', "features":"';
            text += feat;
            text += '"},';
        }

        var splitLine = lines[anomaliesLen-1].split(",");
        var feat = splitLine[0];
        var time = splitLine[1];

        text += '"anomaly number ';
        text += i+1;
        text += '":{'
        text += '"timeStep":';
        text += time;
        text +=', "features":"';
        text += feat;
        text += '"}}';

    }
    

    var jsonObj = JSON.parse(text);
    
    var jsonString = JSON.stringify(jsonObj,null,i);


    return jsonString;
    
}
