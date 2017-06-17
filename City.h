// City.h : Defines the city header for this project.
//

#pragma once

#include "stdio.h"
#include <string>
#include <math.h>
using namespace std;

class City
{
private:
	string name;
	float x, y;
	char status;
public:
	City();
	City(string);
	City(string, float, float);
	City(string, float, float, char);
	~City();
	float getDistance();	
	void print();
	string getName();
	float getDistanceByCity(City);
	float getX();
	float getY();
	char getStatus();
	void setStatus(char);
};