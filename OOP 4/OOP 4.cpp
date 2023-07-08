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

	//Цвета ручек для рисования
	HPEN PenGreen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	HPEN PenRed = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN PenBlue = CreatePen(PS_SOLID, 3, RGB(0, 0, 200));
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(242, 242, 242));
	HPEN PenGray = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));

	//Цвета ручек для рисования
	HBRUSH BrushGreen = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH BrushRed = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH BrushBlue = CreateSolidBrush(RGB(0, 0, 200));
	HBRUSH BrushWhite = CreateSolidBrush(RGB(242, 242, 242));
	HBRUSH BrushGray = CreateSolidBrush(RGB(120, 120, 120));

	vertical_Tower_1 green_tw_1(400, 200, PenGray, BrushGreen);
	vertical_Tower_2 green_tw_2(600, 200, PenGray, BrushGreen);
	left_construction_Tower cons_tw_1(200, 400, PenGray, BrushBlue);
	right_construction_Tower cons_tw_2(400, 400, PenGray, BrushBlue);
	addition niol(200, 400, PenGray, BrushGreen);
	Plane aircraft(200, 200, PenGray, BrushRed);

	//Создание препятствий
	upgraded_ball bill_1(200, 200, PenGray, BrushRed, 10);
	upgraded_ball bill_2(1000, 550, PenGray, BrushRed, 40);
	upgraded_ball bill_3(700, 500, PenGray, BrushRed, 30);
	upgraded_ball bill_4(300, 600, PenGray, BrushRed, 20);
	upgraded_ball bill_5(800, 100, PenGray, BrushRed, 50);
	upgraded_ball bill_6(60, 500, PenGreen, BrushGreen, 15);
	bill_1.set_visible(PenGray, BrushRed);
	bill_2.set_visible(PenGray, BrushRed);
	bill_3.set_visible(PenGray, BrushRed);
	bill_4.set_visible(PenGray, BrushRed);
	bill_4.set_visible(PenGray, BrushRed);
	bill_5.set_visible(PenGray, BrushRed);
	bill_6.set_visible(PenGreen, BrushGreen);

	//Массив указателей на башни для определения коллизий
	vector <Tower*> Tow(6);
	Tow[0] = &green_tw_1;
	Tow[1] = &green_tw_2;
	Tow[2] = &cons_tw_1;
	Tow[3] = &cons_tw_2;
	Tow[4] = &niol;
	Tow[5] = &aircraft;

	//Массив указателей на бомбы для определения коллизий
	vector <ball*> BALL(6);
	BALL[0] = &bill_1;
	BALL[1] = &bill_2;
	BALL[2] = &bill_3;
	BALL[3] = &bill_4;
	BALL[4] = &bill_5;
	BALL[5] = &bill_6;

	//Матрица перехода
	Tower* collisions[6][6] =
	{
		{
			new vertical_Tower_1(green_tw_1.Get_X(),green_tw_1.Get_Y(), PenGray, BrushGreen),		//КБ с прямоугольной крышей и лестницей
			new vertical_Tower_1(1000, 1000,PenWhite, BrushWhite),
			new Tower(cons_tw_1.Get_X(),cons_tw_1.Get_Y(), PenGray, BrushRed),
			new vertical_Tower_2(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushBlue),
			new addition(cons_tw_1.Get_X(),cons_tw_1.Get_Y(), PenGray, BrushRed),
			new Plane(cons_tw_1.Get_X(), cons_tw_1.Get_Y(), PenGray, BrushGreen)
		},									//Уничтоженная башня
		{
			new vertical_Tower_2(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushRed),		//КБ с правой и левой пристройкой,прямоугольной крышей, лестницей 
			new vertical_Tower_1(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushRed),
			new addition(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushRed),
			new vertical_Tower_2(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushBlue),
			new Tower(cons_tw_1.Get_X(),cons_tw_1.Get_Y(), PenGray, BrushRed),
			new Plane(green_tw_2.Get_X(), green_tw_2.Get_Y(), PenGray, BrushGreen)
		},		//КБ без пристройки с прямоугольной крышей и лестницей
		{
			new left_construction_Tower(cons_tw_1.Get_X(),cons_tw_1.Get_Y(), PenGray, BrushRed),	//КБ с левой пристройкой и треугольной крышей
			new vertical_Tower_1(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushRed),
			new right_construction_Tower(cons_tw_2.Get_X(),cons_tw_2.Get_Y(), PenGray, BrushRed),	//КБ с правой пристройкой и треугольной крышей
			new vertical_Tower_2(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushBlue),
			new addition(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushRed),
			new Plane(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushGreen)
		},		//КБ без пристройки с треугольной крышей
		{
			new right_construction_Tower(cons_tw_2.Get_X(),cons_tw_2.Get_Y(), PenGray, BrushRed),	//КБ с правой пристройкой и треугольной крышей
			new vertical_Tower_1(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushRed),
			new left_construction_Tower(cons_tw_1.Get_X(),cons_tw_1.Get_Y(), PenGray, BrushRed),	//КБ с левой пристройкой и треугольной крышей
			new vertical_Tower_2(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushBlue),
			new addition(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushRed),
			new Plane(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushGreen)
		},		//КБ без пристройки и треугольной крышей
		{
			new right_construction_Tower(cons_tw_2.Get_X(),cons_tw_2.Get_Y(),PenGray, BrushRed),	//КБ с правой пристройкой и треугольной крышей
			new vertical_Tower_1(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushRed),
			new left_construction_Tower(cons_tw_1.Get_X(),cons_tw_1.Get_Y(), PenGray, BrushRed),	//КБ с левой пристройкой и треугольной крышей
			new Tower(cons_tw_2.Get_X(),cons_tw_2.Get_Y(), PenGray, BrushRed),
			new addition(green_tw_2.Get_X(),green_tw_2.Get_Y(),PenGray, BrushRed),
			new Plane(green_tw_2.Get_X(),green_tw_2.Get_Y(), PenGray, BrushGreen)
		},
		{
			new right_construction_Tower(aircraft.Get_X(),aircraft.Get_Y(), PenGray, BrushGreen),	//КБ с правой пристройкой и треугольной крышей
			new vertical_Tower_1(aircraft.Get_X(),aircraft.Get_Y(), PenGray, BrushGreen),
			new left_construction_Tower(aircraft.Get_X(),aircraft.Get_Y(), PenGray, BrushGreen),	//КБ с левой пристройкой и треугольной крышей
			new Tower(aircraft.Get_X(),aircraft.Get_Y(), PenGray, BrushGreen),
			new addition(aircraft.Get_X(),aircraft.Get_Y(), PenGray, BrushGreen),
			new Plane(aircraft.Get_X(),aircraft.Get_Y(), PenGray, BrushGreen)	//КБ с левой пристройкой и треугольной крышей
		}
	};

	Point* Pcur;//Указатель на текущий элемент

	Sleep(1000);
	int i = 0;
	Drag(i, Pcur, Tow, BALL, collisions);	//Буксировка неизмененной фигуры

	DeleteObject(Pen);

	return 0;
}