#pragma once
#include"screen.h"
#include <list>




struct shape { // ����������� ������� ����� "������"
	static std::list<shape*> shapes;// ������ ����� (���� �� ��� ������!)
	shape() { shapes.push_back(this); } //������ �������������� � ������
	virtual point north() const = 0;	//����� ��� ��������
	virtual point south() const = 0;
	virtual point east() const = 0;
	virtual point west() const = 0;
	virtual point neast() const = 0;
	virtual point seast() const = 0;
	virtual point nwest() const = 0;
	virtual point swest() const = 0;
	virtual point centre() const = 0;
	virtual void draw() = 0;		//���������
	virtual void move(int, int) = 0;	//�����������
	virtual void resize(double) = 0;    	//��������� �������
	//virtual ~shape() { shapes.erase(shapes.); } //����������
};


std::list<shape*>shape::shapes;//���������� ������ �����

void shape_refresh()//����������� ���� ����� �� ������
{
	screen_clear();
	for (auto p : shape::shapes)
		p->draw();
	screen_refresh();
}

class rotatable : virtual public shape
{
public:
	virtual void rotate_left() = 0;
	virtual void rotate_right() = 0;
};

class reflectable : virtual public shape
{
public:
	virtual void flip_horisontally() = 0;
	virtual void flip_vertically() = 0;
};
class line : public shape {
	/* ������� ������ ["w", "e"].
	   north( ) ���������� ����� "���� ������ ������� � ��� ������
	   �� �����, ��� ����� ��� �������� �����", � �. �. */
protected:
	point w, e;
public:
	line(point a, point b) : w(a), e(b) { }; //������������ ����� (�� ���� ������)
	line(point a, int L) : w(point(a.x + L - 1, a.y)), e(a) {  }; //�������������� �����
	point north() const { return point((w.x + e.x) / 2, e.y < w.y ? w.y : e.y); }
	point south() const { return point((w.x + e.x) / 2, e.y < w.y ? e.y : w.y); }
	point east() const { return point(e.x < w.x ? w.x : e.x, (w.y + e.y) / 2); }
	point west() const { return point(e.x < w.x ? e.x : w.x, (w.y + e.y) / 2); }
	point neast() const { return point(w.x < e.x ? e.x : w.x, e.y < w.y ? w.y : e.y); }
	point seast() const { return point(w.x < e.x ? e.x : w.x, e.y < w.y ? e.y : w.y); }
	point nwest() const { return point(w.x < e.x ? w.x : e.x, e.y < w.y ? w.y : e.y); }
	point swest() const { return point(w.x < e.x ? w.x : e.x, e.y < w.y ? e.y : w.y); }
	point centre() const { return point(w.x < e.x ? w.x - e.x : e.x - w.x, e.y < w.y ? w.y - e.y : e.y - w.y); };
	void move(int a, int b) { w.x += a; w.y += b; e.x += a; e.y += b; }
	void draw() { put_line(w, e); }
	void resize(double d) // ��������� ����� ����� � (d) ���
	{
		e.x = w.x + (e.x - w.x) * d; e.y = w.y + (e.y - w.y) * d;
	}

};


class rectangle : public rotatable {
	/* nw ------ n ------ ne
	   |		       |
	   |		       |
	   w	   c            e
	   |		       |
	   |		       |
	   sw ------- s ------ se */
protected:
	point sw, ne;
public:
	rectangle(point a, point b) : sw(a), ne(b) { }
	point north() const { return point((sw.x + ne.x) / 2, ne.y); }
	point south() const { return point((sw.x + ne.x) / 2, sw.y); }
	point east() const { return point(ne.x, (sw.y + ne.y) / 2); }
	point west() const { return point(sw.x, (sw.y + ne.y) / 2); }
	point neast() const { return ne; }
	point seast() const { return point(ne.x, sw.y); }
	point nwest() const { return point(sw.x, ne.y); }
	point swest() const { return sw; }
	point centre() const { return point(south().x, west().y); }
	void rotate_right() // ������� ������ ������������ se
	{
		int w = ne.x - sw.x, h = ne.y - sw.y; //(����������� ������� �� ����)
		sw.x = ne.x - h*2; ne.y = sw.y + w/2;
	}
	void rotate_left() // ������� ����� ������������ sw
	{
		int w = ne.x - sw.x, h = ne.y - sw.y;
		ne.x = sw.x + h * 2; ne.y = sw.y + w / 2;
	}
	void move(int a, int b)
	{
		sw.x += a; sw.y += b; ne.x += a; ne.y += b;
	}
	void resize(double d)
	{
		ne.x = sw.x + (ne.x - sw.x) * d; ne.y = sw.y + (ne.y - sw.y) * d;
	}
	void draw()
	{
		put_line(nwest(), ne);   put_line(ne, seast());
		put_line(seast(), sw);   put_line(sw, nwest());
	}
};




void up(shape& p, const shape& q) // ��������� p ��� q
{	//��� ������� �������, �� ���� ������! ������������ ����������!!
	point n = q.north();
	point s = p.south();
	p.move(n.x - s.x, n.y - s.y + 1);
}
