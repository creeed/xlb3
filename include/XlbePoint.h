#ifndef __XLBE_POINT_H__
#define __XLBE_POINT_H__

/////////////////////////////////////////////////////////////////////////////////////////////////
//���ߣ����ֱ�
//QQ: 597389076
//mail: creednew2000@163.com

//���������������Ͷ��� ��ɾ��лл��

///////////////////////////////////////////////////////////////////////////////////////////////
namespace xlbe {

///////////////////////////////////////////////////////////////////////////////////////////////
class Point
{
public:
    Point():x_(0), y_(0) {}
    Point(float x, float y):x_(x), y_(y) {}
    Point(const Point &point):x_(point.x_), y_(point.y_) {}
    ~Point() {}

public:
    void offset(float x, float y) { x_+= x; y_+=y; }

    void set_point(float x, float y) { x_=x; y_=y; }

    bool operator == (const Point &point) const { return (x_==point.x_&&y_==point.y_); }
    bool operator != (const Point &point) const { return (x_!=point.x_||y_!=point.y_); }

    Point &operator = (const Point &point) { x_=point.x_; y_=point.y_; return *this; }

    void operator += (const Point &point) { x_+=point.x_; y_+=point.y_; }
    void operator -= (const Point &point) { x_-=point.x_; y_-=point.y_; }

    Point operator + (const Point &point) { return Point(x_+point.x_, y_+point.y_); }
    Point operator - (const Point &point) { return Point(x_-point.x_, y_-point.y_); }
    Point operator - () { return Point(-x_, -y_); }

    Point operator * (float multip) { return Point(x_*multip, y_*multip); }

public:
    float x_;
    float y_;
};


inline Point operator+ (const Point &lhs, const Point &rhs)
{
	return Point(lhs.x_+rhs.x_, lhs.y_+rhs.y_);
}

inline Point operator- (const Point &lhs, const Point &rhs)
{
	return Point(lhs.x_-rhs.x_, lhs.y_-rhs.y_);
}


///////////////////////////////////////////////////////////////////////////////////////////////
}
#endif
