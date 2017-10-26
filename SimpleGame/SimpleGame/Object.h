#pragma once
#include <iostream>
using namespace std;
class Object
{
	float x;
	float y;
	float z;
	float size;
	float r;
	float g;
	float b;
	float a;
	float velocityX;
	float velocityY;
	float life;
public:
	const float time = 0.1;
public:
	Object();
	Object(float x, float y, float z, float size, float r, float g, float b, float a, float velocityX, float velocityY) :x(x), y(y), z(z), size(size), r(r), g(g), b(b), a(a), velocityX(velocityX), velocityY(velocityY) {}
	void setAll(float x, float y, float z, float size, float r, float g, float b, float a, float velocityX, float velocityY);
	void setX(float q) { x = q; }
	void setY(float q) { y = q; }
	void setZ(float q) { z = q; }
	void setSize(float q) { size = q; }
	void setR(float q) { r = q; }
	void setG(float q) { g = q; }
	void setB(float q) { b = q; }
	void setA(float q) { a = q; }
	void setVelocityX(float q) { velocityX = q; }
	void setVelocityY(float q) { velocityY = q; }

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getSize() { return size; }
	float getR() { return r; }
	float getG() { return g; }
	float getB() { return b; }
	float getA() { return a; }
	float getVelocityX(){ return velocityX; }
	float getVelocityY(){ return velocityY; }

	void Update(float eTime);
	~Object();
};

