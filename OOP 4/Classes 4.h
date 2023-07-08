#pragma once
#include "includes.h"

using namespace std;

//��������� � ������� ������������ ���������
class Interface
{
public:
	virtual void set_visible(HPEN color, HBRUSH color_br) = 0;		//����������� �������
	virtual void set_invisible() = 0;								//������������ �������
	virtual void print_build(HPEN color, HBRUSH color_br) = 0;		//����������� �������� ����� �������
	virtual void print_roof_build(HPEN color, HBRUSH color_br) = 0;	//����������� "�����" �������
	virtual void print_sub_build(HPEN color, HBRUSH color_br) = 0;	//����������� ���������� �������
};

//����������� ����� "�����" � ������ ��
class Point :public Interface
{
protected:
	int X;	//���������� X
	int Y;	//���������� Y

	HPEN pen;		//�����
	HBRUSH brush;	//�����

	//��������
	struct heat_box
	{
		int start_X, end_X, start_Y, end_Y;	//���������� ������(� ����� ��������)
	} boxheat;

public:
	//�����������
	Point(int ind_X, int ind_Y, HPEN color, HBRUSH color_br) :Interface()
	{
		X = ind_X;
		Y = ind_Y;
		pen = color;
		brush = color_br;
		boxheat.start_X = X;
		boxheat.end_X = X + 1;
		boxheat.start_Y = Y;
		boxheat.end_Y = Y + 1;
	};

	//���������� X
	int Get_X() { return X; };

	//���������� Y
	int Get_Y() { return Y; }

	//������������� X
	void Set_X(int ind_X) { X = ind_X; };

	//������������� Y
	void Set_Y(int ind_Y) { Y = ind_Y; };

	//���������� ��������
	const heat_box& get() { return boxheat; }

	//���������� ���� �����
	HPEN pen_color() { return pen; }

	//���������� ���� �����
	HBRUSH Brush_color() { return brush; }

	//������ ������� �����
	void set_visible(HPEN color, HBRUSH color_br);

	//������ ��������� �����
	void set_invisible();

	//������� ������� ������ (������ ��)
	virtual void current_region(int X, int Y) = 0;

	//���������� �����
	void Move_To(int X, int Y);
};

//����� ����
class ball :public Point
{
protected:
	int radius;								//������ ����
public:
	//�����������
	ball(int X, int Y, HPEN color, HBRUSH color_br, int Rad) :Point(X, Y, color, color_br) { radius = Rad; };

	void print_build(HPEN color, HBRUSH color_br);	//��������� ����

	void set_rad(int Rad) { radius = Rad; };		//���������� ������ ����
	int get_rad() { return radius; };				//�������� ������ ����

	//���������� �������������� ������
	void current_region(int X, int Y);

	void set_visible(HPEN color, HBRUSH color_br);	//������������ �������

	void set_invisible();							//������������ �������
};

//���������� ����
class upgraded_ball : public ball
{
public:
	//�����������
	upgraded_ball(int X, int Y, HPEN color, HBRUSH color_br, int Rad) : ball(X, Y, color, color_br, Rad) {};

	void print_sub_build(HPEN color, HBRUSH color_br);	//����������� ����������

	void print_roof_build(HPEN color, HBRUSH color_br);	//����������� �������� �������

	void current_region(int X, int Y);	//���������� ��������

	void set_visible(HPEN color, HBRUSH color_br);		//������������ �������

	void set_invisible();				//������������ �������
};

//����� ������ (�����)
class Tower :public Point
{
public:
	Tower(int X, int Y, HPEN color, HBRUSH color_br) :Point(X, Y, color, color_br) {};

	void current_region(int X, int Y);

	//������ ������� ������
	void set_visible(HPEN color, HBRUSH color_br);

	//������ ��������� ������
	void set_invisible();

	//����������� ������ �����
	void print_build(HPEN color, HBRUSH color_br);

	//����������� "�����" �������
	void print_roof_build(HPEN color, HBRUSH color_br);

	//����������� ����������
	void print_sub_build(HPEN color, HBRUSH color_br);
};

//����� ������� ��� ��������
class Plane :public Tower
{
public:
	Plane(int X, int Y, HPEN color, HBRUSH color_br) :Tower(X, Y, color, color_br) {};

	void current_region(int X, int Y);

	//������ ������� ������
	void set_visible(HPEN color, HBRUSH color_br);

	//������ ��������� ������
	void set_invisible();

	void print_build(HPEN color, HBRUSH color_br);

	void print_roof_build(HPEN color, HBRUSH color_br);

	void print_sub_build(HPEN color, HBRUSH color_br);
};

//������������ �������� 1
class vertical_Tower_1 :public Tower
{
public:
	//�����������
	vertical_Tower_1(int X, int Y, HPEN color, HBRUSH color_br) :Tower(X, Y, color, color_br) {};

	//��������� ����� � ���������
	void print_build(HPEN colo, HBRUSH color_br);

	//����������
	void print_sub_build(HPEN color, HBRUSH color_br);

	//�����
	void print_roof_build(HPEN color, HBRUSH color_br);

	//������� ��������������
	void current_region(int X, int Y);

	//������ ������� �����
	void set_visible(HPEN color, HBRUSH color_br);

	//������ ��������� �����
	void set_invisible();
};

//������������ �������� 2
class vertical_Tower_2 :public vertical_Tower_1
{
public:
	//�����������
	vertical_Tower_2(int X, int Y, HPEN color, HBRUSH color_br) :vertical_Tower_1(X, Y, color, color_br) {};

	//����������
	void print_sub_build(HPEN color, HBRUSH color_br);

	void current_region(int X, int Y);

	//������ ������� �����
	void set_visible(HPEN color, HBRUSH color_br);

	//������ ��������� �����
	void set_invisible();
};

//������� �������� 1 (����� ����������)
class left_construction_Tower : public Tower
{
public:
	//�����������
	left_construction_Tower(int X, int Y, HPEN color, HBRUSH color_br) :Tower(X, Y, color, color_br) {};

	//����� ����������
	void print_sub_build(HPEN color, HBRUSH color_br);

	void current_region(int X, int Y);

	//������ ������� �����
	void set_visible(HPEN color, HBRUSH color_br);

	//������ ��������� �����
	void set_invisible();
};

//��� �������
class addition : public left_construction_Tower
{
public:
	addition(int X, int Y, HPEN color, HBRUSH color_br) : left_construction_Tower(X, Y, color, color_br) {};

	void print_roof_build(HPEN color, HBRUSH color_br);

	//������ ������� �����
	void set_visible(HPEN color, HBRUSH color_br);

	//������ ��������� �����
	void set_invisible();
};

//������� �������� 2
class right_construction_Tower : public Tower
{
public:
	//�����������
	right_construction_Tower(int X, int Y, HPEN color, HBRUSH color_br) :Tower(X, Y, color, color_br) {};

	//������ �����������
	void print_sub_build(HPEN color, HBRUSH color_br);

	void current_region(int X, int Y);

	//������ ������� �����
	void set_visible(HPEN color, HBRUSH color_br);

	//������ ��������� �����
	void set_invisible();
};