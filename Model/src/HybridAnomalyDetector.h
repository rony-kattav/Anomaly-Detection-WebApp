
// 206586687 Shaked Or

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "AnomalyDetector.h"


class HybridAnomalyDetector:public SimpleAnomalyDetector {
public:
	HybridAnomalyDetector();
	virtual ~HybridAnomalyDetector();
	// find the normal model of correlations between features
	// and the normal deviation from the pattern so will be
	// able to alert when there is an anomaly. (deviation from the normal)
	virtual void learnNormal(const TimeSeries& ts);

};

#endif /* HYBRIDANOMALYDETECTOR_H_ */
