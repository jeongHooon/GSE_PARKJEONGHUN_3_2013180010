#pragma once
#include <iostream>
#define OBJECT_BUILDING 01
#define OBJECT_CHARACTER 02
#define OBJECT_BULLET 03
#define OBJECT_ARROW 04
#define TEAM_1 10
#define TEAM_2 20
#define MAX_OBJECTS_COUNT 1000
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
	float dirX;
	float dirY;
	float velocity;
	float life;
	float lifetime;
	int type;
	int teamtype;
public:
	float time = 0;
public:
	Object();
	Object(float x, float y, float z, float size, float r, float g, float b, float a, float dirX, float dirY, float velocity, float life, float lifetime,int type, int teamtype) :x(x), y(y), z(z), size(size), r(r), g(g), b(b), a(a), dirX(dirX), dirY(dirY), velocity(velocity), life(life), lifetime(lifetime),type(type), teamtype(teamtype) {}
	void setAll(float x, float y, float z, float size, float r, float g, float b, float a, float dirX, float dirY, float velocity, float life, float lifetime, int type, int teamtype);
	void setX(float q) { x = q; }
	void setY(float q) { y = q; }
	void setZ(float q) { z = q; }
	void setSize(float q) { size = q; }
	void setR(float q) { r = q; }
	void setG(float q) { g = q; }
	void setB(float q) { b = q; }
	void setA(float q) { a = q; }
	void setDirX(float q) { dirX = q; }
	void setDirY(float q) { dirY = q; }
	void setVelocity(float q) { velocity = q; }
	void setLife(float q) { life = q; }
	void setLifeTime(float q) { lifetime = q; }
	void setType(int q) { type = q; }
	void setTeamtype(int q) { teamtype = q; }

	float getX() { return x; }
	float getY() { return y; }
	float getZ() { return z; }
	float getSize() { return size; }
	float getR() { return r; }
	float getG() { return g; }
	float getB() { return b; }
	float getA() { return a; }
	float getDirX() { return dirX; }
	float getDirY() { return dirY; }
	float getVelocity() { return velocity; }
	float getLife() { return life; }
	float getLifeTime() { return lifetime; }
	int getType() { return type; }
	int getTeamtype() { return teamtype; }

	void Update(float eTime);
	~Object();
};

