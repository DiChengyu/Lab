#include "circle.h"
#include <iomanip>
#include <string>
#include <cmath>
#include<math.h>
#include <windows.h>

using namespace std;

float kp = 0.5;
float ki = 0.023;
float kd = 0;
unsigned long currentTime, previousTime;
float elapsedTime;
float error;
float lastError;
float cumError, rateError;

float computePID(float input) {

	MyCom com;
	currentTime = com.msecsElapsed();
	elapsedTime = (float)(currentTime - previousTime);

	error = input;
	cumError = error * elapsedTime;
	rateError = (error - lastError) * elapsedTime;

	float out = kp * error + ki * cumError + kd * rateError;

	lastError = error;
	previousTime = currentTime;

	return out;
}

//void print_robot_info_to_csv(unsigned int time) {
//	ofstream out("out.csv", std::ofstream::app);
//	streambuf * coutbuf = std::cout.rdbuf();
//	cout.rdbuf(out.rdbuf()); 
//	cout << endl;
//	cout << setw(col_width) << (time) << ",";
//	cout << setw(col_width) <<x_cor_task << ",";
//	cout << setw(col_width) <<y_cor_task << ",";
//	cout << setw(col_width) <<speed_vec_task[0] << ",";
//	cout << setw(col_width) <<speed_vec_task[1] << ",";
//		for (size_t i = 0; i < motor_num; i++) {
//			cout << setw(col_width) <<wheel_freq_vec_calc[i] << ",";
//
//		}
//		for (size_t i = 0; i < motor_num; i++) {
//			cout << setw(col_width) <<motor[i].actualVelocity() << ",";
//
//		}
//	cout << setw(col_width) <<speed_vec_calc[0] << ",";
//	cout << setw(col_width) <<speed_vec_calc[1] << ",";
//	cout << setw(col_width) <<x_cor_current << ",";
//	cout << setw(col_width) <<y_cor_current << ",";
//	std::cout.rdbuf(coutbuf); 
//	out.close();
//}

	
int main(int argc, char **argv) {
	std::string ip_addr = "192.168.0.1";
	MyCom com;
	OmniDrive omniDrive;
	Motor motor[3];
	std::cout << "Connecting...";
	com.setAddress(ip_addr.c_str());
	com.connectToServer(true);
	if(!com.isConnected()) {
		std::cout << std::endl << "Could not connect to " << com.address() << std::endl;
		rec::robotino::api2::shutdown();
		exit(1);
	}
	else {
		std::cout << "success" << std::endl;
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
	float x_speed1 = x_speed;
	float y_speed1 = y_speed;
	float rad = 0.0f;
	unsigned int start_time = com.msecsElapsed();
	unsigned int time = com.msecsElapsed();
	size_t col_width = 11;
	//cout << " | " << setw(col_width) << "Time" << " | " << setw(col_width) << "M1 pos"
	//		  << " | " << setw(col_width) << "M2 pos" << " | " << setw(col_width) << "M3 pos"
	//		  << " | " << setw(col_width) << "M1 vel" << " | " << setw(col_width) << "M2 vel"
	//		  << " | " << setw(col_width) << "M3 vel" << " | " << setw(col_width) << "M1 cur"
	//		  << " | " << setw(col_width) << "M2 cur" << " | " << setw(col_width) << "M3 cur"
	//		  << " | " << endl;
	//cout << " |";
	//for (size_t i = 0; i < 10; i++)	{
	//	cout << string(col_width + 2, '-') << "|";
	//}
	//cout << endl;

	while((time - start_time) <= duration_ms) {
		rad = 2 * PI * time / duration_ms;
		x_speed = std::cos(rad) * start_x_speed - std::sin(rad) * start_y_speed;
		y_speed = std::sin(rad) * start_x_speed + std::cos(rad) * start_y_speed;
		omniDrive.setVelocity(x_speed, y_speed, 0.0f);

		x_speed1 = x_speed + computePID(x_speed);
		y_speed1 = y_speed + computePID(y_speed);
		omniDrive.setVelocity(x_speed1, y_speed1, 0.0f);
		//cout << x_speed1 << endl;
		//cout << y_speed1 << endl;
		cout << " | " << x_speed1 << " | " << y_speed1 << endl;
		//cout << " |";
		//cout << " | " << std::setw(col_width) << (time - start_time) << " | ";
		//for(size_t i = 0; i < motor_num; i++) {
		//	cout << setw(col_width) << motor[i].actualPosition() << " | ";
		//}
		//for(size_t i = 0; i < motor_num; i++) {
		//	cout << setw(col_width) << motor[i].actualVelocity() << " | ";
		//}
		//for(size_t i = 0; i < motor_num; i++) {
		//	cout << setw(col_width) << motor[i].motorCurrent() << " | ";
		//}
		//cout << endl;
		rec::robotino::api2::msleep(sleep_ms);
		time = com.msecsElapsed();
	}
	com.disconnectFromServer();
	rec::robotino::api2::shutdown();
	double y;
	int x1, x2, space1, space2;
	for (y = 1; y >= -1; y -= 0.1) {
		//cout<<acos(y)*10<<endl;
		space1 = acos(y) * 10;
		space2 = abs(asin(y)) * 10;
		// x1,space1: x_speed1, "*"
		for (x1 = 0; x1 < space1; x1++) {
			cout << " ";
		}
		cout << "+";
		for (; x1 < 62 - space1; x1++) {
			cout << " ";
		}
		cout << "+" << endl;

		// x2,space2: x_speed2, "+"
		if (y >= 0)
		{
			for (x2 = 0; x2 < space2; x2++)
				cout << " ";
			cout << "-";
			for (; x2 < 31 - space2; x2++)
				cout << " ";
			cout << "-" << endl;
		}
		else
		{
			for (x2 = 0; x2 <= 31 + space2; x2++)
				cout << " ";
			cout << "-";
			for (; x2 <= 62 - space2; x2++)
				cout << " ";
			cout << "-" << endl;
		}
		//Sleep(500);
	}
	return 0;
}