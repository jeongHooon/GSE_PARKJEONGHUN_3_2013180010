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
	void getX(float q) { x = q; }
	void getY(float q) { y = q; }
	void getZ(float q) { z = q; }
	void getSize(float q) { size = q; }
	void getR(float q) { r = q; }
	void getG(float q) { g = q; }
	void getB(float q) { b = q; }
	void getA(float q) { a = q; }
	float setX() { return x; }
	float setY() { return y; }
	float setZ() { return z; }
	float setSize() { return size; }
	float setR() { return r; }
	float setG() { return g; }
	float setB() { return b; }
	float setA() { return a; }
	~Object();
};

