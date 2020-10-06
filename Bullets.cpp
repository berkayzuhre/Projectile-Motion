#include "Bullets.h"
#include "Manager.h"
#include "time.h"
#include "Exp.h"
#define PI 3.14159




Bullets::Bullets(Manager* pManager2, float Q1)
{


	reveal = FALSE;

	xPos = 10 + cos(Q1) * 4 * sqrt(2);
	yPos = 99 - sin(Q1) * 4 * sqrt(2);

	F = 175;

	m = 3;

	aT = F / m;

	aX = 0;

	aY = 15;

	Vx = aT * cos(Q1);

	Vy = -(aT * sin(Q1));

	Q = Q1;

	pManager = pManager2;

	peakY = 0;
	peakX = 0;

	timer = 0;

	check = TRUE;


	index = 0;

}

Bullets::~Bullets()
{


}

void Bullets::Move(float fElapsedTime) {

	Vx += aX*fElapsedTime;

	xPos += Vx*fElapsedTime;

	Vy += aY*fElapsedTime;

	yPos += Vy * fElapsedTime;

	if (Vy > 0 && check) {
		peakY = yPos;
		peakX = xPos;
		check = FALSE;
	}

	timer += fElapsedTime;


	if ( xPos > a[index] && index < 4) {
		Y[index][0] = xPos;
		Y[index][1] = yPos;
		Y[index][2] = timer;
		index++;
	}

	if (index == 3) {

		float y3 = 99 - (-9.21492 + (-2.24602 * (((double)Y[0][0])-10)) + (-2.76760 * (99-Y[0][1])) + (180.36807 * Y[0][2]) + (-0.04942 * (Y[1][0]-10)) + (-1.22990 * (99-Y[1][1])) + (26.49651 * Y[1][2]) + (0.84863 * (Y[2][0]-10)) + (2.87806 * (99-Y[2][1])) + (-56.79186 * Y[2][2]));

		if (reveal) {
			float diff21 = Y[2][2] - 2 * Y[1][2] + Y[0][2];

			pManager->Fill(122, y3-2,128, y3 , PIXEL_SOLID, FG_YELLOW);

			float type = 1.0 / (1 + exp(-(42.06817 + 201.47220 * (diff21))));

			if (type > 0.5) {
				pManager->Fill(140, 20, 150, 30, PIXEL_SOLID, FG_YELLOW);
			}
		}
	}

}

void Bullets::Draw() {

	float perspective = 1;

	float width = 4 * perspective;
	float height = 2 * perspective;





	//pManager->Fill(xPos, yPos-height, (xPos+width), (yPos-1), PIXEL_SOLID,FG_YELLOW);

	float tangent = Vx / Vy;

	float angle = atan(tangent);

	float xDraw = 4 * sin(angle);
	float yDraw = 4 * cos(angle);

	//pManager->Fill(xPos, yPos - height, (xPos + width+xDraw), (yPos - 1+yDraw), PIXEL_SOLID, FG_CYAN);
	if(reveal)
		pManager->DrawLine(xPos, yPos, (xPos + xDraw), (yPos + yDraw), PIXEL_SOLID, FG_YELLOW);
	else
		pManager->DrawLine(xPos, yPos, (xPos + xDraw), (yPos + yDraw), PIXEL_SOLID,FG_GREY);

}

bool Bullets::Dead(Manager* pManager) {

	if (xPos > 170 || yPos > 100 || xPos < 10) {
	
	//pManager->MyExcelFile <<Q*180.0/PI<<","<<timer<<","<<xPos-10 <<","<<99-yPos<<","<<peakX-10<<","<<99-peakY<< endl;

	pManager->MyExcelFile << Y[0][0]-10 << "," << 99-Y[0][1] << "," << Y[0][2] << "," << Y[1][0] - 10 << "," << 99 - Y[1][1] << "," << Y[1][2] << "," << Y[2][0] - 10 << "," << 99 - Y[2][1] << "," << Y[2][2] << "," << Y[3][0] - 10 << "," << 99 - Y[3][1] << "," << Y[3][2] << "," << index << "," << 2 << endl;
		
	return TRUE;

	}

	else
		return FALSE;



}