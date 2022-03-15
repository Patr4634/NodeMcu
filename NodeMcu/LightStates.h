#pragma once
#include "State.h"
#include "Light.h"

class LightOff : public State
{
public:

	static LightOff* Instance();
	virtual void Enter(Light* light);
	virtual void Execute(Light* light);
	virtual void Exit(Light* light);

private:
	LightOff() {}
	LightOff(const LightOff& other);
	LightOff& operator=(const LightOff& other);
};

class LightOn : public State
{
public:

	static LightOn* Instance();
	virtual void Enter(Light* light);
	virtual void Execute(Light* light);
	virtual void Exit(Light* light);

private:
	LightOn() {}
	LightOn(const LightOn& other);
	LightOn& operator=(const LightOn& other);
};

class LightBlink : public State
{
public:

	static LightBlink* Instance();
	virtual void Enter(Light* light);
	virtual void Execute(Light* light);
	virtual void Exit(Light* light);

private:
	LightBlink() {}
	LightBlink(const LightBlink& other);
	LightBlink& operator=(const LightBlink& other);
};