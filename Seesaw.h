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
	const double GRAVITY = -32.1522; //ft/sec
	
	Person* A;
	Person* B;
	int max;
	int min;
	int length;
	int tick;
	double locA;
	double locB;
	Semaphore *semA;
	Semaphore *semB;
	Semaphore *semC;
	int count;
	bool control;

	//threads
	void turnA(double t);
	void turnB(double t);
	
	double calculate(Person *person, double c);
	double motion(Person* person, double t);
	void movement(Person* person, double t);
	void output();
};