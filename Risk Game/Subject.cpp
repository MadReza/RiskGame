#include "Subject.h"

Subject::~Subject()
{
	for each (Observer* observer in observers)
	{
		delete observer;
	}
}

void Subject::Attach(Observer *observer){
	observers.push_back(observer);
}

void Subject::Detach(Observer *observer){
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Subject::Notify(){
	for (vector<Observer*>::const_iterator iter = observers.begin(); iter != observers.end(); ++iter)
    {
        if(*iter != 0)
        {
            (*iter)->Update();
        }
    }
}
