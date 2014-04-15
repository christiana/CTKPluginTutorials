/*
 * TestServiceImpl.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: christiana
 */

#include "Backend.h"

#include "TestServiceImpl.h"

#include <iostream>

TestServiceImpl::TestServiceImpl()
{
	std::cout << "TestService::TestService() called" << std::endl;
}

TestServiceImpl::~TestServiceImpl()
{
}

QString TestServiceImpl::getCustomString() const
{
	std::cout << "TestServiceImpl::getCustomString() called" << std::endl;

	Backend().foo();

	return "TestServiceImpl::getCustomString() content";
}
