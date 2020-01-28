#include "Vector3.h"

namespace db
{
	Vector3::Vector3(float x1, float y1, float z1) :
		x(x1), y(y1), z(z1)
	{

	}

	Vector3::Vector3(Vector3 const& ext) :
		x(ext.x), y(ext.y), z(ext.z)
	{

	}

	float Vector3::length() const
	{
		return (float)sqrt(lenghtSquared());
	}

	float Vector3::lenghtSquared() const
	{
		return x * x + y * y + z * z;
	}

	void Vector3::normalise()
	{
		float len = length();
		if (len != 0)
		{
			x = x / len;
			y = y / len;
			z = z / len;
		}
	}

	std::string Vector3::toString()
	{
		return "Vector3 x: " + std::to_string(x) + " y: " + std::to_string(y) + " z: " + std::to_string(z);
	}

	Vector3 operator+(Vector3 const& v1, Vector3 const& v2)
	{
		return Vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	Vector3 operator-(Vector3 const& v1, Vector3 const& v2)
	{
		return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	Vector3 operator-(Vector3 const& v1)
	{
		return Vector3() - v1;
	}

	Vector3 operator*(Vector3 const& v1, Vector3 const& v2)
	{
		return Vector3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
	}

	Vector3 operator*(float k, Vector3 const& v1)
	{
		return Vector3(v1.x * k, v1.y * k, v1.z * k);
	}

	Vector3 operator*(int k, Vector3 const& v1)
	{
		return Vector3(v1.x * k, v1.y * k, v1.z * k);
	}

	Vector3 operator^(Vector3 const& v1, Vector3 const& v2)
	{
		return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

}