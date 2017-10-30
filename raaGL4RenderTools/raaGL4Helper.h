#pragma once
class raaGL4Helper
{
public:
	raaGL4Helper();
	virtual ~raaGL4Helper();

	void uniform1(int iLocation, unsigned int &val);
	void uniform1(int iLocation, int &val);
	void uniform1(int iLocation, float &val);
	void uniform1(int iLocation, double &val);
	void uniform4V(int iLocation, unsigned int iCount, float* pValue);
	void uniform4V(int iLocation, unsigned int iCount, double* pValue);
	void uniformMat4v(int iLocation, unsigned int uiCount, bool bTranspose, float *pValue);
	void uniformMat4v(int iLocation, unsigned int uiCount, bool bTranspose, double *pValue);


};

