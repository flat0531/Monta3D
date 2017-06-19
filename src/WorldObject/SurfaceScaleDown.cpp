#include "SurfaceScaleDown.h"
#include"cinder/ImageIo.h"

using namespace ci;
using namespace ci::app;
SurfaceScaleDown::SurfaceScaleDown()
{

}

void SurfaceScaleDown::WirteImage(const ci::Surface & surface, const int downrate, const std::string pathname)
{
	float rate = (1.0f / (float(downrate)));

	Vec2i texturesize = surface.getSize()*rate;
	Surface buff;
	buff = Surface(texturesize.x, texturesize.y, true);

	for (int y = 0; y < texturesize.y; y++)
	{
		for (int x = 0; x < texturesize.x; x++)
		{
			buff.setPixel(Vec2i(x, y), ColorA(0, 0, 0, 0));
		}
	}
	int y_size = texturesize.y;
	int x_size = texturesize.x;

	for (int y = 0;y < y_size;y++) {
		for (int x = 0;x < x_size;x++) {

			ColorA color = ColorA(0, 0, 0, 0);

			for (int in_y = 0;in_y < downrate;in_y++) {
				for (int in_x = 0;in_x < downrate;in_x++) {

					color.r += (rate*rate)*(float(surface.getPixel(Vec2i((x*downrate) + in_x, (y*downrate) + in_y)).r)) / 255.f;
					color.g += (rate*rate)*(float(surface.getPixel(Vec2i((x*downrate) + in_x, (y*downrate) + in_y)).g)) / 255.f;
					color.b += (rate*rate)*(float(surface.getPixel(Vec2i((x*downrate) + in_x, (y*downrate) + in_y)).b)) / 255.f;
					color.a += (rate*rate)*(float(surface.getPixel(Vec2i((x*downrate) + in_x, (y*downrate) + in_y)).a)) / 255.f;
				}
			}
			buff.setPixel(Vec2i(x, y), color);
		}
	}

	auto datasourceref =  DataTargetPath::createRef(getAppPath().string() + pathname);

	ci::writeImage(datasourceref, buff);
}
