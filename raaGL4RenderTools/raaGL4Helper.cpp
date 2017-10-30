#include <windows.h>
#include <gl/glew.h>
#include <gl/gl.h>

#include "raaGL4Helper.h"



raaGL4Helper::raaGL4Helper()
{
}

void raaGL4Helper::uniform4V(int iLocation, unsigned iCount, float* pValue)
{
	glUniform4fv(iLocation, iCount, pValue);
}

void raaGL4Helper::uniformMat4v(int iLocation, unsigned uiCount, bool bTranspose, float* pValue)
{
	glUniformMatrix4fv(iLocation, uiCount, bTranspose, pValue);
}

void raaGL4Helper::uniformMat4v(int iLocation, unsigned uiCount, bool bTranspose, double* pValue)
{
	glUniformMatrix4dv(iLocation, uiCount, bTranspose, pValue);
}

void raaGL4Helper::uniform4V(int iLocation, unsigned iCount, double* pValue)
{
	glUniform4dv(iLocation, iCount, pValue);
}

void raaGL4Helper::uniform1(int iLocation, unsigned& val)
{
	glUniform1ui(iLocation, val);
}

void raaGL4Helper::uniform1(int iLocation, int& val)
{
	glUniform1i(iLocation, val);
}

void raaGL4Helper::uniform1(int iLocation, float& val)
{
	glUniform1f(iLocation, val);

}

void raaGL4Helper::uniform1(int iLocation, double& val)
{
	glUniform1d(iLocation, val);

}

raaGL4Helper::~raaGL4Helper()
{
}
