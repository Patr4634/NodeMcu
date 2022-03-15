#pragma once
#include "Light.h"

class Light;

class State
{
public:
	virtual void Enter(Light* light) = 0;
	virtual void Execute(Light* light) = 0;
	virtual void Exit(Light* light) = 0;
};