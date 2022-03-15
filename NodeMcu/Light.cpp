#include "Light.h"
#include "LightStates.h"

Light::Light(int pin):Status(false)
{
	this->pin = pin;
	currentState = LightOff::Instance();
}

void Light::ChangeState(State* newState)
{
	currentState->Exit(this);
	currentState = newState;
	currentState->Enter(this);
}

void Light::Update()
{
	if (currentState)
	{
		currentState->Execute(this);
	}
}
