#pragma once
#include <iostream>
using namespace std;

class Person
{
public:
	Person(); // default constructor
	Person(string theName, double theSpeed);
	void setName(string theName);
	void setSpeed(double speed);
	string getName();
	double getSpeed();
	string toString();
private:
	string name;
	double speed; //ft/sec

};