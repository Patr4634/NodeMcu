#pragma once
#include "State.h"

class State;

class Light
{
public:
	Light(int pin);
	void Update();
	void ChangeState(State* newState);

	int Pin() const { return pin; }
	bool Status;

private:
	int pin;
	State* currentState;
};