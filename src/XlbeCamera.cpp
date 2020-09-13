#include "XlbeException.h"
#include "XlbeCamera.h"
#include "XlbeRoot.h"

/////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

/////////////////////////////////////////////////////////////////////////////////////////
Camera::Camera(const std::string& name )
:Node(name)
{
}

Camera::~Camera()
{
}

void Camera::set_camera(float x, float y, float z, float xv, float yv, float zv, float xu, float yu, float zu)
{
	pos_.x_ = x; pos_.y_ = y; pos_.z_ = z;
	view_.x_ = xv; view_.y_ = yv; view_.z_ = zv;
	up_.x_ = xu; up_.y_ = yu; up_.z_ = zu;
}

void Camera::move_camera(float amount)
{
   Vector3 dir = view_ - pos_;
   dir.normal();

   pos_ += dir * amount;
   view_ += dir * amount;
}

void Camera::rotate_camera(float angle, float x, float y, float z)
{
	float ca = (float)cos(angle);
	float sa = (float)sin(angle);

	Vector3 dir = view_ - pos_;
	dir.normal();

	Vector3 dir2;

	dir2.x_ = (ca + (1 - ca) * x) * dir.x_;
	dir2.x_ += ((1 - ca) * x * y - z * sa)* dir.y_;
	dir2.x_ += ((1 - ca) * x * z + y * sa) * dir.z_;

	dir2.y_ = ((1 - ca) * x * y + z * sa) * dir.x_;
	dir2.y_ += (ca + (1 - ca) * y) * dir.y_;
	dir2.y_ += ((1 - ca) * y * z - x * sa) * dir.z_;

	dir2.z_ = ((1 - ca) *x * z - y * sa) * dir.x_;
	dir2.z_ += ((1 - ca) * y * z + x * sa) * dir.y_;
	dir2.z_ += (ca + (1 - ca) * z) * dir.z_;

	view_ = pos_ + dir2;
}

////////////////////////////////////////////////////////////////////////////////////////////
}
