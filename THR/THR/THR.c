#include "labengine.h"
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#define Pi 3.1415926
typedef struct {
	double x;
	double y;
} point_t;

typedef struct {
	point_t a;
	point_t b;
} rect_t;


point_t Transform(point_t p, rect_t const* rect_from, rect_t const* rect_to) {
	double window_point_x = (p.x - rect_from[0].a.x) * (rect_to[0].b.x - rect_to[0].a.x) / (rect_from[0].b.x - rect_from[0].a.x) + rect_to[0].a.x;
	double window_point_y = (p.y - rect_from[0].a.y) * (rect_to[0].b.y - rect_to[0].a.y) / (rect_from[0].b.y - rect_from[0].a.y) + rect_to[0].a.y;
	point_t window_point = { window_point_x,window_point_y };
	return window_point;
}

void DrawAxes(rect_t const* rect_from, rect_t const* rect_to) {
	point_t center_math = { 0,0 };
	point_t center_wind = Transform(center_math, rect_from, rect_to);
	LabDrawLine(center_wind.x, rect_to[0].a.y, center_wind.x, rect_to[0].b.y);	
	LabDrawLine(rect_to[0].a.x, center_wind.y, rect_to[0].b.x, center_wind.y);
}

void DrawAnalyticalPath(rect_t const* from, rect_t const *to, point_t r0, point_t v0, point_t a0, double dt) {
	LabSetColor(LABCOLOR_GREEN);
	point_t prev = r0;
	double t;
	for (double i = 0; i < -2 * v0.y /a0.y+dt; i += dt) {
		if (i < -2 * v0.y / a0.y) {
			t = i;
		}
		else{
			t = -2 * v0.y / a0.y;
		}
		point_t curr = { r0.x + v0.x * (t), r0.y + v0.y * t + a0.y * (t) * (t) / 2 };
		point_t start_to = Transform(prev, from, to);
		point_t end_to = Transform(curr, from, to);
		prev = curr;
		LabDrawLine(start_to.x,start_to.y, end_to.x, end_to.y);
	}
	
}

void DrawEulerPath(rect_t const *from, rect_t const*to, point_t r0, point_t v0, point_t a0, double dt) {
	LabSetColor(LABCOLOR_RED);
	point_t start_to;
	point_t end_to;
	point_t prev = r0;
	point_t currv = v0;
	point_t curr = r0;
	for (double i = 0; i < -2 * v0.y / a0.y; i += dt) {
		curr.x = curr.x + currv.x * dt;
		curr.y = curr.y + currv.y * dt;
		currv.x = currv.x + a0.x * dt;
		currv.y = currv.y + a0.y * dt;
		start_to = Transform(prev, from, to);
		end_to = Transform(curr, from, to);
		prev = curr;
		LabDrawLine(start_to.x, start_to.y, end_to.x, end_to.y);
	}
}

void SimulateEulerPath(rect_t const* from, rect_t const* to, point_t r0, point_t v0, point_t a0) {
	LabSetColor(LABCOLOR_YELLOW);
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	point_t start_to;
	point_t end_to;
	point_t prev = r0;
	point_t currv = v0;
	point_t curr = r0;
	LARGE_INTEGER currt, prevt;
	double time = 0;
	QueryPerformanceCounter(&prevt);
	while(time <= 3.5){
		QueryPerformanceCounter(&currt);
		double dt = (currt.QuadPart - prevt.QuadPart)/(double)freq.QuadPart;
		curr.x = curr.x + currv.x * dt;
		curr.y = curr.y + currv.y * dt;
		currv.x = currv.x + a0.x * dt;
		currv.y = currv.y + a0.y * dt;
		start_to = Transform(prev, from, to);
		end_to = Transform(curr, from, to);
		prev = curr;
		prevt = currt;
		time += dt;
		LabDrawLine(start_to.x, start_to.y, end_to.x, end_to.y);
		LabDrawFlush();
		
	}

}

int main() {
	if (!LabInit()) {
		return -1;
	}
	rect_t from = { {-3,28}, {41,-5} };
	rect_t to = { {0,0},{LabGetWidth(), LabGetHeight()} };
	DrawAxes(&from, &to);
	point_t r0 = { 0,0 }, v0 = {20.0*cos(Pi/3),20.0 * sin(Pi / 3)}, a0 = {0,-9.8};
	DrawAnalyticalPath(&from, &to, r0, v0, a0, 1);
	DrawEulerPath(&from,&to,r0,v0,a0,1);
	DrawAnalyticalPath(&from,&to, r0, v0, a0, 0.5);
	DrawEulerPath(&from, &to, r0, v0, a0, 0.5);
	SimulateEulerPath(&from,&to,r0,v0,a0);
	LabDrawFlush();


	LabInputKey();

	return 0;
}