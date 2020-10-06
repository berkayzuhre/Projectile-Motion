#pragma once
class Manager;
class Exp;
#include <iostream>
#include <fstream>

class Bullets
{
public:

	Bullets(Manager*,float);

	~Bullets();

	void Move(float);

	void Draw();

	bool Dead(Manager*);
	bool reveal;
	float xPos;
	float yPos;
private:


	int colour;

	

	float Vx;
	float Vy;

	float aX;
	float aY;
	float aT;

	float F;

	float m;

	bool check;

	float Q;

	float peakY;
	float peakX;

	Manager* pManager;

	float timer;

	float Y[4][3];
	int index;


	int a[4]={ 25, 55, 85, 125 };

};

