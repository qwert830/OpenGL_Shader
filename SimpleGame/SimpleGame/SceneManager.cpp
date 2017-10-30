#include "stdafx.h"
#include "SceneManager.h"
#include <random>

void SceneManager::Update(float time)
{
	
	CollisionRect();
	CollisionObject();

	int i = 0;
	for( i = 0; i< manager.size(); i++)
	{
		manager[i]->Update(time);
	}
	for (i = 0; i< manager.size(); i++)
	{
		if (manager[i]->GetLifeTime() <= 0)
		{
			manager.erase(manager.begin() + i);
			i--;
		}
	}
}

void SceneManager::NewObject(int x, int y, COLORS colors, float size)
{
	manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), colors, size));
}

void SceneManager::NewObject(int x, int y, COLORS colors, POS direction, float size)
{
	manager.push_back(new Object(pRenderer, POS(x - windowW, -y + windowH, 0), direction, colors, size));
}

void SceneManager::Draw()
{
	for (auto &d : manager)
	{
		d->DrawObject();
	}
}

void SceneManager::CreateTest()
{
	for (int i = 0; i < 100; i++)
	{
		float x = (float)(rand() % 5) - 0.99f;
		float y = (float)(rand() % 5) - 0.99f;
		NewObject(rand() % windowW * 2, rand() % windowH * 2, COLORS(1, 1, 1, 1),POS(x,y,0), 10);
	}
}

void SceneManager::CollisionRect()
{
	for (auto& d : manager)
	{
		POS tempPos = d->GetPos();
		if (tempPos.x <-windowW || tempPos.x > windowW)
		{
			POS temp = d->GetDirection();
			d->SetDirection(POS(-temp.x, temp.y, 0));
			d->MoveUpdate(0);
		}
		if (tempPos.y < -windowH || tempPos.y > windowH)
		{
			POS temp = d->GetDirection();
			d->SetDirection(POS(temp.x, -temp.y, 0));
			d->MoveUpdate(0);
		}
	}
}

void SceneManager::CollisionObject()
{
	for (int i = 0; i < manager.size(); i++)
		manager[i]->SetColor(1, 1, 1, 1);

	if(manager.size() >= 2)
	for (int i = 0; i < manager.size(); i++)
	{
		POS tempObj1 = manager[i]->GetPos();
		float tempSize1 = manager[i]->GetSize()/2;

		for (int j = i+1; j < manager.size(); j++)
		{
			POS tempObj2 = manager[j]->GetPos();
			float tempSize2 = manager[j]->GetSize()/2;

			if (tempObj1.x - tempSize1 <= tempObj2.x - tempSize2 && tempObj2.x - tempSize2 <= tempObj1.x + tempSize1)
			{
				if (tempObj1.y - tempSize1 <= tempObj2.y - tempSize2 && tempObj2.y - tempSize2 <= tempObj1.y + tempSize1)
				{
					manager[i]->SetColor(1, 0, 0, 1);
					manager[j]->SetColor(1, 0, 0, 1);
					break;
				}
				else if (tempObj1.y - tempSize1 <= tempObj2.y + tempSize2 && tempObj2.y + tempSize2 <= tempObj1.y + tempSize1)
				{
					manager[i]->SetColor(1, 0, 0, 1);
					manager[j]->SetColor(1, 0, 0, 1);
					break;
				}
			}
			else if (tempObj1.x - tempSize1 <= tempObj2.x + tempSize2 && tempObj2.x + tempSize2 <= tempObj1.x + tempSize1)
			{
				if (tempObj1.y - tempSize1 <= tempObj2.y - tempSize2 && tempObj2.y - tempSize2 <= tempObj1.y + tempSize1)
				{
					manager[i]->SetColor(1, 0, 0, 1);
					manager[j]->SetColor(1, 0, 0, 1);
					break;
				}
				else if (tempObj1.y - tempSize1 <= tempObj2.y + tempSize2 && tempObj2.y + tempSize2 <= tempObj1.y + tempSize1)
				{
					manager[i]->SetColor(1, 0, 0, 1);
					manager[j]->SetColor(1, 0, 0, 1);
					break;
				}
			}
		}
	}
}

SceneManager::SceneManager()
{
}


SceneManager::~SceneManager()
{
	manager.~vector();
}
