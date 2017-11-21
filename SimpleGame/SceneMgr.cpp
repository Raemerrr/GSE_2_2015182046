#include "stdafx.h"
#include "SceneMgr.h"

using namespace std;

SceneMgr::SceneMgr()
{
	obj = NULL;
	obj_BUILDING = NULL;
	obj_BULLET = NULL;
	obj_ARROW = NULL;
	g_Renderer = NULL;
	bulletCount = 0;
	arrowCount = 0;
}

SceneMgr::~SceneMgr()
{
}

void SceneMgr::ObjectCreate(int Object_Type)
{
	//srand((unsigned)time(NULL));  //한번만 설정할 것.

	if (Object_Type == OBJECT_CHARACTER)
	{
		obj = new Object[MAX_OBJECTS_COUNT]();
		for (int i = 0; i < (MAX_OBJECTS_COUNT / 2); ++i)
		{
			//cout << " i : " << i << endl;
			//Data TEAM1CharPos = { (rand() % MAX_SCREEN_WIDTH),rand() % (MAX_SCEEN_HEIGHT / 2),0.0f,MAX_OBJECTS_SIZE };
			Data TEAM1CharColor = { 255.0f,0.0f,0.0f,255.0f };
			Data TEAM1CharPos = {-250 + (rand() % MAX_SCREEN_WIDTH),rand() % (MAX_SCEEN_HEIGHT / 2),0.0f,MAX_OBJECTS_SIZE };
			obj[i].setPosition(TEAM1CharPos);
			obj[i].setTeamNum(1);
			/*SceneManager->getObject(DrawObjCheck, OBJECT_CHARACTER)->setObjLifeTime(100000.0f);*/
			obj[i].fixedObjLife(1.0f);
			obj[i].setRGB(TEAM1CharColor);

			float checkX = 1;
			float checkY = 1;

			if (rand() % 2 == 1)
			{
				checkX *= -1;
			}if (rand() % 2 == 1)
			{
				checkY *= -1;
			}
			Data tempDirec = { checkX ,checkY,0.0f,0.0f };
			obj[i].setDirection(tempDirec);
		}
	}
	else if (Object_Type == OBJECT_BUILDING)
	{
		float team1_x = -150;
		float team1_y = 300;
		float team2_x = -150;
		float team2_y = -300;
		obj_BUILDING = new Object[MAX_BUILDING_COUNT]();
		for (int i = 0; i < (MAX_BUILDING_COUNT / 2); ++i) //건물 초기화
		{
			Data temp1 = { team1_x,team1_y,0.0f,MAX_BUILDING_SIZE };
			obj_BUILDING[i].setPosition(temp1);
			obj_BUILDING[i].setTeamNum(1);
			team1_x += 150;
		}
		for (int i = (MAX_BUILDING_COUNT / 2); i < MAX_BUILDING_COUNT; ++i) //건물 초기화
		{
			Data temp1 = { team2_x,team2_y,0.0f,MAX_BUILDING_SIZE };
			obj_BUILDING[i].setPosition(temp1);
			obj_BUILDING[i].setTeamNum(2);
			team2_x += 150;
		}
	}
	else if (Object_Type == OBJECT_BULLET)
	{
		obj_BULLET = new Object[MAX_BULLET_COUNT]();
		for (int i = 0; i < MAX_BULLET_COUNT; ++i)	//총알 초기화
		{
			Data temp = { 999.0,999.0,999.0,1 };
			obj_BULLET[i].setPosition(temp);
			/*Data RGB = { 150.0f,0.0f,255.0f,1.0f };
			obj_BULLET[i].setRGB(RGB);*/
			obj_BULLET[i].fixedObjLife(10.0f);
		}
	}
	else if (Object_Type == OBJECT_ARROW)
	{
		obj_ARROW = new Object[MAX_OBJECTS_COUNT](); // 캐릭터 수 만큼 할당
		for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)	//총알 초기화
		{
			/*Data RGB = { 0.0f,255.0f,255.0f,1.0f };
			obj_ARROW[i].setRGB(RGB);*/
			obj_ARROW[i].fixedObjLife(4.0f);
		}
	}
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
	else if (Object_Type == OBJECT_ARROW)
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
	else if (Object_Type == OBJECT_ARROW)
	{
		return &obj_ARROW[i];
	}
	else
	{
		return nullptr;
	}
}

void SceneMgr::setObject(Object pos)
{
}

void SceneMgr::RendererCreate() {
	g_Renderer = new Renderer(MAX_SCREEN_WIDTH, MAX_SCEEN_HEIGHT);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	team1BulidingImg = g_Renderer->CreatePngTexture("./Resource/1team_building.png");
	team2BulidingImg = g_Renderer->CreatePngTexture("./Resource/2team_building.png");
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

	//		Data charRect = obj[i].getPosition();
	//		for (int j = 0; j < MAX_OBJECTS_COUNT; ++j)
	//		{
	//			if (i == j)
	//			{
	//				continue;
	//			}
	//			Data buildRect = obj[j].getPosition();
	//			if ((charRect.x - Size) < (buildRect.x + Size) && (charRect.x + Size) > (buildRect.x - Size) && (charRect.y - Size) < (buildRect.y + Size) && (charRect.y + Size) > (buildRect.y - Size))
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
	Data TEAM2CharColor = { 0,0, 255,255 };

	int obj_Character_Size = MAX_OBJECTS_SIZE / 2;
	int obj_Building_Size = MAX_BUILDING_SIZE / 2;
	int obj_Bullet_Size = MAX_BULLET_SIZE / 2;
	int obj_Arrow_Size = MAX_ARROW_SIZE / 2;


	for (int i = 0; i < MAX_OBJECTS_COUNT; ++i)
	{
		if (obj[i].getPosition().s < 0.0f || obj[i].getObjLifeTime() < 0.0)	//이미 0.0f는 죽은 처리기 때문에 충돌 체크를 하지 않는다.
		{
			continue;
		}
		Data TEAM1CharColor = { 255.0f,0.0f,0.0f,255.0f };
		Data TEAM2CharColor = { 0.0f,0.0f, 255.0f,255.0f };
		if (i < (MAX_OBJECTS_COUNT / 2))
		{
			obj[i].setRGB(TEAM1CharColor);
		}
		else
		{
			obj[i].setRGB(TEAM2CharColor);
		}
		//obj[i].setRGB(TEAM2CharColor);

		Data charRect = obj[i].getPosition();
		Data arrowRect = obj_ARROW[i].getPosition();

		for (int j = 0; j < MAX_BUILDING_COUNT; ++j)
		{
			if (obj[i].getPosition().s < 0.0)
			{
				break;
			}
			if (obj_BUILDING[j].getPosition().s < 0.0f || obj_BUILDING[j].getObjLifeTime() < 0.0 || obj_BUILDING[j].getTeamNum() == obj[i].getTeamNum() || obj_ARROW[i].getTeamNum() == obj_BUILDING[j].getTeamNum())	//이미 0.0f는 죽은 처리기 때문에 충돌 체크를 하지 않는다.
			{
				continue;
			}
			Data buildRect = obj_BUILDING[j].getPosition();
			//cout << "빌딩의 체력 : " << obj_BUILDING[j].getObjLife() << endl;
			/*if (i == j)
			{
				continue;
			}*/
			if (((charRect.x - obj_Character_Size) < (buildRect.x + obj_Building_Size) && (charRect.x + obj_Character_Size) > (buildRect.x - obj_Building_Size) && (charRect.y - obj_Character_Size) < (buildRect.y + obj_Building_Size) && (charRect.y + obj_Character_Size) > (buildRect.y - obj_Building_Size)))
			{
				//cout << j << " 빌딩의 체력 : " << obj_BUILDING[j].getObjLife() << endl;
				obj[i].setRGB(Red);
				obj_BUILDING[j].setObjLife((-100.00f));
				obj[i].setObjLife(-5.0f);
				if (obj[i].getObjLife() < 0.0 && obj[i].getObjLife() != -1.0f)
				{
					Data temp2 = { 999.0,999.0,999.0,-1.0 };
					obj[i].setPosition(temp2);			//사이즈가 -1 이니 False 상태라 봄
					obj[i].fixedObjLife(-1.0f);			//-1로 라이프를 설정하면 충돌체크, 재발사 등 동작 하지 않음.
					MAX--;
				}
			}
			if ((arrowRect.x - obj_Arrow_Size) < (buildRect.x + obj_Building_Size) && (arrowRect.x + obj_Arrow_Size) > (buildRect.x - obj_Building_Size) && (arrowRect.y - obj_Arrow_Size) < (buildRect.y + obj_Building_Size) && (arrowRect.y + obj_Arrow_Size) > (buildRect.y - obj_Building_Size))
			{
				//cout << j << "빌딩의 체력 : " << obj_BUILDING[j].getObjLife() << endl;
				obj_ARROW[i].setRGB(Red);
				obj_BUILDING[j].setObjLife((-50.00f));
				obj_ARROW[i].setObjLife(-10.0f);
				if (obj_ARROW[i].getObjLife() < 0.0f && obj_ARROW[i].getObjLife() != -1.0f)
				{
					Data temp2 = { 999.0,999.0,999.0,-1.0 };
					Data temp = { 0.0,0.0,0.0,-1.0 };
					obj_ARROW[i].setPosition(temp2);
					obj_ARROW[i].setDirection(temp);
					obj_ARROW[i].fixedObjLife(-1.0f);
				}
			}
			if (obj[i].getObjLife() < 0.0f &&obj[i].getObjLife() != -1.0f)
			{
				Data temp2 = { 999.0,999.0,999.0,-1.0 };
				obj[i].setPosition(temp2);			//사이즈가 -1 이니 False 상태라 봄
				obj[i].fixedObjLife(-1.0f);			//-1로 라이프를 설정하면 충돌체크, 재발사 등 동작 하지 않음.
				MAX--;
			}
			//if (obj_ARROW[i].getObjLife() <= 0.0f)
			//{
			//	Data temp2 = { 999.0,999.0,999.0,-1.0 };
			//	obj_ARROW[i].setPosition(temp2);			//사이즈가 -1 이니 False 상태라 봄
			//	//MAX--;										//obj[i].fixedObjLife(-1.0f); -1로 라이프를 설정하면 충돌체크, 재발사 등 동작 하지 않음.
			//	
			//}
			if (obj_BUILDING[j].getObjLife() < 0.0 && obj_BUILDING[j].getObjLife() != -1.0f)//|| obj_BUILDING[i].getObjLifeTime() < 0.0f
			{
				Data temp = { 999.0,999.0,999.0,-1.0 };
				obj_BUILDING[j].setPosition(temp); //사이즈가 -1 이니 False 상태라 봄
				obj_BUILDING[j].fixedObjLife(-1.0);
				//delete &obj_BUILDING[i];
				//obj[i] = nullptr;
//for (int r = 0; r < MAX_BULLET_COUNT; ++r)
//{
//	Data temp2 = { 999.0,999.0,999.0,-1.0 };
//	obj_BULLET[r].setPosition(temp2);			//사이즈가 -1 이니 False 상태라 봄
//	obj_BULLET[r].fixedObjLife(-1.0f);			//-1로 라이프를 설정하면 충돌체크, 재발사 등 동작 하지 않음.
//}
			}
		}
		for (int q = 0; q < MAX_BULLET_COUNT; ++q)
		{
			if (obj[i].getPosition().s < 0.0)
			{
				break;
			}
			if (obj_BULLET[q].getPosition().s < 0.0f || obj_BULLET[q].getTeamNum() == obj[i].getTeamNum() || obj_ARROW[i].getTeamNum() == obj_BULLET[q].getTeamNum())	//이미 0.0f는 죽은 처리기 때문에 충돌 체크를 하지 않는다.
			{
				continue;
			}
			Data bulletRect = obj_BULLET[q].getPosition();
			/*if (obj_BULLET[q].getObjLife() < 0.0f)
			{
				continue;
			}*/
			if ((charRect.x - obj_Character_Size) < (bulletRect.x + obj_Bullet_Size) && (charRect.x + obj_Character_Size) > (bulletRect.x - obj_Bullet_Size) && (charRect.y - obj_Character_Size) < (bulletRect.y + obj_Bullet_Size) && (charRect.y + obj_Character_Size) > (bulletRect.y - obj_Bullet_Size))
			{
				//cout << "총알의 체력 : " << obj_BULLET[q].getObjLife() << endl;
				obj[i].setRGB(Red);
				obj_BULLET[q].setObjLife((-10.00f));
				if (obj_BULLET[q].getObjLife() < 0.0)//|| obj_BUILDING[i].getObjLifeTime() < 0.0f
				{
					Data temp = { 999.0,999.0,999.0,-1 };
					obj_BULLET[q].setPosition(temp);			//사이즈가 -1 이니 False 상태라 봄
					//obj_BULLET[q].fixedObjLife(10.0f);			//delete &obj_BUILDING[i];
																//obj[i] = nullptr;
				}
			}
			else
			{
				obj_BULLET[q].Update((float)updateTime, OBJECT_BULLET);
			}
		}
		for (int z = 0; z < MAX_OBJECTS_COUNT; ++z)
		{
			if (obj[i].getPosition().s < 0.0)
			{
				break;
			}
			Data arrowRect2 = obj_ARROW[z].getPosition();

			if (i == z || obj_ARROW[z].getPosition().s <= 0.0f || obj_ARROW[z].getObjLife() <= 0.0f || obj_ARROW[z].getTeamNum() == obj[i].getTeamNum())
			{
				continue;
			}
			if (((charRect.x - obj_Character_Size) < (arrowRect2.x + obj_Arrow_Size) && (charRect.x + obj_Character_Size) > (arrowRect2.x - obj_Arrow_Size) && (charRect.y - obj_Character_Size) < (arrowRect2.y + obj_Arrow_Size) && (charRect.y + obj_Character_Size) > (arrowRect2.y - obj_Arrow_Size)))
			{
				//cout << "충돌" << endl;
				Data tmp = { 999.0,999.0,999.0,-1.0 };
				Data tmp2 = { 0.0,0.0,0.0,0.0 };
				obj[i].setPosition(tmp);
				obj_ARROW[z].setPosition(tmp);
				obj[i].setDirection(tmp2);
				obj_ARROW[z].setDirection(tmp2);
				obj[i].setObjLife(-(obj[i].getObjLife()));
				obj_ARROW[z].setObjLife(-10);
				MAX--;
				//return;
			}
			else
			{
				obj_ARROW[z].Update((float)updateTime, OBJECT_ARROW);
			}
		}
		/*for (int a = 0; a < MAX_OBJECTS_COUNT; ++a)
		{
			obj_ARROW[a].Update((float)updateTime, OBJECT_ARROW);
		}*/


		obj[i].Update((float)updateTime, OBJECT_CHARACTER);
	}
}
void SceneMgr::ObjectDraw(int Object_Type, float& timeSet) {

	if (Object_Type == OBJECT_CHARACTER)
	{
		for (int i = 0; i < (MAX_OBJECTS_COUNT/2); ++i)			//team1 Character 그리기
		{
			Data pos = obj[i].getPosition();
			Data rgb = obj[i].getRGB();
			//if (pos.s < 0.0f)
			//{
			//	//cout << i << "번째 오브젝트 재생성" << endl;
			//	pos = { (float)(-250 + (rand() % MAX_SCREEN_WIDTH)),(float)(rand() % (MAX_SCEEN_HEIGHT / 2)),0.0f,(float)MAX_OBJECTS_SIZE };
			//	break;
			//}
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);
		}
		for (int i = (MAX_OBJECTS_COUNT / 2); i < MAX_OBJECTS_COUNT; ++i)	//team2 Character 그리기
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
			if (i < 3)
			{
				g_Renderer->DrawTexturedRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s, team1BulidingImg);
			}
			else
				g_Renderer->DrawTexturedRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s, team2BulidingImg);
		}
	}
	else if (Object_Type == OBJECT_BULLET)
	{
		for (int i = 0; i < MAX_BULLET_COUNT; ++i)
		{
			Data pos = obj_BULLET[i].getPosition();
			Data rgb = obj_BULLET[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);

			if (timeSet > 3000)
			{
				/*cout << "bulletCount : " << bulletCount << endl;
				Data tempPos = { 0, };
				for (int t = 0; t < MAX_BUILDING_COUNT; ++t)
					{
					int tempNum = 0;
					int tempCount = 0;
					tempNum = t * 10;
					tempCount = MAX_BULLET_COUNT/MAX_BUILDING_COUNT;
					for (int j = tempNum; j < tempCount+(tempCount*t); ++j)
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
						tempPos = { obj_BUILDING[t].getPosition().x,obj_BUILDING[t].getPosition().y,obj_BUILDING[t].getPosition().z,MAX_BULLET_SIZE };
						Data tempDirec = { checkX ,checkY,0.0f,0.0f};
						obj_BULLET[bulletCount].setPosition(tempPos);
						obj_BULLET[bulletCount].setDirection(tempDirec);
						if (bulletCount < MAX_BULLET_COUNT)
						{
							bulletCount++;
							cout << bulletCount << endl;
						}
					}
				}*/
				for (int t = 0; t < MAX_BUILDING_COUNT; ++t)
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
					Data tempPos = { obj_BUILDING[t].getPosition().x,obj_BUILDING[t].getPosition().y,obj_BUILDING[t].getPosition().z,MAX_BULLET_SIZE };
					Data tempDirec = { checkX ,checkY,0.0f,0.0f };
					obj_BULLET[bulletCount].setPosition(tempPos);
					obj_BULLET[bulletCount].setDirection(tempDirec);
					if (t < (MAX_BUILDING_COUNT / 2))
					{
						Data Team1BulletColor = { 0.5,0.2,0.7,1 };
						obj_BULLET[bulletCount].setTeamNum(1);
						obj_BULLET[bulletCount].setRGB(Team1BulletColor);
					}
					else
					{
						Data Team2BulletColor = { 1,1,0,1 };
						obj_BULLET[bulletCount].setTeamNum(2);
						obj_BULLET[bulletCount].setRGB(Team2BulletColor);
					}
					if (bulletCount < MAX_BULLET_COUNT)
					{
						bulletCount++;
						//cout << bulletCount << endl;
					}
				}
				timeSet = 0;
			}
		}
	}
	else if (Object_Type == OBJECT_ARROW)
	{
		for (int i = 0; i < MAX_ARROW_COUNT; ++i)
		{
			/*if (obj_ARROW[i].getPosition().s < MAX_ARROW_SIZE)
			{
				continue;
			}*/
			Data pos = obj_ARROW[i].getPosition();
			Data rgb = obj_ARROW[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s);

			if (timeSet > 3000)
			{
				for (int t = 0; t < MAX_OBJECTS_COUNT; ++t)
				{
					if (obj[t].getPosition().s < MAX_OBJECTS_SIZE)
					{
						continue;
					}
					float checkX = 1;
					float checkY = 1;

					if (rand() % 2 == 1)
					{
						checkX *= -1;
					}if (rand() % 2 == 1)
					{
						checkY *= -1;
					}
					Data tempPos = { obj[t].getPosition().x,obj[t].getPosition().y,obj[t].getPosition().z,MAX_ARROW_SIZE };
					Data tempDirec = { checkX ,checkY,0.0f,0.0f };
					obj_ARROW[arrowCount].setPosition(tempPos);
					obj_ARROW[arrowCount].setDirection(tempDirec);
					if (t < (MAX_OBJECTS_COUNT/2))
					{
						Data Team1BulletColor = {255,0,0,255};
						obj_ARROW[arrowCount].setTeamNum(1);
						obj_ARROW[arrowCount].setRGB(Team1BulletColor);
					}
					else
					{
						Data Team2BulletColor = { 0,0,255,255 };
						obj_ARROW[arrowCount].setTeamNum(2);
						obj_ARROW[arrowCount].setRGB(Team2BulletColor);

					}
					if (arrowCount < MAX_ARROW_COUNT)
					{
						arrowCount++;
						//cout << arrowCount << endl;
					}
				}
				timeSet = 0;
			}
		}


	}
}
