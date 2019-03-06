#pragma once
#include "stdlibs.h"

class Observer : public std::enable_shared_from_this<Observer> {
public:
	virtual ~Observer() {};
	virtual void Notify() = 0;
};

class Subject {
	std::vector<std::shared_ptr<Observer>> observers;

public:
	void addObserver(std::shared_ptr<Observer> observer) {
		this->observers.push_back(observer);
	}

	void removeObserver(std::shared_ptr<Observer> observer) {
		std::vector<std::shared_ptr<Observer>>::iterator to_remove = observers.begin();
		for (; to_remove != this->observers.end(); ++to_remove) {
			if (*to_remove == observer) {
				this->observers.erase(to_remove);
				break;
			}
		}
	}

	void notifyObservers() {
		for (auto o : this->observers) {
			if (o != nullptr)
				o->Notify();
		}
	}
};