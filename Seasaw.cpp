//#include "Seesaw.h"
#include "pch.h"

Seesaw::Seesaw()
{
	Person* A = new Person("Jane", 1);
	Person* B = new Person("John", 2);
	max = 10;
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
	tick = 0;
	calculate(A);
	calculate(B);
	//thread creation
	for (int i = 0; i < 10; i++)
	{
		thread thrA = thread(&Seesaw::turnA, this, tick);
		thread thrB = thread(&Seesaw::turnB, this, tick);
		tick = time();
		thrA.join();
		thrB.join();
	}
}

void Seesaw::calculate(Person *person)
{
	double a, b, c;
	double time1, time2, timeFinal;
	a = (-1) * GRAVITY / 2;
	b = (-1) * person->getSpeed();
	c = max - min; //top height
	time1 = (-b + sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
	time2 = (-b - sqrt(pow(b, 2) - (4 * a * c))) / (2 * a);
	if ((time1 > 0) && (time1 < time2))
		timeFinal = time1;
	else if (time2 > 0)
		timeFinal = time2;
	else
	{
		cout << "Time error" << endl;
		exit(0);
	}
	//person reaches max height at timeFinal
	cout << person->getName() << " reaches max height at " << timeFinal << " seconds." << endl;

}

//threads
void Seesaw::turnA(double t)
{
	semA->wait();
	//Fred begins at 1 ft
	turnAMotion(true, t);
	turnAMotion(false, t);
	semA->signal();
}
void Seesaw::turnB(double t)
{
	semA->wait();
	//Wilma begins at 7ft
	turnBMotion(false, t);
	turnBMotion(true, t);

	semA->signal();
}

double Seesaw::time()
{
	semB->wait();
	cout << A->getName() << "(d=" << locA << ",t=" << tick << ")" << endl;
	cout << B->getName() << "(d=" << locB << ",t=" << tick << ")" << endl;
	Sleep(1000);
	tick++;
	semB->signal();
	return tick;
}
void Seesaw::turnAMotion(bool up, double t)
{
	double a, b, dis, disNew;
	int round;
	a = A->getSpeed();
	b = GRAVITY / 2;
	dis = a * t + (b * pow(t, 2)) - min;
	if (up == false)
	{
		a = (-1) * a;
		b = (-1) * b;
		dis = max + a * t + (b * pow(t, 2));
	}
	if ((dis >= min) && (dis <= max))
	{
		disNew = dis;
	}
	else if (dis > max)
	{
		round = (int)dis;
		disNew = max - (round % max);
	}
	else if (dis < min)
	{
		round = (int)dis;
		disNew = min + abs(round % max);
	}
	locA = disNew + min;
	locB = max - disNew;
}

void Seesaw::turnBMotion(bool up, double t)
{
	//Wilma begins at 7 ft
	double a, b, dis, disNew;
	int round;
	a = B->getSpeed();
	b = GRAVITY / 2;
	dis = a * t + (b * pow(t, 2)) - min;
	if (up == false)
	{
		a = (-1) * a;
		b = (-1) * b;
		dis = max + a * t + (b * pow(t, 2));
	}
	if ((dis >= min) && (dis <= max))
	{
		disNew = dis;
	}
	else if (dis > max)
	{
		round = (int)dis;
		disNew = max - (round % max);
	}
	else if (dis < min)
	{
		round = (int)dis;
		disNew = min + abs(round % max);
	}
	//cout << B->getName() << "(d=" << disNew << ",t=" << tick << ")" << endl;
	locB = disNew + min;
	locA = max - disNew;
}