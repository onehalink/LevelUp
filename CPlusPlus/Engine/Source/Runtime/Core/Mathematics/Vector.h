#pragma once

#include "../System/Memory.h"

#include "Math.h"



namespace Engine
{
	using Dimension = SizeType;


	template<Dimension, typename T> struct Vector;

	using Vector2Int = Vector<2, Int32>;
	using Vector3Int = Vector<3, Int32>;
	using Vector4Int = Vector<4, Int32>;

	using Vector2 = Vector<2, RealType>;
	using Vector3 = Vector<3, RealType>;
	using Vector4 = Vector<4, RealType>;


	template<typename T> Vector<2, T> ToVector2(const Vector<3, T>& vector3);
	template<typename T> Vector<2, T> ToVector2(const Vector<4, T>& vector4);
	template<typename T> Vector<3, T> ToVector3(const Vector<2, T>& vector2, T z = T());
	template<typename T> Vector<3, T> ToVector3(const Vector<4, T>& vector4);
	template<typename T> Vector<4, T> ToVector4(const Vector<2, T>& vector2, T z = T(), T w = T());
	template<typename T> Vector<4, T> ToVector4(const Vector<3, T>& vector3, T w = T());


	template<Dimension D, typename T> Vector<D, T> Lerp(const Vector<D, T>& from, const Vector<D, T>& to, RealType amount);


	template<Dimension D, typename T> T Dot(const Vector<D, T>& leftHandSide, const Vector<D, T>& rightHandSide);
	template<Dimension D, typename T> auto Cross(const Vector<D, T>& leftHandSide, const Vector<D, T>& rightHandSide);
	template<Dimension D, typename T> T Magnitude(const Vector<D, T>& instance);
	template<Dimension D, typename T> Vector<D, T> Normalize(const Vector<D, T>& instance);


	template<Dimension D, typename T>
	struct Vector
	{
		T components[D];


		Vector();
		template<typename ...Parameters> Vector(Parameters ...parameters);
		Vector(const Vector<D, T>& other);


		Vector<D, T>& operator=(const Vector<D, T>& other);

		T& operator[](SizeType index);
		const T& operator[](SizeType index) const;

		Vector<D, T> operator+() const;
		Vector<D, T> operator-() const;

		Vector<D, T> operator+(const Vector<D, T>& other) const;
		Vector<D, T> operator-(const Vector<D, T>& other) const;
		Vector<D, T> operator*(const Vector<D, T>& other) const;

		Vector<D, T> operator*(T scalar) const;
		friend Vector<D, T> operator*(T scalar, const Vector<D, T>& instance);
		Vector<D, T> operator/(T scalar) const;

		Vector<D, T>& operator+=(const Vector<D, T>& other);
		Vector<D, T>& operator-=(const Vector<D, T>& other);
		Vector<D, T>& operator*=(const Vector<D, T>& other);

		Vector<D, T>& operator*=(T scalar);
		Vector<D, T>& operator/=(T scalar);
	private:
		Void CopyFrom(const Vector<D, T>& instance);
	};


#pragma region Details
	template<typename T>
	Vector<2, T> ToVector2(const Vector<3, T>& vector3)
	{
		return Vector<2, T>( vector3[0], vector3[1] );
	}

	template<typename T>
	Vector<2, T> ToVector2(const Vector<4, T>& vector4)
	{
		return Vector<2, T>( vector4[0], vector4[1] );
	}

	template<typename T>
	Vector<3, T> ToVector3(const Vector<2, T>& vector2, T z)
	{
		return Vector<3, T>( vector2[0], vector2[1], z );
	}

	template<typename T>
	Vector<3, T> ToVector3(const Vector<4, T>& vector4)
	{
		return Vector<3, T>( vector4[0], vector4[1], vector4[2] );
	}

	template<typename T>
	Vector<4, T> ToVector4(const Vector<2, T>& vector2, T z, T w)
	{
		return Vector<4, T>( vector2[0], vector2[1], z, w );
	}

	template<typename T>
	Vector<4, T> ToVector4(const Vector<3, T>& vector3, T w)
	{
		return Vector<4, T>( vector3[0], vector3[1], vector3[2], w );
	}

	template<Dimension D, typename T>
	Vector<D, T> Lerp(const Vector<D, T>& from, const Vector<D, T>& to, RealType amount)
	{
		Vector<D, T> ret;
		for ( SizeType index = 0; index < D; index++ )
			ret[index] = Lerp( from[index], to[index], amount );

		return ret;
	}

	template<Dimension D, typename T>
	T Dot(const Vector<D, T>& leftHandSide, const Vector<D, T>& rightHandSide)
	{
		T ret = T();
		for ( SizeType index = 0; index < D; index++ )
			ret += leftHandSide[index] * rightHandSide[index];

		return ret;
	}

	template<Dimension D, typename T>
	auto Cross(const Vector<D, T>& leftHandSide, const Vector<D, T>& rightHandSide)
	{
		static_assert( D == 2 || D == 3 );


		if constexpr ( D == 2 )
			return leftHandSide[0] * rightHandSide[1] - leftHandSide[1] * rightHandSide[0]; // xy - yx

		if constexpr ( D == 3 )
			return Vector<3, T>(
				leftHandSide[1] * rightHandSide[2] - leftHandSide[2] * rightHandSide[1], // yz - zy
				leftHandSide[2] * rightHandSide[0] - leftHandSide[0] * rightHandSide[2], // zx - xz
				leftHandSide[0] * rightHandSide[1] - leftHandSide[1] * rightHandSide[0]  // xy - yx
			);
	}

	template<Dimension D, typename T>
	T Magnitude(const Vector<D, T>& instance)
	{
		return SquareRoot( Dot(instance, instance) );
	}

	template<Dimension D, typename T>
	Vector<D, T> Normalize(const Vector<D, T>& instance)
	{
		return instance / Magnitude(instance);
	}

	template<Dimension D, typename T>
	Vector<D, T>::Vector()
	{

	}

	template<Dimension D, typename T>
	template<typename ...Parameters>
	Vector<D, T>::Vector(Parameters ...parameters)
	{
		static_assert( sizeof...(parameters) <= D );


		ParameterPackHelper::CopyTo( components, parameters... );
	}

	template<Dimension D, typename T>
	Vector<D, T>::Vector(const Vector<D, T>& other)
	{
		CopyFrom(other);
	}

	template<Dimension D, typename T>
	Vector<D, T>& Vector<D, T>::operator=(const Vector<D, T>& other)
	{
		CopyFrom(other);

		return *this;
	}

	template<Dimension D, typename T>
	T& Vector<D, T>::operator[](SizeType index)
	{
		return components[index];
	}

	template<Dimension D, typename T>
	const T& Vector<D, T>::operator[](SizeType index) const
	{
		return components[index];
	}

	template<Dimension D, typename T>
	Vector<D, T> Vector<D, T>::operator+() const
	{
		return *this;
	}

	template<Dimension D, typename T>
	Vector<D, T> Vector<D, T>::operator-() const
	{
		Vector<D, T> ret;
		for ( SizeType index = 0; index < D; index++ )
			ret[index] = -components[index];

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T> Vector<D, T>::operator+(const Vector<D, T>& other) const
	{
		Vector<D, T> ret;
		for ( SizeType index = 0; index < D; index++ )
			ret[index] = components[index] + other[index];

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T> Vector<D, T>::operator-(const Vector<D, T>& other) const
	{
		Vector<D, T> ret;
		for ( SizeType index = 0; index < D; index++ )
			ret[index] = components[index] - other[index];

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T> Vector<D, T>::operator*(const Vector<D, T>& other) const
	{
		Vector<D, T> ret;
		for ( SizeType index = 0; index < D; index++ )
			ret[index] = components[index] * other[index];

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T> Vector<D, T>::operator*(T scalar) const
	{
		Vector<D, T> ret;
		for ( SizeType index = 0; index < D; index++ )
			ret[index] = components[index] * scalar;

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T> operator*(T scalar, const Vector<D, T>& instance)
	{
		return instance * scalar;
	}

	template<Dimension D, typename T>
	Vector<D, T> Vector<D, T>::operator/(T scalar) const
	{
		Vector<D, T> ret;
		for ( SizeType index = 0; index < D; index++ )
			ret[index] = components[index] / scalar;

		return ret;
	}

	template<Dimension D, typename T>
	Vector<D, T>& Vector<D, T>::operator+=(const Vector<D, T>& other)
	{
		*this = *this + other;

		return *this;
	}

	template<Dimension D, typename T>
	Vector<D, T>& Vector<D, T>::operator-=(const Vector<D, T>& other)
	{
		*this = *this - other;

		return *this;
	}

	template<Dimension D, typename T>
	Vector<D, T>& Vector<D, T>::operator*=(const Vector<D, T>& other)
	{
		*this = *this * other;

		return *this;
	}

	template<Dimension D, typename T>
	Vector<D, T>& Vector<D, T>::operator*=(T scalar)
	{
		*this = *this * scalar;

		return *this;
	}

	template<Dimension D, typename T>
	Vector<D, T>& Vector<D, T>::operator/=(T scalar)
	{
		*this = *this / scalar;

		return *this;
	}

	template<Dimension D, typename T>
	Void Vector<D, T>::CopyFrom(const Vector<D, T>& instance)
	{
		Memory::Copy(
			instance.components,
			components,
			sizeof(T) * D
		);
	}
#pragma endregion
}