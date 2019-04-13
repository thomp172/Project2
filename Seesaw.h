#pragma once

#include "Person.h"
#include "Semaphore.h"
#include <stdio.h>
#include <thread>
#include <Windows.h>
#include <string>

#define MAX_SEM_COUNT 2
#define THREADCOUNT 2
class Seesaw
{
public:
	Seesaw(); // default constructor
	Seesaw(Person* theA, Person* theB, double theMax, double theMin);
	void init();
private:
	Person* A;
	Person* B;
	double max;
	double min;
	int length;
	int tick;
	double locA;
	double locB;
	Semaphore *semA;
	Semaphore *semB;
	int count;
	bool control;

	//threads
	void turnA(double time);
	void turnB(double time);
	
	double calculate(Person *person, double c);
	void motion(Person* person, double t);
	void movement(Person* person, double t);
	void output();

	void takeTurns(double time1, double time2);
	void fred(double t, bool c);
	void wilma(double t, bool c);
	double up(Person* person, double t, bool c);
};