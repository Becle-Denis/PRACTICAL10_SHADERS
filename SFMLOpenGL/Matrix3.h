#pragma once
#include <string>
#include <cmath>

namespace db
{
	class Vector3;  //further declaration

/// <summary>
/// Class to represent a matrix with 3 column and 3 rows
/// </summary>
	class Matrix3
	{
	public:
		//ATTRIBUTES 
		//Row 1 
		float a11{ 0.0 };
		float a12{ 0.0 };
		float a13{ 0.0 };

		//Row 2 
		float a21{ 0.0 };
		float a22{ 0.0 };
		float a23{ 0.0 };

		//Row 3 
		float a31{ 0.0 };
		float a32{ 0.0 };
		float a33{ 0.0 };

		//FUNCTIONS

		//CONSTRUCTORS 
		/// <summary>
		/// Empty constructor;
		/// </summary>
		Matrix3() = default;

		/// <summary>
		/// Constructor with 3 vectors 
		/// </summary>
		/// <param name="row1">Row1</param>
		/// <param name="row2">Row2</param>
		/// <param name="row3">Row3</param>
		Matrix3(Vector3 row1, Vector3 row2, Vector3 row3);

		/// <summary>
		/// Constructor with 9 values 
		/// </summary>
		Matrix3(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33);

		//OTHER 
		std::string toString();

		//Transpose the given Matrix and return it
		static Matrix3 transpose(Matrix3 m1);

		//return the determinat of the given matrix 
		static float determinant(Matrix3 m1);

		//return the selected row as a vector3 
		Vector3 row(int i) const;

		// return the selected column as a vector3 
		Vector3 column(int i) const;

		//return the inverse of a matrix if exist, 
		static Matrix3 inverse(Matrix3 m1);

		static Matrix3 rotation(int angleDEG);

		static Matrix3 translate(int dx, int dy);

		static Matrix3 scale(int dx, int dy);

		static Matrix3 rotationX(int angleDEG);

		static Matrix3 rotationY(int angleDEG);

		static Matrix3 rotationZ(int angleDEG);

		static Matrix3 scale3D(int dx);

		//OPERATOR

		//sum 2 matrix
		friend Matrix3 operator+ (Matrix3 const& m1, Matrix3 const& m2);

		//difference of 2 matrix
		friend Matrix3 operator- (Matrix3 const& m1, Matrix3 const& m2);

		friend Matrix3 operator- (Matrix3 const& m1);

		//product of a matrix by a scalar
		friend Matrix3 operator* (float x, Matrix3 const& m1);

		// Product of a matrix by a scalar
		friend Matrix3 operator* (Matrix3 const& m1, float x);

		//Product of 2 matrix
		friend Matrix3 operator* (Matrix3 const& m1, Matrix3 const& m2);

		//Product of a matrix by a vector
		friend Vector3 operator* (Matrix3 const& m1, Vector3 const& v1);

		//Product of a vector by a matrix
		friend Vector3 operator*  (Vector3 const& v1, Matrix3 const& m1);



	private:

		static float PI;
	};

}


#include "Vector3.h"
