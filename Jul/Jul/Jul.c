#include "labengine.h"
#include <stdio.h>
#include <math.h>
#define PI 3.1415926

typedef struct {
	double x;
	double y;
} point_t;

typedef struct {
	point_t a;
	point_t b;
} rect_t;

typedef struct {
	int r;
	int g;
	int b;
} color_t;

point_t Transform(point_t p, rect_t const* rect_from, rect_t const* rect_to) {
	double window_point_x = (p.x - rect_from[0].a.x) * (rect_to[0].b.x - rect_to[0].a.x) / (rect_from[0].b.x - rect_from[0].a.x) + rect_to[0].a.x;
	double window_point_y = (p.y - rect_from[0].a.y) * (rect_to[0].b.y - rect_to[0].a.y) / (rect_from[0].b.y - rect_from[0].a.y) + rect_to[0].a.y;
	point_t window_point = { window_point_x,window_point_y };
	return window_point;
}


color_t ColorizeDisk(point_t p, void* radius) {
	color_t color = { 0,0,0 };
	if (p.x * p.x + p.y * p.y <= 1) {
		color.r = 255;
		color.g = 255;
		color.b = 255;
	}
	return color;
}

color_t ColorizeJulia(point_t p, void *data){
	double MaxN = 100;
	int MaxRad = 2;
	char IsBiggerRad = 0;
	double x;
	double y;
	point_t *c = (point_t*)data;
	color_t color = { 255,255,255 };
	for (double i = 0; i < MaxN; i++) {
		x = p.x * p.x - p.y * p.y + c[0].x;
		y = 2 * p.x * p.y + c[0].y;
		p.x = x;
		p.y = y;
		if (p.x*p.x+p.y*p.y >2 || i == 99)
		{
			color.r = 255 * i / MaxN;
			color.g = 255 * (1 -  i / MaxN);
			if (1 <= sqrt(p.x * p.x + p.y * p.y / MaxRad)) {
				color.b = 255;
			}
			else {
				color.b = sqrt(p.x * p.x + p.y * p.y / MaxRad) * 255;
				
			}
			break;
		}
	}
	return color;
}
void DrawAxes(rect_t const *rect_from, rect_t const *rect_to){
	point_t center_math = { 0,0 };
	point_t center_wind = Transform(center_math, rect_from,rect_to);
	LabDrawLine(center_wind.x,rect_to[0].a.y,center_wind.x,rect_to[0].b.y);
	LabDrawLine(rect_to[0].a.x, center_wind.y, rect_to[0].b.x, center_wind.y);
}

void DrawDisk(rect_t const* math, rect_t const *screen, color_t (*getColor)(point_t, void*), void *fn_data){
	color_t color;
	point_t point_math,point_wind;
	for (int i = 0; i < screen[0].b.x;i++) {
		for (int j = 0; j < screen[0].b.y; j++) {
			point_wind.x = i;
			point_wind.y = j;
			point_math = Transform(point_wind,screen,math);
			color = getColor(point_math, fn_data);
			LabSetColorRGB(color.r,color.g,color.b);
			LabDrawPoint(i,j);
		}
	}
}

void DrawJulia(rect_t const* math, rect_t const* screen, color_t(*getColor)(point_t, void*), void* fn_data) {
	color_t color;
	point_t point_math, point_wind;
	for (int i = screen[0].a.x; i < screen[0].b.x; i++) {
		for (int j = screen[0].a.y; j < screen[0].b.y; j++) {
			point_wind.x = i;
			point_wind.y = j;
			point_math = Transform(point_wind, screen, math);
			color = getColor(point_math, fn_data);
			LabSetColorRGB(color.r, color.g, color.b);
			LabDrawPoint(i, j);
		}
	}
}

void DrawCircle(int window, int height, int radius) {
	rect_t math_rect = { {-2,3},{2,-3} };
	rect_t wind_rect = { {0,0},{window / 2,height} };
	DrawDisk(&math_rect, &wind_rect, ColorizeDisk, &radius);
	LabSetColor(LABCOLOR_WHITE);
	DrawAxes(&math_rect, &wind_rect);
}
int main() {

	if (!(LabInit())) {
		printf("Error while initialisation");
		return 1;
	}
	point_t c = {-0.12375, 0.56508 };
	int radius = 1;
	int height = LabGetHeight();
	int window = LabGetWidth();
	double alpha = 0;
	rect_t math_rect = { {-2,3},{2,-3} };
	rect_t wind_rect = { {window/2,0},{window,height} };
	DrawCircle(window, height, radius);
	while (1)
	{
		c.x = 0.32 * sin(alpha);
		c.y = 0.32 - 0.32 * cos(alpha);
		DrawJulia(&math_rect, &wind_rect, ColorizeJulia, &c);
		LabSetColor(LABCOLOR_WHITE);
		DrawAxes(&math_rect, &wind_rect);
		LabDrawFlush();
		alpha += 0.2;
	}

	LabInputKey();

	LabTerm();

	return 0;
}