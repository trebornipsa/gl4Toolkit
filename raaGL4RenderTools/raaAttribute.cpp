#include "raaAttribute.h"

raaGL4::raaAttribute::raaAttributeException::raaAttributeException(unsigned uiCode): m_uiCode(uiCode)
{
	
}

unsigned raaGL4::raaAttribute::raaAttributeException::code()
{
	return m_uiCode;
}

std::string raaGL4::raaAttribute::raaAttributeException::msg()
{
	switch(m_uiCode)
	{
	case csm_uiFloatException:
		return "float type exception";
	case csm_uiIntException:
		return "int type exception";
	case csm_uiUIntException:
		return "unit type exception";
	case csm_uiDoubleException:
		return "double type exception";
	case csm_uiDeleteWhileListersActive:
		return "attempting to delete attribute while listeners still active - see listener count";
	case csm_uiApplyException:
		return "cannot apply attribute";
	default:
		return "undefined type exception";
	}
}

raaGL4::raaAttribute::raaAttribute(unsigned int uiType): m_uiType(uiType), m_ulChangeCount(1), m_uiListenerCount(0)
{
}

void raaGL4::raaAttribute::update()
{
	m_ulChangeCount++;
}

unsigned long raaGL4::raaAttribute::changeCount()
{
	return m_ulChangeCount;
}



unsigned raaGL4::raaAttribute::type()
{
	return m_uiType;
}

unsigned raaGL4::raaAttribute::listenerCount()
{
	return m_uiListenerCount;
}

void raaGL4::raaAttribute::refListener()
{
	m_uiListenerCount++;
}

void raaGL4::raaAttribute::unrefListener()
{
	m_uiListenerCount--;
}

unsigned long raaGL4::raaAttribute::apply(int iLocation)
{
	throw raaAttributeException(raaAttributeException::csm_uiApplyException);

	return m_ulChangeCount;
}

raaGL4::raaAttribute::~raaAttribute()
{
	if(m_uiListenerCount) throw raaAttributeException(raaAttributeException::csm_uiDeleteWhileListersActive);
}
