#include "pch.h"

Seesaw::Seesaw() //default
{
	A = new Person("Jane", 1);
	B = new Person("John", 2);
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
	semB = new Semaphore();//default initializes at 0
	tick = 0;
	double lengthDbl = max - min; //find length
	length = (int) lengthDbl; //lengthDbl will need to be used as an int later
	double time1 = length / A->getSpeed();
	double time2 = length / B->getSpeed();
	//initialize threads to be joined in main() located in CPSC380Project2.cpp
	thrA = thread(&Seesaw::fred, this, time1, time2);
	thrB = thread(&Seesaw::wilma, this, time1, time2);
}

void Seesaw::fred(double time1, double time2) //Person A
{
	double loc;
	int j, k,m;
	for (m = 0; m < 10; m++) //repeat 10 times
	{
		
		for (j = 0; j < time1; j++) //each of Person A's seconds
		{
			loc = up(A, j, true); //A in power
			semA->wait();
			cout << A->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
			semB->signal();
		}
		for (k = 0; k < time2; k++) //each of Person B's seconds
		{
			loc = up(B, k, false); //A not in power
			semA->wait();
			cout << A->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
			semB->signal();
		}
	}
	loc = up(B, k, false); //A not in power
	semA->wait();
	cout << A->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
	semB->signal();
}
void Seesaw::wilma(double time1, double time2) //Person B
{
	double loc;
	int j, k, m;
	for (m = 0; m < 10; m++) //repeat 10 times
	{
		for (j = 0; j < time1; j++) //each of Person A's seconds
		{
			loc = up(A, j, false); //B not in power
			semB->wait();
			cout << B->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
			Sleep(1000);
			tick++;
			semA->signal();
		}
		for (k = 0; k < time2; k++) //each of Person B's seconds
		{
			loc = up(B, k, true); //B in power
			semB->wait();
			cout << B->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
			Sleep(1000);
			tick++;
			semA->signal();
		}
	}
	loc = up(B, k, true); //B in power
	semB->wait();
	cout << B->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
	Sleep(1000);
	semA->signal();
}
double Seesaw::up(Person* person, double t, bool c)
{
	int round;
	double loc;
	double dis = person->getSpeed() * t;
	if ((dis < 0) || (dis > length))
	{
		round = (int)dis;
		dis = abs(round % length);
	}
	
	loc = dis + min; //upward
	if (c == false)  //falling
		loc = max - dis;
	return loc;
}
