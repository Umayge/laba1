#pragma once
#include<iostream>
const int XMAX = 120;
const int YMAX = 50;
class point
{
public:
	int x, y;
	point(int a = 0, int b = 0) :x(a), y(b) {}
};


void put_point(int a, int b);//вывод точки
void put_point(point p);
void put_line(int x0, int y0, int x1, int y1);//вывод линии
void put_line(point a, point b);
void screen_init();//создание экрана
void screen_destroy();//удаление
void screen_refresh();//обновление
void screen_clear();//очистка
bool on_screen(int a, int b);//проверка попадания точки на экране
