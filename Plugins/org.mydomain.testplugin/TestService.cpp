/*
 * TestService.cpp
 *
 *  Created on: Apr 7, 2014
 *      Author: christiana
 */

#include "TestService.h"
#include <iostream>

TestService::~TestService()
{
}

void TestStandalone::printStuff()
{
	std::cout << "TestStandalone::printStuff()" << std::endl;
}

void TestStandalone::printFromBackend()
{
	std::cout << "TestStandalone::printFromBackend()" << std::endl;
}

