#include "calculator.hpp"

/*******************************************************************************************************************************************
 *************************************************************** INTERFACE *****************************************************************
 ******************************************************************************************************************************************/

/*
 * DESCRIPTION: Request to set the calculator type asynchronously.
 */
void Calculator::setType(std::string type, std::function<void(bool)> callback)
{
	ActiveObject::addEvent([this, type, callback]{
		_setType(type);
		callback(true);
	});
}

/*
 * DESCRIPTION: Request to set the calculator type synchronously.
 */
bool Calculator::setType(std::string type)
{
	std::promise<bool> promise;
	ActiveObject::addEvent([this, &promise, type]{
		_setType(type);
		promise.set_value(true);
	});
	return promise.get_future().get();
}

/*
 * DESCRIPTION: Request to get the calculator type asynchronously.
 */
void Calculator::getType(std::function<void(std::string)> callback)
{
	ActiveObject::addEvent([this, callback]{
		callback(_getType());
	});
}

/*
 * DESCRIPTION: Request to get the calculator type synchronously.
 */
std::string Calculator::getType()
{
	std::promise<std::string> promise;
	ActiveObject::addEvent([this, &promise]{
		promise.set_value(_getType());
	});
	return promise.get_future().get();
}

/*
 * DESCRIPTION: Request to add two integars synchronously.
 */
int Calculator::add(int firstNumber, int secondNumber)
{
	std::promise<int> promise;
	ActiveObject::addEvent([this, &promise, &firstNumber, &secondNumber]{
		promise.set_value(_add(firstNumber, secondNumber));
	});
	return promise.get_future().get();
}

/*
 * DESCRIPTION: Request to add two integars asynchronously.
 */
void Calculator::add(int firstNumber, int secondNumber, std::function<void(int result)> callback)
{
	ActiveObject::addEvent([this, firstNumber, secondNumber, callback]{
		callback(_add(firstNumber, secondNumber));
	});
}

/*
 * DESCRIPTION: Request to subtract the second integar from the first integar synchronously.
 */
int Calculator::subtract(int firstNumber, int secondNumber)
{
	std::promise<int> promise;
	ActiveObject::addEvent([this, &promise, &firstNumber, &secondNumber]{
		promise.set_value(_subtract(firstNumber, secondNumber));
	});
	return promise.get_future().get();
}

/*
 * DESCRIPTION: Request to subtract two integars asynchronously.
 */
void Calculator::subtract(int firstNumber, int secondNumber, std::function<void(int result)> callback)
{
	ActiveObject::addEvent([this, firstNumber, secondNumber, callback]{
		callback(_subtract(firstNumber, secondNumber));
	});
}

/*
 * DESCRIPTION: Request to multiply two integars synchronously.
 */
int Calculator::multiply(int firstNumber, int secondNumber)
{
	std::promise<int> promise;
	ActiveObject::addEvent([this, &promise, &firstNumber, &secondNumber]{
		promise.set_value(_multiply(firstNumber, secondNumber));
	});
	return promise.get_future().get();
}

/*
 * DESCRIPTION: Request to multiply two integars asynchronously.
 */
void Calculator::multiply(int firstNumber, int secondNumber, std::function<void(int result)> callback)
{
	ActiveObject::addEvent([this, firstNumber, secondNumber, callback]{
		callback(_multiply(firstNumber, secondNumber));
	});
}

/********************************************************************************************************************************************
 ******************************************************* PRIVATE MEMBER FUNCTIONS(S) ********************************************************
 *******************************************************************************************************************************************/

/*
 * DESCRIPTION: Returns the type of the calculator synchronously.
 */
std::string Calculator::_getType()
{
	return _type;
}

/*
 * DESCRIPTION: Sets the type of the calculator synchronously.
 */
bool Calculator::_setType(std::string type)
{
	_type = type;
   	return true;
}

/*
 * DESCRIPTION: Adds two integars synchronously.
 */
int Calculator::_add(int firstNumber, int secondNumber)
{
	return firstNumber + secondNumber;
}

/*
 * DESCRIPTION: Subtracts the second integar from the first integar synchronously.
 */
int Calculator::_subtract(int firstNumber, int secondNumber)
{
	return firstNumber - secondNumber;
}

/*
 * DESCRIPTION: Multiplies two integars synchronously.
 */
int Calculator::_multiply(int firstNumber, int secondNumber)
{
	return firstNumber * secondNumber;
}