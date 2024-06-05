#include <iostream>
#include "Calculator.hpp"
#include <functional>
#include <thread>

int main()
{
	Calculator calculator;

	// obj.setType("Casio"); // Set the type
	// std::cout << obj.getType() << std::endl; // Get the type and print it

	// obj.setType("Casio", [&obj](bool result){
	// 	if(result)
	// 	{
	// 		std::cout << "Type is set" << std::endl;
	// 		obj.getType([](std::string type){
	// 			std::cout << "Type is " << type << std::endl;
	// 		});
	// 	}
	// 	else
	// 		std::cout << "Type is unset" << std::endl;
	// });

	// obj.setType("Casio"); // Set the type
	// obj.getType([](std::string type){
	// 	std::cout << "Type is " << type << std::endl;
	// });

	calculator.setType("Casio", [&calculator](bool result){});
	std::cout << "Type is " << calculator.getType() << std::endl;

	std::cout << calculator.add(3, 2) << std::endl;
	std::cout << calculator.subtract(3, 2) << std::endl;
	std::cout << calculator.multiply(3, 2) << std::endl;

	std::cout << std::endl;

	calculator.add(6, 4, [](int result){
		std::cout << result << std::endl;
	});

	
	calculator.subtract(6, 4, [](int result){
		std::cout << result << std::endl;
	});

	
	calculator.multiply(6, 4, [](int result){
		std::cout << result << std::endl;
	});

	std::this_thread::sleep_for(std::chrono::seconds(5));
	return 0;
}