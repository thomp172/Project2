#pragma once

#include "Person.h"
#include <Windows.h>
#include <stdio.h>

#define MAX_SEM_COUNT 2
#define THREADCOUNT 2
class Seesaw
{
public:
	Seesaw(); // default constructor
	Seesaw(Person theA, Person theB, double theMax, double theMin);
	void init();
private:
	Person A;
	Person B;
	double max;
	double min;
	HANDLE sem;

	//threads
	void turnA();
};