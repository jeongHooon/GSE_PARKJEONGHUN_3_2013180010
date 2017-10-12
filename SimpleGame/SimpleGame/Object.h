#pragma once
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
public:
	Object();
	Object(float x, float y, float z, float size, float r, float g, float b, float a) :x(x), y(y), z(z), size(size), r(r), g(g), b(b), a(a){}
	void setX(float q) { x = q; }
	void setY(float q) { y = q; }
	void setZ(float q) { z = q; }
	void setSize(float q) { size = q; }
	void setR(float q) { r = q; }
	void setG(float q) { g = q; }
	void setB(float q) { b = q; }
	void setA(float q) { a = q; }
	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getSize() { return size; }
	float getR() { return r; }
	float getG() { return g; }
	float getB() { return b; }
	float getA() { return a; }
	~Object();
};

