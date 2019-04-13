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
	length = max - min;
	tick = 1;
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
		/*thread thrA = thread(&Seesaw::turnA, this, time1);
		thread thrB = thread(&Seesaw::turnB, this, time2);
		thrA.join();
		thrB.join();*/
		takeTurns(time1, time2);
	}
}

void Seesaw::takeTurns(double time1, double time2)
{
	cout << A->getName() << " pushes off the ground" << endl;
	for (int j = 1; j <= time1; j++)
	{
		thread thrA = thread(&Seesaw::fred, this, j, true);
		thread thrB = thread(&Seesaw::wilma, this, j, false);
		thrA.join();
		thrB.join();
	}
	cout << B->getName() << " pushes off the ground" << endl;
	for (int k = 1; k <= time2; k++)
	{
		thread thrA = thread(&Seesaw::fred, this, k, false);
		thread thrB = thread(&Seesaw::wilma, this, k, true);
		thrA.join();
		thrB.join();
	}
}
void Seesaw::fred(double t, bool c)
{
	semA->wait();
	double loc;
	if (c == true)
		loc = up(A, t, c);
	else
		loc = up(B, t, c);
	cout << A->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
	semB->signal();
}
void Seesaw::wilma(double t, bool c)
{
	semB->wait();
	double loc;
	if (c == false)
		loc = up(A, t, c);
	else
		loc = up(B, t, c);
	cout << B->getName() << "(d=" << loc << ",t=" << tick << ")" << endl;
	Sleep(1000);
	tick++;
	semA->signal();
}
double Seesaw::up(Person* person, double t, bool c)
{
	int round;
	double speed = person->getSpeed();
	if ((c == false))
	{
		speed = (-1) * speed;
	}
	double dis = person->getSpeed() * t;
	if ((dis < 0) || (dis > length))
	{
		round = (int)dis;
		dis = abs(round % length);
	}

	locA = dis + min;
	if (c == false)  //falling
		locA = max - dis;
	//locB = max - dis;
	//cout << person->getName() << "(d=" << locA << ",t=" << tick << ")" << endl;
	return locA;
	//output();
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
void Seesaw::turnA(double time)
{
	semA->wait();
	cout << A->getName() << " pushes off the ground" << endl;
	for (int j = 1; j <= time; j++)
	{
		movement(A, j);
	}
	semB->signal();
}
void Seesaw::turnB(double time)
{
	semB->wait();
	cout << B->getName() << " pushes off the ground" << endl;
	for (int j = 1; j <= time; j++)
	{
		movement(B, j);
	}
	semA->signal();
}

void Seesaw::motion(Person *person, double t)
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
	}
	else if (control == false)
	{
		cout << B->getName() << "(d=" << locB << ",t=" << tick << ")" << endl;
	}
	else
	{
		cout << "ERROR" << endl;
		exit(0);
	}
	//output();
}

void Seesaw::movement(Person* person, double t)
{
	Sleep(1000);
	control = true;
	motion(person, t); //output Person A location based on Person person speed
	control = false;
	motion(person, t); //output Person B location based on Person person speed
	tick++;
}


void Seesaw::output()
{
	cout << A->getName() << "(d=" << locA << ",t=" << tick << ")" << endl;
	cout << B->getName() << "(d=" << locB << ",t=" << tick << ")" << endl;
	tick++;
}