#pragma once
#include <algorithm>
#include "..\Math\Math.h"

struct Angle_t
{
	Angle_t() = default;

	Angle_t(float xyz) : x(xyz), y(xyz), z(xyz) {};
	Angle_t(float x, float y) : x(x), y(y), z(0) {};
	Angle_t(float x, float y, float z) : x(x), y(y), z(z) {};
	Angle_t(float* arr) : x(arr[PITCH]), y(arr[YAW]), z(arr[ROLL]) {};

	inline float length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	inline Angle_t normal()
	{
		Angle_t out{};
		float l = length();

		if (l != 0.f)
		{
			out.x = x / l;
			out.y = y / l;
			out.z = z / l;
		}
		else
			out.x = out.y = 0.0f; out.z = 1.0f;

		return out;
	}

	inline Angle_t normalize()
	{
		Angle_t out{};

		out.x = std::isfinite(x) ? std::remainderf(x, 360.f) : 0.f;
		out.y = std::isfinite(y) ? std::remainderf(y, 360.f) : 0.f;
		out.z = z;

		return out;
	}

	inline Angle_t clamp()
	{
		Angle_t out{};

		out.x = std::clamp(x, -85.f, 85.f);
		out.y = std::clamp(y, -180.f, 180.f);
		out.z = z;

		return out;
	}

#pragma region assignment
	inline Angle_t& operator=(const Angle_t& in)
	{
		x = in.x;
		y = in.y;
		z = in.z;

		return *this;
	}
#pragma endregion assignment

#pragma region equality
	inline bool operator!=(const Angle_t& in)
	{
		return (x != in.x || y != in.y || z != in.z);
	}

	inline bool operator==(const Angle_t& in)
	{
		return (x == in.x && y == in.y && z == in.z);
	}
#pragma endregion equality

#pragma region addition
	inline Angle_t operator+(Angle_t in) const
	{
		return Angle_t(
			x + in.x,
			y + in.y,
			z + in.z
		);
	}

	inline Angle_t operator+(float in) const
	{
		return Angle_t(
			x + in,
			y + in,
			z + in
		);
	}

	inline Angle_t& operator+=(Angle_t in)
	{
		x += in.x;
		y += in.y;
		z += in.z;

		return *this;
	}

	inline Angle_t& operator+=(float in)
	{
		x += in;
		y += in;
		z += in;

		return *this;
	}
#pragma endregion addition

#pragma region substraction
	inline Angle_t operator-(Angle_t in) const
	{
		return Angle_t(
			x - in.x,
			y - in.y,
			z - in.z
		);
	}

	inline Angle_t operator-(float in) const
	{
		return Angle_t(
			x - in,
			y - in,
			z - in
		);
	}

	inline Angle_t& operator-=(Angle_t in)
	{
		x -= in.x;
		y -= in.y;
		z -= in.z;

		return *this;
	}

	inline Angle_t& operator-=(float in)
	{
		x -= in;
		y -= in;
		z -= in;

		return *this;
	}
#pragma endregion substraction

#pragma region multiplication
	inline Angle_t operator*(Angle_t in) const
	{
		return Angle_t(
			x * in.x,
			y * in.y,
			z * in.z
		);
	}

	inline Angle_t operator*(float in) const
	{
		return Angle_t(
			x * in,
			y * in,
			z * in
		);
	}

	inline Angle_t& operator*=(Angle_t in)
	{
		x *= in.x;
		y *= in.y;
		z *= in.z;

		return *this;
	}

	inline Angle_t& operator*=(float in)
	{
		x *= in;
		y *= in;
		z *= in;

		return *this;
	}
#pragma endregion multiplication

#pragma region division
	inline Angle_t operator/(Angle_t in) const
	{
		return Angle_t(
			x / in.x,
			y / in.y,
			z / in.z
		);
	}

	inline Angle_t operator/(float in) const
	{
		return Angle_t(
			x / in,
			y / in,
			z / in
		);
	}

	inline Angle_t& operator/=(Angle_t in)
	{
		x /= in.x;
		y /= in.y;
		z /= in.z;

		return *this;
	}

	inline Angle_t& operator/=(float in)
	{
		x /= in;
		y /= in;
		z /= in;

		return *this;
	}
#pragma endregion division

	float x, y, z;
};
