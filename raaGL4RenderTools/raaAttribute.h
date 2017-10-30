#pragma once
#include "raaGL4RenderToolsDefs.h"
#include <exception>
#include <string>
#include "raaGL4Helper.h"

namespace raaGL4
{
	class RAAGL4RENDERTOOLS_DLL_DEF raaAttribute: protected raaGL4Helper
	{
	public:
		class raaAttributeException: public std::exception
		{
		public:
			const static unsigned int csm_uiNoException = 0;
			const static unsigned int csm_uiFloatException = 1;
			const static unsigned int csm_uiIntException = 2;
			const static unsigned int csm_uiUIntException = 3;
			const static unsigned int csm_uiDoubleException = 4;
			const static unsigned int csm_uiDeleteWhileListersActive = 5;
			const static unsigned int csm_uiApplyException = 6;


			raaAttributeException(unsigned int uiCode=0);

			unsigned int code();
			std::string msg();

		protected:
			unsigned int m_uiCode;
		};

		raaAttribute(unsigned int uiType=0);
		virtual ~raaAttribute();

		void update();
		unsigned long changeCount();



		unsigned int type();

		unsigned int listenerCount();
		void refListener();
		void unrefListener();

		virtual unsigned long apply(int iLocation);

	protected:
		unsigned long m_ulChangeCount;
		unsigned int m_uiType;
		unsigned int m_uiListenerCount;
	};
}

