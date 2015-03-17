#pragma once

#include <functional>

using namespace std;

/*
To create a callback just call ctor: Callback cb(myCallbackFunction, arg1, arg2, arg3, etc...)
then cb.call() will call myCallbackFunction with all the arguments given in the ctor
*/
class Callback
{
public:

	/*
	Need to be inline because it is a template ctor 
	see: http://stackoverflow.com/questions/644397/c-class-with-template-cannot-find-its-constructor
	*/
	template<typename ...Args>
	Callback( Args... args)
	{
		_cb = bind(args...);
	}

	void call() const;

private:
	function<void()> _cb;

};