#include "Seesaw.h"
#include <thread>

Seesaw::Seesaw()
{
	Person* A = new Person("Jane",1);
	Person* B = new Person("John", 2);
	max = 10;
	min = 0;
	init();
}
Seesaw::Seesaw(Person theA, Person theB, double theMax, double theMin)
{
	A = theA;
	B = theB;
	max = theMax;
	min = theMin;
	init();
}
void Seesaw::init()
{
	//semaphore
	sem = CreateSemaphore(NULL, MAX_SEM_COUNT, MAX_SEM_COUNT, NULL);
	if (sem == NULL)
	{
		cout << "ERROR" << endl;
		exit(0);
	}
	//thread creation
	thread thrA = thread(&Seesaw::turnA, this);

}

//threads
void Seesaw::turnA()
{

}