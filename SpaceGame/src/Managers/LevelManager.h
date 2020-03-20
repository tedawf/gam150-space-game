#pragma once

#include "AEEngine.h"	
#include "../Global_ECS.h"
const float MIN_SPAWN_X = 2000.0f;
const float MIN_SPAWN_Y = 2000.0f;



namespace LevelManager
{
	void Update();
	void CheckOutOfScreen(ENTITY id);
	
	void SetObjectiveComplete();

	AEVec2 RandomEnemyPosition();
	AEVec2 RandomItemPosition();

	float GetRandomPattern();

	float RandomPos();
	void SetSpawnArea();

	void SetObjectiveSpawn(float randomLevel);
	void SetEnemySpawn(float randomLevel);
	void ClearSpawnArea();
	void Level1_Map();
}



struct objectSpawnArea1
{
	float x;
	float y;
};

struct objectSpawnArea2
{
	float x;
	float y;
};

struct objectSpawnArea3
{
	float x;
	float y;
};

struct objectSpawnArea4
{
	float x;
	float y;
};

struct objectSpawnArea5
{
	float x;
	float y;
};

struct objectSpawnArea6
{
	float x;
	float y;
};

struct objectSpawnArea7
{
	float x;
	float y;
};

struct objectSpawnArea8
{
	float x;
	float y;
};


