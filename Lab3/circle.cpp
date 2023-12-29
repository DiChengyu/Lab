#include "circle.h"
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {
	string ip_addr = "192.168.0.1";
	MyCom com;
	OmniDrive omniDrive;
	Motor motor[3];
	cout << "Connecting...";
	com.setAddress(ip_addr.c_str());
	com.connectToServer(true);
	if(!com.isConnected()) {
		cout << endl << "Could not connect to " << com.address() << endl;
		rec::robotino::api2::shutdown();
		exit(1);
	}
	else {
		cout << "success" << endl;
	}

	size_t motor_num = 3;
	for (unsigned int i = 0; i < motor_num; i++) {
		motor[i].setMotorNumber(i);
	}

	const unsigned int duration_ms = 10000;
	const unsigned int sleep_ms = 100;
	const float start_x_speed = 0.1f; 
	const float start_y_speed = 0.0f; 
	float x_speed = start_x_speed; 
	float y_speed = start_y_speed; 
	float rad = 0.0f;
	unsigned int start_time = com.msecsElapsed();
	unsigned int time = com.msecsElapsed();
	
	size_t col_width = 11;
	cout << " | " << setw(col_width) << "Time" << " | " << setw(col_width) << "M1 pos"
			  << " | " << setw(col_width) << "M2 pos" << " | " << setw(col_width) << "M3 pos"
			  << " | " << setw(col_width) << "M1 vel" << " | " << setw(col_width) << "M2 vel"
			  << " | " << setw(col_width) << "M3 vel" << " | " << setw(col_width) << "M1 cur"
			  << " | " << setw(col_width) << "M2 cur" << " | " << setw(col_width) << "M3 cur"
			  << " | " << endl;
	cout << " |";
	for (size_t i = 0; i < 10; i++)	{
		cout << string(col_width + 2, '-') << "|";
	}
	cout << endl;

	while((time - start_time) <= duration_ms) {
		rad = 2 * PI * time / duration_ms;
		x_speed = cos(rad) * start_x_speed - sin(rad) * start_y_speed;
		y_speed = sin(rad) * start_x_speed + cos(rad) * start_y_speed;
		omniDrive.setVelocity(x_speed, y_speed, 0.0f);

		cout << " | " << setw(col_width) << (time - start_time) << " | ";
		for(size_t i = 0; i < motor_num; i++) {
			cout << setw(col_width) << motor[i].actualPosition() << " | ";
		}
		for(size_t i = 0; i < motor_num; i++) {
			cout << setw(col_width) << motor[i].actualVelocity() << " | ";
		}
		for(size_t i = 0; i < motor_num; i++) {
			cout << setw(col_width) << motor[i].motorCurrent() << " | ";
		}
		cout << endl;
		rec::robotino::api2::msleep(sleep_ms);
		time = com.msecsElapsed();
	}
	com.disconnectFromServer();
	rec::robotino::api2::shutdown();
	return 0;
}