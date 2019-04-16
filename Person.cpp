#include "pch.h"

Person::Person()
{
	name = "Jane";
	speed = 1;
}
Person::Person(string theName, double theSpeed)
{
	name = theName;
	speed = theSpeed;
}

void Person::setName(string theName)
{
	name = theName;
}
void Person::setSpeed(double theSpeed)
{
	speed = theSpeed;
}
string Person::getName()
{
	return name;
}
double Person::getSpeed()
{
	return speed;
}

string Person::toString()
{
	return (name + ": " + to_string(speed) + " ft/s");
}
