#pragma once



#include "raaGL4RenderToolsDefs.h"
#include "raaAttribute.h"

namespace raaGL4
{
	template <class T>
	class RAAGL4RENDERTOOLS_DLL_DEF raaAttributeT: public raaAttribute
	{
	public:
		raaAttributeT();
		raaAttributeT(const T t);
		raaAttributeT(const raaAttributeT<T> &t);
		virtual ~raaAttributeT();


		virtual const T* ptr() const;
		virtual T value();

		T operator=(T &t);
		const T operator=(const T &t);
		T operator=(raaAttributeT<T> &t);
		const T operator=(const raaAttributeT<T> &t);

		T operator*(T &t);
		const T operator*(const T &t);
		T operator*(raaAttributeT<T> &t);
		const T operator*(const raaAttributeT<T> &t);

		T operator*=(T& t);
		const T operator*=(const T& t);
		T operator*=(raaAttributeT<T>& t);
		const T operator*=(const raaAttributeT<T>& t);

		T operator/(T &t);
		const T operator/(const T &t);
		T operator/(raaAttributeT<T> &t);
		const T operator/(const raaAttributeT<T> &t);

		T operator/=(T& t);
		const T operator/=(const T& t);
		T operator/=(raaAttributeT<T>& t);
		const T operator/=(const raaAttributeT<T>& t);

		T operator+(T &t);
		const T operator+(const T &t);
		T operator+(raaAttributeT<T> &t);
		const T operator+(const raaAttributeT<T> &t);

		T operator+=(T& t);
		const T operator+=(const T& t);
		T operator+=(raaAttributeT<T>& t);
		const T operator+=(const raaAttributeT<T>& t);

		T operator-(T &t);
		const T operator-(const T &t);
		T operator-(raaAttributeT<T> &t);
		const T operator-(const raaAttributeT<T> &t);

		T operator-=(T& t);
		const T operator-=(const T& t);
		T operator-=(raaAttributeT<T>& t);
		const T operator-=(const raaAttributeT<T>& t);

		unsigned long apply(int iLocation) override;

		operator T();
		operator const T() const;
	protected:
		T m_tValue;

		void setType();

	};
	
	template raaAttributeT<float>;
	typedef raaAttributeT<float> raaAttribute1F;
	template raaAttributeT<int>;
	typedef raaAttributeT<int> raaAttribute1I;
	template raaAttributeT<unsigned int>;
	typedef raaAttributeT<unsigned int> raaAttribute1UI;
	template raaAttributeT<double>;
	typedef raaAttributeT<double> raaAttribute1D;
	
	/*
	class raaAttribute1f : public raaAttributeT<float>
	{
	public:
		unsigned long apply(int iLocation) override;
	};

	class raaAttribute1i : public raaAttributeT<float>
	{
	public:
		unsigned long apply(int iLocation) override;
	};

	class raaAttribute1ui : public raaAttributeT<float>
	{
	public:
		unsigned long apply(int iLocation) override;
	};

	class raaAttribute1d : public raaAttributeT<float>
	{
	public:
		unsigned long apply(int iLocation) override;
	};
	*/
}
