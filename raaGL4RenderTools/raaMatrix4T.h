#pragma once

#include <string>
#include <list>
#include "raaAttribute.h"
#include "raaVector4T.h"

#include "raaGL4RenderToolsDefs.h"

namespace raaGL4
{


	template<class T>
	class RAAGL4RENDERTOOLS_DLL_DEF raaMatrix4T: public raaAttribute
	{
		typedef std::list<T*> raaMatrix4TStack;
	public:
		class RAAGL4RENDERTOOLS_DLL_DEF  raaMatrix4Exception : public std::exception
		{
		public:
			const static unsigned int csm_uiNoException = 0;
			const static unsigned int csm_uiInvalidTypeException = 1;
			const static unsigned int csm_uiInvalidInputPtrException = 2;
			const static unsigned int csm_uiInvalidInternalPtrException = 3;
			const static unsigned int csm_uiInvertDivisonByZeroException = 4;
			const static unsigned int csm_uiMatrixIndexOutOfBoundsException = 5;
			const static unsigned int csm_uiStackInvalidPop = 6;
			const static unsigned int csm_uiMatrixInversionNotPossible = 7;

			raaMatrix4Exception(unsigned int uiCode = 0);

			unsigned int code();
			std::string msg();

		protected:
			unsigned int m_uiCode;
		};

		class RAAGL4RENDERTOOLS_DLL_DEF raaMatrix4Containment
		{
		public:
			const static unsigned int csm_uiContained = 0;
			const static unsigned int csm_uiReference = 1;

			raaMatrix4Containment(unsigned int uiContainmentType = csm_uiContained);
			raaMatrix4Containment(const raaMatrix4Containment &t);

			bool operator==(const raaMatrix4Containment& t) const;
			bool operator==(const unsigned int t) const;
			bool operator!=(const raaMatrix4Containment& t) const;
			bool operator!=(const unsigned int t) const;

			const raaMatrix4Containment& operator=(const raaMatrix4Containment& t);
			const raaMatrix4Containment& operator=(const unsigned int t);

			operator unsigned int();
			unsigned int value();



		protected:
			unsigned int m_uiContainmentType;
		};

		raaMatrix4T(raaMatrix4Containment t = raaMatrix4Containment(raaMatrix4Containment::csm_uiContained), T* pRawValue=0);
		raaMatrix4T(const raaMatrix4T<T> &t);

		virtual ~raaMatrix4T();

		// load identity
		static const raaMatrix4T<T> identity(); // returns identity -> you could just make a new matrix

		//copy
		const raaMatrix4T<T>& operator=(const raaMatrix4T<T> &t);
		void copy(const raaMatrix4T<T> &t);

		// mult
		const raaMatrix4T<T> operator*(const raaMatrix4T<T> &t);
		void mult(const raaMatrix4T<T> &t);

		// transpose
		const raaMatrix4T<T> operator~(); // returns transpose of matrix

		// invert
		const raaMatrix4T<T> operator!(); // full invert with invertion cached

		operator const T*() const;
		const T* ptr() const;
		const T operator[](unsigned int uiIndex);

		// from mesa
		void rotate(T degrees, raaGL4::raaVector4T<T>& v);
		void translate(const raaGL4::raaVector4T<T>& v);
		void scale(const raaGL4:: raaVector4T<T>& v);


		// vector matrix multiplication
		friend const raaVector4T<T> operator*(const raaVector4T<T>& v, const raaMatrix4T<T>& m);
		friend const raaVector4T<T> operator*(const raaVector4T<T>& v, raaMatrix4T<T>& m);
		friend const raaVector4T<T> operator*(raaVector4T<T>& v, const raaMatrix4T<T>& m);
		friend const raaVector4T<T> operator*(raaVector4T<T>& v, raaMatrix4T<T>& m);
		static const raaVector4T<T> mult(const raaVector4T<T> &v, const raaMatrix4T<T>& m);

		// stack functions
		void push();
		void pop();

		//projection
		void frustum(T l, T r, T b, T t, T n, T f);
		void ortho(T l, T r, T b, T t, T n, T f);
		void perspective(T degreesFOV, T aspect, T n, T f);
		void lookAt(const raaVector4T<T> &eye, const raaVector4T<T> &target, const raaVector4T<T> &up);
		static const raaVector4T<T> project(raaVector4T<T> obj, raaMatrix4T<T> &modelView, raaMatrix4T<T> &projection, int *viewport);
		static const raaVector4T<T> unproject(raaVector4T<T> win, raaMatrix4T<T> &modelView, raaMatrix4T<T> &projection, int *viewport);

		// dirty the inverse flag to force full re-calc on next call to inverse
		void dirtyInverse();

		unsigned long apply(int iLocation) override;

	protected:
		void setDataType();
		T* m_ptValue;
		T m_ptInvValue[16];
		raaMatrix4TStack m_Stack;
		raaMatrix4Containment m_Containment;

		void swapVals(T &a, T&b);
		bool m_bDirtyInverse;
	
	};


	

	template raaMatrix4T<float>;
	typedef raaMatrix4T<float> raaMatrix4fv;
	template raaMatrix4T<double>;
	typedef raaMatrix4T<double> raaMatrix4dv;
/*

	class raaMatrix4fv: public raaMatrix4T<float>
	{
	public:
		unsigned long apply(int iLocation) override;
	};

	class raaMatrix4dv: public raaMatrix4T<double>
	{
	public:
		unsigned long apply(int iLocation) override;
	};
*/

// only provide for completeness so functions in raaVector4T work -> do not use -> need to resolve compilation issues
//	template raaMatrix4T<int>;
//	template raaMatrix4T<unsigned int>;


}
