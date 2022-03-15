#include <Arduino.h>
#include "LightStates.h"

LightOff* LightOff::Instance()
{
	static LightOff instance;
	return &instance;
}

void LightOff::Enter(Light* light)
{
	light->Status = false;
}

void LightOff::Execute(Light* light)
{
	digitalWrite(light->Pin(), LOW);
}

void LightOff::Exit(Light* light)
{

}

LightOn* LightOn::Instance()
{
	static LightOn instance;
	return &instance;
}

void LightOn::Enter(Light* light)
{
	light->Status = true;
}

void LightOn::Execute(Light* light)
{
	digitalWrite(light->Pin(), HIGH);
}

void LightOn::Exit(Light* light)
{

}

LightBlink* LightBlink::Instance()
{
	static LightBlink instance;
	return &instance;
}

void LightBlink::Enter(Light* light)
{

}

void LightBlink::Execute(Light* light)
{
	light->Status = false;
	digitalWrite(light->Pin(), LOW);
	delay(500);
	light->Status = true;
	digitalWrite(light->Pin(), HIGH);
	delay(500);
}

void LightBlink::Exit(Light* light)
{

}