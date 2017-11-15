#pragma once

#define OBJECT_BUILDING 10
#define OBJECT_CHARACTER 11
#define OBJECT_BULLET 12
#define OBJECT_ARROW 13

class Renderer;

enum Team {
	Team_1 = 10,Team_2
};

struct POS {
public :
	float x, y, z;
	POS() {}
	POS(float x, float y, float z) : x(x),y(y),z(z) {}
	POS operator *(float a) {return POS(x*a,y*a,z*a); }
	POS& operator +=(POS temp) { x += (float)temp.x; y += (float)temp.y; z += (float)temp.z; return POS(x, y, z); }
	POS operator =(POS temp) { x = temp.x; y = temp.y; z = temp.z; return POS(x, y, z); }
};

struct COLORS {
public:
	float r, g, b, a;
	COLORS() { r = 1; g = 0; b = 0; a = 1; }
	COLORS(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
};

class Object
{
private:
	POS			pos;			// 생성위치
	POS			direction;		// 이동방향
	COLORS		color;			// 색상
	float		size;			// 사이즈 
	int			state;			// 상태 0 : 빌딩 1 
	
	float		speed;			// 이동속도
	float		weight;			// 무게
	
	float		life;			// 생명력
	float		lifeTime;		// 생명유지시간

	float		attackDelay = 0;// 공격딜레이
	int			id;

	Team		team;			// 팀종류

	Renderer*	renderer;		// 렌더러 포인터
public:
	Object();
	Object(float xpos, float ypos, float zpos, float size) : pos(xpos,ypos,zpos),size(size) {}
	Object(Renderer* gRenderer, POS position, COLORS colors, float size);
	Object(Renderer * gRenderer, POS position, POS direction, COLORS colors, float size);
	~Object();

	void	SetPos(float x, float y, float z);
	void	SetPos(POS position);
	void	SetSize(float size);
	void	SetColor(float r, float g, float b, float a);
	void	SetColor(COLORS color);
	void	SetState(int state);
	void	SetRender(Renderer* pRenderer);
	void	SetDirection(POS direction);
	void	SetSpeed(float inputSpeed);
	void	SetWeight(float inputWeight);
	void	SetLife(float life);
	void	SetLifeTime(float time);
	void	SetAttackDelay(float time);
	void	AddSpeed(float addSpeed);
	void	SetLSSD(float life, float speed, int state, POS direction);
	void	SetID(int num) { id = num; }
	void	SetTeam(Team teamType) { team = teamType; }

	COLORS	NormalizationColor(COLORS color); // 0~255의 값을 0~1로 정규화
	
	int		GetState()			{ return state; }
	int		GetID()				{ return id; }
	Team	GetTeam()			{ return team; }
	float	GetSize()			{ return size; }
	float	GetSpeed()			{ return speed; }
	float   GetWeight()			{ return weight; }
	float   GetLife()			{ return life; }
	float	GetLifeTime()		{ return lifeTime; }
	float	GetAttackDelay()	{ return attackDelay; }
	POS		GetPos()			{ return pos; }
	COLORS	GetColor()			{ return color; }
	POS		GetDirection()		{ return direction; }

	void	DrawObject(int texturesNum);
	void	MoveUpdate(float time);
	void	Update(float time);
};

