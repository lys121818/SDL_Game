#pragma once

//==================================================================================================//
/// STATE
/// A general purpose state interface.
//==================================================================================================//

class State
{
public:
	virtual ~State();

	virtual void Enter() {}
	virtual void Update(double) {}
	virtual void Exit() {}
};