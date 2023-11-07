#pragma once

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
};

