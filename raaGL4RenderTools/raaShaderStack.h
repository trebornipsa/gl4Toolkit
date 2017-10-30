#pragma once

#include <string>
#include <map>

#include "raaGL4RenderToolsDefs.h"

namespace raaGL4
{
	class raaShader;
	class raaShaderProgramme;

	typedef std::map<unsigned int, raaShader*> raaShaderMap;
	typedef std::map<unsigned int, raaShaderMap> raaShaderTypeMap;
	typedef std::map<std::string, raaShader*> raaShaderNameMap;
	typedef std::map<unsigned int, raaShaderNameMap> raaShaderNameTypeMap;
	typedef std::map<unsigned int, raaShaderProgramme*> raaShaderProgramMap;
	typedef std::map<std::string, raaShaderProgramme*> raaShaderProgramNameMap;

	class RAAGL4RENDERTOOLS_DLL_DEF raaShaderStack
	{
	public:
		raaShaderStack();
		~raaShaderStack();

		static void setDefaultPath(std::string sDefaultShaderPath);
		static std::string defaultPath();

		raaShaderProgramme* addProgramFromShaderGroup(std::string sShaderName, std::string sPath = "");

		void useProgramme(raaShaderProgramme *pProgramme);
		void updateCurrentProgrammeAttributes();

	protected:
		static std::string sm_sDefaultPath;
		raaShaderTypeMap m_mShaderTypeMap;
		raaShaderNameTypeMap m_mShaderNameTypeMap;
		raaShaderProgramNameMap m_mShaderProgrammes;
		raaShaderProgramme *m_pActiveProgramme;
	};
}
