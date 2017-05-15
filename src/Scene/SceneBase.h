#pragma once

class SceneBase {
public:
	virtual void setup() {};
	virtual void update() {};
	virtual void draw() {};
	virtual void draw2D() {};
	virtual void shift() {};
private:
};