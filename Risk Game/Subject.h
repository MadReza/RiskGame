#pragma once
#include <vector>
#include <algorithm>
#include "Observer.h"

using std::vector;

class Subject {
private:
	vector<Observer*> observers;

public:
	~Subject();
	void Attach(Observer *observer);
	void Detach(Observer *observer);
    void Notify();
};
