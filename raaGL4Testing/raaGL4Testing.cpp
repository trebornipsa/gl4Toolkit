// raaGL4Testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>

#include <raaGL4RenderTools/raaVector4T.h>
#include <raaGL4RenderTools/raaMatrix4T.h>

void printVec(raaGL4::raaVector4fv &v)
{
	std::cout << v.value(0) << ", " << v.value(1) << ", " << v.value(2) << ", " << v.value(3);
}

int main()
{
	raaGL4::raaVector4fv v0(2.0f, 3.0f, 1.0f);
	raaGL4::raaVector4fv v1(2.0f, 2.0f, 2.0f);
	raaGL4::raaVector4fv v2(1.0f,43.0f, 2.0f);
	raaGL4::raaMatrix4fv m0;

	m0.scale(v1);

	std::cout << "v0 -> "; printVec(v0); std::cout << std::endl;
	std::cout << "v1 -> "; printVec(v1); std::cout << std::endl;
	std::cout << "v2 -> "; printVec(v2); std::cout << std::endl;

	v0 = v0 * m0;
	std::cout << "v0 -> "; printVec(v0); std::cout << std::endl;

	_getch();
    return 0;
}

