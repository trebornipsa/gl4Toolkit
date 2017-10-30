#pragma once

#include "raaAttribute.h"
//#include "raaMatrix4T.h"
#include "raaGL4RenderToolsDefs.h"



namespace raaGL4
{
	
	

	template <class T>
	class RAAGL4RENDERTOOLS_DLL_DEF raaVector4T : public raaAttribute
	{
	public:

		class RAAGL4RENDERTOOLS_DLL_DEF  raaVector4Exception : public std::exception
		{
		public:
			const static unsigned int csm_uiNoException = 0;
			const static unsigned int csm_uiInvalidValuePtrException = 1;
			const static unsigned int csm_uiInvalidInputValuePtrException = 2;
			const static unsigned int csm_uiInvalidInputValueException = 3;
			const static unsigned int csm_uiInvalidInternalValueException = 4;
			const static unsigned int csm_uiInvalidTypeException = 5;

			raaVector4Exception(unsigned int uiCode = 0);

			unsigned int code();
			std::string msg();

		protected:
			unsigned int m_uiCode;
		};

		class RAAGL4RENDERTOOLS_DLL_DEF raaVector4Type
		{
		public:
			const static unsigned int csm_uiPVec = 1;
			const static unsigned int csm_uiDVec = 2;
			const static unsigned int csm_uiCVec = 3;

			raaVector4Type(unsigned int uiVectorType= csm_uiPVec);
			raaVector4Type(const raaVector4Type &t);

			bool operator==(const raaVector4Type& t) const;
			bool operator==(const raaVector4Type t) const;
			bool operator==(const unsigned int t) const;
			bool operator!=(const raaVector4Type& t) const;
			bool operator!=(const unsigned int t) const;
			const raaVector4Type& operator=(const raaVector4Type& t);
			const raaVector4Type& operator=(const unsigned int t);

			operator unsigned int();

		protected:
			unsigned int m_uiVectorType;
		};

		class RAAGL4RENDERTOOLS_DLL_DEF raaVector4Containment
		{
		public:
			const static unsigned int csm_uiContained = 0;
			const static unsigned int csm_uiReference = 1;

			raaVector4Containment(unsigned int uiContainmentType = csm_uiContained);
			raaVector4Containment(const raaVector4Containment &t);

			bool operator==(const raaVector4Containment& t) const;
			bool operator==(const unsigned int t) const;
			bool operator!=(const raaVector4Containment& t) const;
			bool operator!=(const unsigned int t) const;
			const raaVector4Containment& operator=(const raaVector4Containment& t);
			const raaVector4Containment& operator=(const unsigned int t);

			operator unsigned int();
			unsigned int value();

		protected:
			unsigned int m_uiContainmentType;
		};



		raaVector4T(raaVector4Type t = raaVector4Type(raaVector4Type::csm_uiPVec), T* ptValue = 0);
		raaVector4T(T t0, T t1, T t2, raaVector4Type t = raaVector4Type(raaVector4Type::csm_uiPVec));
		raaVector4T(T t0, T t1, T t2, T t3, raaVector4Type t = raaVector4Type(raaVector4Type::csm_uiPVec));
		raaVector4T(raaVector4T<T> &t);
		virtual ~raaVector4T();

		const T* ptr() const;
		T value(unsigned int uiIndex);

		void zero();
		void changeVectorType(const raaVector4Type &t);
		const raaVector4Type& vectorType();
		const raaVector4Type& vectorType() const;
		const raaVector4Containment& containmentType();
		void changeContainmentType(const raaVector4Containment& t, T* pRawData = 0);

		void set(T v0, T v1, T v2);
		void set(T v0, T v1, T v2, T v3);
		void shiftAndScale(T shift, T scale);

		// todo -> check and make sure that all routes are completed
		const raaVector4T<T>& operator=(const raaVector4T<T> &t);
		const raaVector4T<T> operator+(const raaVector4T<T> &t); // vector add
		const raaVector4T<T> operator+(const raaVector4T<T> t); // vector add
		const raaVector4T<T> operator+(const T &t); // scalar add
		const raaVector4T<T> operator-(const raaVector4T<T> &t); // vector sub
		const raaVector4T<T> operator-(const raaVector4T<T> &t) const; // vector sub
		const raaVector4T<T> operator-(const raaVector4T<T> t); // vector sub
		const raaVector4T<T> operator-(const raaVector4T<T> t) const; // vector sub
		const raaVector4T<T> operator-(const T &t); // vector sub
		const raaVector4T<T>& operator+=(const raaVector4T<T> &t); // vector add
		const raaVector4T<T>& operator+=(const T &t); // scalar add
		const raaVector4T<T>& operator-=(const raaVector4T<T> &t); // vector sub
		const raaVector4T<T>& operator-=(const T &t); // vector sub
		const raaVector4T<T> operator*(const raaVector4T<T> &t); // vector add
		const raaVector4T<T> operator*(const T &t); // scalar add
		const raaVector4T<T> operator/(const raaVector4T<T> &t); // vector sub
		const raaVector4T<T> operator/(const T &t); // vector sub
		const raaVector4T<T>& operator*=(const raaVector4T<T> &t); // vector add
		const raaVector4T<T>& operator*=(const T &t); // scalar add
		const raaVector4T<T>& operator/=(const raaVector4T<T> &t); // vector sub
		const raaVector4T<T>& operator/=(const T &t); // vector sub
//		const raaVector4T<T> operator*(const raaMatrix4T<T> &t); // mult by matrix

		// % -> cross product
		const raaVector4T<T> operator%(const raaVector4T<T> &t);

		// ^ -> dot product
		T operator^(const raaVector4T<T> &t);

		// ! -> normalise
		const raaVector4T<T> operator!();
		const raaVector4T<T> operator!() const;

		// ~ -> length
		T operator~();
		T operator~() const;

		const T operator[](unsigned int uiIndex) const;

		unsigned long apply(int iLocation) override;

	protected:
		T* m_ptValue;
		raaVector4Type m_VectorType;
		raaVector4Containment m_Containment;

		void setDataType();
	};

	template raaVector4T<float>;
	typedef raaVector4T<float> raaVector4fv;
	template raaVector4T<double>;
	typedef raaVector4T<double> raaVector4dv;
/*
	class raaVector4fv: public raaVector4T<float>
	{
	public:
//		raaVector4T(raaVector4Type t = raaVector4Type(raaVector4Type::csm_uiPVec), float* ptValue = 0);
//		raaVector4T(float t0, float t1, float t2, raaVector4Type t = raaVector4Type(raaVector4Type::csm_uiPVec));
//		raaVector4T(T t0, T t1, T t2, T t3, raaVector4Type t = raaVector4Type(raaVector4Type::csm_uiPVec));
//		raaVector4T(raaVector4T<T> &t);

		unsigned long apply(int iLocation) override;
	};


	class raaVector4dv: public raaVector4T<double>
	{
	public:
		unsigned long apply(int iLocation) override;

	};

	// not needed at moment and need to resolve compilation issues
	//	template raaVector4T<int>;
	//	typedef raaVector4T<int> raaVector4iv;
	//	template raaVector4T<unsigned int>;
	//	typedef raaVector4T<unsigned int> raaVector4uiv;
*/

}

