#pragma once

#include <exception>

#include "raaGL4RenderToolsDefs.h"

namespace raaGL4
{
	class raaAttribute;

	class RAAGL4RENDERTOOLS_DLL_DEF raaAttributeListener
	{
	public:

		class raaAttributeListenerException: public std::exception
		{
		public:
			const static unsigned int csm_uiNoExcpetion = 0;
			const static unsigned int cms_uiTypeMismatchException = 1;

			raaAttributeListenerException(unsigned int uiCode);
			unsigned int code();
			std::string description();
		protected:
			unsigned int m_uiCode;
		};


		raaAttributeListener(unsigned int uiType, unsigned int uiProgram=0, unsigned int iLocation=-1, raaAttribute *pAttribute=0);
		raaAttributeListener(const raaAttributeListener& r);
		raaAttributeListener();
		virtual ~raaAttributeListener();

		void setAttribute(raaAttribute *pAttribute);
		raaAttribute* attribute();

		bool hasChanged();
		void discardChangeUpdate();
		void resetChangeCount();
		void apply();

		void updateProgramLocation(unsigned int uiProgram, int iLocation);

		const raaAttributeListener& operator=(const raaAttributeListener &r);

	protected:
		raaAttribute *m_pAttribute;
		unsigned long m_ulLastActionedChangeCount;
		unsigned int m_uiType;
		unsigned int m_uiProgram;
		int m_iLocation;
	};
}
