
#include "Manager.h"
#include "Rocket.h"
#include "time.h"
#define PI 3.14159




Rockets::Rockets(Manager* pManager2)
{
	reveal = FALSE;

	xPos = 15;
	yPos = 99;

	//m = (rand()%3)+2;

	m = 3;

	aT = -18 / m;

	aX = 0;

	aY = aT;

	pManager = pManager2;


	timer = 0;

	check = TRUE;

	ceiling = ((rand() % 3) * 10) + 30;


	index = 0;

}

Rockets::~Rockets()
{


}

void Rockets::Move(float fElapsedTime) {


	if (yPos < (ceiling)) {

		aY = 20;
		aX = -(aT*3);
	}

	Vx += aX * fElapsedTime;

	xPos += Vx * fElapsedTime;

	Vy += aY * fElapsedTime;

	yPos += Vy * fElapsedTime;

	if (Vy > 0 && check) {

		check = FALSE;
	}

	timer += fElapsedTime;


	if (xPos > a[index] && index < 4) {
		Y[index][0] = xPos;
		Y[index][1] = yPos;
		Y[index][2] = timer;
		index++;
	}

	if (index == 3) {

		float diff1 = Y[1][2] - Y[0][2];
		float diff2 = Y[2][2] - Y[1][2];


		if (reveal) {
			float y3 = 99 - (-50.0073  + (0.3616 * (99 - Y[0][1])) + (-0.1822 * (99 - Y[1][1])) + (0.9884 * (99 - Y[2][1])) + 6.4163*diff1+ 4.7342*diff2);

			pManager->Fill(122, y3 - 2, 128, y3, PIXEL_SOLID, FG_CYAN);


			float diff21 = Y[2][2] - 2 * Y[1][2] + Y[0][2];

			float type = 1.0 / (1 + exp(-(42.06817 + 201.47220 * (diff21))));


			if (type < 0.5 ) {
				pManager->Fill(140, 20, 150, 30, PIXEL_SOLID, FG_CYAN);
			}

			
		}
	}

}

void Rockets::Draw() {

	float perspective = 1;

	float width = 1 * perspective;
	float height = 4 * perspective;

	float tangent = Vx / Vy;

	float angle=atan(tangent);

	float xDraw = 4 * sin(angle);
	float yDraw = 4 * cos(angle);
	
	//pManager->Fill(xPos, yPos - height, (xPos + width+xDraw), (yPos - 1+yDraw), PIXEL_SOLID, FG_CYAN);
	if(reveal)
		pManager->DrawLine(xPos, yPos, (xPos + xDraw), (yPos + yDraw), PIXEL_SOLID, FG_CYAN);
	else
		pManager->DrawLine(xPos, yPos, (xPos + xDraw), (yPos + yDraw), PIXEL_SOLID, FG_GREY);
}

bool Rockets::Dead(Manager * pManager) {

	if (xPos > 170 || yPos > 100 || xPos < 10) {

		//pManager->MyExcelFile <<Q*180.0/PI<<","<<timer<<","<<xPos-10 <<","<<99-yPos<<","<<peakX-10<<","<<99-peakY<< endl;

		pManager->MyExcelFile << Y[0][0] - 10 << "," << 99 - Y[0][1] << "," << Y[0][2] << "," << Y[1][0] - 10 << "," << 99 - Y[1][1] << "," << Y[1][2] << "," << Y[2][0] - 10 << "," << 99 - Y[2][1] << "," << Y[2][2] << "," << Y[3][0] - 10 << "," << 99 - Y[3][1] << "," << Y[3][2] << "," << index << "," << 1 << endl;

		return TRUE;

	}

	else
		return FALSE;



}