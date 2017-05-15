#include "VerticalLine.h"
using namespace ci;
using namespace ci::app;
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Top/Top.h"
VerticalLine::VerticalLine()
{
}

VerticalLine::VerticalLine(const ci::Vec2f & start_Position, const ci::Vec2f & end_Position)
	: start_Position_(start_Position), end_Position_(end_Position)
{
	//	以下、法線ベクトルを求める計算です。
	//	計算処理が重いので、予め計算しておきます。

	//	終点から始点のベクトルを求めます
	double abx = end_Position_.x - start_Position_.x;
	double aby = end_Position_.y - start_Position_.y;

	//	上で求めたベクトルを正規化（大きさを1にすること）
	double ab_length = sqrt((abx * abx) + (aby * aby));

	if (ab_length > 0) ab_length = 1 / ab_length;
	abx *= ab_length;
	aby *= ab_length;

	//	終点と始点を結んだ線の法線ベクトルを求めます
	normal_vector_ = Vec2f(-aby, abx);

	Vec2f center2D = (start_Position + end_Position) / 2.f;
	centerpos = Vec3f(center2D.x, center2D.y, 0);
	float xsize = std::sqrtf((end_Position.x - start_Position.x)*(end_Position.x - start_Position.x) 
		+ (end_Position.y - start_Position.y)*(end_Position.y - start_Position.y));
	scale = Vec3f(xsize, 0, WorldScale * 2);
	angle = std::atan2(end_Position.y - start_Position.y, end_Position_.x - start_Position.x);
	rotate = Vec3f(0, 0, angle*(180.f / M_PI));
}

void VerticalLine::draw()
{
	DrawM.drawTextureCube(centerpos, scale, rotate, TextureM.getTexture("red3.png"), ColorA(1, 1, 1, 1));
}

bool VerticalLine::is_Hit_Position(ci::Vec3f * position, ci::Vec3f * speed, const double size)
{
	const Vec2f ball_Line_Segment = Vec2f(-normal_vector_.x * (size), -normal_vector_.y * (size));

	const double t = -(normal_vector_.x * position->x + normal_vector_.y * position->y - (start_Position_.x * normal_vector_.x + start_Position_.y * normal_vector_.y))
		/ (normal_vector_.x * ball_Line_Segment.x + normal_vector_.y * ball_Line_Segment.y);
	// 交点
	Vec2f intersection_ = Vec2f(position->x + t * ball_Line_Segment.x, position->y + t * ball_Line_Segment.y);

	// 線と交差している（この時点では無限線）
	if (0.0 < t && t <= 1.0)
	{
		// 交点が線分の間にあるか調べる
		const Vec2f position_a = intersection_ - start_Position_;
		const Vec2f position_b = intersection_ - end_Position_;
		if ((position_a.x * position_b.x) + (position_a.y * position_b.y) <= 0)
		{
			//線分に埋まった分引き戻す
			position->x = intersection_.x + normal_vector_.x * (size)*1.1;
			position->y = intersection_.y + normal_vector_.y * (size);
			return true;
			//ここでセッターを呼ぶ
		}
		
	}

	// 始点と円の当たり判定
	{
		double sx = position->x - start_Position_.x;
		double sy = position->y - start_Position_.y;
		if (sx * sx + sy * sy < (size)* (size))
		{
			// 正規化
			double length = sqrt((sx * sx) + (sy * sy));
			if (length > 0)    length = 1 / length;
			sx = sx * length;
			sy = sy * length;

			// 位置補正
			position->x = start_Position_.x + sx * (size)*1.1;//ここでセッターを呼ぶ
			position->y = start_Position_.y + sy * (size);
			return true;
		}
	}

	// 終点と円の当たり判定
	{
		double sx = position->x - end_Position_.x;
		double sy = position->y - end_Position_.y;
		if (sx * sx + sy * sy < (size)* (size))
		{
			// 正規化
			double length = sqrt((sx * sx) + (sy * sy));
			if (length > 0)    length = 1 / length;
			sx = sx * length;
			sy = sy * length;
			// 位置補正
			position->x = end_Position_.x + sx * (size)*1.1;//ここでセッターを呼ぶ
			position->y = end_Position_.y + sy * (size);
			return true;
		}
	}
	return false;
}
