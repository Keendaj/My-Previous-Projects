#include <stdlib.h>
#include <math.h>
#include "labengine.h"
#define PI 3.1415926

typedef struct {
	int x;
	int y;
}point_t;

void DrawStep(point_t a, point_t b, int depth){
	if (depth == 0) {
		LabDrawLine(a.x,a.y,b.x,a.y);
		LabDrawLine(b.x,a.y,b.x,b.y);
		
		}
	else {
		point_t a2 = { (a.x + b.x) / 2, (a.y + b.y) / 2 };
		DrawStep(a, a2, depth-1);
		DrawStep(a2, b, depth - 1);
	}
}

void DrawKoh(point_t a, point_t b, int depth) {
	point_t a2 = { a.x + (b.x-a.x) / 3,a.y+ (b.y-a.y) / 3 };
	
	point_t vector = {(b.y-a.y),-1*(b.x - a.x) };
	point_t c = { (a.x+b.x)/2 + vector.x/3,(a.y+b.y)/2 + vector.y / 3};
	if (depth == 0) {
		LabDrawLine(a.x,a.y,a2.x,a2.y);
		LabDrawLine(a.x +  (b.x-a.x) *2/ 3, a.y + (b.y-a.y)*2 / 3,b.x,b.y);
		LabDrawLine(a2.x,a2.y,c.x,c.y);
		LabDrawLine(c.x,c.y, a.x + (b.x - a.x) * 2 / 3, a.y + (b.y - a.y) * 2 / 3);
	}
	else if(depth > 0){
		point_t b2 = { a.x + (b.x - a.x) * 2 / 3, a.y + (b.y - a.y) * 2 / 3 };
		DrawKoh(a, a2, depth - 1);
		DrawKoh(a2, c, depth-1);
		DrawKoh(c, b2, depth - 1);
		DrawKoh(b2, b, depth - 1);
	}
}



int main() {
	if (!LabInit()) {
		return 1;
	}
	int n = 3;
	point_t a = {50, 50};
	point_t b = { LabGetWidth() - 50,LabGetHeight() - 50 };
	labkey_t key = LabInputKey();
	while (key != LABKEY_ESC) {
		LabClear();
		if (key == '+') {
			n++;
		}
		else if (key == '-') {
			n--;
		}
		else if (key == '1') {
			DrawStep(a, b, n);
			LabDrawFlush();
		}
		else if (key == '2') {
			DrawKoh(a, b, n);
			LabDrawFlush();
		}
		key = LabInputKey();

	}
	LabTerm();
	return 0;
}




