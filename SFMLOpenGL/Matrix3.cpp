#include "Matrix3.h"

namespace db
{
	float Matrix3::PI = 3.141592653589793;

	Matrix3::Matrix3(Vector3 row1, Vector3 row2, Vector3 row3) :
		a11(row1.x), a12(row1.y), a13(row1.z),
		a21(row2.x), a22(row2.y), a23(row2.z),
		a31(row3.x), a32(row3.y), a33(row3.z)
	{

	}

	Matrix3::Matrix3(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33) :
		a11(a11), a12(a12), a13(a13),
		a21(a21), a22(a22), a23(a23),
		a31(a31), a32(a32), a33(a33)
	{

	}

	std::string Matrix3::toString()
	{
		return "Matrix 3 : \n\tRow 1 : " + std::to_string(a11) + "\t, 2 : " + std::to_string(a12) + "\t, 3 : " + std::to_string(a13) + "\n"
			+ "\tRow 2 : " + std::to_string(a21) + "\t, 2 : " + std::to_string(a22) + "\t, 3 : " + std::to_string(a23) + "\n"
			+ "\tRow 3 : " + std::to_string(a31) + "\t, 2 : " + std::to_string(a32) + "\t, 3 : " + std::to_string(a33) + "\n";
	}

	Matrix3 Matrix3::transpose(Matrix3 m1)
	{
		return Matrix3(m1.a11, m1.a21, m1.a31, m1.a12, m1.a22, m1.a32, m1.a13, m1.a23, m1.a33);
	}

	float Matrix3::determinant(Matrix3 m1)
	{
		return m1.a11 * m1.a22 * m1.a33
			- m1.a11 * m1.a32 * m1.a23
			+ m1.a21 * m1.a32 * m1.a13
			- m1.a31 * m1.a22 * m1.a13
			+ m1.a31 * m1.a12 * m1.a23
			- m1.a21 * m1.a12 * m1.a33;
	}

	Vector3 Matrix3::row(int i) const
	{
		switch (i)
		{
		case 0:
			return Vector3(a11, a12, a13);
		case 1:
			return Vector3(a21, a22, a23);
		case 2:
		default:
			return Vector3(a31, a32, a33);
		}
	}

	Vector3 Matrix3::column(int i) const
	{
		switch (i)
		{
		case 0:
			return Vector3(a11, a21, a31);
		case 1:
			return Vector3(a12, a22, a32);
		case 2:
		default:
			return Vector3(a13, a23, a33);
		}
	}

	Matrix3 Matrix3::inverse(Matrix3 m1)
	{
		double det = determinant(m1);
		if (det == 0)
		{
			return Matrix3();
		}
		else
		{
			float scale = 1 / det;
			Matrix3 answer;
			answer.a11 = scale * (m1.a22 * m1.a33 - m1.a23 * m1.a32);
			answer.a12 = scale * (m1.a13 * m1.a32 - m1.a12 * m1.a33);
			answer.a13 = scale * (m1.a12 * m1.a23 - m1.a13 * m1.a22);

			answer.a21 = scale * (m1.a23 * m1.a31 - m1.a21 * m1.a33);
			answer.a22 = scale * (m1.a11 * m1.a33 - m1.a13 * m1.a31);
			answer.a23 = scale * (m1.a13 * m1.a21 - m1.a11 * m1.a23);

			answer.a31 = scale * (m1.a21 * m1.a32 - m1.a22 * m1.a31);
			answer.a32 = scale * (m1.a12 * m1.a31 - m1.a11 * m1.a32);
			answer.a33 = scale * (m1.a11 * m1.a22 - m1.a12 * m1.a21);

			return answer;
		}
	}

	Matrix3 Matrix3::rotation(int angleDEG)
	{
		float radians = PI / 180 * angleDEG;
		Matrix3 answer;
		answer.a11 = cos(radians);
		answer.a12 = sin(radians);
		answer.a21 = -sin(radians);
		answer.a22 = cos(radians);

		return answer;
	}

	Matrix3 Matrix3::translate(int dx, int dy)
	{
		Matrix3 answer;
		answer.a11 = 1;
		answer.a22 = 1;
		answer.a31 = dx;
		answer.a32 = dy;
		answer.a33 = 1;

		return answer;
	}

	Matrix3 Matrix3::scale(int dx, int dy)
	{
		Matrix3 answer;
		answer.a11 = ((float)dx) / 100;
		answer.a22 = ((float)dy) / 100;
		answer.a33 = 1;

		return answer;
	}

	Matrix3 Matrix3::rotationX(int angleDEG)
	{
		float radians = PI / 180 * angleDEG;
		Matrix3 answer;
		answer.a11 = 1;
		answer.a22 = cos(radians);
		answer.a23 = -sin(radians);
		answer.a32 = sin(radians);
		answer.a33 = cos(radians);

		return answer;
	}

	Matrix3 Matrix3::rotationY(int angleDEG)
	{
		float radians = PI / 180 * angleDEG;
		Matrix3 answer;
		answer.a11 = cos(radians);
		answer.a13 = sin(radians);
		answer.a22 = 1;
		answer.a31 = -sin(radians);
		answer.a33 = cos(radians);

		return answer;
	}

	Matrix3 Matrix3::rotationZ(int angleDEG)
	{
		float radians = PI / 180 * angleDEG;
		Matrix3 answer;
		answer.a11 = cos(radians);
		answer.a12 = -sin(radians);
		answer.a21 = sin(radians);
		answer.a22 = cos(radians);
		answer.a33 = 1;

		return answer;
	}

	Matrix3 Matrix3::scale3D(int dx)
	{
		Matrix3 answer;
		answer.a11 = (float)dx / 100;
		answer.a22 = (float)dx / 100;
		answer.a33 = (float)dx / 100;

		return answer;
	}

	Matrix3 operator+(Matrix3 const& m1, Matrix3 const& m2)
	{
		return Matrix3(
			m1.a11 + m2.a11,
			m1.a12 + m2.a12,
			m1.a13 + m2.a13,

			m1.a21 + m2.a21,
			m1.a22 + m2.a22,
			m1.a23 + m2.a23,

			m1.a31 + m2.a31,
			m1.a32 + m2.a32,
			m1.a33 + m2.a33
		);
	}

	Matrix3 operator-(Matrix3 const& m1, Matrix3 const& m2)
	{
		return Matrix3(
			m1.a11 - m2.a11,
			m1.a12 - m2.a12,
			m1.a13 - m2.a13,

			m1.a21 - m2.a21,
			m1.a22 - m2.a22,
			m1.a23 - m2.a23,

			m1.a31 - m2.a31,
			m1.a32 - m2.a32,
			m1.a33 - m2.a33
		);
	}

	Matrix3 operator-(Matrix3 const& m1)
	{
		return Matrix3() - m1;
	}

	Matrix3 operator*(float x, Matrix3 const& m1)
	{
		return Matrix3(
			m1.a11 * x,
			m1.a12 * x,
			m1.a13 * x,

			m1.a21 * x,
			m1.a22 * x,
			m1.a23 * x,

			m1.a31 * x,
			m1.a32 * x,
			m1.a33 * x
		);
	}

	Matrix3 operator*(Matrix3 const& m1, float x)
	{
		return x * m1;
	}

	Matrix3 operator*(Matrix3 const& m1, Matrix3 const& m2)
	{
		return Matrix3(
			m1.a11 * m2.a11,
			m1.a12 * m2.a12,
			m1.a13 * m2.a13,

			m1.a21 * m2.a21,
			m1.a22 * m2.a22,
			m1.a23 * m2.a23,

			m1.a31 * m2.a31,
			m1.a32 * m2.a32,
			m1.a33 * m2.a33
		);
	}

	Vector3 operator*(Matrix3 const& m1, Vector3 const& v1)
	{
		return Vector3(m1.a11 * v1.x + m1.a12 * v1.y + m1.a13 * v1.z,
			m1.a21 * v1.x + m1.a22 * v1.y + m1.a23 * v1.z,
			m1.a31 * v1.x + m1.a32 * v1.y + m1.a33 * v1.z);
	}

	Vector3 operator*(Vector3 const& v1, Matrix3 const& m1)
	{
		return Vector3(m1.a11 * v1.x + m1.a21 * v1.y + m1.a31 * v1.z,
			m1.a12 * v1.x + m1.a22 * v1.y + m1.a32 * v1.z,
			m1.a13 * v1.x + m1.a23 * v1.y + m1.a33 * v1.z);
	}

}