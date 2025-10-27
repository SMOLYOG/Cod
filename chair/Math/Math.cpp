#include "..\Math\Math.h"
#include "..\Third Party\xor.h"
#include "..\Globals\Globals.h"

float Math::SmartCheck(const Vector3& LocalAngles, const Vector3& LocalPosistion, const Vector3& TargetPosistion)
{
	const auto distance = (TargetPosistion - LocalPosistion).Length();
	const auto angle_difference = (LocalAngles - Math::CalculateAngle(LocalPosistion, TargetPosistion)).Normalize();

	auto pitch_difference = sin(Math::Deg2Rad(angle_difference.x)) * distance;
	auto yaw_difference = sin(Math::Deg2Rad(angle_difference.y)) * distance;

	return sqrt(pitch_difference * pitch_difference + yaw_difference * yaw_difference);
}
void Math::ImageRotated(ImTextureID Texture, ImVec2 Center, ImVec2 TextureSize, float YawDegrees, ImColor Color) {
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float yawRadians = YawDegrees * (M_PI / 180.0f);

	float cosTheta = cos(yawRadians);
	float sinTheta = sin(yawRadians);

	ImVec2 corners[4] = {
		ImVec2(Center.x - TextureSize.x / 2, Center.y - TextureSize.y / 2),
		ImVec2(Center.x + TextureSize.x / 2, Center.y - TextureSize.y / 2),
		ImVec2(Center.x + TextureSize.x / 2, Center.y + TextureSize.y / 2),
		ImVec2(Center.x - TextureSize.x / 2, Center.y + TextureSize.y / 2)
	};

	for (int i = 0; i < 4; i++) {
		ImVec2 translatedCorner = ImVec2(corners[i].x - Center.x, corners[i].y - Center.y);
		corners[i].x = Center.x + translatedCorner.x * cosTheta - translatedCorner.y * sinTheta;
		corners[i].y = Center.y + translatedCorner.x * sinTheta + translatedCorner.y * cosTheta;
	}

	draw_list->AddImageQuad(Texture, corners[0], corners[1], corners[2], corners[3], ImVec2(0, 0), ImVec2(1, 0), ImVec2(1, 1), ImVec2(0, 1), Color);
}
void Math::VectorSubtract(const Vector3& Vector1, const Vector3& Vector2, Vector3& Result) {
	Result.x = Vector1.x - Vector2.x;
	Result.y = Vector1.y - Vector2.y;
	Result.z = Vector1.z - Vector2.z;
}
void Math::RotateTriangle(std::array<ImVec2, 3>& Points, float Rotation)
{
	ImVec2 PointsCenter = ImVec2(Points.at(0).x + Points.at(1).x + Points.at(2).x, Points.at(0).y + Points.at(1).y + Points.at(2).y);
	PointsCenter = ImVec2(PointsCenter.x / 3, PointsCenter.y / 3);

	for (auto& Point : Points)
	{
		Point = ImVec2(Point.x - PointsCenter.x, Point.y - PointsCenter.y);

		const auto TemporayX = Point.x;
		const auto TemporayY = Point.y;

		const auto Posistion = DegreesToRadians(Rotation);
		const auto Cosine = cosf(Posistion);
		const auto sine = sinf(Posistion);

		Point.x = TemporayX * Cosine - TemporayY * sine;
		Point.y = TemporayX * sine + TemporayY * Cosine;

		Point = ImVec2(Point.x + PointsCenter.x, Point.y + PointsCenter.y);
	}
}
float Math::XAngle(const Vector3& LocalPos, const Vector3& WorldPos)
{
	float dl = sqrt((WorldPos.x - LocalPos.x) * (WorldPos.x - LocalPos.x) + (WorldPos.y - LocalPos.y) * (WorldPos.y - LocalPos.y));

	if (dl == 0.0f)
		dl = 1.0f;

	float dl2 = abs(WorldPos.x - LocalPos.x);
	float teta = ((180.0f / D3DX_PI) * acos(dl2 / dl));

	if (WorldPos.x < LocalPos.x)
		teta = 180.0f - teta;

	if (WorldPos.y < LocalPos.y)
		teta = teta * -1.0f;

	if (teta > 180.0f)
		teta = (360.0f - teta) * (-1.0f);

	if (teta < -180.0f)
		teta = (360.0f + teta);

	return teta;
}
float Math::GetDistance(const Vector3& Local, const Vector3& Enemy)
{
	const float distanceX = Local.x - Enemy.x;
	const float distanceY = Local.y - Enemy.y;
	const float distanceZ = Local.z - Enemy.z;
	return std::sqrt((distanceX * distanceX) + (distanceY * distanceY) + (distanceZ * distanceZ));
}
Vector3 Math::CalculateAngle(const Vector3 src, const Vector3 dst)
{
	auto ret = Vector3();

	auto vec_delta = dst - src;

	Math::VectorAngles(vec_delta, ret);

	return ret;
}

angle_t calc_angle(const vec3_t& src, const vec3_t& dst)
{
	vec3_t delta = src - dst;

	angle_t ang;
	ang.x = std::atanf(-delta.z / delta.length_2d()) * (-(180.0 / M_PI));
	ang.y = std::atanf(delta.y / delta.x) * (180.0 / M_PI);
	ang.z = 0.f;

	if (delta.x >= 0.f)
		ang.y += 180.f;


	ang = ang.normalize();

	return ang;
}

Vector3 Math::RotateVector(const Vector3& Vector, float Yaw)
{
	float s, c;
	s = std::sin(Yaw);
	c = std::cos(Yaw);

	Vector3 RotatedVector;
	RotatedVector.x = Vector.x * c - Vector.y * s;
	RotatedVector.y = Vector.x * s + Vector.y * c;
	RotatedVector.z = Vector.z;

	return RotatedVector;
}
bool Math::PointInsideCircle(Vector2 Point, Vector2 Circle) {
	double DrawPlayerDistance = std::sqrt(std::pow(Point.x - Circle.x, 2) + std::pow(Point.y - Circle.y, 2));
	return DrawPlayerDistance <= Aimbot::FOV;
}
float Math::CalculateDistance2D(Vector2 Start, Vector2 End) {
	return Math::VectorLength2D(Vector2(Start.x - End.x, Start.y - End.y), Vector2(Start.x - End.x, Start.y - End.y));
}
void Math::VectorAngles(Vector3 Direction, Vector3& Angle) {
	if (Direction.x == 0.0f && Direction.y == 0.0f) {
		Angle.x = (Direction.z > 0.0f) ? 270.0f : 90.0f;
		Angle.y = 0.0f;
	}
	else {
		Angle.x = atan2(-Direction.z, Direction.Length2D()) * 180.f / static_cast<float>(M_PI);
		Angle.y = atan2(Direction.y, Direction.x) * 180.f / static_cast<float>(M_PI);
	}

	Angle.z = 0.f;
}
float Math::DotProduct(Vector3 Vector1, Vector3 Vector2)
{
	return Vector1.x * Vector2.x + Vector1.y * Vector2.y + Vector1.z * Vector2.z;
}
float Math::VectorLength3D(Vector3 Left, Vector3 Right)
{
	return sqrtf(DotProduct3D(Left, Right));
}
float Math::VectorLength2D(Vector2 Left, Vector2 Right) {
	return sqrtf(DotProduct2D(Left, Right));
}
float Math::DotProduct2D(Vector2 Left, Vector2 Right) {
	return (Left.x * Right.x + Left.y * Right.y);
}
float Math::DotProduct3D(Vector3 Left, Vector3 Right)
{
	return (Left.x * Right.x + Left.y * Right.y + Left.z * Right.z);
}
void Math::NormalizeVector(Vector3& Direction)
{
	float flLen = VectorLength3D(Direction, Direction);

	if (flLen == 0.0f)
	{
		Direction.x = 0.0f;
		Direction.y = 0.0f;
		Direction.z = 1.0f;
	}
	else
	{
		flLen = 1.0f / flLen;
		Direction.x *= flLen;
		Direction.y *= flLen;
		Direction.z *= flLen;
	}
}
std::string Math::RoundFloat(float Number) {
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(1) << Number;
	return oss.str();
}
float Math::NormalizeAngle180(float Angle)
{
	return ((Angle * 0.0027777778f) - floorf((Angle * 0.0027777778f) + 0.5f)) * 360.0f;
}
void Math::NormalizeAngle(Vector3& Angle)
{
	Angle.x = std::isfinite(Angle.x) ? std::remainderf(Angle.x, 360.0f) : 0.0f;
	Angle.y = std::isfinite(Angle.y) ? std::remainderf(Angle.y, 360.0f) : 0.0f;
	Angle.z = 0.0f;
}

float Math::GetFOVValue(float InGameFOV)
{
	float viewAspect = 16.0f / 9.0f;
	float scale = 3.0f / 4.0f;
	float actualFov = 2 * atan(viewAspect * scale * tan(InGameFOV * 0.0087266462)) * 57.2957795;
	return actualFov;
}
float Math::GetMagnitude(Vector3 Vector)
{
	return sqrt(pow(Vector.x, 2) + pow(Vector.y, 2) + pow(Vector.z, 2));
}
float Math::MetersToUnits(float Meters)
{
	return 0.0254 / Meters;
}
float Math::Deg2Rad(const float Degree)
{
	return static_cast<float>(Degree * (3.1415926535 / 180.f));
}

void Math::ClampAngles(Vector3& Angle) {
	while (Angle.x > 180.0f)
		Angle.x -= 360.0f;

	while (Angle.x < -180.0f)
		Angle.x += 360.0f;

	while (Angle.y > 180.0f)
		Angle.y -= 360.0f;

	while (Angle.y < -180.0f)
		Angle.y += 360.0f;

	if (Angle.z != 0.0f)
		Angle.z = 0.0f;
}
float Math::UnitsToMeters(float Units)
{
	return Units * 0.0254;
}

void WorldToCompass(Vector3 MyClientPos, Vector3 MyClientViewAngles, Vector3 World, ImVec2 CompassPosistion, float CompassSize, ImVec2& Screen)
{
	Vector3 Direction, Angles;
	float AngleFloat;

	Direction = MyClientPos;
	Direction.x -= World.x;
	Direction.y -= World.y;
	Direction.z -= World.z;

	Math::NormalizeVector(Direction);
	Math::VectorAngles(Direction, Angles);

	Angles.x -= MyClientViewAngles.x;
	Angles.y -= MyClientViewAngles.y;
	Angles.z -= MyClientViewAngles.z;

	Math::ClampAngles(Angles);

	AngleFloat = ((Angles.y + 180.0f) / 360.0f - 0.25f) * M_PI_DOUBLE;

	Screen.x = CompassPosistion.x + (cosf(AngleFloat) * (CompassSize / 2.0f));
	Screen.y = CompassPosistion.y + (sinf(AngleFloat) * (CompassSize / 2.0f));
}


float CalculateDistance3D(Vector3 start, Vector3 end) {
	Vector3 vDirection = Vector3(start.x - end.x, start.y - end.y, start.z - end.z);
	return Math::VectorLength3D(vDirection, vDirection);
}

void tokenize(std::string const& str, const char* delim, std::vector<std::string>& out) {
	char* token = strtok(const_cast<char*>(str.c_str()), delim);
	while (token != nullptr)
	{
		out.push_back(std::string(token));
		token = strtok(nullptr, delim);
	}
}

bool stringContains(std::string cmp, std::string fnd) {
	return (cmp.find(fnd) != std::string::npos);
}

float angleNormalize180(float angle)
{
	return ((angle * 0.0027777778f) - floorf((angle * 0.0027777778f) + 0.5f)) * 360.0f;
}

void VectorAnglesa(Vector3 direction, Vector3& angles)
{
	float flTemp, flYaw, flPitch;

	if (direction.x == 0.0f && direction.y == 0.0f)
	{
		flYaw = 0.0f;

		if (direction.z > 0.0f)
			flPitch = 90.0f;
		else
			flPitch = 270.0f;
	}

	else
	{
		flYaw = RadiansToDegrees(atan2f(direction.y, direction.x));

		if (flYaw < 0.0f)
			flYaw += 360.0f;

		flTemp = sqrtf(direction.x * direction.x + direction.y * direction.y);
		flPitch = RadiansToDegrees(atan2f(direction.z, flTemp));

		if (flPitch < 0.0f)
			flPitch += 360.0f;
	}

	angles.x = -flPitch;
	angles.y = flYaw;
	angles.z = 0.0f;
}

