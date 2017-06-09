#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include <vector>
#include"Pallet.h"
class PalletManager {
public:
	PalletManager();
	void draw();
	void update();
	void setup();
	ci::ColorA getSelectcolor();
private:
	Pallet pallet;
	int effectcount = 0;
	int effectnexttime = 3;
	bool effectend();
	bool effectnext();
	void effectCountup();
};