// City.cpp : Defines the city class for this project.
//

#include "City.h"
#include <iostream>
#include <math.h>

City::City()
{
	this->name = "";
	this->x = 0;
	this->y = 0;
	this->status = '%';
}

City::City(string name)
{
	this->name = name;
	this->x = 0;
	this->y = 0;
	this->status = '%';
}

City::City(string name, float x, float y)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->status = '%';
}

City::City(string name, float x, float y, char status)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->status = status;
}

City::~City()
{
	//	Destructor	-	Do nothing
}

float City::getDistance()
{
	return sqrt(x*x + y*y);
}

void City::print()
{
	cout << "= = = = = = = = = =" << endl;
	cout << "Nombre:	" << this->name << endl;
	cout << "	X ->	" << this->x << endl;
	cout << "	Y ->	" << this->y << endl;
	cout << "Estado: " << this->status << endl;
}

string City::getName() {
	return this->name;
}

float City::getDistanceByCity(City remote)
{
	return sqrt((x - remote.x)*(x - remote.x) + (y - remote.y)*(y - remote.y));
}

float City::getX() {
	return this->x;
}

float City::getY() {
	return this->y;
}

char City::getStatus() {
	return this->status;
}

void City::setStatus(char c) {
	this->status = c;
}