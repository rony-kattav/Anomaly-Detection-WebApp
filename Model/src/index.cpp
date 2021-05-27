#include <napi.h>
#include <string.h>
#include "timeseries.h"
#include "SimpleAnomalyDetector.h"
#include "HybridAnomalyDetector.h"
#include <sstream> 
#include "anomaly_detection_util.h"


string get_AnomalyReport(TimeSeriesAnomalyDetector* ad, string normalPath, string anomalyPath){
    // create a time series for the normal file
    TimeSeries tsNormal = TimeSeries::TimeSeries(normalPath.c_str());
    // learn the normal model
    ad->learnNormal(tsNormal);
    // create a time series for the anomaly file
    TimeSeries tsAnomaly = TimeSeries::TimeSeries(anomalyPath.c_str());
    // detect the anomalies
    vector<AnomalyReport> anomalyReport = ad->detect(tsAnomaly);
    
    int size =anomalyReport.size();
    if(size < 1){
        return "";
    }
    // parse the report to a long string
    stringstream result;
    for(int i=0;i<size; i++){
        result <<  anomalyReport[i].description << ",";
        result << anomalyReport[i].timeStep;
        result << "\n";
    }

    return result.str();
}


string get_AnomalyReport_Linear_reg(string normalPath, string anomalyPath){

    SimpleAnomalyDetector* sd = new SimpleAnomalyDetector();
    string result = get_AnomalyReport(sd,normalPath,anomalyPath);
    sd->~SimpleAnomalyDetector();
    return result;
}


string get_AnomalyReport_Hybrid(string normalPath, string anomalyPath){

    HybridAnomalyDetector* hd = new HybridAnomalyDetector();
    string result = get_AnomalyReport(hd,normalPath,anomalyPath);
    hd->~HybridAnomalyDetector();
    return result;

}


Napi::String detect(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();

    std::string model_type = (std::string) info[0].ToString();
    std::string normalPath = (std::string) info[1].ToString();
    std::string anomalyPath = (std::string) info[2].ToString();

    std::string result;
    if(strcmp(model_type.c_str(), "Hybrid") == 0){
        result = get_AnomalyReport_Hybrid(normalPath,anomalyPath);
    }
    else if(strcmp(model_type.c_str(), "Regression") == 0){
        result= get_AnomalyReport_Linear_reg(normalPath,anomalyPath);
    }
    return Napi::String::New(env,result);
}


Napi::Object Init(Napi::Env env, Napi::Object exports){

    exports.Set(
        Napi::String::New(env, "detect"),
        Napi::Function::New(env, detect)
    );


    return exports;
}

NODE_API_MODULE(getAnomalyReport,Init)



/*
Napi::String getCorrelatedFeatures(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    std::string normalPath = (std::string) info[0].ToString();
    // create a time series for the normal file
    TimeSeries tsNormal = TimeSeries::TimeSeries(normalPath.c_str());
    // create an anomaly detector
    SimpleAnomalyDetector sd = SimpleAnomalyDetector::SimpleAnomalyDetector();
    // learn the normal model and return the correlated features that it found
    sd.learnNormal(tsNormal);
    vector<correlatedFeatures> cf = sd.getNormalModel();
    // parse the correlates features vector to a long string
    stringstream cf_str;
    for(int i=0; i< cf.size(); i++){
        cf_str << "feature1:" << cf[i].feature1;
        cf_str << ",feature2:" << cf[i].feature2;
        cf_str << ",lin_reg:" << cf[i].lin_reg.a << cf[i].lin_reg.b;
        cf_str << ",threshold:" << cf[i].threshold;
        cf_str << "\n";
    }
    return Napi::String::New(env,cf_str.str());
}

vector<correlatedFeatures> parseCF(string cf){
    vector<correlatedFeatures> cf_vector;
    stringstream cf_stream(cf); 
    string line;
    string cf_field;
    // parse the string into lines
    while(getline(cf_stream,line,'\n')){
        correlatedFeatures correlation;
        stringstream line_stream(line); 
        while(getline(cf_stream,cf_field,',')){
            if (cf_field.find("feature1:") != string::npos){
                correlation.feature1 = cf_field.substr(strlen("feature1:"));
            }
            else if(cf_field.find("feature2:") != string::npos){
                correlation.feature2 = cf_field.substr(strlen("feature2:"));
            }
            else if(cf_field.find("lin_reg:") != string::npos){
                string linregstr = cf_field.substr(strlen("lin_reg:"));
                int pos = linregstr.find("-");
                float a = stof(linregstr.substr(0,pos));
                pos+=2;
                float b = stof(linregstr.substr(pos));
                correlation.lin_reg.a = a;
                correlation.lin_reg.b = b;

            }
            else if(cf_field.find("threshold:") != string::npos){
                correlation.threshold = stof(cf_field.substr(strlen("threshold:")));
            }
        }
        cf_vector.push_back(correlation);
    }
    return cf_vector;

} 


Napi::String detect(const Napi::CallbackInfo& info){
    Napi::Env env = info.Env();
    std::string cf_str = (std::string) info[0].ToString();
    std::string anomalyPath = (std::string) info[1].ToString();
    // create a time series for the anomaly file
    TimeSeries anomalyTs = TimeSeries(anomalyPath.c_str());
    // create an anomaly detector, but send it the acorrelation features we've got 
    SimpleAnomalyDetector sd = SimpleAnomalyDetector();
	sd.setCorrelatedFeatures(parseCF(cf_str));
	vector<AnomalyReport> report = sd.detect(anomalyTs);
    // parse the report to a long string
    stringstream report_str;
    for(int i=0; i< report.size(); i++){
        report_str << "features:" << report[i].description;
        report_str << ",time:" << report[i].timeStep;
        report_str << "\n";
    }
    return Napi::String::New(env,report_str.str());
}


*/
