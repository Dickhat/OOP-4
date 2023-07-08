#include "classes 4.h"

//макрос для определения кода нажатой клавиши
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

static HWND GetConcolWindow()
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
static void PressKey(int VkCode)
{
	while (1)
		if (KEY_DOWN(VkCode))
			break;
}

//Проверка столкновений
static void check(int& i, Point*& current, std::vector <ball*>& BALL, Tower* collisions[6][6])
{
	//for Проверка столкновения по координатам
	for (int j = 0; j < BALL.size(); ++j)
	{
		//if Проверка, что объекты столкнулись
		if (current->get().end_X < BALL[j]->get().start_X
			|| current->get().start_X > BALL[j]->get().end_X
			|| current->get().end_Y > BALL[j]->get().start_Y
			|| current->get().start_Y < BALL[j]->get().end_Y)
		{
			//Нет столкновения
		}
		else
		{
			current->set_invisible();

			//Появление новой фигуры на месте старой
			collisions[i][j]->Move_To(current->Get_X(), current->Get_Y());

			current = collisions[i][j];				//Взять объект из матрицы 
			i = j;

			current->set_visible(current->pen_color(), current->Brush_color());
		}
	}
};

//Буксировка фигуры current
static void Drag(int& i, Point*& current, std::vector <Tower*>& Tow, std::vector <ball*>& BALL, Tower* collisions[6][6])
{
	current = Tow[i];				//Указатель на Базовый класс Tower

	//while 7 - выход
	while (!KEY_DOWN(55))
	{
		// A - влево
		if (KEY_DOWN(65))
		{
			current->Move_To(current->Get_X() - 20, current->Get_Y());

			check(i, current, BALL, collisions);	//Проверка столкновения
		}
		// W - вверх
		else if (KEY_DOWN(87))
		{
			current->Move_To(current->Get_X(), current->Get_Y() - 20);

			check(i, current, BALL, collisions);	//Проверка столкновения
		}
		// D - вправо
		else if (KEY_DOWN(68))
		{
			current->Move_To(current->Get_X() + 20, current->Get_Y());
			check(i, current, BALL, collisions);	//Проверка столкновения

		}
		// S - Вниз
		else if (KEY_DOWN(83))
		{
			current->Move_To(current->Get_X(), current->Get_Y() + 20);
			check(i, current, BALL, collisions);	//Проверка столкновения
		}

		//for Отрисовка всех шаров
		for (int i = 0; i < BALL.size(); i++)
		{
			BALL[i]->set_visible(BALL[i]->pen_color(), BALL[i]->Brush_color());
		}

		Sleep(1);
	}
}
