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
Seesaw::~Seesaw()
{
	delete A;
	delete B;
	delete semA;
	delete semB;
}

void Seesaw::init()
{
	cout << "begin simulation" << endl;
	//semaphore
	semA = new Semaphore(1);
	semB = new Semaphore();
	tick = 0;
	double h = max - min;
	length = (int) h;
	double time1 = calculate(A, min);
	double time2 = calculate(B,max);
	thread thrA = thread(&Seesaw::fred, this, time1, time2);
	thread thrB = thread(&Seesaw::wilma, this, time1, time2);
	thrA.join();
	thrB.join();
}

void Seesaw::fred(double time1, double time2)
{
	double loc;
	int j, k,m;
	for (m = 0; m < 10; m++)
	{
		
		for (j = 0; j < time1; j++)
		{
			loc = up(A, j, true);
			semA->wait();
			cout << A->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
			semB->signal();
		}
		for (k = 0; k < time2; k++)
		{
			loc = up(B, k, false);
			semA->wait();
			cout << A->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
			semB->signal();
		}
	}
}
void Seesaw::wilma(double time1, double time2)
{
	double loc;
	int j, k, m;
	for (m = 0; m < 10; m++)
	{
		for (j = 0; j < time1; j++)
		{
			loc = up(A, j, false);
			semB->wait();
			cout << B->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
			Sleep(1000);
			tick++;
			semA->signal();
		}
		for (k = 0; k < time2; k++)
		{
			loc = up(B, k, true);
			semB->wait();
			cout << B->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
			Sleep(1000);
			tick++;
			semA->signal();
		}
	}
}
double Seesaw::up(Person* person, double t, bool c)
{
	int round;
	double loc;
	double speed = person->getSpeed();
	if (c == false)
	{
		speed = (-1) * speed;
	}
	double dis = person->getSpeed() * t;
	if ((dis < 0) || (dis > length))
	{
		round = (int)dis;
		dis = abs(round % length);
	}

	loc = dis + min;
	if (c == false)  //falling
		loc = max - dis;
	return loc;
}

double Seesaw::calculate(Person *person, double c)
{
	double time;
	time = length/person->getSpeed();
	return time;
}
