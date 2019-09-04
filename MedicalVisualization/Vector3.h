#pragma once
#ifndef _VECTOR3_H_INCLUDE_
#define _VECTOR3_H_INCLUDE_
#include <math.h>
class Vector3
{
public:
	float x, y, z;
	float circler=0.0;
	Vector3() {};
	Vector3(const Vector3 &a) :x(a.x), y(a.y), z(a.z) {};
	Vector3(float _x, float _y, float _z) :x(_x), y(_y), z(_z) {};

	//零向量
	void zero() 
	{
		x = y = z = 0.0f;
	}
	//计算单位向量，进行标准化
	void normalize()
	{
		float magsq = x * x + y * y + z * z;    //平发根之前
		if (magsq > 0.0f)  //必须比0大
		{
			float temp = 1 / sqrt(magsq);
			x *= temp;
			y *= temp;
			z *= temp;

		}
	}
	//负向量,运算符的重载
	Vector3 operator-() const { return Vector3(-x, -y, -z); }

	Vector3 operator*(float a /*标量*/) const
	{
		return Vector3(x*a, y*a, z*a);
	}
	Vector3 operator/(float a) const
	{
		float temp = 1.0f / a;
		return Vector3(x*temp, y*temp, z*temp);
	}

	Vector3 operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	Vector3 operator/=(float a)
	{
		float temp = 1.0f / a;
		x *= temp;
		y *= temp;
		z *= temp;
		return *this;
	}

	Vector3 operator+(const Vector3 &a)const
	{
		return Vector3(x + a.x, y + a.y, z + a.z);
	}

	Vector3 operator+=(const Vector3 &a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}

	Vector3 operator-=(const Vector3 &a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}

	Vector3 operator-(const Vector3 &a)const
	{
		return Vector3(x - a.x, y - a.y, z - a.z);
	}

	//点乘

	float  operator*(const Vector3 &a)const
	{
		return x * a.x + y * a.y + z * a.z;
	}



};

//计算向量的模
inline float vectorMag(const Vector3 &a)
{
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

//非成员函数，实现向量左乘
inline Vector3 operator*(float k, const Vector3 &v)
{
	return Vector3(k*v.x, k*v.y, k*v.z);
}

//计算两点之间的距离
inline float distance(const Vector3 &a, const Vector3 &b)
{
	float dx = a.x - b.x;
	float dy = a.y - b.y;
	float dz = a.z - b.z;

	//计算向量的模。也就是大小，距离

	return sqrt(dx*dx + dy * dy + dz * dz);

}

//计算叉乘

inline Vector3 crossProduct(const Vector3&a, const Vector3 &b)
{
	return Vector3(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
	);
}
//计算三角形的外接圆的圆心和半径
inline Vector3 solveCenterPointOfCircle(std::vector<Vector3> pt, Vector3 cirlepoint)
{
	
	double a1, b1, c1, d1;
	double a2, b2, c2, d2;
	double a3, b3, c3, d3;
	
	double x1 = pt[0].x, y1 = pt[0].y, z1 = pt[0].z;
	double x2 = pt[1].x, y2 = pt[1].y, z2 = pt[1].z;
	double x3 = pt[2].x, y3 = pt[2].y, z3 = pt[2].z;

	a1 = (y1*z2 - y2 * z1 - y1 * z3 + y3 * z1 + y2 * z3 - y3 * z2);
	b1 = -(x1*z2 - x2 * z1 - x1 * z3 + x3 * z1 + x2 * z3 - x3 * z2);
	c1 = (x1*y2 - x2 * y1 - x1 * y3 + x3 * y1 + x2 * y3 - x3 * y2);
	d1 = -(x1*y2*z3 - x1 * y3*z2 - x2 * y1*z3 + x2 * y3*z1 + x3 * y1*z2 - x3 * y2*z1);

	a2 = 2 * (x2 - x1);
	b2 = 2 * (y2 - y1);
	c2 = 2 * (z2 - z1);
	d2 = x1 * x1 + y1 * y1 + z1 * z1 - x2 * x2 - y2 * y2 - z2 * z2;

	a3 = 2 * (x3 - x1);
	b3 = 2 * (y3 - y1);
	c3 = 2 * (z3 - z1);
	d3 = x1 * x1 + y1 * y1 + z1 * z1 - x3 * x3 - y3 * y3 - z3 * z3;

	float x, y, z;
	x = -(b1*c2*d3 - b1 * c3*d2 - b2 * c1*d3 + b2 * c3*d1 + b3 * c1*d2 - b3 * c2*d1)
		/ (a1*b2*c3 - a1 * b3*c2 - a2 * b1*c3 + a2 * b3*c1 + a3 * b1*c2 - a3 * b2*c1);
	y = (a1*c2*d3 - a1 * c3*d2 - a2 * c1*d3 + a2 * c3*d1 + a3 * c1*d2 - a3 * c2*d1)
		/ (a1*b2*c3 - a1 * b3*c2 - a2 * b1*c3 + a2 * b3*c1 + a3 * b1*c2 - a3 * b2*c1);
	z = -(a1*b2*d3 - a1 * b3*d2 - a2 * b1*d3 + a2 * b3*d1 + a3 * b1*d2 - a3 * b2*d1)
		/ (a1*b2*c3 - a1 * b3*c2 - a2 * b1*c3 + a2 * b3*c1 + a3 * b1*c2 - a3 * b2*c1);

	float r = 0.0;
	r = sqrt((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y) + (z1 - z)*(z1 - z));
	r = sqrt((x2 - x)*(x2 - x) + (y2 - y)*(y2 - y) + (z2 - z)*(z2 - z));
	r = sqrt((x3 - x)*(x3 - x) + (y3 - y)*(y3 - y) + (z3 - z)*(z3 - z));
	cirlepoint.x = x;
	cirlepoint.y = y;
	cirlepoint.z = z;
	cirlepoint.circler = r;
	return cirlepoint;

}



#endif