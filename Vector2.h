#pragma once
#include <math.h>

// structure to create a point to vector2 (x & y)
struct Vector2
{
	double m_x;
	double m_y;

	bool operator==(const Vector2& other) const
	{
		return (m_x == other.m_x && m_y == other.m_y);
	}
	bool operator!=(const Vector2& other) const
	{
		return (m_x != other.m_x || m_y != other.m_y);
	}

	static double Distance (const Vector2& object_A, const Vector2& object_B) 
	{
		double distance_x;
		double distance_y;


		distance_x = abs(abs((int)object_A.m_x) - abs((int)object_B.m_x));
		distance_y = abs(abs((int)object_A.m_y) - abs((int)object_B.m_y));

		return sqrt((distance_x * distance_x) + (distance_y * distance_y));
	}
};

