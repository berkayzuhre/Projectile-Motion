#include "Manager.h"
#include "Bullets.h"
#include "Rocket.h"
#include "Cannon.h"
#include "Exp.h"
#include <fstream>

#define PI 3.14159



Manager::Manager()
{
}

Manager::~Manager()
{
}


bool Manager::OnUserCreate() {

	MyExcelFile.open("C:/Users/Grundig/Desktop/test.csv", ios::out | ios::app);

	spaceIt = 0;

	ChampX = 9;
	ChampY = 95;

	nLevelWidth = 20;
	nLevelHeight = 20;

	nTileWidth = ScreenWidth() / nLevelWidth;
	nTileHeight = ScreenHeight() / nLevelHeight;

	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";
	sLevel += L"#..................#";

	home += L".a...aaaaaaaaaa.....";
	home += L".a..aa........aa....";
	home += L".a.aa..........aa...";
	home += L".aaa............aa..";
	home += L"aaaaaaaaaaaaaaaaaaa.";
	home += L"aa..aaa.....aaa..aa.";
	home += L"aa..a.a.....a.a..aa.";
	home += L"aa..aaa.....aaa..aa.";
	home += L"aa.....aaaa......aa.";
	home += L"aa.....a..a......aa.";
	home += L"aa.....a..a......aa.";


	timer = 0;
	timer0 = 0;

	MyCannon = new Cannon;
	
	xPos = 9;
	yPos = 95;

	reveal2 = false;
	Q = (PI/2);

	return true;
}

bool Manager::OnUserUpdate(float fElapsedTime) {

	DrawBoard();

	MyCannon->Draw(this);

	Create_Bullet();

	if (m_keys[66].bPressed) reveal2 = true;

	for (int k = 0; k < BulletNum; k++) {


		if (Bullet[k] != NULL) {

			Bullet[k]->Move(fElapsedTime);
			Bullet[k]->reveal = reveal2;
			Bullet[k]->Draw();

			if (Bullet[k]->Dead(this)) { 
				delete Bullet[k];
				Bullet[k] = NULL;
				 }

		}



	}

	for (int k = 0; k < RocketNum; k++) {


		if (Rocket[k] != NULL) {

			Rocket[k]->Move(fElapsedTime);
			Rocket[k]->reveal = reveal2;

			Rocket[k]->Draw();

			if (Rocket[k]->Dead(this)) {

				delete Rocket[k];
				Rocket[k] = NULL;
			}

		}
	}



	int a[4] = { 125,85,55,25};

	Fill(0, 0, a[spaceIt],ScreenHeight(),PIXEL_THREEQUARTERS, FG_DARK_GREY);

	

	if (m_keys[VK_SPACE].bPressed)
	{
		spaceIt++;
		if (3 < spaceIt) {
			spaceIt = 0;
		}

	}

	Aim(fElapsedTime);

	timer += fElapsedTime;
	timer0 += fElapsedTime;

	if (timer > 6)
	{

		for (int k = 0; k < RocketNum; k++) {
			if (Rocket[k] == NULL) {
				Rocket[k] = new Rockets(this);
				break;
			}
		}
		timer = 0;
	}


	if (timer0 > 3)
	{

		Q = (((float)(rand() % 10)/10)*(PI/2))+PI/12;

		for (int k = 0; k < BulletNum; k++) {
			if (Bullet[k] == NULL) {
				Bullet[k] = new Bullets(this, Q);
				break;
			}
		}
		timer0 = 0;
	}



	return true;
}

void Manager::DrawBoard() {
	

	for (int x = 0; x < nLevelWidth; x++) {
		for (int y = 0; y < nLevelHeight; y++) {

			wchar_t sTileID = sLevel[y * nLevelWidth + x];

			switch (sTileID) {

			case L'.':
				//Draw active black path
				Fill(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, PIXEL_SOLID, FG_BLACK);

				break;
			case L'#':

				//Draw walls
				Fill(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, PIXEL_SOLID, FG_DARK_BLUE);

				break;


			}
		}
	}

	
		for (int y = 0; y < 11; y++) {
			for (int x = 0; x < 20; x++) {

			wchar_t sTileID = home[y * nLevelWidth + x];

			switch (sTileID) {

			case L'.':
				//Draw active black path
				Draw(150+x,89+y, PIXEL_SOLID, FG_BLACK);

				break;
			case L'a':

				//Draw walls
				Draw(150 + x,89+y, PIXEL_SOLID, FG_MAGENTA);

				break;


			}
		}
	}


	if (m_keys[65].bPressed)
		reveal = TRUE;

	if (reveal) {
		int a[4] = { 25,55,85,125 };

		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 100; y++) {
				Draw(a[x], y, PIXEL_SOLID, FG_GREEN);

			}
		}
	}

}


void Manager::Aim(float fElapsedTime) {




	if (m_keys[65].bHeld)
	{
		if (Q>0)
			Q -= 1.5*fElapsedTime;

	}

	if (Q > PI) Q = PI;
	if (Q < 0) Q = 0;




}

void Manager::Create_Bullet() {




}