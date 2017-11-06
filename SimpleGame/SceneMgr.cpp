#include "stdafx.h"
#include "SceneMgr.h"

//#define OBJECT_BUILDING
//#define OBJECT_CHARACTER
//#define OBJECT_BULLET
//#define OBJECT_ARROW

using namespace std;

SceneMgr::SceneMgr()
{
	obj = NULL;
	obj_BUILDING = NULL;
	obj_BULLET = NULL;
	obj_ARROW = NULL;
	g_Renderer = NULL;
	bulletCount = 0;
	emptyBullet = 0;
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::ObjectCreate(int Object_Type)
{

	if (Object_Type == OBJECT_CHARACTER)
	{
		obj = new Object[MAX_OBJECTS_COUNT]();
		/*for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			obj[i] = NULL;
		}*/
	}
	else if (Object_Type == OBJECT_BUILDING)
	{
		obj_BUILDING = new Object[MAX_BUILDING_COUNT]();
		for (int i = 0; i < MAX_BUILDING_COUNT; ++i) //건물 초기화
		{
			Data temp1 = { 0.0f,0.0f,0.0f,MAX_BUILDING_SIZE };
			obj_BUILDING[i].setPosition(temp1);
		}
	}
	else if (Object_Type == OBJECT_BULLET)
	{
		obj_BULLET = new Object[MAX_BULLET_COUNT]();
		for (int i = 0; i < MAX_BULLET_COUNT; ++i)	//총알 초기화
		{
			float checkX = 1;
			float checkY = 1;

			if (rand() % 2 == 1)
			{
				checkX *= -1;
			}if (rand() % 2 == 1)
			{
				checkY *= -1;
			}
			Data temp3 = { checkX,checkY,0.0f,0.0f };
			obj_BULLET[i].setDirection(temp3);

			/*Data temp2 = { 0.0f,0.0f,0.0f,0.0f };
			obj_BULLET[i].setPosition(temp2);*/
			Data RGB = { 0.0f,0.0f,255.0f,0.0f };
			obj_BULLET[i].setRGB(RGB);
			obj_BULLET[i].fixedObjLife(10.0f);
		}
	}
	else
	{
		//obj_ARROW = new Object[NUM]();
	}
	//for (int i = 0; i < NUM; ++i)
	//{
	//	Data temp1 = { (float)((rand() % 500) - 200),(float)(200 - (rand() % 500)),0,SIZE };
	//	Data temp2 = { 255,255, 255,1.0 }; //흰색통일 
	//	float checkX = 1;
	//	float checkY = 1;

	//	if (rand() % 2 == 1)
	//	{
	//		checkX *= -1;
	//	}if (rand() % 2 == 1)
	//	{
	//		checkY *= -1;
	//	}
	//	Data temp3 = { checkX, checkY ,0.0f,0.0f };
	//	obj[i].setPosition(temp1);
	//	obj[i].setRGB(temp2);
	//	obj[i].setDirection(temp3);
	//}
}

void SceneMgr::ObjectAllDelete(int Object_Type)
{
	if (Object_Type == OBJECT_CHARACTER)
	{
		delete[] obj;
	}
	else if (Object_Type == OBJECT_BUILDING)
	{
		delete[] obj_BUILDING;
	}
	else if (Object_Type == OBJECT_BULLET)
	{
		delete[] obj_BULLET;
	}
	else
	{
		delete[] obj_ARROW;
	}
}

Object* SceneMgr::getObject(int i, int Object_Type)
{
	if (Object_Type == OBJECT_CHARACTER)
	{
		return &obj[i];
	}
	else if (Object_Type == OBJECT_BUILDING)
	{
		return &obj_BUILDING[i];
	}
	else if (Object_Type == OBJECT_BULLET)
	{
		return &obj_BULLET[i];
	}
	else
	{
		return &obj_ARROW[i];
	}
}

void SceneMgr::setObject(Object pos)
{
}

void SceneMgr::RendererCreate() {
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
}

void SceneMgr::RendererDelete() {
	delete g_Renderer;
}

Renderer* SceneMgr::getRenderer() {
	return g_Renderer;
}

void SceneMgr::setRenderer(Renderer p) {
}

void SceneMgr::ObjectCollition(int& MAX, float updateTime)
{
	//Data Red = { 255,0, 0,1.0 }; //빨강통일 
	//Data White = { 255,255, 255,1.0 };
	//Data Blue = { 0.0,0.0,255,1.0 };
	//for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	//{
	//	obj[i].setRGB(White);
	//	if (obj[i].getPosition().s > 0.0f)
	//	{
	//		int Size = MAX_OBJECTS_SIZE / 2;

	//		Data Rect1 = obj[i].getPosition();
	//		for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
	//		{
	//			if (i == j)
	//			{
	//				continue;
	//			}
	//			Data Rect2 = obj[j].getPosition();
	//			if ((Rect1.x - Size) < (Rect2.x + Size) && (Rect1.x + Size) > (Rect2.x - Size) && (Rect1.y - Size) < (Rect2.y + Size) && (Rect1.y + Size) > (Rect2.y - Size))
	//			{
	//				obj[i].setRGB(Red);
	//				obj[i].setObjLife((-1.0));
	//			}
	//		}
	//		if (obj[i].getObjLife() <= 0.0 || obj[i].getObjLifeTime() < 0.0f)
	//		{
	//			Data temp = { 0.0,0.0,0.0,-1.0 };
	//			obj[i].setPosition(temp); //사이즈가 -1 이니 False 상태라 봄
	//			MAX--;
	//			//delete &obj[i];
	//			//obj[i] = nullptr;
	//		}
	//		else
	//		{
	//			obj[i].Update((float)updateTime);

	//		}
	//	}
	//}
	//-------------------OBJECT_CHARACTER 간의 충돌 잠시 주석처리
	Data Red = { 255,0, 0,1.0 }; //빨강통일 
	Data White = { 255,255, 255,1.0 };
	Data Blue = { 0.0,0.0,255,1.0 };

	int obj_Character_Size = MAX_OBJECTS_SIZE / 2;
	int obj_Bulidong_Size = MAX_BUILDING_SIZE / 2;
	int obj_Bullet_Size = MAX_BULLET_SIZE / 2;


	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (obj[i].getPosition().s < 0.0f)	//이미 0.0f는 죽은 처리기 때문에 충돌 체크를 하지 않는다.
		{
			continue;
		}
		obj[i].setRGB(White);

		Data Rect1 = obj[i].getPosition();
		for (int j = 0; j < MAX_BUILDING_COUNT; ++j)
		{
			Data Rect2 = obj_BUILDING[j].getPosition();
			//cout << "빌딩의 체력 : " << obj_BUILDING[j].getObjLife() << endl;
			/*if (i == j)
			{
				continue;
			}*/

			if (obj_BUILDING[j].getObjLife() < 0.0f)
			{
				continue;
			}
			if ((Rect1.x - obj_Character_Size) < (Rect2.x + obj_Bulidong_Size) && (Rect1.x + obj_Character_Size) > (Rect2.x - obj_Bulidong_Size) && (Rect1.y - obj_Character_Size) < (Rect2.y + obj_Bulidong_Size) && (Rect1.y + obj_Character_Size) > (Rect2.y - obj_Bulidong_Size))
			{
				cout << "빌딩의 체력 : " << obj_BUILDING[j].getObjLife() << endl;
				obj[i].setRGB(Red);
				obj_BUILDING[j].setObjLife((-100.00f));
				obj[i].setObjLife(-5.0f);
			}
			if (obj[i].getObjLife() <= 0.0f)
			{
				Data temp2 = { 0.0,0.0,0.0,-1.0 };
				obj[i].setPosition(temp2);			//사이즈가 -1 이니 False 상태라 봄
				//obj[i].fixedObjLife(-1.0f);			//-1로 라이프를 설정하면 충돌체크, 재발사 등 동작 하지 않음.
				MAX--;
			}
			if (obj_BUILDING[j].getObjLife() <= 0.0)//|| obj_BUILDING[i].getObjLifeTime() < 0.0f
			{
				Data temp = { 0.0,0.0,0.0,-1.0 };
				obj_BUILDING[j].setPosition(temp); //사이즈가 -1 이니 False 상태라 봄
												   //delete &obj_BUILDING[i];
												   //obj[i] = nullptr;
				for (int r = 0; r < MAX_BULLET_COUNT; ++r)
				{
					Data temp2 = { 0.0,0.0,0.0,-1.0 };
					obj_BULLET[r].setPosition(temp2);			//사이즈가 -1 이니 False 상태라 봄
					obj_BULLET[r].fixedObjLife(-1.0f);			//-1로 라이프를 설정하면 충돌체크, 재발사 등 동작 하지 않음.
				}
			}
		}
		for (int q = 0; q < MAX_BULLET_COUNT; ++q)
		{
			Data Rect3 = obj_BULLET[q].getPosition();
			if (obj_BULLET[q].getObjLife() < 0.0f)
			{
				continue;
			}
			if ((Rect1.x - obj_Character_Size) < (Rect3.x + obj_Bullet_Size) && (Rect1.x + obj_Character_Size) > (Rect3.x - obj_Bullet_Size) && (Rect1.y - obj_Character_Size) < (Rect3.y + obj_Bullet_Size) && (Rect1.y + obj_Character_Size) > (Rect3.y - obj_Bullet_Size))
			{
				//cout << "총알의 체력 : " << obj_BULLET[q].getObjLife() << endl;
				obj[i].setRGB(Red);
				obj_BULLET[q].setObjLife((-10.00f));
			}
			if (obj_BULLET[q].getObjLife() < 0.0)//|| obj_BUILDING[i].getObjLifeTime() < 0.0f
			{
				Data temp = { 0.0,0.0,0.0,MAX_BULLET_SIZE };
				obj_BULLET[q].setPosition(temp);			//사이즈가 -1 이니 False 상태라 봄
				obj_BULLET[q].fixedObjLife(10.0f);			//delete &obj_BUILDING[i];
															//obj[i] = nullptr;
				float checkX = 1;
				float checkY = 1;

				if (rand() % 2 == 1)
				{
					checkX *= -1;
				}if (rand() % 2 == 1)
				{
					checkY *= -1;
				}
				Data temp3 = { checkX,checkY,0.0f,0.0f };
				obj_BULLET[q].setDirection(temp3);

			}
			else
			{
				obj_BULLET[q].Update((float)updateTime, OBJECT_BULLET);
			}
		}
		obj[i].Update((float)updateTime, OBJECT_CHARACTER);
	}
}
void SceneMgr::ObjectDraw(int Object_Type, int& timeSet) {
	if (Object_Type == OBJECT_CHARACTER)
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			Data pos = obj[i].getPosition();
			Data rgb = obj[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);
		}
	}
	else if (Object_Type == OBJECT_BUILDING)
	{
		for (int i = 0; i < MAX_BUILDING_COUNT; ++i)
		{
			//Data BUILDINGPOS = { 0.0f,0.0f,0.0f,MAX_BUILDING_SIZE };
			//obj_BUILDING[i].setPosition(BUILDINGPOS);  //초기값의 사이즈가 0이기때문에 생성되지 않음. 그래서 건물 크기만 큼으로 생성
			//obj_BUILDING[i].setObjLife((1.0f));
			//이곳에서 위와같은 셋 작업을 하게되면 무한 루프식으로 계속 값을 더해주거나, 그자리에 위치하게 만드니 하지말 것.

			Data pos = obj_BUILDING[i].getPosition();
			Data rgb = obj_BUILDING[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);

			
		}
	}
	else if (Object_Type == OBJECT_BULLET)
	{
		for (int i = 0; i < MAX_BULLET_COUNT; ++i)
		{
			/*if (obj_BULLET[i].getPosition().s < MAX_BULLET_SIZE)
			{
				bulletCount = i;
			}*/
			Data pos = obj_BULLET[i].getPosition();
			Data rgb = obj_BULLET[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);

			if (timeSet > 300)
			{
				/*Data temp2 = { 0.0f,0.0f,0.0f,MAX_BULLET_SIZE };
				obj_BULLET[bulletCount].setPosition(temp2);
				Data pos = obj_BUILDING[bulletCount].getPosition();
				Data rgb = obj_BUILDING[bulletCount].getRGB();
				if (bulletCount > MAX_BULLET_COUNT)
				{

				}*/
				//cout << "bulletCount : " << bulletCount << endl;
				float checkX = 1;
				float checkY = 1;

				if (rand() % 2 == 1)
				{
				checkX *= -1;
				}if (rand() % 2 == 1)
				{
				checkY *= -1;
				}

				Data temp3 = { checkX,checkY,0.0f,0.0f };
				obj_BULLET[bulletCount].setDirection(temp3);

				Data temp2 = { 0.0f,0.0f,0.0f,MAX_BULLET_SIZE };
				obj_BULLET[bulletCount].setPosition(temp2);
				bulletCount++;
				if (bulletCount > MAX_BULLET_COUNT)
				{
					bulletCount = 0;
				}
				timeSet = 0;
			}
		}
	}
	else
	{
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
		{
			Data pos = obj_ARROW[i].getPosition();
			Data rgb = obj_ARROW[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);
		}
	}
}