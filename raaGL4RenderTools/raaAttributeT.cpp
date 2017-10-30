#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <type_traits>
#include "raaAttributeT.h"

template <class T>
raaGL4::raaAttributeT<T>::raaAttributeT(const raaAttributeT<T>& f) : m_tValue(f.m_tValue)
{
	setType();
}

template <class T>
raaGL4::raaAttributeT<T>::raaAttributeT()
{
	if (std::is_same<T, float>::value) m_tValue = (T)0.0f;
	else if (std::is_same<T, int>::value)  m_tValue=(T)0;
	else if (std::is_same<T, unsigned int>::value)  m_tValue = (T)0;
	else if (std::is_same<T, double>::value)  m_tValue=(T)0.0;
	setType();
}

template <class T>
raaGL4::raaAttributeT<T>::raaAttributeT(const T t) : m_tValue(t)
{
	setType();
}

template <class T>
void raaGL4::raaAttributeT<T>::setType()
{
	if (std::is_same<T, float>::value)  m_uiType = GL_FLOAT;
	else if (std::is_same<T, int>::value)  m_uiType = GL_INT;
	else if (std::is_same<T, unsigned int>::value)  m_uiType = GL_UNSIGNED_INT;
	else if (std::is_same<T, double>::value)  m_uiType = GL_DOUBLE;
}

template <class T>
unsigned long raaGL4::raaAttributeT<T>::apply(int iLocation)
{
/*
	switch(m_uiType)
	{
	case GL_FLOAT:
		glUniform1f(iLocation, m_tValue);
		break;
	case GL_INT:
		glUniform1i(iLocation, m_tValue);
		break;
	case GL_UNSIGNED_INT:
		glUniform1ui(iLocation, m_tValue);
		break;
	case GL_DOUBLE:
		glUniform1d(iLocation, m_tValue);
		break;
	}
*/

	uniform1(iLocation, m_tValue);
	return m_ulChangeCount;
}

template <class T>
const T* raaGL4::raaAttributeT<T>::ptr() const
{
	return &m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::value()
{
	return m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator=(T& t)
{
	m_tValue = t;
	update();
	return t;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator=(raaAttributeT<T>& t)
{
	m_tValue = t.m_tValue;
	update();
	return t.m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator*(T& t)
{
	return m_tValue*t;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator*(const T& t)
{
	return m_tValue*t;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator*(raaAttributeT<T>& t)
{
	return m_tValue*t.m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator*(const raaAttributeT<T>& t)
{
	return m_tValue*t.m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator*=(T& t)
{
	m_tValue *= t;
	update();
	return m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator*=(const T& t)
{
	m_tValue *= t;
	update();
	return m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator*=(raaAttributeT<T>& t)
{
	m_tValue *= t.m_tValue;
	update();
	return m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator/(T& t) 
{
	return m_tValue / t;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator/(const T& t) 
{
	return m_tValue / t;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator/(raaAttributeT<T>& t) 
{
	return m_tValue / t.m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator/(const raaAttributeT<T>& t) 
{
	return m_tValue / t.m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator/=(T& t) 
{
	m_tValue /= t;
	update();
	return m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator/=(const T& t) 
{
	m_tValue /= t;
	update();
	return m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator/=(raaAttributeT<T>& t) 
{
	m_tValue /= t.m_tValue;
	update();
	return m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator/=(const raaAttributeT<T>& t) 
{
	m_tValue /= t.m_tValue;
	update();
	return m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator*=(const raaAttributeT<T>& t)
{
	m_tValue *= t;
	update();
	return m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator=(const raaAttributeT<T>& t)
{
	m_tValue = t.m_tValue;
	update();
	return t.m_tValue;
}

//+
template <class T>
T raaGL4::raaAttributeT<T>::operator+(T& t)
{
	return m_tValue + t;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator+(const T& t)
{
	return m_tValue + t;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator+(raaAttributeT<T>& t)
{
	return m_tValue + t.m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator+(const raaAttributeT<T>& t)
{
	return m_tValue + t.m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator+=(T& t)
{
	m_tValue += t;
	update();
	return m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator+=(const T& t)
{
	m_tValue += t;
	update();
	return m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator+=(raaAttributeT<T>& t)
{
	m_tValue += t.m_tValue;
	update();
	return m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator+=(const raaAttributeT<T>& t)
{
	m_tValue += t.m_tValue;
	update();
	return m_tValue;
}

//-
template <class T>
T raaGL4::raaAttributeT<T>::operator-(T& t)
{
	return m_tValue - t;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator-(const T& t)
{
	return m_tValue - t;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator-(raaAttributeT<T>& t)
{
	return m_tValue - t.m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator-(const raaAttributeT<T>& t)
{
	return m_tValue - t.m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator-=(T& t)
{
	m_tValue -= t;
	update();
	return m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator-=(const T& t)
{
	m_tValue -= t;
	update();
	return m_tValue;
}

template <class T>
T raaGL4::raaAttributeT<T>::operator-=(raaAttributeT<T>& t)
{
	m_tValue -= t.m_tValue;
	update();
	return m_tValue;
}



template <class T>
const T raaGL4::raaAttributeT<T>::operator-=(const raaAttributeT<T>& t)
{
	m_tValue -= t.m_tValue;
	update();
	return m_tValue;
}

template <class T>
raaGL4::raaAttributeT<T>::operator T()
{
	return m_tValue;
}

template <class T>
raaGL4::raaAttributeT<T>::operator const T() const
{
	return m_tValue;
}

template <class T>
const T raaGL4::raaAttributeT<T>::operator=(const T& t)
{
	m_tValue = t;
	update();
	return t;
}



template <class T>
raaGL4::raaAttributeT<T>::~raaAttributeT()
{
}

/*
unsigned long raaGL4::raaAttribute1f::apply(int iLocation)
{
	glUniform1f(iLocation, m_tValue);
	return m_ulChangeCount;
}

unsigned long raaGL4::raaAttribute1i::apply(int iLocation)
{
	glUniform1i(iLocation, m_tValue);
	return m_ulChangeCount;
}

unsigned long raaGL4::raaAttribute1ui::apply(int iLocation)
{
	glUniform1ui(iLocation, m_tValue);
	return m_ulChangeCount;
}

unsigned long raaGL4::raaAttribute1d::apply(int iLocation)
{
	glUniform1d(iLocation, m_tValue);
	return m_ulChangeCount;
}
*/