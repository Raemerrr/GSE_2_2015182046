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
	AICharCount = 0;
}

SceneMgr::~SceneMgr()
{
	for (int i = 1; i < 5; ++i) // ARROW 추가되면 4까지
	{
		ObjectAllDelete(i);
	}
	delete g_Renderer;
}

void SceneMgr::ObjectCreate(int Object_Type)
{
	if (Object_Type == OBJECT_CHARACTER)
	{
		obj = new Object[MAX_OBJECTS_COUNT]();
		for (int i = 0; i < (MAX_OBJECTS_COUNT / 2); ++i)
		{
			Data TEAM1CharColor = { 255.0f,0.0f,0.0f,255.0f };
			Data TEAM1CharPos = { 0.f,0.f,0.f,-1.f };
			obj[i].setPosition(TEAM1CharPos);
			obj[i].setTeamNum(1);
			//obj[i].setObjLifeTime(100000.f);
			obj[i].fixedObjLife(-1.f);
			obj[i].setRGB(TEAM1CharColor);
		}
		for (int i = (MAX_OBJECTS_COUNT / 2); i < MAX_OBJECTS_COUNT; ++i)
		{
			Data TEAM2CharColor = { 0.f,0.f, 255,255 };
			Data TEAM2CharPos = { MAX_SCREEN_WIDTH * 10,MAX_SCEEN_HEIGHT / 2,0.0f,MAX_OBJECTS_SIZE };
			obj[i].setPosition(TEAM2CharPos);
			obj[i].setTeamNum(2);
			obj[i].fixedObjLife(1.0f);
			obj[i].setRGB(TEAM2CharColor);
			Data tempDirec = { 0.f ,0.f,0.f,0.f };
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
			Data temp = { (MAX_SCREEN_WIDTH * 10),MAX_SCEEN_HEIGHT,0.f,MAX_BULLET_SIZE };
			obj_BULLET[i].setPosition(temp);
			obj_BULLET[i].fixedObjLife(10.0f);
		}
	}
	else if (Object_Type == OBJECT_ARROW)
	{
		obj_ARROW = new Object[MAX_ARROW_COUNT](); // 캐릭터 수 만큼 할당
		for (int i = 0; i < MAX_ARROW_COUNT; ++i)	//총알 초기화
		{
			Data temp = { MAX_SCREEN_WIDTH,(MAX_SCEEN_HEIGHT * 10),0.f,MAX_ARROW_SIZE };
			obj_ARROW[i].setPosition(temp);
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
	else// if (Object_Type == OBJECT_ARROW)
	{
		return &obj_ARROW[i];
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

void SceneMgr::ObjectCollition1(float updateTime)
{

	Data DeathPoint = { 999.f,999.f,999.f,-1.f };
	Data DeathDirec = { 0.f,0.f,0.f,0.f };

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
		Data charRect = obj[i].getPosition();

		for (int j = 0; j < MAX_BUILDING_COUNT; ++j)
		{
			if (obj_BUILDING[j].getPosition().s < 0.0f || obj_BUILDING[j].getTeamNum() == obj[i].getTeamNum())	//이미 0.0f는 죽은 처리기 때문에 충돌 체크를 하지 않는다.
			{
				continue;
			}
			Data buildRect = obj_BUILDING[j].getPosition();
			if (((charRect.x - obj_Character_Size) < (buildRect.x + obj_Building_Size) && (charRect.x + obj_Character_Size) > (buildRect.x - obj_Building_Size) && (charRect.y - obj_Character_Size) < (buildRect.y + obj_Building_Size) && (charRect.y + obj_Character_Size) > (buildRect.y - obj_Building_Size)))
			{
				//cout << j << " 빌딩의 체력 : " << obj_BUILDING[j].getObjLife() << endl;
				obj_BUILDING[j].setObjLife((-100.f));
				obj[i].setObjLife(-5.f);
			}
		}

		for (int q = 0; q < MAX_BULLET_COUNT; ++q)
		{
			if (obj_BULLET[q].getPosition().s < 0.0f || obj_BULLET[q].getTeamNum() == obj[i].getTeamNum())	//이미 0.0f는 죽은 처리기 때문에 충돌 체크를 하지 않는다.
			{
				continue;
			}
			Data bulletRect = obj_BULLET[q].getPosition();
			if ((charRect.x - obj_Character_Size) < (bulletRect.x + obj_Bullet_Size) && (charRect.x + obj_Character_Size) > (bulletRect.x - obj_Bullet_Size) && (charRect.y - obj_Character_Size) < (bulletRect.y + obj_Bullet_Size) && (charRect.y + obj_Character_Size) > (bulletRect.y - obj_Bullet_Size))
			{
				obj[i].setObjLife(-1.0);
				obj_BULLET[q].setObjLife((-10.00f));
			}
		}

		for (int z = 0; z < MAX_ARROW_COUNT; ++z)
		{
			Data arrowRect2 = obj_ARROW[z].getPosition();
			if (obj_ARROW[z].getPosition().s < 0.0f || obj_ARROW[z].getTeamNum() == obj[i].getTeamNum())	//이미 0.0f는 죽은 처리기 때문에 충돌 체크를 하지 않는다.
			{
				continue;
			}
			if (((charRect.x - obj_Character_Size) < (arrowRect2.x + obj_Arrow_Size) && (charRect.x + obj_Character_Size) > (arrowRect2.x - obj_Arrow_Size) && (charRect.y - obj_Character_Size) < (arrowRect2.y + obj_Arrow_Size) && (charRect.y + obj_Character_Size) > (arrowRect2.y - obj_Arrow_Size)))
			{
				obj[i].setPosition(DeathPoint);
				obj_ARROW[z].setPosition(DeathPoint);
				obj[i].setDirection(DeathDirec);
				obj_ARROW[z].setDirection(DeathDirec);
				obj[i].setObjLife(-(obj[i].getObjLife()));
				obj_ARROW[z].fixedObjLife(-1.f);
			}
		}
		for (int t = 0; t < MAX_OBJECTS_COUNT; ++t)
		{
			if (obj[t].getObjLife() < 0.0)
			{
				obj[t].setPosition(DeathPoint);			//사이즈가 -1 이니 False 상태라 봄
				obj[t].fixedObjLife(-1.0f);				//-1로 라이프를 설정하면 충돌체크, 재발사 등 동작 하지 않음.
			}
			else
			{
				obj[t].Update((float)updateTime, OBJECT_CHARACTER);
			}
		}

		for (int j = 0; j < MAX_BUILDING_COUNT; ++j)
		{
			if (obj_BUILDING[j].getObjLife() < 0.0)//|| obj_BUILDING[i].getObjLifeTime() < 0.0f
			{
				obj_BUILDING[j].setPosition(DeathPoint); //사이즈가 -1 이니 False 상태라 봄
				obj_BUILDING[j].fixedObjLife(-1.0);
			}
		}

		for (int q = 0; q < MAX_BULLET_COUNT; ++q)
		{
			if (obj_BULLET[q].getObjLife() < 0.0)//|| obj_BUILDING[i].getObjLifeTime() < 0.0f
			{
				obj_BULLET[q].setPosition(DeathPoint);
			}
			else
			{
				obj_BULLET[q].Update((float)updateTime, OBJECT_BULLET);
			}
		}
		for (int q = 0; q < MAX_ARROW_COUNT; ++q)
		{
			if (obj_ARROW[q].getObjLife() < 0.0)//|| obj_BUILDING[i].getObjLifeTime() < 0.0f
			{
				obj_ARROW[q].setPosition(DeathPoint);
			}
			else
			{
				obj_ARROW[q].Update((float)updateTime, OBJECT_ARROW);
			}
		}
	}
}

void SceneMgr::ObjectCollition2(float updateTime)
{
	Data DeathPoint = { 999.f,999.f,999.f,-1.f };
	Data DeathDirec = { 0.f,0.f,0.f,0.f };
	int obj_Building_Size = MAX_BUILDING_SIZE / 2;
	int obj_Bullet_Size = MAX_BULLET_SIZE / 2;
	int obj_Arrow_Size = MAX_ARROW_SIZE / 2;

	for (int i = 0; i < MAX_BUILDING_COUNT; ++i)
	{
		if (obj_BUILDING[i].getPosition().s < 0.0f)// || obj_BUILDING[i].getObjLifeTime() < 0.0)	//이미 0.0f는 죽은 처리기 때문에 충돌 체크를 하지 않는다.
		{
			continue;
		}
		Data buildRect = obj_BUILDING[i].getPosition();

		for (int q = 0; q < MAX_BULLET_COUNT; ++q)
		{
			if (obj_BULLET[q].getPosition().s < 0.0f || obj_BULLET[q].getTeamNum() == obj_BUILDING[i].getTeamNum())	//이미 0.0f는 죽은 처리기 때문에 충돌 체크를 하지 않는다.
			{
				continue;
			}
			Data bulletRect = obj_BULLET[q].getPosition();
			if ((buildRect.x - obj_Building_Size) < (bulletRect.x + obj_Bullet_Size) && (buildRect.x + obj_Building_Size) > (bulletRect.x - obj_Bullet_Size) && (buildRect.y - obj_Building_Size) < (bulletRect.y + obj_Bullet_Size) && (buildRect.y + obj_Building_Size) > (bulletRect.y - obj_Bullet_Size))
			{
				obj_BUILDING[i].setObjLife(-30.f);
				obj_BULLET[q].setObjLife((-10.f));
			}
		}

		for (int z = 0; z < MAX_ARROW_COUNT; ++z)
		{
			Data arrowRect2 = obj_ARROW[z].getPosition();
			if (obj_ARROW[z].getPosition().s < 0.0f || obj_ARROW[z].getTeamNum() == obj_BUILDING[i].getTeamNum())	//이미 0.0f는 죽은 처리기 때문에 충돌 체크를 하지 않는다.
			{
				continue;
			}
			if (((buildRect.x - obj_Building_Size) < (arrowRect2.x + obj_Arrow_Size) && (buildRect.x + obj_Building_Size) > (arrowRect2.x - obj_Arrow_Size) && (buildRect.y - obj_Building_Size) < (arrowRect2.y + obj_Arrow_Size) && (buildRect.y + obj_Building_Size) > (arrowRect2.y - obj_Arrow_Size)))
			{
				obj_ARROW[z].setPosition(DeathPoint);
				obj_ARROW[z].setDirection(DeathDirec);
				obj_BUILDING[i].setObjLife(-50.f);
				obj_ARROW[z].fixedObjLife(-1.f);
			}
		}
	}

}

void SceneMgr::ObjectDraw(int Object_Type, float& timeSet) {

	if (Object_Type == OBJECT_CHARACTER)
	{
		for (int i = 0; i < (MAX_OBJECTS_COUNT / 2); ++i)			//team1 Character 그리기
		{
			int DrawObjCheck = 0;
			Data pos = obj[i].getPosition();
			Data rgb = obj[i].getRGB();
			for (int j = 0; j < (MAX_OBJECTS_COUNT / 2); ++j)
			{
				if (obj[j].getObjLife() < 0.0f)
				{
					//cout << "SceneManager->getObject(" << j << ", OBJECT_CHARACTER)->getPosition().s < 0.0f 실행" << endl;
					DrawObjCheck = AICharCount;
					//cout << CheckObjectCount << endl;
					AICharCount = j;
					break;
				}
			}
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s, (float)LEVEL_SKY);
			g_Renderer->DrawSolidRectGauge(pos.x, pos.y + 10, pos.z, MAX_OBJECTS_SIZE * 3, 5, 1.f, 0.f, 0.f, 1.f, 1.f, (float)LEVEL_GOD);

			if (timeSet > 3000)
			{
				Data TEAM1CharPos = { (float)(-250 + (rand() % MAX_SCREEN_WIDTH)),(float)(rand() % (MAX_SCEEN_HEIGHT / 2)),0.0f,(float)MAX_OBJECTS_SIZE };
				obj[AICharCount].setPosition(TEAM1CharPos);
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
				obj[AICharCount].setDirection(tempDirec);
				obj[AICharCount].fixedObjLife(1.f);
				if (DrawObjCheck != 0)
				{
					AICharCount = DrawObjCheck;
				}
				if (AICharCount < (MAX_OBJECTS_COUNT - 1) && DrawObjCheck == 0)
				{
					AICharCount++;
				}
				timeSet = 0;
			}
		}
		for (int i = (MAX_OBJECTS_COUNT / 2); i < MAX_OBJECTS_COUNT; ++i)	//team2 Character 그리기
		{
			Data pos = obj[i].getPosition();
			Data rgb = obj[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s, 0);
			g_Renderer->DrawSolidRectGauge(pos.x, pos.y + 10, pos.z, MAX_OBJECTS_SIZE * 3, 5, 0.f, 0.f, 1.f, 1.f, 1.f, (float)LEVEL_GOD);
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
			float BuildHealth = obj_BUILDING[i].getObjLife() / MAX_BUILDING_LIFE;
			//cout << i << "번쨰 건물의 체력" << obj_BUILDING[i].getObjLife()  <<endl;
			if (i < 3)
			{
				g_Renderer->DrawTexturedRect(pos.x, pos.y, pos.z, pos.s, 1.f, 1.f, 1.f, 1.f, team1BulidingImg, LEVEL_GOD);
				g_Renderer->DrawSolidRectGauge(pos.x, pos.y + 60, pos.z, 100, 5, 1.f, 0.f, 0.f, 1.f, BuildHealth, LEVEL_GOD);
			}
			else
			{
				g_Renderer->DrawTexturedRect(pos.x, pos.y, pos.z, pos.s, 1.f, 1.f, 1.f, 1.f, team2BulidingImg, LEVEL_GOD);
				g_Renderer->DrawSolidRectGauge(pos.x, pos.y + 60, pos.z, 100, 5, 0.f, 0.f, 1.f, 1.f, BuildHealth, LEVEL_GOD);
			}
		}

	}
	else if (Object_Type == OBJECT_BULLET)
	{
		for (int i = 0; i < MAX_BULLET_COUNT; ++i)
		{
			int DrawObjCheck = 0;
			Data pos = obj_BULLET[i].getPosition();
			Data rgb = obj_BULLET[i].getRGB();

			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s, (float)LEVEL_GROUND);

			if (timeSet > 3000)
			{
				for (int t = 0; t < MAX_BUILDING_COUNT; ++t)
				{
					Data tempCharPos = obj_BUILDING[t].getPosition();
					if (tempCharPos.s < 0.0f)
					{
						continue;
					}
					Data tempPos = { tempCharPos.x,tempCharPos.y,tempCharPos.z,MAX_BULLET_SIZE };
					obj_BULLET[bulletCount].setPosition(tempPos);
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
					obj_BULLET[bulletCount].setDirection(tempDirec);
					if (t < (MAX_BUILDING_COUNT / 2))
					{
						Data Team1BulletColor = { 0.5f,0.2f,0.7f,1.f };
						obj_BULLET[bulletCount].setTeamNum(1);
						obj_BULLET[bulletCount].setRGB(Team1BulletColor);
					}
					else
					{
						Data Team2BulletColor = { 1,1,0,1 };
						obj_BULLET[bulletCount].setTeamNum(2);
						obj_BULLET[bulletCount].setRGB(Team2BulletColor);
					}
					bulletCount++;
					if (bulletCount >= MAX_BULLET_COUNT)
					{
						for (int u = 0; u < MAX_BULLET_COUNT; ++u)
						{
							if (obj_BULLET[u].getPosition().s < 0.0) {
								bulletCount = u;
							}
						}
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
			Data pos = obj_ARROW[i].getPosition();
			Data rgb = obj_ARROW[i].getRGB();
			g_Renderer->DrawSolidRect(pos.x, pos.y, pos.z, pos.s, rgb.x, rgb.y, rgb.z, rgb.s, (float)LEVEL_GROUND);

			if (timeSet > 3000)
			{
				for (int t = 0; t < MAX_OBJECTS_COUNT; ++t)
				{
					if (obj[t].getObjLife() < 0.0f)
					{
						continue;
					}
					Data tempPos = { obj[t].getPosition().x,obj[t].getPosition().y,obj[t].getPosition().z,MAX_ARROW_SIZE };
					obj_ARROW[arrowCount].setPosition(tempPos);
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
					obj_ARROW[arrowCount].setDirection(tempDirec);
					if (t < (MAX_OBJECTS_COUNT / 2))
					{
						Data Team1ArrowColor = { 255.f,0.f,0.f,255.f };
						obj_ARROW[arrowCount].setTeamNum(1);
						obj_ARROW[arrowCount].setRGB(Team1ArrowColor);
					}
					else
					{
						Data Team2ArrowColor = { 0.f,0.f,255.f,255.f };
						obj_ARROW[arrowCount].setTeamNum(2);
						obj_ARROW[arrowCount].setRGB(Team2ArrowColor);

					}
					arrowCount++;
					//cout << arrowCount << endl;
					if (arrowCount >= MAX_ARROW_COUNT)
					{
						for (int u = 0; u < MAX_ARROW_COUNT; ++u)
						{
							if (obj_ARROW[u].getPosition().s < 0.0) {
								//cout << u << "번째 ARROW객체 재생성" << endl;
								arrowCount = u;
							}
						}
					}
				}
				timeSet = 0;
			}
		}
	}
}
