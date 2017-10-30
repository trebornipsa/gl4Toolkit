#include <windows.h>
#include <GL/glew.h>
#include <gl/gl.h>
#include "raaShader.h"
#include "raaShaderStack.h"
#include  "raaShaderProgramme.h"
#include <iostream>

std::string raaGL4::raaShaderStack::sm_sDefaultPath = "..\\shaders\\";

raaGL4::raaShaderStack::raaShaderStack(): m_pActiveProgramme(0)
{
}

raaGL4::raaShaderStack::~raaShaderStack()
{
}

void raaGL4::raaShaderStack::setDefaultPath(std::string sDefaultShaderPath)
{
	if (sDefaultShaderPath.length()) sm_sDefaultPath = sDefaultShaderPath;
	else sm_sDefaultPath = "..//shaders//";

}

std::string raaGL4::raaShaderStack::defaultPath()
{
	return sm_sDefaultPath;
}

raaGL4::raaShaderProgramme* raaGL4::raaShaderStack::addProgramFromShaderGroup(std::string sShaderName, std::string sPath)
{
	if (!sPath.length()) sPath = sm_sDefaultPath;

	std::string sP = sPath+ "\\"+sShaderName+".*";
	std::wstring sWPath(sP.begin(), sP.end());

	raaShaderProgramme *pProgram = new raaShaderProgramme(sShaderName);

	WIN32_FIND_DATA data;
	HANDLE hFind = ::FindFirstFile(sWPath.c_str(), &data);
	if(hFind!=INVALID_HANDLE_VALUE)
	{
		do
		{
			std::wstring w(data.cFileName);
			std::string s(w.begin(), w.end());

			raaShader *pShader = 0;

			try
			{
				pShader = new raaShader(s, sPath);
			}
			catch(const char* msg)
			{
				if(!strcmp("Unknown shader exception", msg))
				{
					std::cout << "could not create shader -> s";
					delete pShader;
					pShader = 0;
				}
			}

			if (pShader)
			{
				std::string sName = pShader->name();
				unsigned int uiType = pShader->shaderType();

				pShader->buildShader();

				if((m_mShaderNameTypeMap[uiType].find(sName)==m_mShaderNameTypeMap[uiType].end()) 
					&& (m_mShaderTypeMap[uiType].find(pShader->shader()) == m_mShaderTypeMap[uiType].end()) 
					&& pShader->shader())
				{
					m_mShaderNameTypeMap[uiType][sName] = pShader;
					m_mShaderTypeMap[uiType][pShader->shader()] = pShader;
					pProgram->addShader(pShader);
				}
				else delete pShader;
			}
		} while(::FindNextFile(hFind, &data));
		::FindClose(hFind);

		m_mShaderProgrammes[sShaderName] = pProgram;
		pProgram->build();
		return pProgram;
	}
	return 0;
}

void raaGL4::raaShaderStack::useProgramme(raaShaderProgramme* pProgramme)
{
	if (pProgramme != m_pActiveProgramme)
	{
		m_pActiveProgramme = pProgramme;
		if(pProgramme) glUseProgram(pProgramme->programme());
	}

	if(m_pActiveProgramme)
	{
		for(raaAttributeListenerMap::iterator it=m_pActiveProgramme->listeners().begin(); it!= m_pActiveProgramme->listeners().end();it++)
		{
			it->second.apply();
		}
	}
}

void raaGL4::raaShaderStack::updateCurrentProgrammeAttributes()
{
	if (m_pActiveProgramme)
	{
		for (raaAttributeListenerMap::iterator it = m_pActiveProgramme->listeners().begin(); it != m_pActiveProgramme->listeners().end(); it++)
		{
			it->second.apply();
		}
	}
}
