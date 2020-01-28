#pragma once
#include <string>

namespace db
{

	class Vector3
	{
	public: //attributes 

		float x{ 0.0 };
		float y{ 0.0 };
		float z{ 0.0 };


	public: //functions

		//CONSTRUCTORS
		// empty constructor 
		Vector3() = default;

		// constructor with 3 values 
		Vector3(float x1, float y1, float z1);

		// copy connstructor
		Vector3(Vector3 const&);

		//OTHER

		float length() const;

		float lenghtSquared() const;

		//Reduce the length to 1
		void normalise();

		std::string toString();

		//OPERATOR
		//sum of 2 vectors
		friend Vector3 operator+(Vector3 const& v1, Vector3 const& v2);

		//diference of 2 vectors
		friend Vector3 operator-(Vector3 const& v1, Vector3 const& c2);

		//negative of vectors
		friend Vector3 operator-(Vector3 const& v1);

		//scalar product of 2 vectors
		friend Vector3 operator*(Vector3 const& v1, Vector3 const& v2);

		//product of a scalar by a vector
		friend Vector3 operator*(float k, Vector3 const& v1);

		//Product of a scalat by a vector
		friend Vector3 operator*(int k, Vector3 const& v1);

		//vector product of 2 vectors
		friend Vector3 operator^ (Vector3 const& v1, Vector3 const& v2);
	};
}

