
// 206586687 Shaked Or


#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include <vector>
#include <algorithm>
#include <string.h>
#include <math.h>
#include "timeseries.h"
#include <iostream>
#include <memory>
#include <utility>
#include "AnomalyDetector.h"
#include "minCircle.h"


struct correlatedFeatures {
	string feature1, feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;
	float xCenter;
	float yCenter;
};


class SimpleAnomalyDetector :public TimeSeriesAnomalyDetector {
	vector<correlatedFeatures> cf;
	int isHybrid;
	float corrThreshold = 0.9;
	float corrMinThreshold = 0.5;

	// adds a correlation of the two features to the learned moddel
	void addCorrelation(const string& feature1, const string& feature2, float pear, const TimeSeries& ts);
	int isInCF(const TimeSeries& ts, const string& feature1, const string& feature2) const;
	void addCircleCorrelarion(const string& feature1, const string& feature2, float pear, const TimeSeries& ts);



public:
	// constructor
	SimpleAnomalyDetector();

	SimpleAnomalyDetector(int hybrid);

	//distructor
	virtual ~SimpleAnomalyDetector();


	// Gets a time series and learn the normal correlations between the features
	virtual void learnNormal(const TimeSeries& ts);
	
	// Gets a flight information and detects anomalies according to the learned normal model
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);


	// returns the normak model
	vector<correlatedFeatures> getNormalModel() {
		return cf;
	}


	void setThreshold(float threshold);

	float getThreshold();

	static string detect(const TimeSeries& anomalyTs, vector<correlatedFeatures> cf);
	
	void setCorrelatedFeatures(vector<correlatedFeatures> correlations){
		cf = correlations;
	}

};



class VectorHandler {

	vector<string> vec;
	int vecSize;

public:
	VectorHandler(vector<string> v);
	int Vector_getSize();
	string Vector_getLine(int index);
};


class CharPtrHandler {

	char* cptr;

public:
	CharPtrHandler(string str);
	virtual ~CharPtrHandler();
	char* CharPtr_Get();
};



// extern "C" __declspec(dllexport) void* Anomaly_Detecor_Create();

// extern "C" __declspec(dllexport) void Anomaly_Detecor_LearnNormal(SimpleAnomalyDetector* sd,TimeSeries* ts);

// extern "C" __declspec(dllexport) void* Anomaly_Detecor_Detect(SimpleAnomalyDetector * sd, TimeSeries * ts);
// extern "C" __declspec(dllexport) int Anomaly_Detecor_getReportSize(VectorHandler * vec);
// extern "C" __declspec(dllexport) void* Anomaly_Detecor_getAnomaly(VectorHandler * vec, int index);
// extern "C" __declspec(dllexport) void Anomaly_Detecor_DeleteAnomaly(CharPtrHandler* cptr);



#endif /* SIMPLEANOMALYDETECTOR_H_ */
