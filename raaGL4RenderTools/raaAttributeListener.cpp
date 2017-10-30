
#include "raaAttribute.h"
#include "raaAttributeListener.h"
#include <iostream>

raaGL4::raaAttributeListener::raaAttributeListenerException::raaAttributeListenerException(unsigned uiCode): m_uiCode(uiCode)
{
	
}

unsigned raaGL4::raaAttributeListener::raaAttributeListenerException::code()
{
	return m_uiCode;
}

std::string raaGL4::raaAttributeListener::raaAttributeListenerException::description()
{
	switch(m_uiCode)
	{
	case cms_uiTypeMismatchException:
		return "the attribute type and listener type do not match";
	default:
		return "no exception";
	}
}

raaGL4::raaAttributeListener::raaAttributeListener(unsigned uiType, unsigned uiProgram, unsigned iLocation, raaAttribute* pAttribute): m_uiType(uiType), m_uiProgram(m_uiProgram), m_iLocation(iLocation), m_ulLastActionedChangeCount(0), m_pAttribute(pAttribute)
{
	if (m_pAttribute)
	{
		if (m_pAttribute->type() != m_uiType) throw raaAttributeListenerException(raaAttributeListenerException::cms_uiTypeMismatchException);

		m_pAttribute->refListener();
	}
}

raaGL4::raaAttributeListener::raaAttributeListener(const raaAttributeListener& r): m_iLocation(r.m_iLocation), m_uiProgram(r.m_uiProgram), m_uiType(r.m_uiType), m_ulLastActionedChangeCount(r.m_ulLastActionedChangeCount), m_pAttribute(r.m_pAttribute)
{
}

raaGL4::raaAttributeListener::raaAttributeListener()
{
	m_iLocation = -1;
	m_uiProgram = 0;
	m_uiType = 0;
	m_ulLastActionedChangeCount = 0;
	m_pAttribute = 0;

}

void raaGL4::raaAttributeListener::setAttribute(raaAttribute* pAttribute)
{
	if (m_pAttribute) m_pAttribute->unrefListener();
	m_pAttribute = pAttribute;
	if (m_pAttribute)
	{
		m_ulLastActionedChangeCount = 0;
		if (m_pAttribute->type() != m_uiType) throw raaAttributeListenerException(raaAttributeListenerException::cms_uiTypeMismatchException);
		m_pAttribute->refListener();
	}
}

raaGL4::raaAttribute* raaGL4::raaAttributeListener::attribute()
{
	return m_pAttribute;
}

bool raaGL4::raaAttributeListener::hasChanged()
{
	if(m_pAttribute)
	{
		if (m_pAttribute->changeCount() > m_ulLastActionedChangeCount) return true;
	}
	return false;
}

void raaGL4::raaAttributeListener::discardChangeUpdate()
{
	if(m_pAttribute) m_ulLastActionedChangeCount = m_pAttribute->changeCount();
}

void raaGL4::raaAttributeListener::resetChangeCount()
{
	m_ulLastActionedChangeCount = 0;
}

void raaGL4::raaAttributeListener::apply()
{
	if (hasChanged())
	{
		try
		{
			m_ulLastActionedChangeCount = m_pAttribute->apply(m_iLocation);
		}
		catch (raaAttribute::raaAttributeException &e)
		{
			std::cout <<e.msg() << std::endl;
		}
	}
}

void raaGL4::raaAttributeListener::updateProgramLocation(unsigned uiProgram, int iLocation)
{
	m_uiProgram = uiProgram;
	m_iLocation = iLocation;
	m_ulLastActionedChangeCount = 0;
}

const raaGL4::raaAttributeListener& raaGL4::raaAttributeListener::operator=(const raaAttributeListener& r) 
{
	m_iLocation = r.m_iLocation;
	m_uiProgram = r.m_uiProgram;
	m_uiType = r.m_uiType;
	m_ulLastActionedChangeCount = r.m_ulLastActionedChangeCount;
	m_pAttribute = r.m_pAttribute;
	return r;
}

raaGL4::raaAttributeListener::~raaAttributeListener()
{
	if (m_pAttribute) m_pAttribute->unrefListener();
}
