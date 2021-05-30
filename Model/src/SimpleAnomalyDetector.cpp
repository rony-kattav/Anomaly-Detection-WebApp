//#include "pch.h"
#include "SimpleAnomalyDetector.h"



/*
 * SimpleAnomalyDetector.cpp
 *
 * Author: 206586687 Shaked Or
 */

 //#include "minCircle.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
	cf = {};
	isHybrid = 0;

}
SimpleAnomalyDetector::SimpleAnomalyDetector(int hybrid) {
	cf = {};
	if (hybrid) {
		isHybrid = 1;
	}
	else {
		isHybrid = 0;
	}
}


SimpleAnomalyDetector::~SimpleAnomalyDetector() {

}

// Returns 1 if the feature has a correlation in cf and 0 if not.
int SimpleAnomalyDetector::isInCF(const TimeSeries& ts, const string& feature1, const string& feature2) const {
	vector<string> features = ts.getFeatures();
	for (const auto& corr : cf) {
		if (corr.feature1 == feature1 && corr.feature2 == feature2) {
			return 1;
		}
	}
	return 0;
}

void SimpleAnomalyDetector::setThreshold(float threshold) {
	if (threshold >= 0 && threshold <= 1) {
		corrThreshold = threshold;
	}
}

float SimpleAnomalyDetector::getThreshold() {
	return corrThreshold;
}

void SimpleAnomalyDetector::addCorrelation(const string& feature1, const string& feature2, float pear, const TimeSeries& ts) {
	correlatedFeatures correlated;
	correlated.feature1 = feature1;
	correlated.feature2 = feature2;
	correlated.corrlation = pear;
	//cout << feature1 << "-" << feature2 << endl;
	vector<shared_ptr<Point>> ptr = ts.getPoints(correlated.feature1, correlated.feature2);
	shared_ptr<Point>* points = &(ptr[0]);
	correlated.lin_reg = linear_reg(points, ts.getTime());
	// find the threshold
	float maxThresh = 0;
	for (int k = 0; k < ts.getTime(); k++) {
		float deviation = dev(*points[k], correlated.lin_reg);
		if (deviation > maxThresh) {
			maxThresh = deviation;
		}
	}
	correlated.threshold = maxThresh * 1.1;
	cf.push_back(correlated);
}


void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
	cf = {};
	vector<string> features = ts.getFeatures();
	int numOfFeatures = features.size();
	float pear;
	for (int i = 0; i < numOfFeatures; i++) {
		vector<float> vecX = ts.getFeatureColoumn(features[i]);
		float const* x = &vecX[0];
		float maxPearson = 0;
		int maxIndex = 0;
		for (int j = 0; j < numOfFeatures; j++) {
			if (j != i) {
				vector<float> vecY = ts.getFeatureColoumn(features[j]);
				float const* y = &vecY[0];
				pear = pearson(x, y, ts.getTime());
				if (fabs(pear) > fabs(maxPearson)) {
					maxPearson = pear;
					maxIndex = j;
				}
			}

		}
		// if the correlation is strong enough 
		if (fabs(maxPearson) >= corrThreshold || fabs(fabs(maxPearson) - corrThreshold) <= pow(10, -10)) {
			// if the simetric correlation is not in cf
			if (!isInCF(ts, features[maxIndex], features[i])) {
				addCorrelation(features[i], features[maxIndex], maxPearson, ts);
			}
		}		
		else if (isHybrid) {
			if (fabs(maxPearson) >= corrMinThreshold || fabs(fabs(maxPearson) - corrMinThreshold) <= pow(10, -10)) {
				if (!isInCF(ts, features[maxIndex], features[i])) {
					addCircleCorrelarion(features[i], features[maxIndex], maxPearson, ts);
				}
			}
		}

	}
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts) {
	vector<AnomalyReport> anomalies;
	int numOfLines = ts.getTime();
	// timeStep order
	for (int j = 0; j < numOfLines; j++) {
		for (int i = 0; i < cf.size(); i++) {
	// alphabetical order		
	//for (int i = 0; i < cf.size(); i++) {
	//	for (int j = 0; j < numOfLines; j++) {
			correlatedFeatures correlated = cf[i];
			int time = j + 1;
			Point p = Point(ts.getValue(time, correlated.feature1), ts.getValue(time, correlated.feature2));
			float deviation = dev(p, correlated.lin_reg);
			if (isHybrid && correlated.lin_reg.a == 0 && correlated.lin_reg.b == 0) {
				// if this is a circle correlation
				if (dist(p, Point(correlated.xCenter, correlated.yCenter)) >= correlated.threshold) {
					string description = correlated.feature1 + "-" + correlated.feature2;
					AnomalyReport anomaly(description, time);
					anomalies.push_back(anomaly);
				}

			}
			// if the deviation is above the threshhold(or equal)
			else if (deviation >= correlated.threshold || fabs(deviation - correlated.threshold) <= pow(10, -10)) {
				string description = correlated.feature1 + "-" + correlated.feature2;
				AnomalyReport anomaly(description, time);
				anomalies.push_back(anomaly);
			}
		}
	}
	return anomalies;
}

void SimpleAnomalyDetector::addCircleCorrelarion(const string& feature1, const string& feature2, float pear, const TimeSeries& ts) {
	correlatedFeatures correlated;
	correlated.feature1 = feature1;
	correlated.feature2 = feature2;
	correlated.corrlation = pear;
	// Line(0,0) will be the identifier for a circle correlation 
	correlated.lin_reg = Line(0, 0);
	vector<shared_ptr<Point>> ptr = ts.getPoints(correlated.feature1, correlated.feature2);
	int size = ptr.size();
	Point** points = new Point * [size];
	for (int i = 0; i < size; i++) {
		Point* p = ptr[i].get();
		points[i] = new Point(p);
	}
	Circle circ = findMinCircle(points, size);
	for (int i = 0; i < size; i++) {
		delete points[i];
	}
	correlated.threshold = circ.radius * 1.1;
	correlated.xCenter = circ.center.x;
	correlated.yCenter = circ.center.y;
	cf.push_back(correlated);
}


// VectorHandler::VectorHandler(vector<string> v) {
// 	vec = {};
// 	for (int i = 0; i < v.size(); i++) {
// 		vec.push_back(v[i]);
// 	}
// 	vecSize = v.size();
// }
// int VectorHandler::Vector_getSize() {
// 	return vecSize;
// }
// string VectorHandler::Vector_getLine(int index) {
// 	return vec[index];
// }



// CharPtrHandler::CharPtrHandler(string str) {
// 	const char* cstring = str.c_str();
// 	int len = strlen(cstring);
// 	cptr = new char[len + 1];
// 	memcpy(cptr, cstring, len + 1);
// }

// CharPtrHandler::~CharPtrHandler() {
// 	delete[] cptr;
// }

// char* CharPtrHandler::CharPtr_Get() {
// 	return cptr;
// }




// extern "C" __declspec(dllexport) void* Anomaly_Detecor_Create() {
// 	return new SimpleAnomalyDetector();
// }


// extern "C" __declspec(dllexport) void Anomaly_Detecor_LearnNormal(SimpleAnomalyDetector* sd, TimeSeries * ts) {
// 	sd->learnNormal((*ts));
// }

// extern "C" __declspec(dllexport) void* Anomaly_Detecor_Detect(SimpleAnomalyDetector * sd, TimeSeries * ts) {
// 	vector<AnomalyReport> report = sd->detect(*ts);
// 	vector<string> stringrep = {};
// 	for (int i = 0; i < report.size(); i++) {
		
// 		string str = report[i].description +"-" + to_string(report[i].timeStep);
// 		stringrep.push_back(str);
// 	}
// 	return (void*)new VectorHandler(stringrep) ;
// }


// extern "C" __declspec(dllexport) int Anomaly_Detecor_getReportSize(VectorHandler* vec) {
// 	return vec->Vector_getSize();
// }

// extern "C" __declspec(dllexport) void * Anomaly_Detecor_getAnomaly(VectorHandler * vec, int index) {
// 	string anomaly = vec->Vector_getLine(index);
// 	return (void*) new CharPtrHandler(anomaly);
// }

// extern "C" __declspec(dllexport) char* Anomaly_Detecor_getAnomalyString(CharPtrHandler * cptr) {
// 	return cptr->CharPtr_Get();
// }

// extern "C" __declspec(dllexport) void Anomaly_Detecor_DeleteAnomaly(CharPtrHandler * cptr) {
// 	delete cptr;
// }


