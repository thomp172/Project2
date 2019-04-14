#pragma once

#include "Person.h"
#include "Semaphore.h"
#include <stdio.h>
#include <thread>
#include <Windows.h>
#include <string>

class Seesaw
{
public:
	Seesaw(); // default constructor
	Seesaw(Person* theA, Person* theB, double theMax, double theMin);
	~Seesaw();
private:
	Person* A;
	Person* B;
	double max;
	double min;
	int length;
	int tick;
	Semaphore *semA;
	Semaphore *semB;

	//threads
	void fred(double time1, double time2);
	void wilma(double time1, double time2);
	
	void init();
	double calculate(Person *person, double c);
	double up(Person* person, double t, bool c);
};