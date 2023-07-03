#pragma once
#include "includes.h"

using namespace std;

//Интерфейс с чистыми виртуальными функциями
class Interface
{
public:
	virtual void set_visible(HPEN color) = 0;	//Отображение объекта
	virtual void set_invisible() = 0;			//Исчезновение объекта
	virtual void print_build() = 0;				//Отображение основной части объекта
	virtual void print_roof_build() = 0;		//Отображение "крыши" объекта
	virtual void print_sub_build() = 0;			//Отображение пристройки объекта
};

//Абстрактный класс "точка" с чистой ВФ
class Point :public Interface
{
protected:
	int X;	//Координата X
	int Y;	//Координата Y

	HPEN pen;//Ручка

	//Хитбоксы
	struct heat_box
	{
		int start_X, end_X, start_Y, end_Y;	//Координаты фигуры(В форме квадрата)
	} boxheat;

public:
	//КОНСТРУКТОР
	Point(int ind_X, int ind_Y, HPEN color) :Interface()
	{
		X = ind_X;
		Y = ind_Y;
		pen = color;
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

	//Делает видимой точку
	void set_visible(HPEN color);

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
	ball(int X, int Y, HPEN color, int Rad) :Point(X, Y, color) { radius = Rad; };

	void print_build();						//Рисование ядра

	void set_rad(int Rad) { radius = Rad; };//Установить радиус ядра
	int get_rad() { return radius; };		//Получить радиус ядра

	//Запоминает местоположение фигуры
	void current_region(int X, int Y);

	void set_visible(HPEN color);			//Отображаение объекта

	void set_invisible();					//Исчезновение объекта
};

//Улучшенное ядро
class upgraded_ball : public ball
{
public:
	//Конструктор
	upgraded_ball(int X, int Y, HPEN color, int Rad) : ball(X, Y, color, Rad) {};

	void print_sub_build();				//Отображение подобъекта

	void print_roof_build();			//Отображение верхушки объекта

	void current_region(int X, int Y);	//Отобразить хитбоксы

	void set_visible(HPEN color);		//Отображаение объекта

	void set_invisible();				//Исчезновение объекта
};

//Класс фигура (Башня)
class Tower :public Point
{
public:
	Tower(int X, int Y, HPEN color) :Point(X, Y, color) {};

	void current_region(int X, int Y);

	//Делает видимым объект
	void set_visible(HPEN color);

	//Делает невидимым объект
	void set_invisible();

	//Отображение основы башни
	void print_build();

	//Отображение "крыши" объекта
	void print_roof_build();

	//Отображение пристройки
	void print_sub_build();
};

//Класс Самолет для ПРАКТИКИ
class Plane :public Tower
{
public:
	Plane(int X, int Y, HPEN color) :Tower(X, Y, color) {};

	void current_region(int X, int Y);

	//Делает видимым объект
	void set_visible(HPEN color);

	//Делает невидимым объект
	void set_invisible();

	void print_build();

	void print_roof_build();

	void print_sub_build();
};

//Вертикальная иерархия 1
class vertical_Tower_1 :public Tower
{
public:
	//Конструктор
	vertical_Tower_1(int X, int Y, HPEN color) :Tower(X, Y, color) {};

	//Основание башни с лестницей
	void print_build();

	//Пристройка
	void print_sub_build();

	//Башня
	void print_roof_build();

	//Текущее местоположение
	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color);

	//Делает невидимой башню
	void set_invisible();
};

//Вертикальная иерархия 2
class vertical_Tower_2 :public vertical_Tower_1
{
public:
	//Конструктор
	vertical_Tower_2(int X, int Y, HPEN color) :vertical_Tower_1(X, Y, color) {};

	//Пристройка
	void print_sub_build();

	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color);

	//Делает невидимой башню
	void set_invisible();
};

//Веерная иерархия 1 (Левая пристройка)
class left_construction_Tower : public Tower
{
public:
	//Конструктор
	left_construction_Tower(int X, int Y, HPEN color) :Tower(X, Y, color) {};

	//Левая пристройка
	void print_sub_build();

	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color);

	//Делает невидимой башню
	void set_invisible();
};

//Доп задание
class addition : public left_construction_Tower
{
public:
	addition(int X, int Y, HPEN color) : left_construction_Tower(X, Y, color) {};

	void print_roof_build();

	//Делает видимой башню
	void set_visible(HPEN color);

	//Делает невидимой башню
	void set_invisible();
};

//Веерная иерархия 2
class right_construction_Tower : public Tower
{
public:
	//Конструктор
	right_construction_Tower(int X, int Y, HPEN color) :Tower(X, Y, color) {};

	//Правая конструкция
	void print_sub_build();

	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color);

	//Делает невидимой башню
	void set_invisible();
};