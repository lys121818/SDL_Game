#pragma once
#include <math.h>

// structure to create a point to vector2 (x & y)
template<typename DataType>
struct Vector2
{
	DataType m_x;
	DataType m_y;

	bool operator==(const Vector2& other) const
	{
		return (m_x == other.m_x && m_y == other.m_y);
	}
	bool operator!=(const Vector2& other) const
	{
		return (m_x != other.m_x || m_y != other.m_y);
	}

	Vector2 operator -(const Vector2& right) const
	{
		Vector2 vec;
		vec.m_x = m_x - right.m_x;
		vec.m_y = m_y - right.m_y;

		return vec;
	}

	Vector2 operator *(const Vector2& right) const
	{
		Vector2 vec;
		vec.m_x = m_x * right.m_x;
		vec.m_y = m_y * right.m_y;

		return vec;
	}

	static float Distance (const Vector2& object_A, const Vector2& object_B)
	{
		float distance_x;
		float distance_y;


		distance_x = abs(abs((int)object_A.m_x) - abs((int)object_B.m_x));
		distance_y = abs(abs((int)object_A.m_y) - abs((int)object_B.m_y));

		return sqrtf((distance_x * distance_x) + (distance_y * distance_y));
	}

	DataType SquareLength()
	{
		return m_x * m_x + m_y * m_y;
	}

	Vector2 Normalized()
	{
		// calculate the length
		float length = sqrtf(SquareLength());

		if (length == 0)
			return Vector2(0.0, 0.0);
		else
			return Vector2(m_x / length, m_y / length);
	}
};

 