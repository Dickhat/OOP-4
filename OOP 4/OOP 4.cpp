#include "classes.h"

HDC hdc;//Контекст устройства(содержит описание видеокарты и всех необходимых графических элементов)

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

HWND GetConcolWindow()
{
	char str[128];
	// char title[128]="xxxxxxxxxxxxxxxxxx";
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";	//новая версия Windows
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str)); // получить заголовок окна
	SetConsoleTitle(title);						// установить новый заголовок окна
	Sleep(100);									// ждем смены заголовка окна (100 мс);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);// определяем дескриптор окна
	SetConsoleTitle((LPWSTR)str);				//возвращаем прежний заголовок

	return hwnd;//вернуть дескриптор окна
}//end GetConcolWindow()

//функция паузы до нажатия кнопки
int PressKey(int VkCode)
{
	while (1)
		if (KEY_DOWN(VkCode))
			return VkCode;
}

//Делает видимой точку
void Point::set_visible(HPEN color)
{
	SetPixel(hdc, X, Y, RGB(255, 0, 0));		//рисуем точку установленным цветом
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));	//рисуем точку установленным цветом
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));	//рисуем точку установленным цветом
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));//рисуем точку установленным цветом
	current_region(X, Y);						//Текущая область фигуры
};

//Делает невидимой точку
void Point::set_invisible()
{
	SetPixel(hdc, X, Y, RGB(0, 0, 0));			//рисуем точку установленным цветом
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 0));		//рисуем точку установленным цветом
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 0));		//рисуем точку установленным цветом
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 0));	//рисуем точку установленным цветом
};

//Перемещает точку
void Point::Move_To(int X, int Y)
{
	set_invisible();
	Set_X(X);
	Set_Y(Y);
	set_visible(pen);
}

//Перетаскивание точки
void Point::Drag()
{
	//while 7 - выход
	while (!KEY_DOWN(55))
	{
		// A - влево
		if (KEY_DOWN(65))
		{
			Move_To(Get_X() - 20, Get_Y());
		}
		// W - вверх
		else if (KEY_DOWN(87))
		{
			Move_To(Get_X(), Get_Y() - 20);
		}
		// D - вправо
		else if (KEY_DOWN(68))
		{
			Move_To(Get_X() + 20, Get_Y());
		}
		// S - Вниз
		else if (KEY_DOWN(83))
		{
			Move_To(Get_X(), Get_Y() + 20);
		}
		Sleep(10);
	}
}

//Рисование ядра
void ball::Paint_ball()
{
	Ellipse(hdc, X - radius, Y - radius, X + radius, Y + radius);
}

//Запоминает местоположение фигуры
void ball::current_region(int X, int Y)
{
	boxheat.start_X = X - radius;
	boxheat.end_X = X + radius;
	boxheat.start_Y = Y + radius;
	boxheat.end_Y = Y - radius;
}

void ball::set_visible(HPEN color)
{
	//HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	//делаем перо активным 
	SelectObject(hdc, color);
	Paint_ball();
	current_region(X, Y);						//Текущая область фигуры

	//DeleteObject(color);
}

void ball::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//делаем перо активным 
	SelectObject(hdc, PenBlack);
	Paint_ball();

	DeleteObject(PenBlack);
}

//Рисование Башни
void Tower::Paint()
{
	//Основание башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 125);
	LineTo(hdc, X + 40, Y + 125);
	LineTo(hdc, X + 40, Y + 80);
	LineTo(hdc, X + 20, Y + 80);
	LineTo(hdc, X + 20, Y + 125);
	LineTo(hdc, X + 40, Y + 125);
	LineTo(hdc, X, Y + 125);
	LineTo(hdc, X, Y);

	//Крыша башни
	LineTo(hdc, X - 30, Y);
	LineTo(hdc, X - 30, Y - 60);
	LineTo(hdc, X - 5, Y - 60);
	LineTo(hdc, X - 5, Y - 30);
	LineTo(hdc, X + 25, Y - 30);
	LineTo(hdc, X + 25, Y - 60);
	LineTo(hdc, X + 50, Y - 60);
	LineTo(hdc, X + 50, Y - 30);
	LineTo(hdc, X + 75, Y - 30);
	LineTo(hdc, X + 75, Y - 30);
	LineTo(hdc, X + 75, Y - 60);
	LineTo(hdc, X + 95, Y - 60);
	LineTo(hdc, X + 95, Y);
	LineTo(hdc, X, Y);
}

void Tower::current_region(int X, int Y)
{
	boxheat.start_X = X - 30;
	boxheat.end_X = X + 95;
	boxheat.start_Y = Y + 125;
	boxheat.end_Y = Y - 60;
};

//Делает видимой точку
void Tower::set_visible(HPEN color)
{
	//HPEN PenRed = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	//делаем перо активным 
	SelectObject(hdc, color);
	Paint();
	current_region(X, Y);

	//DeleteObject(color);
};

//Делает невидимой точку
void Tower::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenBlack = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//делаем перо активным 
	SelectObject(hdc, PenBlack);
	Paint();

	DeleteObject(PenBlack);
};

void vertical_Tower_1::current_region(int X, int Y)
{
	boxheat.start_X = X - 30;
	boxheat.end_X = X + 95;
	boxheat.start_Y = Y + 125;
	boxheat.end_Y = Y - 60;
};

//Делает видимой башню
void vertical_Tower_1::set_visible(HPEN color)
{
	//HPEN PenGreen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	//делаем перо активным 
	SelectObject(hdc, color);
	Paint();
	current_region(X, Y);

	//DeleteObject(color);
};

//Делает невидимой башню
void vertical_Tower_1::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	Paint();
	DeleteObject(PenWhite);
};

//Рисование башни в вертикальной иерархии
void vertical_Tower_2::print_construction()
{
	//Пристройка башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 63);
	LineTo(hdc, X + 150, Y + 63);
	LineTo(hdc, X + 150, Y + 125);
	LineTo(hdc, X + 60, Y + 125);

	//Крыша пристройки
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 35);
	LineTo(hdc, X + 130, Y + 35);
	LineTo(hdc, X + 150, Y + 63);

	//Окно пристройки
	MoveToEx(hdc, X + 100, Y + 100, NULL);
	LineTo(hdc, X + 100, Y + 80);
	LineTo(hdc, X + 100, Y + 80);
	LineTo(hdc, X + 125, Y + 80);
	LineTo(hdc, X + 125, Y + 100);
	LineTo(hdc, X + 100, Y + 100);
	LineTo(hdc, X + 112, Y + 100);
	LineTo(hdc, X + 112, Y + 80);
}

void vertical_Tower_2::current_region(int X, int Y)
{
	boxheat.start_X = X;
	boxheat.end_X = X + 150;
	boxheat.start_Y = Y + 125;
	boxheat.end_Y = Y;
};

//Делает видимой башню в вертикальной иерархии 2
void vertical_Tower_2::set_visible(HPEN color)
{
	//HPEN PenBlue = CreatePen(PS_SOLID, 3, RGB(0, 0, 200));
	//делаем перо активным 
	SelectObject(hdc, color);
	Paint();
	print_construction();
	current_region(X, Y);

	//DeleteObject(color);
};

//Делает невидимой башню в вертикальной иерархии 2
void vertical_Tower_2::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	Paint();
	print_construction();

	DeleteObject(PenWhite);
};

//Левая пристройка в веерной иерархии
void left_construction_Tower::left_print()
{
	//Пристройка башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y + 63);
	LineTo(hdc, X - 90, Y + 63);
	LineTo(hdc, X - 90, Y + 125);
	LineTo(hdc, X, Y + 125);

	//Крыша пристройки
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y + 35);
	LineTo(hdc, X - 70, Y + 35);
	LineTo(hdc, X - 90, Y + 63);

	//Окно пристройки
	MoveToEx(hdc, X - 40, Y + 100, NULL);
	LineTo(hdc, X - 40, Y + 80);
	LineTo(hdc, X - 40, Y + 80);
	LineTo(hdc, X - 65, Y + 80);
	LineTo(hdc, X - 65, Y + 100);
	LineTo(hdc, X - 40, Y + 100);
	LineTo(hdc, X - 53, Y + 100);
	LineTo(hdc, X - 53, Y + 80);
}

void left_construction_Tower::current_region(int X, int Y)
{
	boxheat.start_X = X - 90;
	boxheat.end_X = X;
	boxheat.start_Y = Y + 125;
	boxheat.end_Y = Y;
};

//Делает видимой левую башню в веерной иерархии
void left_construction_Tower::set_visible(HPEN color)
{
	//HPEN PenGreen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	//делаем перо активным 
	SelectObject(hdc, color);
	Paint();
	left_print();
	current_region(X, Y);

	//DeleteObject(color);
};

//Делает невидимой левую башню в веерной иерархии
void left_construction_Tower::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	Paint();
	left_print();

	DeleteObject(PenWhite);
};

//Правая пристройка
void right_construction_Tower::right_print()
{
	//Пристройка башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 63);
	LineTo(hdc, X + 150, Y + 63);
	LineTo(hdc, X + 150, Y + 125);
	LineTo(hdc, X + 60, Y + 125);

	//Крыша пристройки
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 35);
	LineTo(hdc, X + 130, Y + 35);
	LineTo(hdc, X + 150, Y + 63);

	//Окно пристройки
	MoveToEx(hdc, X + 100, Y + 100, NULL);
	LineTo(hdc, X + 100, Y + 80);
	LineTo(hdc, X + 100, Y + 80);
	LineTo(hdc, X + 125, Y + 80);
	LineTo(hdc, X + 125, Y + 100);
	LineTo(hdc, X + 100, Y + 100);
	LineTo(hdc, X + 112, Y + 100);
	LineTo(hdc, X + 112, Y + 80);
}

void right_construction_Tower::current_region(int X, int Y)
{
	boxheat.start_X = X;
	boxheat.end_X = X + 150;
	boxheat.start_Y = Y + 125;
	boxheat.end_Y = Y;
};

//Делает видимой правую башню в веерной иерархии
void right_construction_Tower::set_visible(HPEN color)
{
	//HPEN PenGreen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	//делаем перо активным 
	SelectObject(hdc, color);
	Paint();
	right_print();
	current_region(X, Y);

	//DeleteObject(color);
};

//Делает невидимой правую башню в веерной иерархии
void right_construction_Tower::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	Paint();
	right_print();

	DeleteObject(PenWhite);
};

//Проверка столкновений
int check(int i, int j, vector <Tower*>& Tow, vector <ball*>& BALL);

int main()
{
	//получим дескриптор консольного окна
	HWND hwnd = GetConcolWindow();
	hdc = GetWindowDC(hwnd);			 // контекст устройства консольного окна

	Tower* Pcur;						//Указатель на текущий элемент

	//Перья и цвета
	HPEN PenGreen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));		//Зеленый
	HPEN PenRed = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));		//Красный
	HPEN PenBlue = CreatePen(PS_SOLID, 3, RGB(0, 0, 200));		//Синий
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));	//Белый
	HPEN PenGray = CreatePen(PS_SOLID, 3, RGB(120, 120, 120));	//Серый

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

	//for использование матрицы перехода
	for (int i = 0; i < Tow.size(); ++i)
	{
		Pcur = Tow[i];									//Указатель на ПК
		Pcur->set_visible(Pcur->pen_color());			//Отображение фигуры
		Sleep(1000);
		Pcur->Drag();									//Буксировка фигуры

		//for Поиск коллизий с шарами
		for (int j = 0; j < BALL.size(); ++j)
		{
			//if Произошла коллизия
			if (check(i, j, Tow, BALL))
			{
				Pcur->set_invisible();					//Убрать старый объект

				//Появление новой фигуры на месте старой
				collisions[i][j]->Move_To(Pcur->Get_X(), Pcur->Get_Y());

				Pcur = collisions[i][j];				//Взять объект из матрицы перехода
				Pcur->set_visible(Pcur->pen_color());	//Отобразить новый объект

				Sleep(1000);

				//if Проверка, что двигаем не пустой объект
				if (i == 0 && j == 1)
					break;

				BALL[0]->set_visible(PenRed);			//Повторная отрисовка шара
				BALL[1]->set_visible(PenRed);			//Повторная отрисовка шара
				
				Pcur->Drag();						//Буксировка фигуры
				break;
			}//if
		}//for

		BALL[0]->set_visible(PenRed);			//Повторная отрисовка шара
		BALL[1]->set_visible(PenRed);			//Повторная отрисовка шара
		Pcur->set_invisible();					//Убрать новый объект
	}//for

	return 0;
}

//Проверка столкновений
int check(int i, int j, vector <Tower*>& Tow, vector <ball*>& BALL)
{

	//if Проверка, что объекты столкнулись
	if (Tow[i]->get().end_X < BALL[j]->get().start_X
		|| Tow[i]->get().start_X > BALL[j]->get().end_X
		|| Tow[i]->get().end_Y > BALL[j]->get().start_Y
		|| Tow[i]->get().start_Y < BALL[j]->get().end_Y)
		return 0;
	else
		return (j + 1);	//Вернуть номер объекта столкновения

};