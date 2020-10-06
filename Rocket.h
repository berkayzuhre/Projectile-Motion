#pragma once

class Manager;
#include <iostream>
#include <fstream>

class Rockets
{
public:

	Rockets(Manager*);

	~Rockets();

	void Move(float);

	void Draw();

	bool Dead(Manager*);
	bool reveal;
	float xPos;
	float yPos;
private:



	float Vx;
	float Vy;

	float aX;
	float aY;
	float aT;

	int ceiling;

	float m;

	bool check;

	float Q;


	Manager* pManager;

	float timer;

	float Y[4][3] = {0};
	int index;


	int a[4] = { 25, 55, 85, 125 };


};

