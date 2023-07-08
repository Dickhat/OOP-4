#pragma once
#include "includes.h"

using namespace std;

//Интерфейс с чистыми виртуальными функциями
class Interface
{
public:
	virtual void set_visible(HPEN color, HBRUSH color_br) = 0;		//Отображение объекта
	virtual void set_invisible() = 0;								//Исчезновение объекта
	virtual void print_build(HPEN color, HBRUSH color_br) = 0;		//Отображение основной части объекта
	virtual void print_roof_build(HPEN color, HBRUSH color_br) = 0;	//Отображение "крыши" объекта
	virtual void print_sub_build(HPEN color, HBRUSH color_br) = 0;	//Отображение пристройки объекта
};

//Абстрактный класс "точка" с чистой ВФ
class Point :public Interface
{
protected:
	int X;	//Координата X
	int Y;	//Координата Y

	HPEN pen;		//Ручка
	HBRUSH brush;	//Кисть

	//Хитбоксы
	struct heat_box
	{
		int start_X, end_X, start_Y, end_Y;	//Координаты фигуры(В форме квадрата)
	} boxheat;

public:
	//КОНСТРУКТОР
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

	//Возвращает X
	int Get_X() { return X; };

	//Возвращает Y
	int Get_Y() { return Y; }

	//Устанавливает X
	void Set_X(int ind_X) { X = ind_X; };

	//Устанавливает Y
	void Set_Y(int ind_Y) { Y = ind_Y; };

	//Возвращает хитбоксы
	const heat_box& get() { return boxheat; }

	//Возвращает цвет ручки
	HPEN pen_color() { return pen; }

	//Возвращает цвет кисти
	HBRUSH Brush_color() { return brush; }

	//Делает видимой точку
	void set_visible(HPEN color, HBRUSH color_br);

	//Делает невидимой точку
	void set_invisible();

	//Текущая область фигуры (Чистая ВФ)
	virtual void current_region(int X, int Y) = 0;

	//Перемещает точку
	void Move_To(int X, int Y);
};

//Класс ядро
class ball :public Point
{
protected:
	int radius;								//Радиус ядра
public:
	//Конструктор
	ball(int X, int Y, HPEN color, HBRUSH color_br, int Rad) :Point(X, Y, color, color_br) { radius = Rad; };

	void print_build(HPEN color, HBRUSH color_br);	//Рисование ядра

	void set_rad(int Rad) { radius = Rad; };		//Установить радиус ядра
	int get_rad() { return radius; };				//Получить радиус ядра

	//Запоминает местоположение фигуры
	void current_region(int X, int Y);

	void set_visible(HPEN color, HBRUSH color_br);	//Отображаение объекта

	void set_invisible();							//Исчезновение объекта
};

//Улучшенное ядро
class upgraded_ball : public ball
{
public:
	//Конструктор
	upgraded_ball(int X, int Y, HPEN color, HBRUSH color_br, int Rad) : ball(X, Y, color, color_br, Rad) {};

	void print_sub_build(HPEN color, HBRUSH color_br);	//Отображение подобъекта

	void print_roof_build(HPEN color, HBRUSH color_br);	//Отображение верхушки объекта

	void current_region(int X, int Y);	//Отобразить хитбоксы

	void set_visible(HPEN color, HBRUSH color_br);		//Отображаение объекта

	void set_invisible();				//Исчезновение объекта
};

//Класс фигура (Башня)
class Tower :public Point
{
public:
	Tower(int X, int Y, HPEN color, HBRUSH color_br) :Point(X, Y, color, color_br) {};

	void current_region(int X, int Y);

	//Делает видимым объект
	void set_visible(HPEN color, HBRUSH color_br);

	//Делает невидимым объект
	void set_invisible();

	//Отображение основы башни
	void print_build(HPEN color, HBRUSH color_br);

	//Отображение "крыши" объекта
	void print_roof_build(HPEN color, HBRUSH color_br);

	//Отображение пристройки
	void print_sub_build(HPEN color, HBRUSH color_br);
};

//Класс Самолет для ПРАКТИКИ
class Plane :public Tower
{
public:
	Plane(int X, int Y, HPEN color, HBRUSH color_br) :Tower(X, Y, color, color_br) {};

	void current_region(int X, int Y);

	//Делает видимым объект
	void set_visible(HPEN color, HBRUSH color_br);

	//Делает невидимым объект
	void set_invisible();

	void print_build(HPEN color, HBRUSH color_br);

	void print_roof_build(HPEN color, HBRUSH color_br);

	void print_sub_build(HPEN color, HBRUSH color_br);
};

//Вертикальная иерархия 1
class vertical_Tower_1 :public Tower
{
public:
	//Конструктор
	vertical_Tower_1(int X, int Y, HPEN color, HBRUSH color_br) :Tower(X, Y, color, color_br) {};

	//Основание башни с лестницей
	void print_build(HPEN colo, HBRUSH color_br);

	//Пристройка
	void print_sub_build(HPEN color, HBRUSH color_br);

	//Башня
	void print_roof_build(HPEN color, HBRUSH color_br);

	//Текущее местоположение
	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color, HBRUSH color_br);

	//Делает невидимой башню
	void set_invisible();
};

//Вертикальная иерархия 2
class vertical_Tower_2 :public vertical_Tower_1
{
public:
	//Конструктор
	vertical_Tower_2(int X, int Y, HPEN color, HBRUSH color_br) :vertical_Tower_1(X, Y, color, color_br) {};

	//Пристройка
	void print_sub_build(HPEN color, HBRUSH color_br);

	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color, HBRUSH color_br);

	//Делает невидимой башню
	void set_invisible();
};

//Веерная иерархия 1 (Левая пристройка)
class left_construction_Tower : public Tower
{
public:
	//Конструктор
	left_construction_Tower(int X, int Y, HPEN color, HBRUSH color_br) :Tower(X, Y, color, color_br) {};

	//Левая пристройка
	void print_sub_build(HPEN color, HBRUSH color_br);

	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color, HBRUSH color_br);

	//Делает невидимой башню
	void set_invisible();
};

//Доп задание
class addition : public left_construction_Tower
{
public:
	addition(int X, int Y, HPEN color, HBRUSH color_br) : left_construction_Tower(X, Y, color, color_br) {};

	void print_roof_build(HPEN color, HBRUSH color_br);

	//Делает видимой башню
	void set_visible(HPEN color, HBRUSH color_br);

	//Делает невидимой башню
	void set_invisible();
};

//Веерная иерархия 2
class right_construction_Tower : public Tower
{
public:
	//Конструктор
	right_construction_Tower(int X, int Y, HPEN color, HBRUSH color_br) :Tower(X, Y, color, color_br) {};

	//Правая конструкция
	void print_sub_build(HPEN color, HBRUSH color_br);

	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color, HBRUSH color_br);

	//Делает невидимой башню
	void set_invisible();
};