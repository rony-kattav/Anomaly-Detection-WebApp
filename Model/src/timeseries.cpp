#include "timeseries.h"
#include <stdio.h>  /* defines FILENAME_MAX */
#include <stdlib.h>
// #define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#define GetCurrentDir getcwd
#endif
#include <iostream>
#include <windows.h>


/*
 * timeseries.cpp
 *
 * Author: 206586687 Shaked Or
 */



pair<map<string, int>, vector<vector<float>>> TimeSeries::csvToTable(const char* CSVfileName) {

	// need to check if this is a path to a file and if not, if it is a content of a csv file in string
	
	ifstream csvFile(CSVfileName);

	stringstream content;

	if (csvFile.is_open() && csvFile.good()) {
		content << csvFile.rdbuf();    
		csvFile.close();
	}
	else{
		content << CSVfileName;
	}

	string line, coloumn;
//	if (!csvFile.is_open()) {
//		throw runtime_error("There has been a problem with opening the file");
//	}
	pair<map<string, int>, vector<vector<float>>> table;


	//if (csvFile.good()) {
		// reading the features line
		//getline(csvFile, line);
		getline(content,line);
		stringstream strstm(line);
		int idx = 0;
		while (getline(strstm, coloumn, ',')) {
			table.first[coloumn] = idx;
			idx++;
		}
		string value;
		// reading the data
		//while (getline(csvFile, line)) {
		while(getline(content,line)){
			stringstream strstm(line);
			vector<float> rowVector;
			while (getline(strstm, value, ',')) {
				rowVector.push_back(stof(value));
			}
			table.second.push_back(rowVector);
		}

	//	csvFile.close();
	//}
	return table;
}

TimeSeries::TimeSeries(const char* CSVfileName) {
	table = csvToTable(CSVfileName);
}

int TimeSeries::getFeatureColoumnIndex(const string& feature) const {
	return table.first.at(feature);
}

TimeSeries::~TimeSeries() {

}

TimeSeries::TimeSeries(const vector<string>& featurs) {
	map<string, int> f;
	// creates the features row
	for (int i = 0; i < featurs.size(); i++) {
		f[featurs[i]] = i;
	}
	table.first = f;
	// creates the data table
	table.second = { {} };
}

void TimeSeries::addLine(const vector<float>& tableLine) {
	table.second.push_back(tableLine);
}

const vector<string> TimeSeries::getFeatures() const {
	vector<string> features(table.first.size(), "");
	for (const auto& it : table.first) {
		// table.first: key: feature, value: index in table
		// insert the feature to it's matching index in the vector
		features[it.second] = it.first;
	}
	return features;
}

void TimeSeries::setFeatures(const vector<string>& featurs) {
	map<string, int> f;
	for (int i = 0; i < featurs.size(); i++) {
		f[featurs[i]] = i;
	}
	table.first = f;
}


float TimeSeries::getValue(int time, const string& feature) const {
	int featureColoumn = getFeatureColoumnIndex(feature);
	// time -1 because the table starts from time = 1 and not 0
	return table.second[time - 1][featureColoumn];
}


vector<float> TimeSeries::getFeatureColoumn(const string& feature) const {
	vector<float> values;
	int featureColoumn = getFeatureColoumnIndex(feature);
	for (int i = 0; i < table.second.size(); i++) {
		values.push_back(table.second[i][featureColoumn]);
	}
	return values;
}

int TimeSeries::getTime() const {
	return table.second.size();
}

vector<shared_ptr<Point>> TimeSeries::getPoints(const string& feature1, const string& feature2) const {
	// shared_ptr so there is no need to free the memory of the points
	vector<shared_ptr<Point>> points;
	vector<float> x = getFeatureColoumn(feature1);
	vector<float> y = getFeatureColoumn(feature2);
	for (int i = 0; i < getTime(); i++) {
		float a = x[i];
		float b = y[i];
		shared_ptr<Point> ptr(new Point(x[i], y[i]));

		points.push_back(ptr);
	}
	return points;
}

void TimeSeries::toPrint() const {
	vector<string> features = getFeatures();
	// prints the features row
	for (const auto& it : features) {
		cout << it << ",";
	}
	cout << "" << endl;
	float x = table.second[1].size();
	// prints the data
	for (int i = 0; i < table.second.size(); i++) {
		for (int j = 0; j < table.second[0].size(); j++) {
			cout << to_string(table.second[i][j]) << ",";
		}
		cout << "" << endl;
	}
}



