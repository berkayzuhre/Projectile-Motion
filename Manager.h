#pragma once
#include "olcConsoleGameEngine.h"
class Bullets;
class Cannon;
class Rockets;
class Exp;
constexpr auto BulletNum = 10000;
constexpr auto RocketNum = 100;
#include <iostream>
#include <fstream>


class Manager: public olcConsoleGameEngine
{
public:
	Manager();
	~Manager();

	virtual bool OnUserUpdate(float fElapsedTime);

	virtual bool OnUserCreate();

	void DrawBoard();

	ofstream MyExcelFile;

	float Q;

	void Aim(float);

	void Create_Bullet();

private:

	wstring sLevel;

	wstring home;

	int nLevelWidth;
	int nLevelHeight;

	int nTileWidth; 
	int nTileHeight; 

	float ChampX;
	float ChampY;

	wstring Closed;

	char ChampDirection;

	int map2[20][20];

	int xPos;

	int yPos;

	float timer;
	float timer0;

	Cannon* MyCannon;
	
	int spaceIt;
	bool reveal;

	bool reveal2;

	Bullets* Bullet[BulletNum];
	Rockets* Rocket[RocketNum];


};

