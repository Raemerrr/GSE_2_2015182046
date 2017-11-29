#include "stdafx.h"
#include "Object.h"

using namespace std;

Object::Object()
{
	//srand((unsigned)time(NULL));  //한번만 설정할 것.
	Position.x = 999.0f;		//겹치지 않는 위치에서 시작하기 위함.(맵상에 존재 않하는 것 처럼)
	Position.y = 999.0f;		//겹치지 않는 위치에서 시작하기 위함.
	Position.z = 999.0f;		//겹치지 않는 위치에서 시작하기 위함.
	Position.s = 1.0f;
	Rgb.x = 0.0;
	Rgb.y = 0.0;
	Rgb.z = 0.0;
	Rgb.s = 0.0;
	vX = 0.0; //X의 방향
	vY = 0.0; //Y의 방향
	teamNum = 0;

	Direction.x = 0.f;
	Direction.y = 0.f;
	Direction.z = 0.f;//삭제 유무
	Direction.s = 0.f;//삭제 유무
	objLife = 0.f; //라이프
	lifeTime = 1000.f; //라이프
}

Object::~Object()
{
}

Data Object::getPosition()
{
	return Position;
}

void Object::setPosition(Data pos)
{
	Position.x = pos.x;
	Position.y = pos.y;
	Position.z = pos.z;
	Position.s = pos.s;
}

Data Object::getRGB()
{
	return Rgb;
}

void Object::setRGB(Data rgb)
{
	Rgb.x = rgb.x;
	Rgb.y = rgb.y;
	Rgb.z = rgb.z;
	Rgb.s = rgb.s;
}

Data Object::getDirection()
{
	Direction.x = vX;
	Direction.y = vY;
	return Direction;
}

void Object::setDirection(Data p)
{
	vX = p.x;
	vY = p.y;
}

float Object::getObjLife()
{
	return objLife;
}

void Object::setObjLife(float p)
{
	objLife += p;
}

void Object::fixedObjLife(float p)
{
	objLife = p;
}

float Object::getObjLifeTime()
{
	return lifeTime;
}

void Object::setObjLifeTime(float p)
{
	lifeTime = p;
}

int Object::getTeamNum() 
{
	return teamNum;
}

void Object::setTeamNum(int a) 
{
	teamNum = a;
}

void Object::Update(float elapsedTime, int OBJECT_TYPE)
{
	int screenX = MAX_SCREEN_WIDTH / 2;
	int screenY = MAX_SCEEN_HEIGHT / 2;

	float objSpeed = 0.0f;
	if (OBJECT_TYPE == OBJECT_CHARACTER)
	{
		objSpeed = 300.f;
	}
	else if (OBJECT_TYPE == OBJECT_BULLET)
	{
		objSpeed = 600.f;
	}
	else if (OBJECT_TYPE == OBJECT_ARROW)
	{
		objSpeed = 100.f;
	}

	elapsedTime = elapsedTime / 1000.f;
	//cout << bulletSpawnTime << endl; 

	//캐릭터 라이프타임 잠시 주석처리
	/*if (!(lifeTime <= 0.0f) && OBJECT_TYPE == OBJECT_CHARACTER)
	{
		lifeTime -= 1.0;
	}*/

	if (OBJECT_TYPE == OBJECT_CHARACTER)
	{
		Position.x = Position.x + vX * elapsedTime * objSpeed;  //이동구현
		Position.y = Position.y + vY * elapsedTime * objSpeed;	//이동구현
		if (Position.x > screenX) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < (-screenX)) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > screenY) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < (-screenY)) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}/*if (Position.x > screenX || Position.x < (-screenX) || Position.y > screenY || Position.y < (-screenY))
		{
			objLife = (-1.f);
		}*/
	}
	else if (OBJECT_TYPE == OBJECT_BULLET) {
		Position.x = Position.x + vX * elapsedTime * objSpeed;	//이동구현
		Position.y = Position.y + vY * elapsedTime * objSpeed;	//이동구현
		//cout << "BULLET x : " << Position.x <<  endl;
		//cout << Position.x << endl;
		//Position.s = MAX_BULLET_SIZE;
		if (Position.x > screenX || Position.x < (-screenX) || Position.y > screenY || Position.y < (-screenY))
		{
			/*vX = 0;
			vY = 0;
			Position.s = -1.0f;
			Position.x = 999.0f;
			Position.y = 999.0f;*/
			objLife = (-1.f);

			//cout << "장소 이탈" << endl;
		}

		//장소 이탈 전.
		/*if (Position.x > screenX) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < (-screenX)) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > screenY) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < (-screenY)) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}*/
	}
	else if (OBJECT_TYPE == OBJECT_ARROW) {
		Position.x = Position.x + vX * elapsedTime * objSpeed;	//이동구현
		Position.y = Position.y + vY * elapsedTime * objSpeed;	//이동구현		
		if (Position.x > screenX || Position.x < (-screenX) || Position.y > screenY || Position.y < (-screenY))
		{
			/*vX = 0;
			vY = 0;
			Position.s = -1.0f;
			Position.x = 999.0f;
			Position.y = 999.0f;*/
			objLife = (-1.f);

			//cout << "장소 이탈" << endl;
		}
																
		//장소 이탈 전.													
		/*if (Position.x > screenX) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < (-screenX)) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > screenY) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < (-screenY)) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}*/
	}
}
