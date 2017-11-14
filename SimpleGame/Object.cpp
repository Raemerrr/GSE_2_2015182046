#include "stdafx.h"
#include "Object.h"

using namespace std;

Object::Object()
{
	//srand((unsigned)time(NULL));  //한번만 설정할 것.
	Position.x = 999.0;		//겹치지 않는 위치에서 시작하기 위함.(맵상에 존재 않하는 것 처럼)
	Position.y = 999.0;		//겹치지 않는 위치에서 시작하기 위함.
	Position.z = 999.0;		//겹치지 않는 위치에서 시작하기 위함.
	Position.s = 0.0;
	Rgb.x = 0.0;
	Rgb.y = 0.0;
	Rgb.z = 0.0;
	Rgb.s = 1.0;
	vX = 0.0; //X의 방향
	vY = 0.0; //Y의 방향

	Direction.x = 0.0;
	Direction.y = 0.0;
	Direction.z = 0.0;//삭제 유무
	Direction.s = 0.0;//삭제 유무
	objLife = 1000.0; //라이프
	lifeTime = 1000.0; //라이프
}
//Object::Object(const Object& other) {
//	Position.x = other.Position.x;		//겹치지 않는 위치에서 시작하기 위함.(맵상에 존재 않하는 것 처럼)
//	Position.y = 999.0;		//겹치지 않는 위치에서 시작하기 위함.
//	Position.z = 999.0;		//겹치지 않는 위치에서 시작하기 위함.
//	Position.s = 0.0;
//	Rgb.x = 0.0;
//	Rgb.y = 0.0;
//	Rgb.z = 0.0;
//	Rgb.s = 1.0;
//	vX = 0.0; //X의 방향
//	vY = 0.0; //Y의 방향
//
//	Direction.x = 0.0;
//	Direction.y = 0.0;
//	Direction.z = 0.0;//삭제 유무
//	Direction.s = 0.0;//삭제 유무
//	objLife = 1000.0; //라이프
//	lifeTime = 1000.0; //라이프
//}
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

void Object::Update(float elapsedTime, int OBJECT_TYPE)
{
	float objSpeed = 0.0f;
	if (OBJECT_TYPE == OBJECT_CHARACTER)
	{
		objSpeed = 100.0f;
	}
	else if (OBJECT_TYPE == OBJECT_BULLET)
	{
		objSpeed = 3.0f;
	}
	else if (OBJECT_TYPE == OBJECT_ARROW)
	{
		objSpeed = 5.0f;
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
		if (Position.x > 250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < -250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > 250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < -250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
	}
	else if (OBJECT_TYPE == OBJECT_BULLET) {
		Position.x = Position.x + vX * elapsedTime * objSpeed;	//이동구현
		Position.y = Position.y + vY * elapsedTime * objSpeed;	//이동구현
		//cout << Position.x << endl;
		//Position.s = MAX_BULLET_SIZE;
		//if (Position.x > 250 || Position.x < -250 || Position.y > 250 || Position.y < -250)
		//{
		//	/*float checkX = 1;
		//	float checkY = 1;

		//	if (rand() % 2 == 1)
		//	{
		//		checkX *= -1;
		//	}if (rand() % 2 == 1)
		//	{
		//		checkY *= -1;
		//	}
		//	vX = checkX;
		//	vY = checkY;*/
		//	Position.s = 0.0f;
		//	Position.x = 0.0f;
		//	Position.y = 0.0f;
		//	//cout << "장소 이탈" << endl;
		//}

		/*float checkX = 1;
		float checkY = 1;

		if (rand() % 2 == 1)
		{
			checkX *= -1;
		}if (rand() % 2 == 1)
		{
			checkY *= -1;
		}

		if (Position.x > 250) {
			vX = checkX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < -250) {
			vX = checkX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > 250) {
			vX = (float)(rand() % 2);
			vY = checkY;
		}
		if (Position.y < -250) {
			vX = (float)(rand() % 2);
			vY = checkY;
		}*/
		if (Position.x > 250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < -250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > 250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < -250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
	}
	else if (OBJECT_TYPE == OBJECT_ARROW) {
		Position.x = Position.x + vX * elapsedTime * objSpeed;	//이동구현
		Position.y = Position.y + vY * elapsedTime * objSpeed;	//이동구현		
		if (Position.x > 250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.x < -250) {
			vX = -vX;
			vY = (float)(rand() % 2);
		}
		if (Position.y > 250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
		if (Position.y < -250) {
			vY = -vY;
			vX = (float)(rand() % 2);
		}
	}
}
