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
	const double START = 0;
	const double GRAVITY = -9.8;

	Person* A;
	Person* B;
	double max;
	double min;
	Semaphore *sem;

	//threads
	void turn(Person* person);
};