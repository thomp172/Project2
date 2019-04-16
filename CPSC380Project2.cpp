// CPSC380Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"


int main()
{
	Person *fred = new Person("Fred", 1);
	Person *wilma = new Person("Wilma", 1.5);
	Seesaw *seesaw = new Seesaw(fred,wilma,7,1);
	seesaw->thrA.join();
	seesaw->thrB.join();
}

