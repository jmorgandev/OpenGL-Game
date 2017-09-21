#ifndef Color3_H
#define Color3_H

#include <math.h>

//Color3 template class
template <class TYPE> class Color3 {
public:
	Color3() : m_R(0), m_G(0), m_B(0), m_A(1){}
	Color3(TYPE r, TYPE g, TYPE b, TYPE a = 0.0f) : m_R(r), m_G(g), m_B(b), m_A(a){}
	~Color3() {}

	TYPE getR() { return m_R; }
	TYPE getG() { return m_G; }
	TYPE getB() { return m_B; }
	TYPE getA() { return m_A; }

	void set(TYPE r, TYPE g, TYPE b, TYPE a = 0.0f) { m_R = r; m_G = g; m_B = b; m_A = a; }

	void setR(TYPE r) { m_R = r; }
	void setG(TYPE g) { m_G = g; }
	void setB(TYPE b) { m_B = b; }
	void setA(TYPE a) { m_A = a; }

	void modR(TYPE r) { m_R += r; }
	void modG(TYPE g) { m_G += g; }
	void modB(TYPE b) { m_B += b; }
	void modA(TYPE a) { m_A += a; }

	void setZero() { m_R = 0; m_G = 0; m_B = 0; m_A = 1; }

	void toMatrix(float* arr) {
		arr[0] = m_R;
		arr[1] = m_G;
		arr[2] = m_B;
		arr[3] = m_A;
	}

	Color3 operator+(const Color3& c2) const {
		return Color3(m_R + c2.m_R, m_G + c2.m_G, m_B + c2.m_B, m_A + c2.m_A);
	}

	Color3 operator-(const Color3& c2) const {
		return Color3(m_R - c2.m_R, m_G - c2.m_G, m_B - c2.m_B, m_A - c2.m_A);
	}
	Color3 operator-() {
		Color3 c;
		c.m_R = -m_R;
		c.m_G = -m_G;
		c.m_B = -m_B;
		c.m_A = -m_A;
		return c;
	}

	Color3& operator+=(const Color3& c2) {
		m_R += c2.m_R;
		m_G += c2.m_G;
		m_B += c2.m_B;
		m_A += c2.m_A;
		return *this;
	}

	Color3& operator-=(const Color3& c2) {
		m_R -= c2.m_R;
		m_G -= c2.m_G;
		m_B -= c2.m_B;
		m_A -= c2.m_A;
		return *this;
	}

	Color3 operator*(TYPE scalar) {
		return Color3(m_R * scalar, m_G * scalar, m_B * scalar, m_A * scalar);
	}

	Color3 operator/(TYPE scalar) {
		return Color3(m_R / scalar, m_G / scalar, m_B / scalar, m_A / scalar);
	}

	Color3 operator*=(TYPE scalar) {
		m_R *= scalar;
		m_G *= scalar;
		m_B *= scalar;
		m_A *= scalar;
		return *this;
	}

	Color3& operator/=(TYPE scalar) {
		m_R /= scalar;
		m_G /= scalar;
		m_B /= scalar;
		m_A /= scalar;
		return *this;
	}

	Color3 White() {
		return Color3(1.0f, 1.0f, 1.0f, 1.0f);
	}

	Color3 Black() {
		return Color3(0.0f, 0.0f, 0.0f, 1.0f);
	}

private:
	TYPE m_R, m_G, m_B, m_A;
};

typedef Color3<float> Color3f;
typedef Color3<int> Color3i;

#endif