
#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

enum class Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NON
};
class Line
{
public:
    Line();

    Line(ci::Vec2f _p1, ci::Vec2f _p2,bool _isvertical = false );
    
    void Draw();
    bool IsIntersect(ci::Vec2f _p1, ci::Vec2f _p2);
    void SetPoint(ci::Vec2f _p1, ci::Vec2f _p2);
    ci::Vec2f Intersection_Point(ci::Vec2f _p1, ci::Vec2f _p2);
    ci::Vec2f Collision(ci::Vec2f _pos, ci::Vec2f _size, ci::Vec2f _vec);
    Direction HitDirection(ci::Vec2f _pos, ci::Vec2f _size, ci::Vec2f _vec);
	float getangle();
	ci::Vec3f getCenterpos();
	ci::Vec3f getRotate();
	ci::Vec3f getScale();
	bool getvertical() {
		return isvertical;
	}
private:
    ci::Vec2f point1;
    ci::Vec2f point2;
    ci::Vec2f vec;
	ci::Vec3f centerpos;
	ci::Vec3f rotate;
	ci::Vec3f scale;
	bool isvertical;
	float angle;
	void drawLineV(ci::Vec2f _p1, ci::Vec2f _p2, ci::ColorA color = ci::ColorA(1,1,1,1));
    bool IsVertical();
    int status();
    ci::Vec2f intersection_point(ci::Vec2f p1, ci::Vec2f p2, ci::Vec2f p3, ci::Vec2f p4);
    bool linetoline(ci::Vec2f p1, ci::Vec2f p2, ci::Vec2f p3, ci::Vec2f p4);
    int is_right();
	
    ci::Vec2f CollisionUp(ci::Vec2f _p1, ci::Vec2f _p2, ci::Vec2f _pos, ci::Vec2f _vec);
    ci::Vec2f CollisionDown(ci::Vec2f _p1, ci::Vec2f _p2, ci::Vec2f _pos, ci::Vec2f _vec);
    ci::Vec2f CollisionLeft(ci::Vec2f _p1, ci::Vec2f _p2, ci::Vec2f _pos, ci::Vec2f _vec);
    ci::Vec2f CollisionRight(ci::Vec2f _p1, ci::Vec2f _p2, ci::Vec2f _pos, ci::Vec2f _vec);

    ci::Vec2f RightPoint(bool i);
};



