#pragma once

class Foo
{
public:
	int member_int = 50;

	void NonConstFunction()
	{
		member_int = 51;
	}

	// puting const at the end of a function is a way of telling the compiler and other programmers that this function will not change the 
	// internal state of the class, aka modify member variables.
	int ConstFunction() const
	{
		// Illegal
		//member_int = 51;

		return member_int * 2;
	}
};