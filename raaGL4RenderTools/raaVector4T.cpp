#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>


#include "raaVector4T.h"
#include <cstdarg>


template <class T>
raaGL4::raaVector4T<T>::raaVector4Exception::raaVector4Exception(unsigned uiCode): m_uiCode(uiCode)
{
	
}

template <class T>
unsigned raaGL4::raaVector4T<T>::raaVector4Exception::code()
{
	return m_uiCode;
}

template <class T>
std::string raaGL4::raaVector4T<T>::raaVector4Exception::msg()
{
	switch(m_uiCode)
	{
	case csm_uiInvalidValuePtrException:
		return "invalide vector value (ptr) exception";
	case csm_uiInvalidInputValuePtrException:
		return "the input reference vector memory address is invalid";
	case csm_uiInvalidInputValueException:
		return "the input reference vector is invalid";
	case csm_uiInvalidInternalValueException:
		return "the internal data vector is invalid";
	default:
		return "unknown exception";
	}
}

template <class T>
raaGL4::raaVector4T<T>::raaVector4Type::raaVector4Type(unsigned uiVectorType): m_uiVectorType(uiVectorType) 
{				
}

template <class T>
raaGL4::raaVector4T<T>::raaVector4Type::raaVector4Type(const raaVector4Type& t): m_uiVectorType(t.m_uiVectorType)
{}

template <class T>
bool raaGL4::raaVector4T<T>::raaVector4Type::operator==(const raaVector4Type& t) const {
	if (m_uiVectorType == t.m_uiVectorType) return true;
	return false;
}

template <class T>
bool raaGL4::raaVector4T<T>::raaVector4Type::operator==(const raaVector4Type t) const 
{
	if (m_uiVectorType == t.m_uiVectorType) return true;
	return false;
}

template <class T>
bool raaGL4::raaVector4T<T>::raaVector4Type::operator==(const unsigned t) const {
	if (m_uiVectorType == t) return true;
	return false;
}

template <class T>
bool raaGL4::raaVector4T<T>::raaVector4Type::operator!=(const raaVector4Type& t) const {
	if (m_uiVectorType != t.m_uiVectorType) return true;
	return false;
}

template <class T>
bool raaGL4::raaVector4T<T>::raaVector4Type::operator!=(const unsigned t) const {
	if (m_uiVectorType != t) return true;
	return false;
}

template <class T>
const typename raaGL4::raaVector4T<T>::raaVector4Type& raaGL4::raaVector4T<T>::raaVector4Type::operator=(const raaVector4Type& t) {
	m_uiVectorType = t.m_uiVectorType;
	return *this;
}

template <class T>
raaGL4::raaVector4T<T>::raaVector4Containment::raaVector4Containment(unsigned uiContainmentType): m_uiContainmentType(uiContainmentType)
{
	
}

template <class T>
raaGL4::raaVector4T<T>::raaVector4Containment::raaVector4Containment(const raaVector4Containment& t): m_uiContainmentType(t.m_uiContainmentType)
{
	
}

template <class T>
bool raaGL4::raaVector4T<T>::raaVector4Containment::operator==(const raaVector4Containment& t) const 
{
	if (m_uiContainmentType == t.m_uiContainmentType) return true;
	return false;
}

template <class T>
bool raaGL4::raaVector4T<T>::raaVector4Containment::operator==(const unsigned t) const 
{
	if (m_uiContainmentType == t) return true;
	return false;
}

template <class T>
bool raaGL4::raaVector4T<T>::raaVector4Containment::operator!=(const raaVector4Containment& t) const 
{
	if (m_uiContainmentType != t.m_uiContainmentType) return true;
	return false;
}

template <class T>
bool raaGL4::raaVector4T<T>::raaVector4Containment::operator!=(const unsigned t) const 
{
	if (m_uiContainmentType != t) return true;
	return false;
}

template <class T>
const typename raaGL4::raaVector4T<T>::raaVector4Containment& raaGL4::raaVector4T<T>::raaVector4Containment::operator=(const raaVector4Containment& t) 
{
	m_uiContainmentType = t.m_uiContainmentType;
	return *this;
}

template <class T>
const typename raaGL4::raaVector4T<T>::raaVector4Containment& raaGL4::raaVector4T<T>::raaVector4Containment::operator=(const unsigned t) 
{
	m_uiContainmentType = t;
	return *this;
}

template <class T>
raaGL4::raaVector4T<T>::raaVector4Containment::operator unsigned() 
{
	return m_uiContainmentType;
}

template <class T>
unsigned raaGL4::raaVector4T<T>::raaVector4Containment::value()
{
	return m_uiContainmentType;
}

template <class T>
const typename raaGL4::raaVector4T<T>::raaVector4Type& raaGL4::raaVector4T<T>::raaVector4Type::operator=(const unsigned t) {
	m_uiVectorType = t;
	return *this;
}

template <class T>
raaGL4::raaVector4T<T>::raaVector4Type::operator unsigned() 
{
	return m_uiVectorType;
}



template <class T>
raaGL4::raaVector4T<T>::raaVector4T(raaVector4Type t, T* ptValue): m_VectorType(t), m_Containment(raaVector4Containment::csm_uiReference), m_ptValue(ptValue)
{
	setDataType();
	if (m_ptValue) raaAttribute::update();
	else
	{
		m_Containment =raaVector4Containment::csm_uiContained ;
		m_ptValue = new T[4];
		zero();
	}
}

template <class T>
raaGL4::raaVector4T<T>::raaVector4T(T t0, T t1, T t2, raaVector4Type t) : m_VectorType(t), m_Containment(raaVector4Containment::csm_uiContained)
{
	setDataType();
	m_ptValue = new T[4];
	m_ptValue[0] = t0;
	m_ptValue[1] = t1;
	m_ptValue[2] = t2;

	switch (m_VectorType)
	{
	case raaVector4Type::csm_uiCVec:
		m_ptValue[3] = 1.0f;
	case raaVector4Type::csm_uiDVec:
		m_ptValue[3] = 0.0f;
	default:
		m_ptValue[3] = 1.0f;
	}
	raaAttribute::update();
}

template <class T>
raaGL4::raaVector4T<T>::raaVector4T(T t0, T t1, T t2, T t3, raaVector4Type t) : m_VectorType(t), m_Containment(raaVector4Containment::csm_uiContained)
{
	setDataType();
	m_ptValue = new T[4];
	m_ptValue[0] = t0;
	m_ptValue[1] = t1;
	m_ptValue[2] = t2;
	m_ptValue[2] = t3;

	raaAttribute::update();
}

template <class T>
raaGL4::raaVector4T<T>::raaVector4T(raaVector4T<T>& t): m_Containment(raaVector4Containment::csm_uiContained)
{
	if (t.m_ptValue)
	{
		m_ptValue = new T[4];
		m_ptValue[0] = t.m_ptValue[0];
		m_ptValue[1] = t.m_ptValue[1];
		m_ptValue[2] = t.m_ptValue[2];
		m_ptValue[3] = t.m_ptValue[3];
		m_VectorType = t.m_VectorType;
		setDataType();
		raaAttribute::update();
	}

	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValueException);
}

template <class T>
const T* raaGL4::raaVector4T<T>::ptr() const
{
	return m_ptValue;
}

template <class T>
T raaGL4::raaVector4T<T>::value(unsigned uiIndex)
{
	return m_ptValue[uiIndex];
}

template <class T>
raaGL4::raaVector4T<T>::~raaVector4T()
{
	if (m_Containment == raaVector4Containment::csm_uiContained) delete[] m_ptValue;
}

template <class T>
const typename raaGL4::raaVector4T<T>::raaVector4Type& raaGL4::raaVector4T<T>::vectorType()
{
	return m_VectorType;
}

template <class T>
const typename raaGL4::raaVector4T<T>::raaVector4Type& raaGL4::raaVector4T<T>::vectorType() const
{
	return m_VectorType;
}

template <class T>
void raaGL4::raaVector4T<T>::changeVectorType(const raaVector4Type	 &t)
{
	if (m_ptValue)
	{
		if (m_VectorType != t)
		{
			m_VectorType = t;

			switch (m_VectorType)
			{
			case raaVector4Type::csm_uiCVec:
				m_ptValue[3] = 1.0f;
				break;
			case raaVector4Type::csm_uiDVec:
				m_ptValue[3] = 0.0f;
				break;
			default:
				m_ptValue[3] = 1.0f;
				break;
			}
		}
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}



template <class T>
const typename raaGL4::raaVector4T<T>::raaVector4Containment& raaGL4::raaVector4T<T>::containmentType()
{
	return m_Containment;
}

template <class T>
void raaGL4::raaVector4T<T>::set(T v0, T v1, T v2)
{
	if(!m_ptValue) throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
	m_ptValue[0] = v0;
	m_ptValue[1] = v1;
	m_ptValue[2] = v2;
	update();
}

template <class T>
void raaGL4::raaVector4T<T>::set(T v0, T v1, T v2, T v3)
{
	if (!m_ptValue) throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
	m_ptValue[0] = v0;
	m_ptValue[1] = v1;
	m_ptValue[2] = v2;
	if (m_VectorType == raaVector4Type::csm_uiCVec) m_ptValue[3] = v3;
	update();
}

template <class T>
void raaGL4::raaVector4T<T>::shiftAndScale(T shift, T scale)
{
	if (!m_ptValue) throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
	m_ptValue[0] = m_ptValue[0] * scale + shift;
	m_ptValue[1] = m_ptValue[1] * scale + shift;
	m_ptValue[2] = m_ptValue[2] * scale + shift;
	if (m_VectorType == raaVector4Type::csm_uiCVec) m_ptValue[3] = m_ptValue[3] * scale + shift;
	update();

}

template <class T>
void raaGL4::raaVector4T<T>::changeContainmentType(const raaVector4Containment& t, T* pRawData)
{
	if(m_Containment!=t)
	{
		if (!m_ptValue) throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
		m_Containment = t;

		switch(m_Containment)
		{
		case raaVector4Containment::csm_uiContained:
			{
				T* v = new T[4];
				v[0] = m_ptValue[0];
				v[1] = m_ptValue[1];
				v[2] = m_ptValue[2];
				v[4] = m_ptValue[3];
				m_ptValue = v;
			}
			break;
		case raaVector4Containment::csm_uiReference:
			if(pRawData)
			{
				pRawData[0] = m_ptValue[0];
				pRawData[1] = m_ptValue[1];
				pRawData[2] = m_ptValue[2];
				pRawData[3] = m_ptValue[3];
				delete[] m_ptValue;
				m_ptValue = pRawData;
				raaAttribute::update();
			}
			else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
			break;
		}
	}
}

template <class T>
void raaGL4::raaVector4T<T>::zero()
{
	if (!m_ptValue) throw raaVector4Exception(raaVector4Exception::csm_uiInvalidValuePtrException);
	switch(m_VectorType)
	{
	case raaVector4Type::csm_uiCVec:
		m_ptValue[0] = m_ptValue[1] = m_ptValue[2] = m_ptValue[3] = 1.0f;
		raaAttribute::update();
		break;
	case raaVector4Type::csm_uiDVec:
		m_ptValue[0] = m_ptValue[1] = m_ptValue[2] = m_ptValue[3] = 0.0f;
		raaAttribute::update();
		break;
	default:
		m_ptValue[0] = m_ptValue[1] = m_ptValue[2] = 0.0f;
		m_ptValue[3] = 1.0f;
		raaAttribute::update();
		break;

	}
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator+(const raaVector4T<T>& t) 
{
	if (m_ptValue && t.m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] + t.m_ptValue[0];
		v.m_ptValue[1] = m_ptValue[1] + t.m_ptValue[1];
		v.m_ptValue[2] = m_ptValue[2] + t.m_ptValue[2];
		if(m_VectorType== raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] + t.m_ptValue[3];
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator+(const raaVector4T<T> t) 
{
	if (m_ptValue && t.m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] + t.m_ptValue[0];
		v.m_ptValue[1] = m_ptValue[1] + t.m_ptValue[1];
		v.m_ptValue[2] = m_ptValue[2] + t.m_ptValue[2];
		if (m_VectorType == raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] + t.m_ptValue[3];
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator*(const raaVector4T<T>& t)
{
	if (m_ptValue && t.m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] * t.m_ptValue[0];
		v.m_ptValue[1] = m_ptValue[1] * t.m_ptValue[1];
		v.m_ptValue[2] = m_ptValue[2] * t.m_ptValue[2];
		if (m_VectorType == raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] * t.m_ptValue[3];
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}


template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator-(const raaVector4T<T>& t)
{
	if (m_ptValue && t.m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] - t.m_ptValue[0];
		v.m_ptValue[1] = m_ptValue[1] - t.m_ptValue[1];
		v.m_ptValue[2] = m_ptValue[2] - t.m_ptValue[2];
		if (m_VectorType == raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] - t.m_ptValue[3];
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator-(const raaVector4T<T>& t) const 
{
	if (m_ptValue && t.m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] - t.m_ptValue[0];
		v.m_ptValue[1] = m_ptValue[1] - t.m_ptValue[1];
		v.m_ptValue[2] = m_ptValue[2] - t.m_ptValue[2];
		if (m_VectorType == raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] - t.m_ptValue[3];
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator-(const raaVector4T<T> t) 
{
	if (m_ptValue && t.m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] - t.m_ptValue[0];
		v.m_ptValue[1] = m_ptValue[1] - t.m_ptValue[1];
		v.m_ptValue[2] = m_ptValue[2] - t.m_ptValue[2];
		if (m_VectorType == raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] - t.m_ptValue[3];
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator-(const raaVector4T<T> t) const 
{
	if (m_ptValue && t.m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] - t.m_ptValue[0];
		v.m_ptValue[1] = m_ptValue[1] - t.m_ptValue[1];
		v.m_ptValue[2] = m_ptValue[2] - t.m_ptValue[2];
		if (m_VectorType == raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] - t.m_ptValue[3];
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator/(const raaVector4T<T>& t)
{
	if (m_ptValue && t.m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] / t.m_ptValue[0];
		v.m_ptValue[1] = m_ptValue[1] / t.m_ptValue[1];
		v.m_ptValue[2] = m_ptValue[2] / t.m_ptValue[2];
		if (m_VectorType == raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] / t.m_ptValue[3];
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator/(const T& t)
{
	if (m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] / t;
		v.m_ptValue[1] = m_ptValue[1] / t;
		v.m_ptValue[2] = m_ptValue[2] / t;
		if (m_VectorType == raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] / t;
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator+(const T& t) 
{
	if (m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] + t;
		v.m_ptValue[1] = m_ptValue[1] + t;
		v.m_ptValue[2] = m_ptValue[2] + t;
		if (m_VectorType == raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] + t;
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator*(const T& t)
{
	if (m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] * t;
		v.m_ptValue[1] = m_ptValue[1] * t;
		v.m_ptValue[2] = m_ptValue[2] + t;
		if (m_VectorType == raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] * t;
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}

template <class T>
const raaGL4::raaVector4T<T>& raaGL4::raaVector4T<T>::operator+=(const raaVector4T<T>& t) 
{
	if (m_ptValue)
	{
		m_ptValue[0] += t.m_ptValue[0];
		m_ptValue[1] += t.m_ptValue[1];
		m_ptValue[2] += t.m_ptValue[2];
		if(m_VectorType== raaVector4Type::csm_uiCVec) m_ptValue[3] += t.m_ptValue[3];
		raaAttribute::update();
		return *this;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
const raaGL4::raaVector4T<T>& raaGL4::raaVector4T<T>::operator*=(const raaVector4T<T>& t)
{
	if (m_ptValue)
	{
		m_ptValue[0] *= t.m_ptValue[0];
		m_ptValue[1] *= t.m_ptValue[1];
		m_ptValue[2] *= t.m_ptValue[2];
		if (m_VectorType == raaVector4Type::csm_uiCVec) m_ptValue[3] *= t.m_ptValue[3];
		raaAttribute::update();
		return *this;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
const raaGL4::raaVector4T<T>& raaGL4::raaVector4T<T>::operator+=(const T& t) 
{
	if (m_ptValue)
	{
		m_ptValue[0] += t;
		m_ptValue[1] += t;
		m_ptValue[2] += t;
		if (m_VectorType == raaVector4Type::csm_uiCVec) m_ptValue[3] += t;
		raaAttribute::update();
		return *this;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
const raaGL4::raaVector4T<T>& raaGL4::raaVector4T<T>::operator*=(const T& t)
{
	if (m_ptValue)
	{
		m_ptValue[0] *= t;
		m_ptValue[1] *= t;
		m_ptValue[2] *= t;
		if (m_VectorType == raaVector4Type::csm_uiCVec) m_ptValue[3] *= t;
		raaAttribute::update();
		return *this;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
const raaGL4::raaVector4T<T>& raaGL4::raaVector4T<T>::operator-=(const raaVector4T<T>& t)
{
	if (m_ptValue)
	{
		m_ptValue[0] -= t.m_ptValue[0];
		m_ptValue[1] -= t.m_ptValue[1];
		m_ptValue[2] -= t.m_ptValue[2];
		if (m_VectorType == raaVector4Type::csm_uiCVec) m_ptValue[3] -= t.m_ptValue[3];
		raaAttribute::update();
		return *this;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}
template <class T>
const raaGL4::raaVector4T<T>& raaGL4::raaVector4T<T>::operator/=(const raaVector4T<T>& t)
{
	if (m_ptValue)
	{
		m_ptValue[0] /= t.m_ptValue[0];
		m_ptValue[1] /= t.m_ptValue[1];
		m_ptValue[2] /= t.m_ptValue[2];
		if (m_VectorType == raaVector4Type::csm_uiCVec) m_ptValue[3] /= t.m_ptValue[3];
		raaAttribute::update();
		return *this;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
const raaGL4::raaVector4T<T>& raaGL4::raaVector4T<T>::operator/=(const T& t) 
{
	if (m_ptValue)
	{
		m_ptValue[0] /= t;
		m_ptValue[1] /= t;
		m_ptValue[2] /= t;
		if (m_VectorType == raaVector4Type::csm_uiCVec) m_ptValue[3] /= t;
		raaAttribute::update();
		return *this;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}
/*
template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator*(const raaMatrix4T<T>& t) 
{
	if (!m_ptValue) throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);

	if(t)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] * t[0] + m_ptValue[1] * t[4] + m_ptValue[2] * t[8] + m_ptValue[3] * t[12];
		v.m_ptValue[1] = m_ptValue[0] * t[1] + m_ptValue[1] * t[5] + m_ptValue[2] * t[9] + m_ptValue[3] * t[13];
		v.m_ptValue[2] = m_ptValue[0] * t[2] + m_ptValue[1] * t[6] + m_ptValue[2] * t[10] + m_ptValue[3] * t[14];
		v.m_ptValue[3] = m_ptValue[3];
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);

}
*/
template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator%(const raaVector4T<T>& t) 
{
	if(m_ptValue && t.m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[1] * t.m_ptValue[2] - m_ptValue[2] * t.m_ptValue[1];
		v.m_ptValue[1] = m_ptValue[2] * t.m_ptValue[0] - m_ptValue[0] * t.m_ptValue[2];
		v.m_ptValue[2] = m_ptValue[0] * t.m_ptValue[1] - m_ptValue[1] * t.m_ptValue[0];
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
T raaGL4::raaVector4T<T>::operator^(const raaVector4T<T>& t)
{
	if (m_ptValue && t.m_ptValue)
	{
		return m_ptValue[0] * t.m_ptValue[0] + m_ptValue[1] * t.m_ptValue[1] + m_ptValue[2] * t.m_ptValue[2];
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator!() 
{
	if (m_ptValue)
	{
		T len = ~(*this);
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[1]/len;
		v.m_ptValue[1] = m_ptValue[2]/len;
		v.m_ptValue[2] = m_ptValue[3]/len;
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator!() const 
{
	if (m_ptValue)
	{
		T len = ~(*this);
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[1] / len;
		v.m_ptValue[1] = m_ptValue[2] / len;
		v.m_ptValue[2] = m_ptValue[3] / len;
		v.m_VectorType = m_VectorType;
		return v;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
T raaGL4::raaVector4T<T>::operator~() 
{
	if (m_ptValue)
	{
		return sqrt(m_ptValue[0] * m_ptValue[0] + m_ptValue[1] * m_ptValue[1] + m_ptValue[2] * m_ptValue[2]);
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
T raaGL4::raaVector4T<T>::operator~() const 
{
	if (m_ptValue)
	{
		return sqrt(m_ptValue[0] * m_ptValue[0] + m_ptValue[1] * m_ptValue[1] + m_ptValue[2] * m_ptValue[2]);
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
const T raaGL4::raaVector4T<T>::operator[](unsigned uiIndex) const
{
	if(!m_ptValue) throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
	return m_ptValue[uiIndex];
}

template <class T>
unsigned long raaGL4::raaVector4T<T>::apply(int iLocation)
{
	if(!m_ptValue)  throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
/*
	switch(raaAttribute::m_uiType)
	{
	case GL_FLOAT_VEC4:
		glUniform4fv(iLocation, 1, (T*)m_ptValue);
		break;
	case GL_DOUBLE_VEC4:
		glUniform4dv(iLocation, 1, (T*)m_ptValue);
		break;
	}
*/
	uniform4V(iLocation, 1, m_ptValue);

	return m_ulChangeCount;
}

template <class T>
const raaGL4::raaVector4T<T>& raaGL4::raaVector4T<T>::operator-=(const T& t) 
{
	if (m_ptValue)
	{
		m_ptValue[0] -= t;
		m_ptValue[1] -= t;
		m_ptValue[2] -= t;
		if (m_VectorType == raaVector4Type::csm_uiCVec) m_ptValue[3] -= t;
		raaAttribute::update();
		return *this;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
}

template <class T>
const raaGL4::raaVector4T<T> raaGL4::raaVector4T<T>::operator-(const T& t) 
{
	if (m_ptValue)
	{
		raaVector4T<T> v;
		v.m_ptValue[0] = m_ptValue[0] - t;
		v.m_ptValue[1] = m_ptValue[1] - t;
		v.m_ptValue[2] = m_ptValue[2] - t;
		if (m_VectorType == raaVector4Type::csm_uiCVec) v.m_ptValue[3] = m_ptValue[3] - t;
		else v.m_ptValue[3] = m_ptValue[3];
		v.m_VectorType = m_VectorType;
		return v;

	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValuePtrException);
}

template <class T>
const raaGL4::raaVector4T<T>& raaGL4::raaVector4T<T>::operator=(const raaVector4T<T>& t) 
{
	if (m_ptValue && t.m_ptValue)
	{
		m_ptValue[0] = t.m_ptValue[0];
		m_ptValue[1] = t.m_ptValue[1];
		m_ptValue[2] = t.m_ptValue[2];
		m_ptValue[3] = t.m_ptValue[3];
		m_VectorType = t.m_VectorType;
		raaAttribute::raaAttribute::update();
		return t;
	}
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInputValueException);
}

template <class T>
void raaGL4::raaVector4T<T>::setDataType()
{
	if (std::is_same<T, float>::value)  raaAttribute::m_uiType = GL_FLOAT_VEC4;
	else if (std::is_same<T, int>::value)  raaAttribute::m_uiType = GL_INT_VEC4;
	else if (std::is_same<T, unsigned int>::value)  raaAttribute::m_uiType = GL_UNSIGNED_INT_VEC4;
	else if (std::is_same<T, double>::value)  raaAttribute::m_uiType = GL_DOUBLE_VEC4;
	else throw raaVector4Exception(raaVector4Exception::csm_uiInvalidTypeException);
}
/*
unsigned long raaGL4::raaVector4fv::apply(int iLocation)
{
	if (!m_ptValue)  throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
	glUniform4fv(iLocation, 1, m_ptValue);
	return m_ulChangeCount;
}

unsigned long raaGL4::raaVector4dv::apply(int iLocation)
{
	if (!m_ptValue)  throw raaVector4Exception(raaVector4Exception::csm_uiInvalidInternalValueException);
	glUniform4dv(iLocation, 1, m_ptValue);
	return m_ulChangeCount;
}
*/