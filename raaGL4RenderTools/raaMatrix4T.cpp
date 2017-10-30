#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include "raaVector4T.h"
#include "raaMatrix4T.h"


#define PI 3.14159265358979323846 

template <class T>
raaGL4::raaMatrix4T<T>::raaMatrix4Exception::raaMatrix4Exception(unsigned uiCode) : m_uiCode(uiCode)
{}

template <class T>
unsigned raaGL4::raaMatrix4T<T>::raaMatrix4Exception::code()
{
	return m_uiCode;
}

template <class T>
raaGL4::raaMatrix4T<T>::raaMatrix4Containment::raaMatrix4Containment(unsigned uiContainmentType) : m_uiContainmentType(uiContainmentType)
{}

template <class T>
raaGL4::raaMatrix4T<T>::raaMatrix4Containment::raaMatrix4Containment(const raaMatrix4Containment& t) : m_uiContainmentType(t.m_uiContainmentType)
{}

template <class T>
bool raaGL4::raaMatrix4T<T>::raaMatrix4Containment::operator==(const raaMatrix4Containment& t) const 
{
	if (m_uiContainmentType == t.m_uiContainmentType) return true;
	return false;
}

template <class T>
bool raaGL4::raaMatrix4T<T>::raaMatrix4Containment::operator==(const unsigned t) const 
{
	if (m_uiContainmentType == t) return true;
	return false;
}

template <class T>
bool raaGL4::raaMatrix4T<T>::raaMatrix4Containment::operator!=(const raaMatrix4Containment& t) const 
{
	if (m_uiContainmentType != t.m_uiContainmentType) return true;
	return false;
}

template <class T>
bool raaGL4::raaMatrix4T<T>::raaMatrix4Containment::operator!=(const unsigned t) const 
{
	if (m_uiContainmentType != t) return true;
	return false;
}

template <class T>
const typename raaGL4::raaMatrix4T<T>::raaMatrix4Containment& raaGL4::raaMatrix4T<T>::raaMatrix4Containment::operator=(const raaMatrix4Containment& t) 
{
	m_uiContainmentType = t.m_uiContainmentType;
	return *this;
}

template <class T>
const typename raaGL4::raaMatrix4T<T>::raaMatrix4Containment& raaGL4::raaMatrix4T<T>::raaMatrix4Containment::operator=(const unsigned t) 
{
	m_uiContainmentType = t;
	return *this;
}

template <class T>
raaGL4::raaMatrix4T<T>::raaMatrix4Containment::operator unsigned() 
{
	return m_uiContainmentType;

}

template <class T>
raaGL4::raaMatrix4T<T>::raaMatrix4T(raaMatrix4Containment t, T* ptRawData) : m_Containment(raaMatrix4Containment::csm_uiContained), m_bDirtyInverse(true)
{
	
	if (m_Containment == raaMatrix4Containment::csm_uiContained)
	{
		m_ptValue = new T[16];
		if(ptRawData)
		{
			for (unsigned int i = 0; i < 16; i++) m_ptValue[i] = ptRawData[i];
		}
		else
		{
			for (int i = 0; i < 16; i++) m_ptValue[i] = 0.0;
			m_ptValue[0] = m_ptValue[5] = m_ptValue[10] = m_ptValue[15]=1.0;
		}
		update();
	}
	else
	{
		if (ptRawData)
		{
			m_ptValue = ptRawData;
			update();
		}
		else throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInputPtrException);
	}
}

template <class T>
raaGL4::raaMatrix4T<T>::raaMatrix4T(const raaMatrix4T<T>& t) : m_Containment(raaMatrix4Containment::csm_uiContained), m_bDirtyInverse(true)
{
	if(!t.m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInputPtrException);
	m_ptValue = new T[16];
	for (unsigned int i = 0; i < 16; i++) m_ptValue[i] = t.m_ptValue[i];
}

template <class T>
unsigned raaGL4::raaMatrix4T<T>::raaMatrix4Containment::value()
{
	return m_uiContainmentType;
}

template <class T>
const T* raaGL4::raaMatrix4T<T>::ptr() const
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	return m_ptValue;
}

template <class T>
const T raaGL4::raaMatrix4T<T>::operator[](unsigned uiIndex)
{
	if (uiIndex > 15) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiMatrixIndexOutOfBoundsException);
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);

	return m_ptValue[uiIndex];
}

template <class T>
raaGL4::raaMatrix4T<T>::operator const T*() const 
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	return m_ptValue;
}

template <class T>
std::string raaGL4::raaMatrix4T<T>::raaMatrix4Exception::msg()
{
	switch(m_uiCode)
	{
	case csm_uiInvalidInputPtrException:
		return "the input pointer is not valid";
	case csm_uiInvalidTypeException:
		return "invalid type for a matrix 4";
	case csm_uiInvalidInternalPtrException:
		return "the internal pointer is invalid";
	case csm_uiInvertDivisonByZeroException:
		return "inversion process has generated a determinant of zero";
	case csm_uiMatrixIndexOutOfBoundsException:
		return "the index provided to access the matrix data is greater than 15";
	case csm_uiMatrixInversionNotPossible:
		return "the requested matrix inversion is not possible";
	default:
		return "unknow exception code";
	}
}

template <class T>
raaGL4::raaMatrix4T<T>::~raaMatrix4T()
{
	for (raaMatrix4TStack::iterator it = m_Stack.begin(); it != m_Stack.end(); it++)
		delete[](*it);
}

template <class T>
const raaGL4::raaMatrix4T<T> raaGL4::raaMatrix4T<T>::identity()
{
	return raaMatrix4T<T>();
}

template <class T>
const raaGL4::raaMatrix4T<T>& raaGL4::raaMatrix4T<T>::operator=(const raaMatrix4T<T>& t) 
{
	if(!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	if(!t.m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInputPtrException);
	
	for (int i = 0; i < 16; i++) m_ptValue[i] = t.m_ptValue[i];
	update();
	dirtyInverse();

	return *this;

}

template <class T>
void raaGL4::raaMatrix4T<T>::copy(const raaMatrix4T<T>& t)
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	if (!t.m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInputPtrException);

	for (int i = 0; i < 16; i++) m_ptValue[i] = t.m_ptValue[i];
	update();
	dirtyInverse();
}



template <class T>
const raaGL4::raaMatrix4T<T> raaGL4::raaMatrix4T<T>::operator*(const raaMatrix4T<T>& t) 
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	if (!t.m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInputPtrException);

	unsigned int uiIndex = 0;
	raaMatrix4T<T> m;
#define A(row,col)  m_ptValue[(col<<2)+row]
#define B(row,col)  t.m_ptValue[(col<<2)+row]
#define P(row,col)  m.m_ptValue[(col<<2)+row]
	for (unsigned int i = 0; i < 4; i++) 
	{
		T ai0 = A(i, 0), ai1 = A(i, 1), ai2 = A(i, 2), ai3 = A(i, 3);
		P(i, 0) = ai0 * B(0, 0) + ai1 * B(1, 0) + ai2 * B(2, 0) + ai3 * B(3, 0);
		P(i, 1) = ai0 * B(0, 1) + ai1 * B(1, 1) + ai2 * B(2, 1) + ai3 * B(3, 1);
		P(i, 2) = ai0 * B(0, 2) + ai1 * B(1, 2) + ai2 * B(2, 2) + ai3 * B(3, 2);
		P(i, 3) = ai0 * B(0, 3) + ai1 * B(1, 3) + ai2 * B(2, 3) + ai3 * B(3, 3);
	}
#undef A
#undef B
#undef P
	return m;
}



template <class T>
void raaGL4::raaMatrix4T<T>::mult(const raaMatrix4T<T>& t)
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	if (!t.m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInputPtrException);

	unsigned int uiIndex = 0;
	raaMatrix4T<T> m;

#define A(row,col)  m_ptValue[(col<<2)+row]
#define B(row,col)  t.m_ptValue[(col<<2)+row]
#define P(row,col)  m.m_ptValue[(col<<2)+row]
	for (unsigned int i = 0; i < 4; i++)
	{
		T ai0 = A(i, 0), ai1 = A(i, 1), ai2 = A(i, 2), ai3 = A(i, 3);
		P(i, 0) = ai0 * B(0, 0) + ai1 * B(1, 0) + ai2 * B(2, 0) + ai3 * B(3, 0);
		P(i, 1) = ai0 * B(0, 1) + ai1 * B(1, 1) + ai2 * B(2, 1) + ai3 * B(3, 1);
		P(i, 2) = ai0 * B(0, 2) + ai1 * B(1, 2) + ai2 * B(2, 2) + ai3 * B(3, 2);
		P(i, 3) = ai0 * B(0, 3) + ai1 * B(1, 3) + ai2 * B(2, 3) + ai3 * B(3, 3);
	}
#undef A
#undef B
#undef P

	copy(m);
}

template <class T>
const raaGL4::raaMatrix4T<T> raaGL4::raaMatrix4T<T>::operator~() 
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	raaMatrix4T<T> m(*this);

	swapVals(m.m_ptValue[4], m.m_ptValue[1]);
	swapVals(m.m_ptValue[8], m.m_ptValue[2]);
	swapVals(m.m_ptValue[9], m.m_ptValue[6]);
	swapVals(m.m_ptValue[3], m.m_ptValue[12]);
	swapVals(m.m_ptValue[7], m.m_ptValue[13]);
	swapVals(m.m_ptValue[11], m.m_ptValue[14]);

	return m;
}

template <class T>
const raaGL4::raaMatrix4T<T> raaGL4::raaMatrix4T<T>::operator!() 
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
/*
	raaMatrix4T<T> m(*this);



	T det;

	m.m_ptValue[0] = m_ptValue[5] * m_ptValue[10] * m_ptValue[15] -m_ptValue[5] * m_ptValue[11] * m_ptValue[14] -m_ptValue[9] * m_ptValue[6] * m_ptValue[15] +m_ptValue[9] * m_ptValue[7] * m_ptValue[14] +m_ptValue[13] * m_ptValue[6] * m_ptValue[11] -m_ptValue[13] * m_ptValue[7] * m_ptValue[10];
	m.m_ptValue[4] = -m_ptValue[4] * m_ptValue[10] * m_ptValue[15] +m_ptValue[4] * m_ptValue[11] * m_ptValue[14] +m_ptValue[8] * m_ptValue[6] * m_ptValue[15] -m_ptValue[8] * m_ptValue[7] * m_ptValue[14] -m_ptValue[12] * m_ptValue[6] * m_ptValue[11] +m_ptValue[12] * m_ptValue[7] * m_ptValue[10];
	m.m_ptValue[8] = m_ptValue[4] * m_ptValue[9] * m_ptValue[15] -m_ptValue[4] * m_ptValue[11] * m_ptValue[13] -m_ptValue[8] * m_ptValue[5] * m_ptValue[15] +m_ptValue[8] * m_ptValue[7] * m_ptValue[13] +m_ptValue[12] * m_ptValue[5] * m_ptValue[11] -m_ptValue[12] * m_ptValue[7] * m_ptValue[9];
	m.m_ptValue[12] = -m_ptValue[4] * m_ptValue[9] * m_ptValue[14] +m_ptValue[4] * m_ptValue[10] * m_ptValue[13] +m_ptValue[8] * m_ptValue[5] * m_ptValue[14] -m_ptValue[8] * m_ptValue[6] * m_ptValue[13] -m_ptValue[12] * m_ptValue[5] * m_ptValue[10] +m_ptValue[12] * m_ptValue[6] * m_ptValue[9];
	m.m_ptValue[1] = -m_ptValue[1] * m_ptValue[10] * m_ptValue[15] +m_ptValue[1] * m_ptValue[11] * m_ptValue[14] +m_ptValue[9] * m_ptValue[2] * m_ptValue[15] -m_ptValue[9] * m_ptValue[3] * m_ptValue[14] -m_ptValue[13] * m_ptValue[2] * m_ptValue[11] +m_ptValue[13] * m_ptValue[3] * m_ptValue[10];
	m.m_ptValue[5] = m_ptValue[0] * m_ptValue[10] * m_ptValue[15] -m_ptValue[0] * m_ptValue[11] * m_ptValue[14] -m_ptValue[8] * m_ptValue[2] * m_ptValue[15] +m_ptValue[8] * m_ptValue[3] * m_ptValue[14] +m_ptValue[12] * m_ptValue[2] * m_ptValue[11] -m_ptValue[12] * m_ptValue[3] * m_ptValue[10];
	m.m_ptValue[9] = -m_ptValue[0] * m_ptValue[9] * m_ptValue[15] +m_ptValue[0] * m_ptValue[11] * m_ptValue[13] +m_ptValue[8] * m_ptValue[1] * m_ptValue[15] -m_ptValue[8] * m_ptValue[3] * m_ptValue[13] -m_ptValue[12] * m_ptValue[1] * m_ptValue[11] +m_ptValue[12] * m_ptValue[3] * m_ptValue[9];
	m.m_ptValue[13] = m_ptValue[0] * m_ptValue[9] * m_ptValue[14] -m_ptValue[0] * m_ptValue[10] * m_ptValue[13] -m_ptValue[8] * m_ptValue[1] * m_ptValue[14] +m_ptValue[8] * m_ptValue[2] * m_ptValue[13] +m_ptValue[12] * m_ptValue[1] * m_ptValue[10] -m_ptValue[12] * m_ptValue[2] * m_ptValue[9];
	m.m_ptValue[2] = m_ptValue[1] * m_ptValue[6] * m_ptValue[15] -m_ptValue[1] * m_ptValue[7] * m_ptValue[14] -m_ptValue[5] * m_ptValue[2] * m_ptValue[15] +m_ptValue[5] * m_ptValue[3] * m_ptValue[14] +m_ptValue[13] * m_ptValue[2] * m_ptValue[7] -m_ptValue[13] * m_ptValue[3] * m_ptValue[6];
	m.m_ptValue[6] = -m_ptValue[0] * m_ptValue[6] * m_ptValue[15] +m_ptValue[0] * m_ptValue[7] * m_ptValue[14] +m_ptValue[4] * m_ptValue[2] * m_ptValue[15] -m_ptValue[4] * m_ptValue[3] * m_ptValue[14] -m_ptValue[12] * m_ptValue[2] * m_ptValue[7] +m_ptValue[12] * m_ptValue[3] * m_ptValue[6];
	m.m_ptValue[10] = m_ptValue[0] * m_ptValue[5] * m_ptValue[15] -m_ptValue[0] * m_ptValue[7] * m_ptValue[13] -m_ptValue[4] * m_ptValue[1] * m_ptValue[15] +m_ptValue[4] * m_ptValue[3] * m_ptValue[13] +m_ptValue[12] * m_ptValue[1] * m_ptValue[7] -m_ptValue[12] * m_ptValue[3] * m_ptValue[5];
	m.m_ptValue[14] = -m_ptValue[0] * m_ptValue[5] * m_ptValue[14] +m_ptValue[0] * m_ptValue[6] * m_ptValue[13] +m_ptValue[4] * m_ptValue[1] * m_ptValue[14] -m_ptValue[4] * m_ptValue[2] * m_ptValue[13] -m_ptValue[12] * m_ptValue[1] * m_ptValue[6] +m_ptValue[12] * m_ptValue[2] * m_ptValue[5];
	m.m_ptValue[3] = -m_ptValue[1] * m_ptValue[6] * m_ptValue[11] +m_ptValue[1] * m_ptValue[7] * m_ptValue[10] +m_ptValue[5] * m_ptValue[2] * m_ptValue[11] -m_ptValue[5] * m_ptValue[3] * m_ptValue[10] -m_ptValue[9] * m_ptValue[2] * m_ptValue[7] +m_ptValue[9] * m_ptValue[3] * m_ptValue[6];
	m.m_ptValue[7] = m_ptValue[0] * m_ptValue[6] * m_ptValue[11] -m_ptValue[0] * m_ptValue[7] * m_ptValue[10] -m_ptValue[4] * m_ptValue[2] * m_ptValue[11] +m_ptValue[4] * m_ptValue[3] * m_ptValue[10] +m_ptValue[8] * m_ptValue[2] * m_ptValue[7] -m_ptValue[8] * m_ptValue[3] * m_ptValue[6];
	m.m_ptValue[11] = -m_ptValue[0] * m_ptValue[5] * m_ptValue[11] +m_ptValue[0] * m_ptValue[7] * m_ptValue[9] +m_ptValue[4] * m_ptValue[1] * m_ptValue[11] -m_ptValue[4] * m_ptValue[3] * m_ptValue[9] -m_ptValue[8] * m_ptValue[1] * m_ptValue[7] +m_ptValue[8] * m_ptValue[3] * m_ptValue[5];
	m.m_ptValue[15] = m_ptValue[0] * m_ptValue[5] * m_ptValue[10] -m_ptValue[0] * m_ptValue[6] * m_ptValue[9] -m_ptValue[4] * m_ptValue[1] * m_ptValue[10] +m_ptValue[4] * m_ptValue[2] * m_ptValue[9] +m_ptValue[8] * m_ptValue[1] * m_ptValue[6] -m_ptValue[8] * m_ptValue[2] * m_ptValue[5];

	det = m_ptValue[0] * m.m_ptValue[0] + m_ptValue[1] * m.m_ptValue[4] + m_ptValue[2] * m.m_ptValue[8] + m_ptValue[3] * m.m_ptValue[12];

	if (det == 0) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvertDivisonByZeroException);

	for (unsigned int i = 0; i < 16; i++) m.m_ptValue[i] /= det;
	*/
	raaMatrix4T<T> mOut(raaMatrix4Containment(raaMatrix4Containment::csm_uiReference), m_ptInvValue);
	if(m_bDirtyInverse)
	{
		const T *m = m_ptValue;
		T *out = m_ptInvValue;
		T wtmp[4][8];
		T m0, m1, m2, m3, s;
		T *r0, *r1, *r2, *r3;

#define MAT(m,r,c) (m)[(c)*4+(r)]
#define SWAP_ROWS(a, b) { T *_tmp = a; (a)=(b); (b)=_tmp; }

		r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

		r0[0] = MAT(m, 0, 0), r0[1] = MAT(m, 0, 1), r0[2] = MAT(m, 0, 2), r0[3] = MAT(m, 0, 3), r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,
		r1[0] = MAT(m, 1, 0), r1[1] = MAT(m, 1, 1), r1[2] = MAT(m, 1, 2), r1[3] = MAT(m, 1, 3), r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,
		r2[0] = MAT(m, 2, 0), r2[1] = MAT(m, 2, 1),r2[2] = MAT(m, 2, 2), r2[3] = MAT(m, 2, 3),r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,
		r3[0] = MAT(m, 3, 0), r3[1] = MAT(m, 3, 1),r3[2] = MAT(m, 3, 2), r3[3] = MAT(m, 3, 3),r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

		/* choose pivot - or die */
		if (abs(r3[0])>abs(r2[0])) SWAP_ROWS(r3, r2);
		if (abs(r2[0])>abs(r1[0])) SWAP_ROWS(r2, r1);
		if (abs(r1[0])>abs(r0[0])) SWAP_ROWS(r1, r0);
		if (0.0 == r0[0])  return GL_FALSE;

		/* eliminate first variable     */
		m1 = r1[0] / r0[0]; m2 = r2[0] / r0[0]; m3 = r3[0] / r0[0];
		s = r0[1]; r1[1] -= m1 * s; r2[1] -= m2 * s; r3[1] -= m3 * s;
		s = r0[2]; r1[2] -= m1 * s; r2[2] -= m2 * s; r3[2] -= m3 * s;
		s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
		s = r0[4];
		if (s != 0.0F) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
		s = r0[5];
		if (s != 0.0F) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
		s = r0[6];
		if (s != 0.0F) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
		s = r0[7];
		if (s != 0.0F) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }

		/* choose pivot - or die */
		if (abs(r3[1])>abs(r2[1])) SWAP_ROWS(r3, r2);
		if (abs(r2[1])>abs(r1[1])) SWAP_ROWS(r2, r1);
		if (0.0 == r1[1])  throw raaMatrix4Exception(raaMatrix4Exception::csm_uiMatrixInversionNotPossible);

		/* eliminate second variable */
		m2 = r2[1] / r1[1]; m3 = r3[1] / r1[1];
		r2[2] -= m2 * r1[2]; r3[2] -= m3 * r1[2];
		r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
		s = r1[4]; if (0.0F != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
		s = r1[5]; if (0.0F != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
		s = r1[6]; if (0.0F != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
		s = r1[7]; if (0.0F != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }

		/* choose pivot - or die */
		if (abs(r3[2])>abs(r2[2])) SWAP_ROWS(r3, r2);
		if (0.0 == r2[2])  throw raaMatrix4Exception(raaMatrix4Exception::csm_uiMatrixInversionNotPossible);

		/* eliminate third variable */
		m3 = r3[2] / r2[2];
		r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
			r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
			r3[7] -= m3 * r2[7];

		/* last check */
		if (0.0 == r3[3]) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiMatrixInversionNotPossible);;

		s = 1.0 / r3[3];             /* now back substitute row 3 */
		r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;

		m2 = r2[3];                 /* now back substitute row 2 */
		s = 1.0 / r2[2];
		r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
		m1 = r1[3];
		r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
		m0 = r0[3];
		r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

		m1 = r1[2];                 /* now back substitute row 1 */
		s = 1.0 / r1[1];
		r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
			r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
		m0 = r0[2];
		r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

		m0 = r0[1];                 /* now back substitute row 0 */
		s = 1.0 / r0[0];
		r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

		MAT(out, 0, 0) = r0[4]; MAT(out, 0, 1) = r0[5],
			MAT(out, 0, 2) = r0[6]; MAT(out, 0, 3) = r0[7],
			MAT(out, 1, 0) = r1[4]; MAT(out, 1, 1) = r1[5],
			MAT(out, 1, 2) = r1[6]; MAT(out, 1, 3) = r1[7],
			MAT(out, 2, 0) = r2[4]; MAT(out, 2, 1) = r2[5],
			MAT(out, 2, 2) = r2[6]; MAT(out, 2, 3) = r2[7],
			MAT(out, 3, 0) = r3[4]; MAT(out, 3, 1) = r3[5],
			MAT(out, 3, 2) = r3[6]; MAT(out, 3, 3) = r3[7];

		m_bDirtyInverse = false;
#undef MAT
#undef SWAP_ROWS
	}

	return mOut;
}




template <class T>
void raaGL4::raaMatrix4T<T>::rotate(T degrees, raaGL4::raaVector4T<T>& v)
{

	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	raaMatrix4T<T> m;
	
	#define M(row,col)  m.m_ptValue[col*4+row]
	
	T x = v[0];
	T y = v[1];
	T z = v[2];
	T s = std::sin(degrees*PI / 180.0);
	T c = std::cos(degrees*PI / 180.0);
	bool bOptimised = false;

	if (x == 0.0) 
	{
		if (y == 0.0) 
		{
			if (z != 0.0) 
			{ // rotate only around z-axis
				bOptimised = true;
				M(0, 0) = c;
				M(1, 1) = c;
				if (z < 0.0) 
				{
					M(0, 1) = s;
					M(1, 0) = -s;
				}
				else 
				{
					M(0, 1) = -s;
					M(1, 0) = s;
				}
			}
		}
		else if (z == 0.0) 
		{ // rotate only around y-axis
			bOptimised = true;
			M(0, 0) = c;
			M(2, 2) = c;
			if (y < 0.0) 
			{
				M(0, 2) = -s;
				M(2, 0) = s;
			}
			else 
			{
				M(0, 2) = s;
				M(2, 0) = -s;
			}
		}
	}
	else if (y== 0.0) 
	{
		if (z == 0.0) 
		{ 	// rotate only around x-axis
			bOptimised = true;
			M(1, 1) = c;
			M(2, 2) = c;
			if (x < 0.0) 
			{
				M(1, 2) = s;
				M(2, 1) = -s;
			}
			else 
			{
				M(1, 2) = -s;
				M(2, 1) = s;
			}
		}
	}

	if (!bOptimised)
	{
		T mag = sqrt(x * x + y * y + z * z);
		T xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

		if (mag <= 1.0e-4F) return;

		x /= mag;
		y /= mag;
		z /= mag;
		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * s;
		ys = y * s;
		zs = z * s;
		one_c = 1.0 - c;

		// We already hold the identity-matrix so we can skip some statements 
		M(0, 0) = (one_c * xx) + c;
		M(0, 1) = (one_c * xy) - zs;
		M(0, 2) = (one_c * zx) + ys;

		M(1, 0) = (one_c * xy) + zs;
		M(1, 1) = (one_c * yy) + c;
		M(1, 2) = (one_c * yz) - xs;

		M(2, 0) = (one_c * zx) - ys;
		M(2, 1) = (one_c * yz) + xs;
		M(2, 2) = (one_c * zz) + c;
	}
#undef M
	mult(m);
}

template <class T>
void raaGL4::raaMatrix4T<T>::translate(const raaGL4:: raaVector4T<T>& v)
{


	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);

	m_ptValue[12] = m_ptValue[0] * v[0] + m_ptValue[4] * v[1] + m_ptValue[8] * v[2] + m_ptValue[12];
	m_ptValue[13] = m_ptValue[1] * v[0] + m_ptValue[5] * v[1] + m_ptValue[9] * v[2] + m_ptValue[13];
	m_ptValue[14] = m_ptValue[2] * v[0] + m_ptValue[6] * v[1] + m_ptValue[10] * v[2] + m_ptValue[14];
	m_ptValue[15] = m_ptValue[3] * v[0] + m_ptValue[7] * v[1] + m_ptValue[11] * v[2] + m_ptValue[15];
	update();
	dirtyInverse();
}

template <class T>
void raaGL4::raaMatrix4T<T>::scale(const raaVector4T<T> &v)
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	
	m_ptValue[0] *= v[0];   m_ptValue[4] *= v[1];   m_ptValue[8] *= v[2];
	m_ptValue[1] *= v[0];   m_ptValue[5] *= v[1];   m_ptValue[9] *= v[2];
	m_ptValue[2] *= v[0];   m_ptValue[6] *= v[1];   m_ptValue[10] *= v[2];
	m_ptValue[3] *= v[0];   m_ptValue[7] *= v[1];   m_ptValue[11] *= v[2];

	update();
	dirtyInverse();
}

template <class T>
const raaGL4::raaVector4T<T> operator*(const raaGL4::raaVector4T<T>& v, const raaGL4::raaMatrix4T<T>& m) 
{
	T v0, v1, v2, v3;

	v0 = v[0] * m[0] + v[1] * m[4] * v[2] * m[8] + v[3] * m[12];
	v1 = v[0] * m[1] + v[1] * m[5] * v[2] * m[9] + v[3] * m[13];
	v2 = v[0] * m[2] + v[1] * m[6] * v[2] * m[10] + v[3] * m[14];
	v3 = v[0] * m[3] + v[1] * m[7] * v[2] * m[11] + v[3] * m[15];

	return raaVector4T<T>(v0, v1, v2, v3, v.vectorType());
}

template <class T>
const raaGL4::raaVector4T<T> operator*(const raaGL4::raaVector4T<T>& v, raaGL4::raaMatrix4T<T>& m)
{
	T v0, v1, v2, v3;

	v0 = v[0] * m[0] + v[1] * m[4] * v[2] * m[8] + v[3] * m[12];
	v1 = v[0] * m[1] + v[1] * m[5] * v[2] * m[9] + v[3] * m[13];
	v2 = v[0] * m[2] + v[1] * m[6] * v[2] * m[10] + v[3] * m[14];
	v3 = v[0] * m[3] + v[1] * m[7] * v[2] * m[11] + v[3] * m[15];

	return raaVector4T<T>(v0, v1, v2, v3, v.vectorType());
}

template <class T>
const raaGL4::raaVector4T<T> operator*(raaGL4::raaVector4T<T>& v, const raaGL4::raaMatrix4T<T>& m)
{
	T v0, v1, v2, v3;

	v0 = v[0] * m[0] + v[1] * m[4] * v[2] * m[8] + v[3] * m[12];
	v1 = v[0] * m[1] + v[1] * m[5] * v[2] * m[9] + v[3] * m[13];
	v2 = v[0] * m[2] + v[1] * m[6] * v[2] * m[10] + v[3] * m[14];
	v3 = v[0] * m[3] + v[1] * m[7] * v[2] * m[11] + v[3] * m[15];

	return raaVector4T<T>(v0, v1, v2, v3, v.vectorType());
}

template <class T>
const raaGL4::raaVector4T<T> operator*(raaGL4::raaVector4T<T>& v, raaGL4::raaMatrix4T<T>& m)
{
	T v0, v1, v2, v3;

	v0 = v[0] * m[0] + v[1] * m[4] * v[2] * m[8] + v[3] * m[12];
	v1 = v[0] * m[1] + v[1] * m[5] * v[2] * m[9] + v[3] * m[13];
	v2 = v[0] * m[2] + v[1] * m[6] * v[2] * m[10] + v[3] * m[14];
	v3 = v[0] * m[3] + v[1] * m[7] * v[2] * m[11] + v[3] * m[15];

	return raaVector4T<T>(v0, v1, v2, v3, v.vectorType());
}


template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaMatrix4T<T>::mult(const raaVector4T<T>& v, const raaMatrix4T<T>& m)
{
	T v0, v1, v2, v3;

	v0 = v[0] * m[0] + v[1] * m[4] * v[2] * m[8] + v[3] * m[12];
	v1 = v[0] * m[1] + v[1] * m[5] * v[2] * m[9] + v[3] * m[13];
	v2 = v[0] * m[2] + v[1] * m[6] * v[2] * m[10] + v[3] * m[14];
	v3 = v[0] * m[3] + v[1] * m[7] * v[2] * m[11] + v[3] * m[15];

	return raaVector4T<T>(v0, v1, v2, v3, v.vectorType());
}

template <class T>
void raaGL4::raaMatrix4T<T>::push()
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	T* pMat = new T[16];
	for (int i = 0; i < 16; pMat[i] = m_ptValue[i++]);
	m_Stack.push_front(pMat);
}

template <class T>
void raaGL4::raaMatrix4T<T>::pop()
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	if (!m_Stack.size()) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiStackInvalidPop);

	T* pMat = m_Stack.front();
	for (int i = 0; i < 16; m_ptValue[i] = pMat[i++]);
	m_Stack.pop_front();
	delete[] pMat;
	dirtyInverse();
	update();
}

template <class T>
void raaGL4::raaMatrix4T<T>::frustum(T l, T r, T b, T t, T n, T f)
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	T x, y, _a, _b, _c, _d;

	x = (2.0*n) / (r - l);
	y = (2.0*n) / (t - b);
	_a = (r + l) / (r - l);
	_b = (t + b) / (t - b);
	_c = -(f + n) / (f - n);
	_d = -(2.0*f*n) / (f - n); 

	raaMatrix4T<T> m;

#define M(row,col)  m.m_ptValue[col*4+row]
	M(0, 0) = x;     M(0, 1) = 0.0;  M(0, 2) = _a;      M(0, 3) = 0.0;
	M(1, 0) = 0.0;  M(1, 1) = y;     M(1, 2) = _b;      M(1, 3) = 0.0;
	M(2, 0) = 0.0;  M(2, 1) = 0.0;  M(2, 2) = _c;      M(2, 3) = _d;
	M(3, 0) = 0.0;  M(3, 1) = 0.0;  M(3, 2) = -1.0;  M(3, 3) = 0.0;
#undef M

	mult(m);
}

template <class T>
void raaGL4::raaMatrix4T<T>::ortho(T l, T r, T b, T t, T n, T f)
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	raaMatrix4T<T> m;

#define M(row,col)  m.m_ptValue[col*4+row]
	M(0, 0) = 2.0 / (r - l);
	M(0, 1) = 0.0;
	M(0, 2) = 0.0;
	M(0, 3) = -(r + l) / (r - l);

	M(1, 0) = 0.0;
	M(1, 1) = 2.0 / (t - b);
	M(1, 2) = 0.0;
	M(1, 3) = -(t + b) / (t - b);

	M(2, 0) = 0.0;
	M(2, 1) = 0.0;
	M(2, 2) = -2.0 / (f - n);
	M(2, 3) = -(f + n) / (f - n);

	M(3, 0) = 0.0;
	M(3, 1) = 0.0;
	M(3, 2) = 0.0;
	M(3, 3) = 1.0;
#undef M

	mult(m);
}

template <class T>
void raaGL4::raaMatrix4T<T>::perspective(T degreesFOV, T aspect, T n, T f)
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	raaMatrix4T<T> m;
	T sine, cotangent, deltaZ;
	T radians = degreesFOV / 2.0 * PI / 180;

	deltaZ = f - n;
	sine = sin(radians);
	if ((deltaZ == 0.0) || (sine == 0.0) || (aspect == 0.0)) 	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidTypeException);
	
	cotangent = cos(radians) / sine;

#define M(row,col)  m.m_ptValue[col*4+row]
	M(0,0) = cotangent / aspect;
	M(1,1) = cotangent;
	M(2,2) = -(f + n) / deltaZ;
	M(2,3) = -1.0;
	M(3,2) = -2.0 * n * f / deltaZ;
	M(3, 3) = 0.0;
#undef M

	mult(m);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaMatrix4T<T>::project(raaVector4T<T> obj, raaMatrix4T<T>& modelView, raaMatrix4T<T>& projection, int* viewport)
{
	raaVector4T<T> v, o(obj);
	o.changeVectorType(raaVector4T<T>::raaVector4Type::csm_uiPVec);
	v = raaMatrix4T<T>::mult(o, modelView);
	v = raaMatrix4T<T>::mult(v, projection);
	v.set(v[0] / v[3], v[1] / v[3], v[2] / v[3]);
	v.shiftAndScale(0.5, 0.5);
	v.set(v[0] * viewport[2] + viewport[0], v[1] * viewport[3] + viewport[1], v[2]);
	return v;
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaMatrix4T<T>::unproject(raaVector4T<T> win, raaMatrix4T<T>& modelView, raaMatrix4T<T>& projection, int* viewport)
{
	raaMatrix4T<T> m;
	raaVector4T<T> v;
	m = modelView*projection;
	m = !m;
	v.set((win[0] - viewport[0]) / viewport[2], (win[1] - viewport[1]) / viewport[3], win[3]);
	v.shiftAndScale(-1.0, 2.0);
	v = raaMatrix4T<T>::mult(v, m);
	if (v[3] == 0.0) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvertDivisonByZeroException);
	v.set(v[0] / v[3], v[1] / v[3], v[2] / v[3]);
	return v;
}

template <class T>
void raaGL4::raaMatrix4T<T>::lookAt(const raaVector4T<T>& eye, const raaVector4T<T>& target, const raaVector4T<T>& up)
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	raaVector4T<T> dir, right, u;

	dir = !(target - eye);
	right = !(dir%up);
	u = !(right%dir);
	raaMatrix4T<T> m;
#define M(row,col)  m.m_ptValue[col*4+row]
	M(0, 0) = right[0];
	M(1, 0) = right[1];
	M(2, 0) = right[2];

	M(0, 1) = u[0];
	M(1, 1) = u[1];
	M(2, 1) = u[2];

	M(0, 2) = -dir[0];
	M(1, 2) = -dir[1];
	M(2, 2) = -dir[2];

	mult(m);
	translate(eye);


#undef M

}
/*
template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaMatrix4T<T>::project(raaVector4T<T> obj, raaMatrix4T<T>& modelView, raaMatrix4T<T>& projection, int *viewport)
{
	raaVector4T<T> v, o(obj);
	o.changeVectorType(raaVector4T<T>::raaVector4Type::csm_uiPVec);
	v = o*modelView;
	v = v*projection;
	v.set(v[0] / v[3], v[1] / v[3], v[2] / v[3]);
	v.shiftAndScale(0.5, 0.5);
	v.set(v[0] * viewport[2] + viewport[0], v[1] * viewport[3] + viewport[1],v[2]);
	return v;
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaMatrix4T<T>::unproject(raaVector4T<T> win, raaMatrix4T<T>& modelView, raaMatrix4T<T>& projection, int *viewport) 
{
	raaMatrix4T<T> m;
	raaVector4T<T> v;
	m = modelView*projection;
	m = !m;
	v.set((win[0] - viewport[0]) / viewport[2], (win[1] - viewport[1]) / viewport[3], win[3]);
	v.shiftAndScale(-1.0, 2.0);
	v = v*m;
	if (v[3] == 0.0) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvertDivisonByZeroException);
	v.set(v[0] / v[3], v[1] / v[3], v[2] / v[3]);
	return v;

}
*/

template <class T>
void raaGL4::raaMatrix4T<T>::dirtyInverse()
{
	m_bDirtyInverse = true;
}

template <class T>
unsigned long raaGL4::raaMatrix4T<T>::apply(int iLocation)
{
	if (!m_ptValue) throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
/*
	switch(m_uiType)
	{
	case GL_FLOAT_MAT4:
		glUniformMatrix4fv(iLocation, 1, false, m_ptValue);
		break;
	case GL_DOUBLE_MAT4:
		glUniformMatrix4dv(iLocation, 1, false, m_ptValue);
		break;
	}
*/

	uniformMat4v(iLocation, 1, false, m_ptValue);
	return m_ulChangeCount;
}

template <class T>
void raaGL4::raaMatrix4T<T>::setDataType()
{
	if (std::is_same<T, float>::value)  m_uiType = GL_FLOAT_MAT4;
	else if (std::is_same<T, double>::value)  m_uiType = GL_DOUBLE_MAT4;
	else throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidTypeException);
}

template <class T>
void raaGL4::raaMatrix4T<T>::swapVals(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}
/*
unsigned long raaGL4::raaMatrix4fv::apply(int iLocation)
{
	if (!m_ptValue)  throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	glUniformMatrix4fv(iLocation, 1, false, m_ptValue);
	return m_ulChangeCount;
}

unsigned long raaGL4::raaMatrix4dv::apply(int iLocation)
{
	if (!m_ptValue)  throw raaMatrix4Exception(raaMatrix4Exception::csm_uiInvalidInternalPtrException);
	glUniformMatrix4dv(iLocation, 1, false, m_ptValue);
	return m_ulChangeCount;
}
*/