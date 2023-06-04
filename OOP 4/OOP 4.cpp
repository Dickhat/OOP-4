#include "support.h"

HDC hdc;//Контекст устройства(содержит описание видеокарты и всех необходимых графических элементов)

int main()
{
	//получим дескриптор консольного окна
	HWND hwnd = GetConcolWindow();
	hdc = GetWindowDC(hwnd);    // контекст устройства консольного окна

	// Зададим перо и цвет пера
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);

	HPEN PenGreen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	HPEN PenRed = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN PenBlue = CreatePen(PS_SOLID, 3, RGB(0, 0, 200));
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	HPEN PenGray = CreatePen(PS_SOLID, 3, RGB(120, 120, 120));

	vertical_Tower_1 green_tw_1(400, 200, PenGreen);
	vertical_Tower_2 green_tw_2(600, 200, PenGreen);

	left_construction_Tower cons_tw_1(200, 400, PenBlue);
	right_construction_Tower cons_tw_2(400, 400, PenGray);

	ball bill_1(200, 200, PenRed, 10);
	ball bill_2(800, 400, PenRed, 40);
	bill_1.set_visible(PenRed);
	bill_2.set_visible(PenRed);

	//Массив указателей для определения коллизий
	vector <Tower*> Tow(4);
	Tow[0] = &green_tw_1;
	Tow[1] = &green_tw_2;
	Tow[2] = &cons_tw_1;
	Tow[3] = &cons_tw_2;

	vector <ball*> BALL(2);
	BALL[0] = &bill_1;
	BALL[1] = &bill_2;

	//Матрица перехода
	Tower* collisions[4][2] =
	{
		{new vertical_Tower_1(green_tw_1.Get_X(),green_tw_1.Get_Y(), PenRed),		//Красная башня
		new vertical_Tower_1(1000, 1000,PenWhite)},									//Уничтоженная башня
		{new vertical_Tower_2(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenRed),		//Красная башня с правой пристройкой 
		new vertical_Tower_1(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenRed)},		//Красная башня без пристройки
		{new left_construction_Tower(cons_tw_1.Get_X(),cons_tw_1.Get_Y(), PenRed),	//Красная башня с левой пристройкой
		new vertical_Tower_1(cons_tw_1.Get_X(),cons_tw_1.Get_Y(), PenRed)},			//Красная башня без пристройки
		{new right_construction_Tower(cons_tw_2.Get_X(),cons_tw_2.Get_Y(), PenRed),	//Красная башня с правой пристройкой
		new vertical_Tower_1(cons_tw_2.Get_X(),cons_tw_2.Get_Y(), PenRed)}			//Красная башня без пристройки
	};

	Point* Pcur;				//Указатель на текущий элемент

	//for использование матрицы перехода
	for (int i = 0; i < Tow.size(); ++i)
	{
		Pcur = Tow[i];							//Указатель на ПК
		Pcur->set_visible(Pcur->pen_color());	//Отображение фигуры
		Sleep(1000);
		Drag(i, Pcur, Tow, BALL, collisions);	//Буксировка неизмененной фигуры

		Pcur->set_invisible();					//Убрать новый объект

		BALL[0]->set_visible(PenRed);			//Повторная отрисовка шара
		BALL[1]->set_visible(PenRed);			//Повторная отрисовка шара
	}//for

	DeleteObject(Pen);

	return 0;
}