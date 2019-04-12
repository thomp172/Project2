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
	semB = new Semaphore(1);
	semC = new Semaphore(1);
	length = max - min;
	tick = 0;
	count = 0;
	int time1 = calculate(A, min);
	int time2 = calculate(B,max);
	count = (time1 + time2) * 10;
	//thread creation
	locA = min;
	locB = max;
	int j, k;
	again = true;
	/*thread thrT = thread(&Seesaw::time, this);
	thrT.join();*/
	for (int i=0; i<10; i++)//repeat 10 times
	{
		thread thrA = thread(&Seesaw::turnA, this, time1);
		thrA.join();
		thread thrB = thread(&Seesaw::turnB, this, time2);
		thrB.join();
	}
	again = false;
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
	for (int j = 0; j < (2 * time1); j++)
	{
		turnAMotion(true, j);
		cout << A->getName() << "(d=" << locA << ",t=" << tick << ")" << endl;
		cout << B->getName() << "(d=" << locB << ",t=" << tick << ")" << endl;
		tick++;
	}
	semA->signal();
}
void Seesaw::turnB(double time2)
{
	semA->wait();
	for (int j = 0; j < (2 * time2); j++)
	{
		turnBMotion(true, j);
		cout << A->getName() << "(d=" << locA << ",t=" << tick << ")" << endl;
		cout << B->getName() << "(d=" << locB << ",t=" << tick << ")" << endl;
		tick++;
	}
	semA->signal();
}

void Seesaw::time()
{
	while (again = true)
	{
		semC->wait();
		cout << A->getName() << "(d=" << locA << ",t=" << tick << ")" << endl;
		cout << B->getName() << "(d=" << locB << ",t=" << tick << ")" << endl;
		Sleep(1000);
		tick++;
		semC->signal();
	}
}
void Seesaw::turnAMotion(bool up, double t)
{
	double a, b, dis, disNew;
	int round;
	dis = A->getSpeed() * t;
	if ((dis >= 0) && (dis <= length))
	{
		disNew = dis;
	}
	else if (dis > length)
	{
		round = (int)dis;
		disNew = length - (round % length);
	}
	else if (dis < 0)
	{
		round = (int)dis;
		disNew = abs(round % length);
	}
	locA = disNew + min;
	locB = max - disNew;
}

void Seesaw::turnBMotion(bool up, double t)
{
	//Wilma begins at 7 ft
	double a, b, dis, disNew;
	int round;
	dis = B->getSpeed() * t;
	if ((dis >= 0) && (dis <= length))
	{
		disNew = dis;
	}
	else if (dis > length)
	{
		round = (int)dis;
		disNew = length - (round % length);
	}
	else if (dis < 0)
	{
		round = (int)dis;
		disNew = abs(round % length);
	}
	//cout << B->getName() << "(d=" << disNew << ",t=" << tick << ")" << endl;
	locB = disNew + min;
	locA = max - disNew;
}