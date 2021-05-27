#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <iterator>
#include <array>
#include <math.h>
#include <memory>
#include "anomaly_detection_util.h"
#include <iostream>
#include <map>

using namespace std;

class TimeSeries {


	// map for the line of the features - key: feature name , value: coloumn index
	// vector of vectors for the values in the table
	pair<map<string, int>, vector<vector<float>>> table;

	// Recieves a CSV file name, reads the file and insert the data to the table field.
	pair<map<string, int>, vector<vector<float>>> csvToTable(const char* CSVfileName);

public:


	// Creates a TimeSeries from a csv file
	TimeSeries(const char* CSVfileName);

	//destructor
	virtual ~TimeSeries();

	// Creates a TimeSeries with only features row.
	TimeSeries(const vector<string>& featurs);

	//Adds a new line with data about the flight
	void addLine(const vector<float>& tableLine);

	// returns the features row
	const vector<string> getFeatures() const;

	// changes the features row
	void setFeatures(const vector<string>& featurs);

	// returns the value from the requested feature in the requested time
	float getValue(int time, const string& feature) const;

	// returns the table coloumn of the requested feature
	vector<float> getFeatureColoumn(const string& feature) const;

	// returns the index of the feature
	int getFeatureColoumnIndex(const string& feature) const;

	// returns the amount of rows = the time that has passed (= the last second)
	int getTime() const;

	// returns a points vector that in point i : x = feature1 at time i, y= feature2 at time i
	vector<shared_ptr<Point>> getPoints(const string& feature1, const string& feature2) const;

	//prints the table
	void toPrint() const;



};


#endif /* TIMESERIES_H_ */