// laba1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include"shape.h"

class h_circle : public rectangle, public reflectable {
	bool reflected;
public:
	h_circle(point a, point b, bool r = true, bool p = true) : rectangle(a, b), reflected(r) { }
	void draw();
	void flip_horisontally() { }; // Отразить горизонтально (пустая функция)
	void flip_vertically() { reflected = !reflected; };	// Отразить вертикально
};

class h_circle1 : public rectangle, public reflectable, public rotatable //наша параша
{
	int quarter1, quarter2;

public:
	h_circle1(point a, int r, int q1 = 1) :
		quarter1(q1 >= 1 && q1 <= 4 ? q1 : 1),
		quarter2(quarter1 <= 3 ? quarter1 + 1 : 1),
		rectangle(point(a.x-r,a.y-r),point(a.x+r,a.y+r)) {}
	void draw();
	void flip_horisontally();
	void flip_vertically();
	void rotate_left();
	void rotate_right();
};

void h_circle1::flip_horisontally()//наша параша
{
	if (quarter1 == 1 && quarter2 == 2)
	{
		quarter1 = 3;
		quarter2 = 4;

	}
	else if (quarter1 == 3 && quarter2 == 4)
	{
		quarter1 = 1;
		quarter2 = 2;
	}
}

void h_circle1::flip_vertically()//наша параша
{
	if (quarter1 == 2 && quarter2 == 3)
	{
		quarter1 = 4;
		quarter2 = 1;

	}
	else if (quarter1 == 4 && quarter2 == 1)
	{
		quarter1 = 2;
		quarter2 = 3;
	}
}
void h_circle1::rotate_left()//наша параша
{
	quarter1 = quarter1 + 1 <= 4 ? quarter1 + 1 : 1;
	quarter2 = quarter2 + 1 <= 4 ? quarter2 + 1 : 1;
}
void h_circle1::rotate_right()//наша параша
{
	quarter1 = quarter1 - 1 >= 1 ? quarter1 - 1 : 4;
	quarter2 = quarter2 - 1 >= 1 ? quarter2 - 1 : 4;
}
void h_circle1::draw()//наша параша
{
	//std::cout << quarter1<<std::endl;
	//std::cout << quarter2;
	int x = 0;
	int y = north().y - centre().y;
	int delta = 1 - 2 * (north().y - centre().y);
	int error = 0;
	while (y >= 0) {
		if(quarter1==1 || quarter2==1)
			put_point(centre().x + x, centre().y + y);
		if(quarter1==4 || quarter2==4)
			put_point(centre().x + x, centre().y - y);
		if(quarter1==2 || quarter2 ==2)
			put_point(centre().x - x, centre().y + y);
		if(quarter1 ==3 || quarter2 == 3)
			put_point(centre().x - x, centre().y - y);
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
	if(quarter1==1 && quarter2==2 || quarter1==3 && quarter2==4)
	put_line(west(),east());
	if(quarter1 == 2 && quarter2 == 3 || quarter1 == 4 && quarter2 == 1)
	put_line(north(), south());
}

void h_circle::draw() //Алгоритм Брезенхэма для окружностей
{   //(выдаются два сектора, указываемые значением reflected)
	int x0 = (sw.x + ne.x) / 2, y0 = reflected ? sw.y : ne.y;
	int radius = (ne.x - sw.x) / 2;
	int x = 0, y = radius, delta = 2 - 2 * radius, error = 0;
	while (y >= 0) { // Цикл рисования
		if (reflected) { put_point(x0 + x, y0 + y * 0.7); put_point(x0 - x, y0 + y * 0.7); }
		else { put_point(x0 + x, y0 - y * 0.7); put_point(x0 - x, y0 - y * 0.7); }
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) { ++x; delta += 2 * x + 1; continue; }
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) { --y; delta += 1 - 2 * y; continue; }
		++x; delta += 2 * (x - y);  --y;
	}
	
}


// ПРИМЕР ДОБАВКИ: дополнительная функция присоединения…
void down(shape& p, const shape& q)
{
	point n = q.south();
	point s = p.north();
	p.move(n.x - s.x, n.y - s.y - 1);
}

void sw(shape& p, const shape& q)//наша параша
{
	point c = p.centre();
	point w = q.swest();
	p.move(w.x - c.x, w.y - c.y - 1);
	
}
void se(shape& p, const shape& q)//наша параша
{
	point c = p.centre();
	point w = q.seast();
	p.move(w.x - c.x, w.y - c.y - 1);
}

void w(shape& p, const shape& q)//наша параша
{
	point c = p.south();
	point w = q.west();
	p.move(w.x - c.x, w.y - c.y);
}
void e(shape& p, const shape& q)//наша параша
{
	point c = p.south();
	point w = q.seast();
	p.move(w.x - c.x, w.y - c.y);
}




// Cборная пользовательская фигура - физиономия
class myshape : public rectangle { // Моя фигура ЯВЛЯЕТСЯ
	int w, h;			             //        прямоугольником
	line l_eye; // левый глаз – моя фигура СОДЕРЖИТ линию
	line r_eye; // правый глаз
	line mouth; // рот
public:
	myshape(point, point);
	void draw();
	void move(int, int);
	void resize(double) { }
};
myshape::myshape(point a, point b)
	: rectangle(a, b),	//Инициализация базового класса
	w(neast().x - swest().x + 1), // Инициализация данных
	h(neast().y - swest().y + 1), // - строго в порядке объявления!
	l_eye(point(swest().x + 2, swest().y + h * 3 / 4), 2),
	r_eye(point(swest().x + w - 4, swest().y + h * 3 / 4), 2),
	mouth(point(swest().x + 2, swest().y + h / 4), w - 4)
{ }
void myshape::draw()
{
	rectangle::draw(); //Контур лица (глаза и нос рисуются сами!) 
	int a = (swest().x + neast().x) / 2;
	int b = (swest().y + neast().y) / 2;
	put_point(point(a, b)); // Нос – существует только на рисунке!
}

void myshape::move(int a, int b)
{
	rectangle::move(a, b);
	l_eye.move(a, b);  r_eye.move(a, b);
	mouth.move(a, b);
}


int main()
{
	setlocale(LC_ALL, "Rus");
	screen_init();
	//== 1.Объявление набора фигур ==
	rectangle hat(point(0, 0), point(14, 5));
	line brim(point(0, 15), 17);
	myshape face(point(50, 10), point(62, 18));
	h_circle beard(point(35, 10), point(45,10));

	h_circle1 whiskers_r(point(27,12),2,1);
	h_circle1 whiskers_l(point(15,12),2,4);

	h_circle1 horn_r(point(32,23),3,1);
	h_circle1 horn_l(point(10,23),3,1);
	

	//h_circle horn_r(point(30,10),point(30,20));
	shape_refresh();
	std::cout << "=== Generated... ===\n";
	std::cin.get(); //Смотреть исходный набор



//== 2.Подготовка к сборке ==
	hat.rotate_right();
	brim.resize(2.0);
	face.resize(2.0);
	beard.flip_vertically();
	
	whiskers_r.flip_horisontally();
	whiskers_l.flip_vertically();
	horn_l.rotate_left();
	horn_r.rotate_right();

	shape_refresh();
	std::cout << "=== Prepared... ===\n";
	std::cin.get(); //Смотреть результат поворотов/отражений



//== 3.Сборка изображения ==
//	face.move(0, -10); // Лицо - в исходное положение
	up(brim, face);
	up(hat, brim);
	down(beard, face);
	se(whiskers_r,face);
	sw(whiskers_l,face);
	e(horn_r,brim);
	w(horn_l,brim);
	whiskers_r.rotate_left();
	shape_refresh();
	std::cout << "=== Ready! ===\n";
	std::cin.get(); //Смотреть результат
	screen_destroy();
	return 0;
}


/*int main()
{
	setlocale(LC_ALL, "Rus");
	screen_init();

	myshape face(point(15, 10), point(27, 18));
	h_circle1 crug(point (35,47),2,1);
	shape_refresh();
	crug.rotate_left();
	shape_refresh();
	dw(crug, face);

	shape_refresh();
	return 0;
}*/



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
