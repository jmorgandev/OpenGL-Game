#ifndef Vector3_H
#define Vector3_H

#include <math.h>

//Vector3 template class
template <class TYPE> class Vector3 {
public:
	Vector3() : m_X(1), m_Y(1), m_Z(1){}
	Vector3(TYPE x, TYPE y, TYPE z) : m_X(x), m_Y(y), m_Z(z){}

	TYPE getX() { return m_X; }
	TYPE getY() { return m_Y; }
	TYPE getZ() { return m_Z; }

	void set(TYPE x, TYPE y, TYPE z) { m_X = x; m_Y = y; m_Z = z; }
	void set(Vector3& vec) { m_X = vec.getX(); m_Y = vec.getY(); m_Z = vec.getZ(); }

	void mod(TYPE x, TYPE y, TYPE z) { m_X += x; m_Y += y; m_Z += z; }
	void mod(Vector3& vec) { m_X += vec.getX(); m_Y += vec.getY(); m_Z += vec.getZ(); }

	void setX(TYPE x) { m_X = x; }
	void setY(TYPE y) { m_Y = y; }
	void setZ(TYPE z) { m_Z = z; }

	void modX(TYPE x) { m_X += x; }
	void modY(TYPE y) { m_Y += y; }
	void modZ(TYPE z) { m_Z += z; }

	void setZero() { m_X = 0; m_Y = 0; m_Z = 0; }

	void toMatrix(float* arr) {
		arr[0] = m_X;
		arr[1] = m_Y;
		arr[2] = m_Z;
		arr[3] = 1.0f;
	}

	TYPE length() { return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z); }

	TYPE lengthSqr() { return (m_X * m_X + m_Y * m_Y + m_Z * m_Z); }

	TYPE distance(const Vector3& v2) {
		int xd = abs(v2.m_X) - abs(m_X);
		int yd = abs(v2.m_Y) - abs(m_Y);
		int zd = abs(v2.m_Z) - abs(m_Z);
		return sqrt(xd * xd + yd * yd + zd * zd);
	}

	void normalize() {
		TYPE l = length();
		if (l > 0) {
			m_X /= l;
			m_Y /= l;
			m_Z /= l;
		}
	}

	Vector3 operator+(const Vector3& v2) const {
		return Vector3(m_X + v2.m_X, m_Y + v2.m_Y, m_Z + v2.m_Z);
	}

	Vector3 operator-(const Vector3& v2) const {
		return Vector3(m_X - v2.m_X, m_Y - v2.m_Y, m_Z - v2.m_Z);
	}
	Vector3 operator-() {
		Vector3 v;
		v.m_X = -m_X;
		v.m_Y = -m_Y;
		v.m_Z = -m_Z;
		return v;
	}

	Vector3& operator+=(const Vector3& v2) {
		m_X += v2.m_X;
		m_Y += v2.m_Y;
		m_Z += v2.m_Z;
		return *this;
	}

	Vector3& operator-=(const Vector3& v2) {
		m_X -= v2.m_X;
		m_Y -= v2.m_Y;
		m_Z -= v2.m_Z;
		return *this;
	}

	Vector3 operator*(TYPE scalar) {
		return Vector3(m_X * scalar, m_Y * scalar, m_Z * scalar);
	}

	Vector3 operator/(TYPE scalar) {
		return Vector3(m_X / scalar, m_Y / scalar, m_Z / scalar);
	}

	Vector3 operator*=(TYPE scalar) {
		m_X *= scalar;
		m_Y *= scalar;
		m_Z *= scalar;
		return *this;
	}

	Vector3& operator/=(TYPE scalar) {
		m_X /= scalar;
		m_Y /= scalar;
		m_Z /= scalar;
		return *this;
	}

	float dotProduct(const Vector3& vec1) {
		return m_X * vec1.m_X + m_Y * vec1.m_Y + m_Z * vec1.m_Z;
	}

	Vector3 Cross(const Vector3& vec) {
		return Vector3(m_Y * vec.m_Z - m_Z * vec.m_Y, m_Z * vec.m_X - m_X * vec.m_Z, m_X * vec.m_Y - m_Y * vec.m_X);
	}

	static Vector3 Up() {
		return Vector3(0, 1, 0);
	}

private:
	TYPE m_X, m_Y, m_Z;
};

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

#endif