#ifndef __XLBE_VECTOR_H__
#define __XLBE_VECTOR_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//作者：徐林炳
//QQ: 597389076
//mail: creednew2000@163.com

//请尊重作者辛勤劳动， 勿删，谢谢。

///////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Vector2
{
public:
	Vector2();
	Vector2(float x, float y);

	void operator = (Vector2 &v);
	Vector2 operator - (Vector2 &v);
	Vector2 operator + (Vector2 &v);
	Vector2 operator * (Vector2 &v);
	Vector2 operator / (Vector2 &v);

	Vector2 operator + (float f);
	Vector2 operator - (float f);
	Vector2 operator * (float f);
	Vector2 operator / (float f);

	void operator += (Vector2 &v);
	void operator -= (Vector2 &v);
	void operator *= (Vector2 &v);
	void operator /= (Vector2 &v);
	void operator += (float f);
	void operator -= (float f);
	void operator *= (float f);
	void operator /= (float f);

	void normal();
	float get_length();
	void normalize(Vector2 &v1, Vector2 &v2);
	
	float dot_product(Vector2 &v1);
	void cross_product(Vector2 &v1, Vector2 &v2);

	float x_, y_;
};

/////////////////////////////////////////////////////////////////////////////////////////////////
class Xlbe_Export Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);

	void operator = (Vector3 &v);
	Vector3 operator - (Vector3 &v);
	Vector3 operator + (Vector3 &v);
	Vector3 operator * (Vector3 &v);
	Vector3 operator / (Vector3 &v);

	Vector3 operator + (float f);
	Vector3 operator - (float f);
	Vector3 operator * (float f);
	Vector3 operator / (float f);

	void operator += (Vector3 &v);
	void operator -= (Vector3 &v);
	void operator *= (Vector3 &v);
	void operator /= (Vector3 &v);
	void operator += (float f);
	void operator -= (float f);
	void operator *= (float f);
	void operator /= (float f);

	void normal();
	float get_length();
	void normalize(Vector3 &v1, Vector3 &v2, Vector3 &v3);
	
	float dot_product(Vector3 &v1);
	void cross_product(Vector3 &v1, Vector3 &v2);

	float x_, y_, z_;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif