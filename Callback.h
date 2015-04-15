#pragma once

#include <functional>

using namespace std;

/*
To create a callback just call ctor: Callback cb(myCallbackFunction, arg1, arg2, arg3, etc...)
In order to call an object's method do the following:
ObjectClass * o = new ObjectClass();
Callback cb(&ObjectClass::myMethod, o, ... argument list for method myMethod ...);
then cb.call(optional data ptr) will call myCallbackFunction with all the arguments given in the ctor
myCallbackFunction should always have at least 1 void* parameter and it should be the last
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
		_cb = bind(args..., placeholders::_1);
	}

	/* one can give a ptr to data to forward to the callback as last argument */
	void call(void* = nullptr) const;

private:
	function<void(void*)> _cb;

};