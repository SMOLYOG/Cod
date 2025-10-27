#pragma once
#include "..\Globals\framework.h"
#include "..\Vector\Vector3.h"
#include "..\Vector\Vector2.h"
#include "../ImGui/imgui.h"

#define DegreesToRadians(a) ((a)*((float)M_PI/180.0f))
#define RadiansToDegrees(a) ((a)*(180.0f/(float)M_PI))
#define M_PI_DOUBLE   (3.14159265358979323846f * 2.0f)
#define _PTR_MAX_VALUE ((PVOID) 0x000F000000000000)
#define D3DX_PI    ((FLOAT)  3.1415927f)
#define M_PI   3.14159265358979323846
#define PITCH 0
#define ROLL 2
#define YAW 1 

const float YAW_MAX_RIGHT = -179.9f;
const float YAW_MAX_LEFT = 179.9f;
const float PITCH_MAX_DOWN = 70.f;
const float PITCH_MAX_UP = -70.f;
const float pi = 3.1415927f;

namespace Math
{
	float SmartCheck(const Vector3& LocalAngles, const Vector3& LocalPosistion, const Vector3& TargetPosistion);
	void ImageRotated(ImTextureID Texture, ImVec2 Center, ImVec2 TextureSize, float YawDegrees, ImColor Color);
	void VectorSubtract(const Vector3& vec1, const Vector3& vec2, Vector3& result);
	void RotateTriangle(std::array<ImVec2, 3>& Points, float Rotation);
	float XAngle(const Vector3& LocalPos, const Vector3& WorldPos);
	Vector3 CalculateAngle(const Vector3 src, const Vector3 dst);
	float GetDistance(const Vector3& lhs, const Vector3& rhs);
	Vector3 RotateVector(const Vector3& Vector, float Yaw);
	bool PointInsideCircle(Vector2 Point, Vector2 Circle);
	float CalculateDistance2D(Vector2 Start, Vector2 End);
	void VectorAngles(Vector3 Direction, Vector3& Angle);
	float DotProduct(Vector3 Vector1, Vector3 Vector2);
	float VectorLength3D(Vector3 Left, Vector3 Right);
	float VectorLength2D(Vector2 Left, Vector2 Right);
	float DotProduct2D(Vector2 Left, Vector2 Right);
	float DotProduct3D(Vector3 Left, Vector3 Right);
	void NormalizeVector(Vector3& Direction);
	std::string RoundFloat(float Number);
	float NormalizeAngle180(float Angle);
	void NormalizeAngle(Vector3& Angle);
	float GetFOVValue(float InGameFOV);
	float GetMagnitude(Vector3 Vector);
	float Deg2Rad(const float Degree);
	float MetersToUnits(float meters);
	float UnitsToMeters(float units);
	void ClampAngles(Vector3& Angle);
}

struct angle_t
{
	angle_t() = default;

	angle_t(float xyz) : x(xyz), y(xyz), z(xyz) {};
	angle_t(float x, float y) : x(x), y(y), z(0) {};
	angle_t(float x, float y, float z) : x(x), y(y), z(z) {};
	angle_t(float* arr) : x(arr[PITCH]), y(arr[YAW]), z(arr[ROLL]) {};

	inline float length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	inline angle_t normal()
	{
		angle_t out{};
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

	inline angle_t normalize()
	{
		angle_t out{};

		out.x = std::isfinite(x) ? std::remainderf(x, 360.f) : 0.f;
		out.y = std::isfinite(y) ? std::remainderf(y, 360.f) : 0.f;
		out.z = z;

		return out;
	}

	inline angle_t clamp()
	{
		angle_t out{};

		out.x = std::clamp(x, -85.f, 85.f);
		out.y = std::clamp(y, -180.f, 180.f);
		out.z = z;

		return out;
	}

#pragma region assignment
	inline angle_t& operator=(const angle_t& in)
	{
		x = in.x;
		y = in.y;
		z = in.z;

		return *this;
	}
#pragma endregion assignment

#pragma region equality
	inline bool operator!=(const angle_t& in)
	{
		return (x != in.x || y != in.y || z != in.z);
	}

	inline bool operator==(const angle_t& in)
	{
		return (x == in.x && y == in.y && z == in.z);
	}
#pragma endregion equality

#pragma region addition
	inline angle_t operator+(angle_t in) const
	{
		return angle_t(
			x + in.x,
			y + in.y,
			z + in.z
		);
	}

	inline angle_t operator+(float in) const
	{
		return angle_t(
			x + in,
			y + in,
			z + in
		);
	}

	inline angle_t& operator+=(angle_t in)
	{
		x += in.x;
		y += in.y;
		z += in.z;

		return *this;
	}

	inline angle_t& operator+=(float in)
	{
		x += in;
		y += in;
		z += in;

		return *this;
	}
#pragma endregion addition

#pragma region substraction
	inline angle_t operator-(angle_t in) const
	{
		return angle_t(
			x - in.x,
			y - in.y,
			z - in.z
		);
	}

	inline angle_t operator-(float in) const
	{
		return angle_t(
			x - in,
			y - in,
			z - in
		);
	}

	inline angle_t& operator-=(angle_t in)
	{
		x -= in.x;
		y -= in.y;
		z -= in.z;

		return *this;
	}

	inline angle_t& operator-=(float in)
	{
		x -= in;
		y -= in;
		z -= in;

		return *this;
	}
#pragma endregion substraction

#pragma region multiplication
	inline angle_t operator*(angle_t in) const
	{
		return angle_t(
			x * in.x,
			y * in.y,
			z * in.z
		);
	}

	inline angle_t operator*(float in) const
	{
		return angle_t(
			x * in,
			y * in,
			z * in
		);
	}

	inline angle_t& operator*=(angle_t in)
	{
		x *= in.x;
		y *= in.y;
		z *= in.z;

		return *this;
	}

	inline angle_t& operator*=(float in)
	{
		x *= in;
		y *= in;
		z *= in;

		return *this;
	}
#pragma endregion multiplication

#pragma region division
	inline angle_t operator/(angle_t in) const
	{
		return angle_t(
			x / in.x,
			y / in.y,
			z / in.z
		);
	}

	inline angle_t operator/(float in) const
	{
		return angle_t(
			x / in,
			y / in,
			z / in
		);
	}

	inline angle_t& operator/=(angle_t in)
	{
		x /= in.x;
		y /= in.y;
		z /= in.z;

		return *this;
	}

	inline angle_t& operator/=(float in)
	{
		x /= in;
		y /= in;
		z /= in;

		return *this;
	}
#pragma endregion division

	float x, y, z;
};

angle_t calc_angle(const vec3_t& src, const vec3_t& dst);

extern void WorldToCompass(Vector3 MyClientPos, Vector3 MyClientViewAngles, Vector3 World, ImVec2 CompassPosistion, float CompassSize, ImVec2& Screen);

extern float CalculateDistance3D(Vector3 start, Vector3 end);

extern void tokenize(std::string const& str, const char* delim, std::vector<std::string>& out);

extern bool stringContains(std::string cmp, std::string fnd);

extern float angleNormalize180(float angle);

extern void VectorAnglesa(Vector3 direction, Vector3& angles);