#include "Line.h"
#include "../Top/Top.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
using namespace ci;
using namespace ci::app;
////線のコンストラクタ
Line::Line(Vec2f _p1, Vec2f _p2,bool _isvertical){

    SetPoint(_p1, _p2);
	Vec2f center2D= (_p1 + _p2) / 2.f;
	centerpos = Vec3f(center2D.x, center2D.y,0);
    vec = Vec2f::zero();
	float xsize = std::sqrtf((_p2.x - _p1.x)*(_p2.x - _p1.x) + (_p2.y - _p1.y)*(_p2.y - _p1.y));
	scale = Vec3f(xsize,0, WorldScale *2);
	angle = std::atan2(_p2.y-_p1.y, _p2.x - _p1.x);
	rotate = Vec3f(0, 0, angle*(180.f / M_PI));
	isvertical = _isvertical;
}

//線分と線分が接触したらtrueを返す
bool Line::IsIntersect(Vec2f _p1, Vec2f _p2){
    drawLineV(_p1, _p2);
    if (((point1.x - point2.x)*(_p1.y - point1.y) + (point1.y - point2.y)*(point1.x - _p1.x))*
        (((point1.x - point2.x)*(_p2.y - point1.y)) + (point1.y - point2.y)*(point1.x - _p2.x)) <= 0){
        if (((_p1.x - _p2.x)*(point1.y - _p1.y) + (_p1.y - _p2.y)*(_p1.x - point1.x))*
            (((_p1.x - _p2.x)*(point2.y - _p1.y)) + (_p1.y - _p2.y)*(_p1.x - point2.x)) <= 0)
            return true;
    }
    return false;
}

//線_p1と_p2を結ぶ線の交点を返す関数
Vec2f Line::Intersection_Point(Vec2f _p1, Vec2f _p2){
    float A = (point2.y - point1.y) / (point2.x - point1.x);
    float B = (_p1.y - _p2.y) / (_p1.x - _p2.x);
    Vec2f a;
    a.x = (A*point1.x - point1.y - B*_p2.x + _p2.y) / (A - B);
    a.y = (point2.y - point1.y) / (point2.x - point1.x)*(a.x - point1.x) + point1.y;
    float b;
    if (point1.x == point2.x){
        b = _p2.y - (B*_p2.x);
        a.x = point1.x;
        a.y = a.x*B + b;
    }
    if (_p2.x == _p1.x){
        b = point1.y - (A * point1.x);
        a.x = _p2.x;
        a.y = a.x * A + b;
    }
    return a;
}
//めり込んだ分だけ返す関数
Vec2f Line::Collision(Vec2f _pos, Vec2f _size, Vec2f _vec){
    Vec2f size_2 = _size / 2;
    Vec2f pos_center = _pos + size_2;
    Vec2f pos_after = pos_center - _vec;



    Vec2f a = Vec2f::zero();
    if (_vec.y <= 0){
        a += CollisionUp(point2 + Vec2f(-size_2.x*is_right(), size_2.y), point1 + Vec2f(-size_2.x * is_right(), size_2.y), pos_center, _vec);
        a += CollisionUp(point1 + Vec2f(-size_2.x, size_2.y), point1 + size_2, pos_center, _vec);
    }
    //drawLineV(point2 + Vec2f(-size_2.x*is_right, size_2.y), point1 + Vec2f(-size_2.x * is_right, size_2.y));
    //drawLineV(point1 + Vec2f(-size_2.x, size_2.y), point1 + size_2);
    if (_vec.y >= 0){
        a += CollisionDown(point2 + Vec2f(size_2.x*is_right(), -size_2.y), point1 + Vec2f(size_2.x*is_right(), -size_2.y), pos_center, _vec);
        a += CollisionDown(point2 + Vec2f(size_2.x, -size_2.y), point2 - size_2, pos_center, _vec);


    }
    //drawLineV(point2 + Vec2f(size_2.x*is_right, -size_2.y), point1 + Vec2f(size_2.x*is_right, -size_2.y));
    //drawLineV(point2 + Vec2f(size_2.x, -size_2.y), point2 - size_2);
    //左
    if (_vec.x >= 0){
        //a += CollisionLeft(RightPoint(1) + Vec2f(-size_2.x, size_2.y), RightPoint(1) - size_2, pos_center, _vec);
    }
    //drawLineV(RightPoint(1) + Vec2f(-size_2.x, size_2.y), RightPoint(1) - size_2);
    //右
    if (_vec.x <= 0){
        //a += CollisionRight(RightPoint(0) + Vec2f(size_2.x, -size_2.y), RightPoint(0) + size_2, pos_center, _vec);

    }
    //drawLineV(RightPoint(0) + Vec2f(size_2.x, -size_2.y), RightPoint(0) + size_2);
    return a;
}

//どこに当たったかを返す
Direction Line::HitDirection(Vec2f _pos, Vec2f _size, Vec2f _vec){
    Vec2f _pos2 = _pos - _vec;

    if (_vec.y <= 0){
        if (IsIntersect(_pos + Vec2f(_size.x, 0),
            _pos2 + Vec2f(_size.x, 0)))
        {
            return Direction::UP;
        }
    }

    return Direction::NON;
}

//point2つのセット
void Line::SetPoint(Vec2f _p1, Vec2f _p2){
    if (_p1.y >= _p2.y){
        point1 = _p1;
        point2 = _p2;
    }
    else
    {
        point1 = _p2;
        point2 = _p1;
    }
}

//線の描画
void Line::Draw(){
	DrawM.drawTextureCube(centerpos,scale,rotate,TextureM.getTexture("red3.png"),ColorA(1,1,1,1));
    //drawLineV(point1, point2);
}
//vec2fでの線の描画簡略化
void Line::drawLineV(Vec2f _p1, Vec2f _p2, ColorA color){
	gl::lineWidth(0.2f);
	gl::drawLine(Vec3f(_p1.x, _p1.y, 0), Vec3f(_p2.x, _p2.y, 0));
}
//縦だったらtrue
bool Line::IsVertical(){
    float A = (point2.y - point1.y) / (point2.x - point1.x);
    return (std::abs(A) > 1) || (point1.x == point2.x);
}

int Line::status(){
    if (point1.x <= point2.x){
        if (point1.y <= point2.y){
            return 1;
        }
        if (point1.y >= point2.y){
            return 2;
        }
    }
    if (point1.x >= point2.x){
        if (point1.y >= point2.y){
            return 3;
        }
        if (point1.y <= point2.y){
            return 4;
        }
    }
}


Vec2f Line::CollisionUp(Vec2f _p1, Vec2f _p2,
    Vec2f _pos, Vec2f _vec){
    Vec2f pos_after = _pos - _vec;
    if (linetoline(_p1, _p2, _pos, pos_after))
        return Vec2f(0, intersection_point(_p1, _p2, _pos, _pos + Vec2f(0, 1)).y - _pos.y + 3);
    return Vec2f::zero();
}

Vec2f Line::CollisionDown(Vec2f _p1, Vec2f _p2, Vec2f _pos, Vec2f _vec){
    Vec2f pos_after = _pos - _vec;
    if (linetoline(_p1, _p2, _pos, pos_after))
        return Vec2f(0, intersection_point(_p1, _p2, _pos, _pos + Vec2f(0, 1)).y - _pos.y - 3);
    return Vec2f::zero();
}
Vec2f Line::CollisionLeft(Vec2f _p1, Vec2f _p2, Vec2f _pos, Vec2f _vec){

    Vec2f pos_after = _pos - _vec;
    if (linetoline(_p1, _p2, _pos, pos_after))
        return Vec2f(intersection_point(_p1, _p2, _pos, _pos + Vec2f(1, 0)).x - _pos.x - 3, 0);
    return Vec2f::zero();
}
Vec2f Line::CollisionRight(Vec2f _p1, Vec2f _p2, Vec2f _pos, Vec2f _vec){
    Vec2f pos_after = _pos - _vec;
    if (linetoline(_p1, _p2, _pos, pos_after))
        return Vec2f(intersection_point(_p1, _p2, _pos, _pos + Vec2f(1, 0)).x - _pos.x + 3, 0);
    return Vec2f::zero();
}

Vec2f Line::intersection_point(Vec2f p1, Vec2f p2, Vec2f p3, Vec2f p4){
    float A = (p2.y - p1.y) / (p2.x - p1.x);
    float B = (p4.y - p3.y) / (p4.x - p3.x);
    Vec2f a;
    a.x = (A*p1.x - p1.y - B*p3.x + p3.y) / (A - B);
    a.y = (p2.y - p1.y) / (p2.x - p1.x)*(a.x - p1.x) + p1.y;
    float b;
    if (p1.x == p2.x){
        b = p3.y - (B*p3.x);
        a.x = p1.x;
        a.y = a.x*B + b;
    }
    if (p3.x == p4.x){
        b = p1.y - (A * p1.x);
        a.x = p3.x;
        a.y = a.x * A + b;
    }
    return a;
}

bool Line::linetoline(Vec2f p1, Vec2f p2, Vec2f p3, Vec2f p4){

    if (((p1.x - p2.x)*(p3.y - p1.y) + (p1.y - p2.y)*(p1.x - p3.x))*
        (((p1.x - p2.x)*(p4.y - p1.y)) + (p1.y - p2.y)*(p1.x - p4.x)) <= 0){
        if (((p3.x - p4.x)*(p1.y - p3.y) + (p3.y - p4.y)*(p3.x - p1.x))*
            (((p3.x - p4.x)*(p2.y - p3.y)) + (p3.y - p4.y)*(p3.x - p2.x)) <= 0)
            return true;
    }
    return false;

}

int Line::is_right(){
    return (point1.x >= point2.x) * 2 - 1;
}

float Line::getangle()
{
	return angle;
}

ci::Vec3f Line::getCenterpos()
{
	return centerpos;
}

ci::Vec3f Line::getRotate()
{
	return rotate;
}

ci::Vec3f Line::getScale()
{
	return scale;
}

Vec2f Line::RightPoint(bool i){
    if (i){
        if(point1.x >= point2.x) {
            return point2;
        }
        return point1;
    }
    
    if (point1.x >= point2.x){
       
        return point1;
    }
    return point2;
}
