#ifndef _CALCULATOR_HPP_
#define _CALCULATOR_HPP_

#include "activeobject.hpp"

#include <string>
#include <future>
#include <map>

// Calculator
class Calculator : public ActiveObject
{
    /*******************************************************************************************************************************************
     ************************************************************** CONSTRUCTOR(S) *************************************************************
     ******************************************************************************************************************************************/

public:

	Calculator() = default;

	/*******************************************************************************************************************************************
     *************************************************************** DESTRUCTOR ****************************************************************
     ******************************************************************************************************************************************/

public:

	~Calculator() = default;

	/*******************************************************************************************************************************************
     *************************************************************** INTERFACE *****************************************************************
     ******************************************************************************************************************************************/

public:

	/*
	 * DESCRIPTION: Request to set the calculator type asynchronously.
	 */
	void setType(std::string type, std::function<void(bool)> callback);

	/*
	 * DESCRIPTION: Request to set the calculator type synchronously.
	 */
	bool setType(std::string type);

	/*
	 * DESCRIPTION: Request to get the calculator type asynchronously.
	 */
	void getType(std::function<void(std::string)> callback);
	
	/*
	 * DESCRIPTION: Request to get the calculator type synchronously.
	 */
	std::string getType();
	
	/*
	 * DESCRIPTION: Request to add two integars asynchronously.
	 */
	int add(int firstNumber, int secondNumber);

	/*
	 * DESCRIPTION: Request to add two integars synchronously.
	 */
	void add(int firstNumber, int secondNumber, std::function<void(int result)> callback);
	
	/*
	 * DESCRIPTION: Request to subtract the second integar from the first integar synchronously.
	 */
	int subtract(int firstNumber, int secondNumber);

	/*
	 * DESCRIPTION: Request to subtract two integars asynchronously.
	 */
	void subtract(int firstNumber, int secondNumber, std::function<void(int result)> callback);

	/*
	 * DESCRIPTION: Request to multiply two integars synchronously.
	 */
	int multiply(int firstNumber, int secondNumber);

	/*
	 * DESCRIPTION: Request to multiply two integars asynchronously.
	 */
	void multiply(int firstNumber, int secondNumber, std::function<void(int result)> callback);

	/********************************************************************************************************************************************
     ******************************************************* PRIVATE MEMBER FUNCTIONS(S) ********************************************************
     *******************************************************************************************************************************************/

private:

	/*
 	* DESCRIPTION: Returns the type of the calculator synchronously.
 	*/
	std::string _getType();

	/*
 	* DESCRIPTION: Sets the type of the calculator synchronously.
	 */
	bool _setType(std::string type);

	/*
	 * DESCRIPTION: Adds two integars synchronously.
	 */
	int _add(int firstNumber, int secondNumber);

	/*
	 * DESCRIPTION: Subtracts the second integar from the first integar synchronously.
	 */
	int _subtract(int firstNumber, int secondNumber);

	/*
	 * DESCRIPTION: Multiplies two integars synchronously.
	 */
	int _multiply(int firstNumber, int secondNumber);

	/*******************************************************************************************************************************************
     ********************************************************* PRIVATE DATA MEMBER(S) **********************************************************
     ******************************************************************************************************************************************/

private:

	/*
	 * DESCRIPTION: Type of the calculator.
	 */
	std::string _type;
};

#endif
