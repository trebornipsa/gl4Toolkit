#pragma once

#include <string>
#include <map>

#include "raaGL4RenderToolsDefs.h"
#include "raaAttributeListener.h"

namespace raaGL4
{
	class raaShader;

	typedef std::map<unsigned int, raaShader*>raaProgrammeShaderMap;
	typedef std::map<std::string, raaAttributeListener> raaAttributeListenerMap;

	class RAAGL4RENDERTOOLS_DLL_DEF raaShaderProgramme
	{
	public:
		raaShaderProgramme(std::string sName);
		virtual ~raaShaderProgramme();

		void addShader(raaShader *pShader);
		void removeShader(raaShader *pShader);
		bool hasShader(raaShader *pShader);
		const raaProgrammeShaderMap& shaders();

		void build();
		void release();

		raaAttributeListenerMap& listeners();

		unsigned int programme();

	protected:
		std::string m_sName;
		raaProgrammeShaderMap m_mShaders;
		unsigned int m_uiProgram;
		raaAttributeListenerMap m_mListeners;
	};
}

