#include "labengine.h"
#include <math.h>
#define PI 3.1415926

void DrawFigure(double startx, double starty, double length, double angle, int EdgeCount, double a,int counter){
	double prevheight = starty + length * sin(angle), prevwidth = startx + length*cos(angle),currheight,currwidth;
	for (int i = 0; i < EdgeCount; i++) {
		angle += 2 * PI / EdgeCount;
		currheight = starty+ length * sin(angle);
		currwidth = startx + length * cos(angle);
		if (counter) {
			DrawFigure(currwidth, currheight, length / 2, angle + a, EdgeCount, a,counter-1);
		}
		LabDrawLine(prevwidth, prevheight, currwidth, currheight);
		LabDrawFlush();
		prevheight = currheight;
		prevwidth = currwidth;
	}
}

int main() {
	
	if (!LabInit()) {
		return 1;
	}
	int EdgeCount = 3;
	int height = LabGetHeight();
	int width = LabGetWidth();
	double newwidth, newheight;
	LabSetColor(LABCOLOR_GREEN);
	double a = 0;
	double FigRotate = 0;
	double length = width/4;
	newwidth = width / 2 + length * cos(0);
	newheight = height / 2 + length * sin(0);
	double currwidth, currheight, prevwidth,prevheight;
	while (!LabInputKeyReady())
	{
		LabClear();
		prevheight = newheight;
		prevwidth = newwidth;
		DrawFigure(width/2,height/2,length,FigRotate+a,EdgeCount, a,2);
		newwidth = width/2 + length * cos(a);
		newheight = height / 2 + length * sin(a);
		a += 0.1;
		LabDelay(100);
	}
	LabInputKey();
	LabTerm();


	return 0;
}
