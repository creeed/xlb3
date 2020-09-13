#include "XlbeException.h"
#include "XlbeVector.h"

////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

////////////////////////////////////////////////////////////////////////////////////////////
Vector2::Vector2()
{
   x_ = y_ = 0.0;
}

Vector2::Vector2(float x, float y)
{
   x_ = x;
   y_ = y;
}

void Vector2::operator = (Vector2 &v)
{
   x_ = v.x_;
   y_ = v.y_;
}

Vector2 Vector2::operator - (Vector2 &v)
{
   return Vector2(x_ - v.x_, y_ - v.y_);
}

Vector2 Vector2::operator + (Vector2 &v)
{
   return Vector2(x_ + v.x_, y_ + v.y_);
}

Vector2 Vector2::operator * (Vector2 &v)
{
   return Vector2(x_ * v.x_, y_ * v.y_);
}

Vector2 Vector2::operator / (Vector2 &v)
{
   return Vector2(x_ / v.x_, y_ / v.y_);
}

Vector2 Vector2::operator + (float f)
{
   return Vector2(x_ + f, y_ + f);
}

Vector2 Vector2::operator - (float f)
{
   return Vector2(x_ - f, y_ - f);
}

Vector2 Vector2::operator * (float f)
{
   return Vector2(x_ * f, y_ * f);
}

Vector2 Vector2::operator / (float f)
{
   f = 1 / f;

   return Vector2(x_ * f, y_ * f);
}

void Vector2::operator += (Vector2 &v)
{
   x_ += v.x_;
   y_ += v.y_;
}

void Vector2::operator -= (Vector2 &v)
{
   x_ -= v.x_;
   y_ -= v.y_;
}

void Vector2::operator *= (Vector2 &v)
{
   x_ *= v.x_;
   y_ *= v.y_;
}

void Vector2::operator /= (Vector2 &v)
{
   x_ /= v.x_;
   y_ /= v.y_;
}

void Vector2::operator += (float f)
{
   x_ += f;
   y_ += f;
}

void Vector2::operator -= (float f)
{
   x_ -= f;
   y_ -= f;
}

void Vector2::operator *= (float f)
{
   x_ *= f;
   y_ *= f;
}

void Vector2::operator /= (float f)
{
   f = 1 / f;

   x_ *= f;
   y_ *= f;
}

void Vector2::cross_product(Vector2 &v1, Vector2 &v2)
{

}

float Vector2::dot_product(Vector2 &v1)
{
   return x_ * v1.x_ + y_ * v1.y_;
}

float Vector2::get_length()
{
   return (float)sqrt((x_ * x_ + y_ * y_));
}

void Vector2::normal()
{
   float lenght = get_length();

   if(lenght == 0.0f) lenght = 1.0f;

   x_ = x_ / lenght;
   y_ = y_ / lenght;
}

void Vector2::normalize(Vector2 &v1, Vector2 &v2)
{
}

////////////////////////////////////////////////////////////////////////////////////////////
Vector3::Vector3()
{
   x_ = y_ = z_ = 0.0;
}

Vector3::Vector3(float x, float y, float z)
{
   x_ = x;
   y_ = y;
   z_ = z;
}

void Vector3::operator = (Vector3 &v)
{
   x_ = v.x_;
   y_ = v.y_;
   z_ = v.z_;
}

Vector3 Vector3::operator - (Vector3 &v)
{
   return Vector3(x_ - v.x_, y_ - v.y_, z_ - v.z_);
}

Vector3 Vector3::operator + (Vector3 &v)
{
   return Vector3(x_ + v.x_, y_ + v.y_, z_ + v.z_);
}

Vector3 Vector3::operator * (Vector3 &v)
{
   return Vector3(x_ * v.x_, y_ * v.y_, z_ * v.z_);
}

Vector3 Vector3::operator / (Vector3 &v)
{
   return Vector3(x_ / v.x_, y_ / v.y_, z_ / v.z_);
}

Vector3 Vector3::operator + (float f)
{
   return Vector3(x_ + f, y_ + f, z_ + f);
}

Vector3 Vector3::operator - (float f)
{
   return Vector3(x_ - f, y_ - f, z_ - f);
}

Vector3 Vector3::operator * (float f)
{
   return Vector3(x_ * f, y_ * f, z_ * f);
}

Vector3 Vector3::operator / (float f)
{
   f = 1 / f;

   return Vector3(x_ * f, y_ * f, z_ * f);
}

void Vector3::operator += (Vector3 &v)
{
   x_ += v.x_;
   y_ += v.y_;
   z_ += v.z_;
}

void Vector3::operator -= (Vector3 &v)
{
   x_ -= v.x_;
   y_ -= v.y_;
   z_ -= v.z_;
}

void Vector3::operator *= (Vector3 &v)
{
   x_ *= v.x_;
   y_ *= v.y_;
   z_ *= v.z_;
}

void Vector3::operator /= (Vector3 &v)
{
   x_ /= v.x_;
   y_ /= v.y_;
   z_ /= v.z_;
}

void Vector3::operator += (float f)
{
   x_ += f;
   y_ += f;
   z_ += f;
}

void Vector3::operator -= (float f)
{
   x_ -= f;
   y_ -= f;
   z_ -= f;
}

void Vector3::operator *= (float f)
{
   x_ *= f;
   y_ *= f;
   z_ *= f;
}

void Vector3::operator /= (float f)
{
   f = 1 / f;

   x_ *= f;
   y_ *= f;
   z_ *= f;
}

void Vector3::cross_product(Vector3 &v1, Vector3 &v2)
{
   x_ = ((v1.y_ * v2.z_) - (v1.z_ * v2.y_));
   y_ = ((v1.z_ * v2.x_) - (v1.x_ * v2.z_));
   z_ = ((v1.x_ * v2.y_) - (v1.y_ * v2.x_));
}

float Vector3::dot_product(Vector3 &v1)
{
   return x_ * v1.x_ + y_ * v1.y_ + z_ * v1.z_;
}

float Vector3::get_length()
{
   return (float)sqrt((x_ * x_ + y_ * y_ + z_ * z_));
}

void Vector3::normal()
{
   float lenght = get_length();

   if(lenght == 0.0f) lenght = 1.0f;

   x_ = x_ / lenght;
   y_ = y_ / lenght;
   z_ = z_ / lenght;
}

void Vector3::normalize(Vector3 &v1, Vector3 &v2, Vector3 &v3)
{
   Vector3 e1, e2;

   e1.x_ = v2.x_ - v1.x_;
   e1.y_ = v2.y_ - v1.y_;
   e1.z_ = v2.z_ - v1.z_;
   e1.normal();

   e2.x_ = v3.x_ - v1.x_;
   e2.y_ = v3.y_ - v1.y_;
   e2.z_ = v3.z_ - v1.z_;
   e2.normal();

   cross_product(e1, e2);
   normal();
}

////////////////////////////////////////////////////////////////////////////////////////////
}