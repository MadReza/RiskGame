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
	void attach(Observer *observer);
	void detach(Observer *observer);
    void notify();
};
