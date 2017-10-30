#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "raaShader.h"
#include "raaShaderProgramme.h"
#include <iostream>

raaGL4::raaShaderProgramme::raaShaderProgramme(std::string sName) : m_sName(sName), m_uiProgram(0)
{

}

void raaGL4::raaShaderProgramme::addShader(raaShader* pShader)
{
	if (pShader) m_mShaders[pShader->shaderType()] = pShader;
}

void raaGL4::raaShaderProgramme::removeShader(raaShader* pShader)
{
	if (pShader && m_mShaders[pShader->shaderType()] == pShader) m_mShaders.erase(pShader->shaderType());
}

bool raaGL4::raaShaderProgramme::hasShader(raaShader* pShader)
{
	if (pShader && m_mShaders[pShader->shaderType()] == pShader) return true;
	return false;
}

const raaGL4::raaProgrammeShaderMap& raaGL4::raaShaderProgramme::shaders()
{
	return m_mShaders;
}

void raaGL4::raaShaderProgramme::build()
{
	if (!m_uiProgram) m_uiProgram = glCreateProgram();
	for(raaProgrammeShaderMap::iterator it=m_mShaders.begin();it!=m_mShaders.end();it++) glAttachShader(m_uiProgram, it->second->shader());
	glLinkProgram(m_uiProgram);

	// now identify the inputs
	// currently using older version (upto4.3) -> new version is ARB_program_interface_query
	int iNumAttrbutes = 0;
	
	glGetProgramiv(m_uiProgram, GL_ACTIVE_ATTRIBUTES, &iNumAttrbutes);

	for(int i=0;i<iNumAttrbutes;i++)
	{
		char acAttrib[256];
		GLsizei iLen = 00;
		int iSize = 0;
		unsigned int uiType;
		int iLoc = 0;

		glGetActiveAttrib(m_uiProgram, i, 256, &iLen, &iSize, &uiType, acAttrib);
//		glGetAttribLocation(m_uiProgram, acAttrib);
		m_mListeners[acAttrib] = raaAttributeListener(uiType, m_uiProgram, glGetAttribLocation(m_uiProgram, acAttrib));

		std::string sType;

		switch(uiType)
		{
		case GL_FLOAT:
			sType = "GL_FLOAT";
			break;
		case GL_FLOAT_VEC2:
			sType = "GL_FLOAT_VEC2";
			break;
		case GL_FLOAT_VEC3:
			sType = "GL_FLOAT_VEC3";
			break;
		case GL_FLOAT_VEC4:
			sType = "GL_FLOAT_VEC4";
			break;
		case GL_FLOAT_MAT2:
			sType = "GL_FLOAT_MAT2";
			break;
		case GL_FLOAT_MAT3:
			sType = "GL_FLOAT_MAT3";
			break;
		case GL_FLOAT_MAT4:
			sType = "GL_FLOAT_MAT4";
			break;
		case GL_FLOAT_MAT2x3:
			sType = "GL_FLOAT_MAT2x3";
			break;
		case GL_FLOAT_MAT2x4:
			sType = "GL_FLOAT_MAT2x4";
			break;
		case GL_FLOAT_MAT3x2:
			sType = "GL_FLOAT_MAT3x2";
			break;
		case GL_FLOAT_MAT3x4:
			sType = "GL_FLOAT_MAT3x4";
			break;
		case GL_FLOAT_MAT4x2:
			sType = "GL_FLOAT_MAT4x2";
			break;
		case GL_FLOAT_MAT4x3:
			sType = "GL_FLOAT_MAT4x3";
			break;
		case GL_INT:
			sType = "GL_INT";
			break;
		case GL_INT_VEC2:
			sType = "GL_INT_VEC2";
			break;
		case GL_INT_VEC3:
			sType = "GL_INT_VEC3";
			break;
		case GL_INT_VEC4:
			sType = "GL_INT_VEC4";
			break;
		case GL_UNSIGNED_INT:
			sType = "GL_UNSIGNED_INT";
			break;
		case GL_UNSIGNED_INT_VEC2:
			sType = "GL_UNSIGNED_INT_VEC2";
			break;
		case GL_UNSIGNED_INT_VEC3:
			sType = "GL_UNSIGNED_INT_VEC3";
			break;
		case GL_UNSIGNED_INT_VEC4:
			sType = "GL_UNSIGNED_INT_VEC4";
			break;
		case GL_DOUBLE:
			sType = "GL_DOUBLE";
			break;
		case GL_DOUBLE_VEC2:
			sType = "GL_DOUBLE_VEC2";
			break;
		case GL_DOUBLE_VEC3:
			sType = "GL_DOUBLE_VEC3";
			break;
		case GL_DOUBLE_VEC4:
			sType = "GL_DOUBLE_VEC4";
			break;
		case GL_DOUBLE_MAT2:
			sType = "GL_DOUBLE_MAT2";
			break;
		case GL_DOUBLE_MAT3:
			sType = "GL_DOUBLE_MAT3";
			break;
		case GL_DOUBLE_MAT4:
			sType = "GL_DOUBLE_MAT4";
			break;
		case GL_DOUBLE_MAT2x3:
			sType = "GL_DOUBLE_MAT2x3";
			break;
		case GL_DOUBLE_MAT2x4:
			sType = "GL_DOUBLE_MAT2x4";
			break;
		case GL_DOUBLE_MAT3x2:
			sType = "GL_DOUBLE_MAT3x2";
			break;
		case GL_DOUBLE_MAT3x4:
			sType = "GL_DOUBLE_MAT3x4";
			break;
		case GL_DOUBLE_MAT4x2:
			sType = "GL_DOUBLE_MAT4x2";
			break;
		case GL_DOUBLE_MAT4x3:
			sType = "GL_DOUBLE_MAT4x3";
			break;
		default:
			sType = "Unknow";
			break;
		}

//		std::cout << "Attrib -> " << acAttrib << " :: " << iSize << " of type -> " << sType << std::endl;
	}
}

void raaGL4::raaShaderProgramme::release()
{
	if (m_uiProgram) glDeleteProgram(m_uiProgram);
	m_uiProgram = 0;
}

raaGL4::raaAttributeListenerMap& raaGL4::raaShaderProgramme::listeners()
{
	return m_mListeners;
}

unsigned raaGL4::raaShaderProgramme::programme()
{
	return m_uiProgram;
}

raaGL4::raaShaderProgramme::~raaShaderProgramme()
{
	release();
}
