#include"screen.h"
#include<iostream>
char screen[YMAX][XMAX];
enum color { black = '*', white = '.' };

void put_point(int a, int b)//вывод точки
{
	if (on_screen(a, b))
		screen[b][a] = black;
}
void put_point(point p)
{
	put_point(p.x, p.y);
}
void put_line(int x0, int y0, int x1, int y1)//вывод линии
{
	int dx = 1;
	int a = x1 - x0;
	if (a < 0)
	{
		dx = -1;
		a = -a;
	}
	int dy = 1;
	int b = y1 - y0;
	if (b < 0)
	{
		dy = -1;
		b = -b;
	}
	int two_a = 2 * a;
	int two_b = 2 * b;
	int xcrit = -b + two_a;
	int eps = 0;
	for (;;)
	{
		put_point(x0, y0);
		if (x0 == x1 && y0 == y1)break;
		if (eps <= xcrit)
		{
			x0 += dx;
			eps += two_b;
		}
		if (eps >= a || a < b)
		{
			y0 += dy;
			eps -= two_a;
		}
	}
}
void put_line(point a, point b)
{
	put_line(a.x, a.y, b.x, b.y);
}
void screen_init()//создание экрана
{
	for (auto y = 0; y < YMAX; ++y)
		for (auto& x : screen[y]) x = white;
}
void screen_destroy()//удаление
{
	for (auto y = 0; y < YMAX; ++y)
	{
		for (auto& x : screen[y]) x = black;
	}
}
void screen_refresh()//обновление
{
	for (int y = YMAX - 1; 0 <= y; --y)
	{
		for (auto x : screen[y])
			std::cout << x;
		std::cout << '\n';
	}
}
void screen_clear()//очистка
{
	screen_init();
}


bool on_screen(int a, int b)//проверка попадания точки на экране
{
	return 0 <= a && a < XMAX && 0 <= b && b < YMAX;
}