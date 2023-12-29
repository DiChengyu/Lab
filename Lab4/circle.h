#ifndef CIRCLE__CIRCLE_H_
#define CIRCLE__CIRCLE_H_
using namespace std;
#include <iostream>
#include "rec/robotino/api2/all.h"
using namespace rec::robotino::api2;

#define PI 3.1415f

class MyCom : public Com {
public:
	MyCom() : Com() {}

	void errorEvent(const char* errorString) {
		cerr << "Error: " << errorString << endl;
	}
	void connectedEvent() {
		cout << "Connected." << endl;
	}
	void connectionClosedEvent() {
		cout << "Connection closed." << endl;
	}
};

#endif  // CIRCLE__CIRCLE_H_
