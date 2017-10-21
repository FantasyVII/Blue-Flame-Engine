#include "Vector4.h"
#include "Math.h"

namespace BF
{
	namespace Math
	{
		Vector4::Vector4() :
			x(0.0f), y(0.0f), z(0.0f), w(0.0f)
		{
		}

		Vector4::Vector4(float value) :
			x(value), y(value), z(value), w(value)
		{
		}

		Vector4::Vector4(float x, float y, float z, float w) :
			x(x), y(y), z(z), w(w)
		{
		}

		Vector4::~Vector4()
		{
		}

		float Vector4::Dot(const Vector4& vector) const
		{
			return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
		}

		float Vector4::Distance(const Vector4& vector) const
		{
			Vector4 d = Direction(vector);
			return sqrt((d.x * d.x + d.y * d.y + d.z * d.z + d.w * d.w));
		}

		float Vector4::Magnitude() const
		{
			return (float)sqrt(Dot(*this));
		}

		Vector4 Vector4::Direction(const Vector4& vector) const
		{
			return Vector4(abs(vector.x - x), abs(vector.y - y), abs(vector.z - z), abs(vector.w - w));
		}

		Vector4 Vector4::Normalize() const
		{
			float length = Magnitude();

			if (length > 0)
				return Vector4(x / length, y / length, z / length, w / length);
			else
				return Vector4(0);
		}

		Vector4 Vector4::Center() const
		{
			return Vector4(x / 2, y / 2, z / 2, w / 2);
		}

		Vector4 Vector4::Min()
		{
			float min = Math::Min(x, y);
			float min2 = Math::Min(z, w);
			return Vector4(Math::Min(min, min2));
		}

		Vector4 Vector4::Max()
		{
			float max = Math::Max(x, y);
			float max2 = Math::Max(z, w);
			return Vector4(Math::Max(max, max2));
		}

		Vector4 operator+(const Vector4& left, const Vector4& right)
		{
			return Vector4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
		}

		Vector4 operator-(const Vector4& left, const Vector4& right)
		{
			return Vector4(left.x - right.x, left.y - right.y, left.z - right.z, left.w - right.w);
		}

		Vector4 operator*(const Vector4& left, const Vector4& right)
		{
			return Vector4(left.x * right.x, left.y * right.y, left.z * right.z, left.w * right.w);
		}

		Vector4 operator/(const Vector4& left, const Vector4& right)
		{
			return Vector4(left.x / right.x, left.y / right.y, left.z / right.z, left.w / right.w);
		}

		Vector4& Vector4::operator+=(const Vector4& right)
		{
			x += right.x;
			y += right.y;
			z += right.z;
			w += right.w;
			return *this;
		}

		Vector4& Vector4::operator-=(const Vector4& right)
		{
			x -= right.x;
			y -= right.y;
			z -= right.z;
			w -= right.w;
			return *this;
		}

		Vector4& Vector4::operator*=(const Vector4& right)
		{
			x *= right.x;
			y *= right.y;
			z *= right.z;
			w *= right.w;
			return *this;
		}

		Vector4& Vector4::operator/=(const Vector4& right)
		{
			x /= right.x;
			y /= right.y;
			z /= right.z;
			w /= right.w;
			return *this;
		}

		bool Vector4::operator>(const Vector4& right)
		{
			return Magnitude() > right.Magnitude();
		}

		bool Vector4::operator>=(const Vector4& right)
		{
			return Magnitude() >= right.Magnitude();
		}

		bool Vector4::operator<(const Vector4& right)
		{
			return Magnitude() < right.Magnitude();
		}

		bool Vector4::operator<=(const Vector4& right)
		{
			return Magnitude() <= right.Magnitude();
		}

		bool Vector4::operator==(const Vector4 &right)
		{
			return x == right.x && y == right.y && z == right.z && w == right.w;
		}

		bool Vector4::operator!=(const Vector4 &right)
		{
			return !(*this == right);
		}

		std::ostream& operator<<(std::ostream& os, const Vector4& vector)
		{
			return os << "{" << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << "}";
		}
	}
}