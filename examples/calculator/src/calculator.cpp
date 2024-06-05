#include "Calculator.hpp"

/*******************************************************************************************************************************************
 *************************************************************** INTERFACE *****************************************************************
 ******************************************************************************************************************************************/

/*
 * DESCRIPTION: Request to set the calculator type asynchronously.
 */
void Calculator::setType(std::string type, std::function<void(bool)> callback)
{
	ActiveObject::addEvent<bool>([this, type]() -> bool {
		return _setType(type);
	}, callback);
}

/*
 * DESCRIPTION: Request to set the calculator type synchronously.
 */
bool Calculator::setType(std::string type)
{
	return ActiveObject::addEvent<bool>([this, type]() -> bool {
		return _setType(type);
	});
}

/*
 * DESCRIPTION: Request to get the calculator type asynchronously.
 */
void Calculator::getType(std::function<void(std::string)> callback)
{
	ActiveObject::addEvent<std::string>([this]() -> std::string {
		return _getType();
	}, callback);
}
	
/*
 * DESCRIPTION: Request to get the calculator type synchronously.
 */
std::string Calculator::getType()
{
	return ActiveObject::addEvent<std::string>([this]() -> std::string {
		return _getType();
	});
}
	
/*
 * DESCRIPTION: Request to add two integars asynchronously.
 */
int Calculator::add(int firstNumber, int secondNumber)
{
	return ActiveObject::addEvent<int>([this, firstNumber, secondNumber]() -> int {
		return _add(firstNumber, secondNumber);
	});
}

/*
 * DESCRIPTION: Request to add two integars synchronously.
 */
void Calculator::add(int firstNumber, int secondNumber, std::function<void(int result)> callback)
{
	ActiveObject::addEvent<int>([this, firstNumber, secondNumber]() -> int {
		return _add(firstNumber, secondNumber);
	}, callback);
}
	
/*
 * DESCRIPTION: Request to subtract the second integar from the first integar synchronously.
 */
int Calculator::subtract(int firstNumber, int secondNumber)
{
	return ActiveObject::addEvent<int>([this, firstNumber, secondNumber]() -> int {
		return _subtract(firstNumber, secondNumber);
	});
}

/*
 * DESCRIPTION: Request to subtract two integars asynchronously.
 */
void Calculator::subtract(int firstNumber, int secondNumber, std::function<void(int result)> callback)
{
	ActiveObject::addEvent<int>([this, firstNumber, secondNumber]() -> int {
		return _subtract(firstNumber, secondNumber);
	}, callback);
}

/*
 * DESCRIPTION: Request to multiply two integars synchronously.
 */
int Calculator::multiply(int firstNumber, int secondNumber)
{
	return ActiveObject::addEvent<int>([this, firstNumber, secondNumber]() -> int {
		return _multiply(firstNumber, secondNumber);
	});
}

/*
 * DESCRIPTION: Request to multiply two integars asynchronously.
 */
void Calculator::multiply(int firstNumber, int secondNumber, std::function<void(int result)> callback)
{
	ActiveObject::addEvent<int>([this, firstNumber, secondNumber]() -> int {
		return _multiply(firstNumber, secondNumber);
	}, callback);
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