//#include "Seesaw.h"
#include "pch.h"

Seesaw::Seesaw()
{
	Person* A = new Person("Jane", 1);
	Person* B = new Person("John", 2);
	max = 5;
	min = 0;
	init();
}
Seesaw::Seesaw(Person* theA, Person* theB, double theMax, double theMin)
{
	A = theA;
	B = theB;
	max = theMax;
	min = theMin;
	init();
}
void Seesaw::init()
{
	cout << "begin simulation" << endl;
	//semaphore
	semA = new Semaphore(1);
	semB = new Semaphore();
	semC = new Semaphore(1);
	length = max - min;
	tick = 0;
	count = 0;
	control = true;
	int time1 = calculate(A, min);
	int time2 = calculate(B,max);
	count = (time1 + time2) * 10;
	//thread creation
	locA = min;
	locB = max;
	for (int i=0; i<10; i++)//repeat 10 times
	{
		thread thrA = thread(&Seesaw::turnA, this, time1);
		thrA.join();
		thread thrB = thread(&Seesaw::turnB, this, time2);
		thrB.join();
	}
}

double Seesaw::calculate(Person *person, double c)
{
	double time;
	time = length/person->getSpeed();
	//person reaches max height at timeFinal
	cout << person->getName() << " reaches max height at " << time << " seconds." << endl;
	return time;
}

//threads
void Seesaw::turnA(double time1)
{
	semA->wait();
	for (int j = 0; j < time1; j++)
	{
		movement(A, j);
	}
	for (int k = time1; k > 0; k--)
	{
		movement(A, k);
	}
	semB->signal();
	semA->signal();
}
void Seesaw::turnB(double time2)
{
	semB->wait();
	semA->wait();
	for (int j = 0; j < time2; j++)
	{
		movement(B, j);
	}
	for (int k = time2; k > 0; k--)
	{
		movement(B, k);
	}
	semA->signal();
}

double Seesaw::motion(Person *person, double t)
{
	int round;
	double dis = person->getSpeed() * t;
	if ((dis < 0) && (dis > length))
	{
		round = (int)dis;
		dis = abs(round % length);
	}

	locA = dis + min;
	locB = max - dis;
	if (control == true)
	{
		cout << A->getName() << "(d=" << locA << ",t=" << tick << ")" << endl;
		return locA;
	}
	else if (control == false)
	{
		cout << B->getName() << "(d=" << locB << ",t=" << tick << ")" << endl;
		return locB;
	}
	else
	{
		cout << "ERROR" << endl;
		exit(0);
	}
	//output();
	return locA;
}

void Seesaw::movement(Person* person, double t)
{
	Sleep(1000);
	control = true;
	motion(person, t);
	control = false;
	motion(person, t);
	tick++;
}


void Seesaw::output()
{
	cout << A->getName() << "(d=" << locA << ",t=" << tick << ")" << endl;
	cout << B->getName() << "(d=" << locB << ",t=" << tick << ")" << endl;
	tick++;
}