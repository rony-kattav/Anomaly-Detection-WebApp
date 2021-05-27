// 206586687 Shaked Or
#include "HybridAnomalyDetector.h"

// initializes the "isHybrid" field in simple animaly detector
// that it will know to find correlation and detect deviations
// that suits to minimal circle instead of linare regression.
HybridAnomalyDetector::HybridAnomalyDetector():SimpleAnomalyDetector(1) {}

void HybridAnomalyDetector::learnNormal(const TimeSeries& ts){
	SimpleAnomalyDetector::learnNormal(ts);
}

HybridAnomalyDetector::~HybridAnomalyDetector() {}

