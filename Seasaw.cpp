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
	sem = new Semaphore(1);
	//thread creation
	for (int i = 0; i < 10; i++)
	{
		thread thrA = thread(&Seesaw::turn, this, A);
		thread thrB = thread(&Seesaw::turn, this, B);
		thrA.join();
		thrB.join();
	}

}

//threads
void Seesaw::turn(Person* person)
{
	sem->wait();
	cout << person->getName() << " pushes up" << endl;
	//Fred begins at 1 ft
	//set up quadratic
	double a, b, c;
	double time1, time2, timeReal;
	a = (-1) * person->getSpeed();
	b = GRAVITY / 2;
	c = max - min;
	//quadratic formula to find time
	time1 = ((-1) * b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	time2 = ((-1) * b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if ((time1 > 0) && (time1 < time2))
		timeReal = time1;
	else if (time2 > 0)
		timeReal = time2;
	else
	{
		cout << "ERROR: time" << endl;
		exit(0);
	}
	timeReal = timeReal * 1000; //1000 milliseconds
	int time = (int)timeReal; //convert to integer
	Sleep(time);
	cout << person->getName() << " reaches top" << endl;
	Sleep(time);
	cout << person->getName() << " lands" << endl;
	sem->signal();
}