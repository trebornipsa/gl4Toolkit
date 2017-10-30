#include "raaShader.h"
#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>


#include<fstream>
#include <sstream>
#include <iostream>

#include "raaShaderStack.h"


raaGL4::raaShader::raaShader(unsigned int uiShaderType, std::string sFilename, std::string sPath): m_uiShaderType(uiShaderType), m_sShaderFile(sFilename), m_sShaderPath(sPath), m_uiShader(0)
{
	if (sFilename.length())
	{
		size_t tNameStart = sFilename.find_last_of('\\');
		size_t tNameEnd = sFilename.find_last_of('.');

		tNameStart = (tNameStart == std::string::npos) ? 0 : ++tNameStart;
		if (tNameEnd != std::string::npos) tNameEnd -= tNameStart;
		
		m_sName = sFilename.substr(++tNameStart, tNameEnd);
		readShader();
	}
}

raaGL4::raaShader::raaShader(std::string sFilename, std::string sPath): m_uiShaderType(0), m_sShaderFile(sFilename), m_sShaderPath(sPath), m_uiShader(0)
{
	if(sFilename.length())
	{
		size_t tNameStart = sFilename.find_last_of('\\');
		size_t tNameEnd = sFilename.find_last_of('.');

		tNameStart = (tNameStart == std::string::npos) ? 0 : ++tNameStart;
		if (tNameEnd != std::string::npos) tNameEnd -= tNameStart;

		m_sName = sFilename.substr(++tNameStart, tNameEnd);

		size_t t= std::string::npos;
		if ((t = sFilename.find_last_of('.')) != std::string::npos)
		{
			m_uiShaderType = nameToType(sFilename.substr(++t, std::string::npos));

			if (!m_uiShaderType) throw "Unknown shader exception";

			readShader();
		}
	}
}

void raaGL4::raaShader::buildShader()
{
	if (!m_uiShader) m_uiShader = glCreateShader(m_uiShaderType);
	const char *pcStr = m_sShader.c_str();
	glShaderSource(m_uiShader, 1, &pcStr, 0);
	glCompileShader(m_uiShader);
}

unsigned raaGL4::raaShader::shader()
{
	return m_uiShader;
}

unsigned raaGL4::raaShader::shaderType()
{
	return m_uiShaderType;
}

void raaGL4::raaShader::releaseShader()
{
	if (m_uiShader)
	{
		glDeleteShader(m_uiShader);
		m_uiShader = 0;
	}
}

std::string& raaGL4::raaShader::code()
{
	return m_sShader;
}

void raaGL4::raaShader::set(std::string sCode)
{
	m_sShader = sCode;
}

void raaGL4::raaShader::saveShader()
{
	std::string sFilename;

	if (m_sShaderPath.length()) sFilename = m_sShaderPath + "\\" + m_sShaderFile;
	else sFilename = raaShaderStack::defaultPath() + "\\" + m_sShaderFile;

	std::ofstream file(sFilename, std::ios::ate | std::ios::binary);

	if(file.is_open())
	{
		file.write(m_sShader.c_str(), m_sShader.length());
		file.close();
	}
}

std::string raaGL4::raaShader::name()
{
	return m_sName;
}

raaGL4::raaShader::~raaShader()
{
	releaseShader();
}

void raaGL4::raaShader::readShader()
{
	std::string sFilename;

	if (m_sShaderPath.length()) sFilename = m_sShaderPath + "\\" + m_sShaderFile;
	else sFilename = raaShaderStack::defaultPath() + "\\" + m_sShaderFile;

	std::ifstream file(sFilename);

	if (file.is_open())
	{
		std::stringstream buffer;
		buffer << file.rdbuf();
		m_sShader = buffer.str();
		file.close();
	}
	else
	{
		std::cout << "failed to open file!->" << sFilename << std::endl;
	}
}

unsigned raaGL4::raaShader::nameToType(std::string sExt)
{
	if (sExt.length())
	{
		if (sExt == "vert") return GL_VERTEX_SHADER;
		else if (sExt == "comp") return GL_COMPUTE_SHADER;
		else if (sExt == "geom") return GL_GEOMETRY_SHADER;
		else if (sExt == "frag") return GL_FRAGMENT_SHADER;
		else if (sExt == "tesc") return GL_TESS_CONTROL_SHADER;
		else if (sExt == "tese") return GL_TESS_EVALUATION_SHADER;
	}

	return  0;
}

unsigned raaGL4::raaShader::fileNameToType(std::string sFilename)
{
	if(sFilename.length() && sFilename.find_last_of('.')!=std::string::npos)
	{
		size_t t = sFilename.find_last_of('.') != std::string::npos;
		std::string sExt = sFilename.substr(++t, std::string::npos);

		return nameToType(sExt);
	}
	return 0;
}
