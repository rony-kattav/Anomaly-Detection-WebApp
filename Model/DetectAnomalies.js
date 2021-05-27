
// //var regfile = "C:\\Users\\User\\Desktop\\flight\\reg_flight.csv";
// //var anomalyfile = "C:\\Users\\User\\Desktop\\flight\\paths\\anomaly_flight20210411204122.csv";

// var regfile = "./reg_flight.csv"
// var anomalyfile = "./anomaly_flight20210411204122.csv";


// var fs = require('fs');

// fs.readFile(regfile, 'utf8', function(err, data) {
//     if (err) throw err;
//     /*
//     fs.readFile(anomalyfile, 'utf8', function(err, data2) {
//         if (err) throw err;
//         console.log(detect("Hybrid", data, data2));
//     });
//     */
//     console.log(detect("Hybrid", data, anomalyfile));

// });



//console.log(detect("Hybrid",regfile,anomalyfile));


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
    

    var myobj = JSON.parse(text);
    
    var jsonfile = JSON.stringify(myobj,null,i);

    /*
    var fs = require('fs');
    const { features } = require('process');
    fs.writeFile("Anomaly_Report.json", jsonfile, function(err, result) {
        if(err) console.log('error', err);
    });
    */

    return jsonfile;
    
}
