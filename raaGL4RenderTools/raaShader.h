#pragma once

#include <string>

#include "raaGL4RenderToolsDefs.h"

namespace raaGL4
{
	class RAAGL4RENDERTOOLS_DLL_DEF raaShader
	{
	public:
		raaShader(unsigned int uiShaderType, std::string sFilename, std::string sPath = "");
		raaShader(std::string sFilename, std::string sPath = "");
		virtual ~raaShader();

		void buildShader();
		unsigned int shader();
		unsigned int shaderType();
		void releaseShader();
		std::string& code();
		void set(std::string sCode);
		void saveShader();
		std::string name();

		static unsigned int nameToType(std::string sExt);
		static unsigned int fileNameToType(std::string sFilename);

	protected:
		void readShader();
		std::string m_sShader;
		unsigned int m_uiShaderType;
		std::string m_sShaderFile;
		std::string m_sShaderPath;
		unsigned int m_uiShader;
		std::string m_sName;
	};
}