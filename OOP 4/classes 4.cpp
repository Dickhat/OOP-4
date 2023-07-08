#include "classes 4.h"

extern HDC hdc;//Контекст устройства(содержит описание видеокарты и всех необходимых графических элементов)

//Делает видимой точку
void Point::set_visible(HPEN color, HBRUSH color_br)
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
}

//Перемещает точку
void Point::Move_To(int X, int Y)
{
	set_invisible();
	Set_X(X);
	Set_Y(Y);
	set_visible(pen, brush);
}

//Рисование ядра
void ball::print_build(HPEN color, HBRUSH color_br)
{
	BeginPath(hdc);
	SelectObject(hdc, color_br);

	Ellipse(hdc, X - radius, Y - radius, X + radius, Y + radius);

	EndPath(hdc);
	FillPath(hdc);

	SelectObject(hdc, color);
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

//Отображение ядра
void ball::set_visible(HPEN color, HBRUSH color_br)
{
	//делаем перо активным 
	SelectObject(hdc, color);
	print_build(color, color_br);

	current_region(X, Y);						//Текущая область фигуры
}

//Исчезновение ядра
void ball::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//Белый цвет (сейчас)
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 255, 255));

	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	print_build(PenWhite, BrushWhite);

	DeleteObject(PenWhite);
	DeleteObject(BrushWhite);
}

//Отображение пристройки объекта
void upgraded_ball::print_sub_build(HPEN color, HBRUSH color_br)
{
	MoveToEx(hdc, X, Y, NULL);
};

//Отображение верхней части объекта
void upgraded_ball::print_roof_build(HPEN color, HBRUSH color_br)
{
	//Основание башни
	MoveToEx(hdc, X, Y - radius, NULL);
	LineTo(hdc, X, Y - radius - 20);
};

void upgraded_ball::current_region(int X, int Y)
{
	boxheat.start_X = X - radius;
	boxheat.end_X = X + radius;
	boxheat.start_Y = Y + radius;
	boxheat.end_Y = Y - radius;
};

void upgraded_ball::set_visible(HPEN color, HBRUSH color_br)
{
	//делаем перо активным 
	SelectObject(hdc, color);
	print_build(color, color_br);		//Отобразить основной объект
	print_sub_build(color, color_br);	//Отобразить пристройку
	print_roof_build(color, color_br);	//Отобразить верхнюю часть объекта

	current_region(X, Y);	//Текущая область фигуры
};

void upgraded_ball::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//Белый цвет (сейчас)
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 255, 255));

	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	print_build(PenWhite, BrushWhite);		//Отобразить основной объект
	print_sub_build(PenWhite, BrushWhite);	//Отобразить пристройку
	print_roof_build(PenWhite, BrushWhite);	//Отобразить верхнюю часть объекта

	DeleteObject(PenWhite);
	DeleteObject(BrushWhite);
};

//Отображение основания башни
void Tower::print_build(HPEN color, HBRUSH color_br)
{
	BeginPath(hdc);
	SelectObject(hdc, color_br);

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

	EndPath(hdc);
	FillPath(hdc);

	SelectObject(hdc, color);
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
}

//Отображение крыши башни
void Tower::print_roof_build(HPEN color, HBRUSH color_br)
{
	BeginPath(hdc);
	SelectObject(hdc, color_br);

	//Крыша башни
	LineTo(hdc, X - 30, Y);
	LineTo(hdc, X + 28, Y - 60);
	LineTo(hdc, X + 88, Y);
	LineTo(hdc, X, Y);

	EndPath(hdc);
	FillPath(hdc);

	SelectObject(hdc, color);
	//Крыша башни
	LineTo(hdc, X - 30, Y);
	LineTo(hdc, X + 28, Y - 60);
	LineTo(hdc, X + 88, Y);
	LineTo(hdc, X, Y);
}

//Текущее местоположение
void Tower::current_region(int X, int Y)
{
	boxheat.start_X = X - 30;
	boxheat.end_X = X + 95;
	boxheat.start_Y = Y + 125;
	boxheat.end_Y = Y - 60;
};

//Делает видимой пристройку
void Tower::print_sub_build(HPEN color, HBRUSH color_br)
{}

//Делает видимой башню
void Tower::set_visible(HPEN color, HBRUSH color_br)
{
	//делаем перо активным 
	SelectObject(hdc, color);
	print_build(color, color_br);

	HBRUSH brush = CreateSolidBrush(RGB(144, 100, 100));

	print_roof_build(color, brush);

	DeleteObject(brush);

	current_region(X, Y);
};

//Делает невидимой точку
void Tower::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//Белый цвет (сейчас)
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 255, 255));

	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	print_build(PenWhite, BrushWhite);
	print_roof_build(PenWhite, BrushWhite);

	DeleteObject(PenWhite);
	DeleteObject(BrushWhite);
};

//Текущее местоположение
void vertical_Tower_1::current_region(int X, int Y)
{
	boxheat.start_X = X - 30;
	boxheat.end_X = X + 95;
	boxheat.start_Y = Y + 125;
	boxheat.end_Y = Y - 60;
};

//Основание башни с лестницей
void vertical_Tower_1::print_build(HPEN color, HBRUSH color_br)
{
	BeginPath(hdc);
	SelectObject(hdc, color_br);

	//Основание башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 125);
	LineTo(hdc, X, Y + 125);
	LineTo(hdc, X , Y);
	LineTo(hdc, X + 60, Y);

	EndPath(hdc);
	FillPath(hdc);

	SelectObject(hdc, color);

	//Основание башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 125);
	LineTo(hdc, X + 40, Y + 125);
	LineTo(hdc, X + 40, Y);
	LineTo(hdc, X + 20, Y);
	LineTo(hdc, X + 20, Y + 125);
	LineTo(hdc, X + 40, Y + 125);
	LineTo(hdc, X + 40, Y + 105);
	LineTo(hdc, X + 20, Y + 105);
	LineTo(hdc, X + 20, Y + 85);
	LineTo(hdc, X + 40, Y + 85);
	LineTo(hdc, X + 40, Y + 65);
	LineTo(hdc, X + 20, Y + 65);
	LineTo(hdc, X + 20, Y + 45);
	LineTo(hdc, X + 40, Y + 45);
	LineTo(hdc, X + 40, Y + 25);
	LineTo(hdc, X + 20, Y + 25);
	LineTo(hdc, X + 20, Y + 125);
	LineTo(hdc, X, Y + 125);
	LineTo(hdc, X, Y);
}

//Пристройка левая
void vertical_Tower_1::print_sub_build(HPEN color, HBRUSH color_br)
{};

//Башня прямоугольниками
void vertical_Tower_1::print_roof_build(HPEN color, HBRUSH color_br)
{
	BeginPath(hdc);
	SelectObject(hdc, color_br);

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

	EndPath(hdc);
	FillPath(hdc);

	SelectObject(hdc, color);

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

//Делает видимой башню
void vertical_Tower_1::set_visible(HPEN color, HBRUSH color_br)
{
	//делаем перо активным 
	SelectObject(hdc, color);
	print_build(color, color_br);		 //Отображение башни

	HBRUSH brush = CreateSolidBrush(RGB(144, 100, 100));
	print_roof_build(color, brush);		//Отображение крыши башни
	DeleteObject(brush);

	print_sub_build(color, color_br);	 //Отображение пристройки башни

	current_region(X, Y);
};

//Делает невидимой башню
void vertical_Tower_1::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//Белый цвет (сейчас)
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 255, 255));

	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	print_build(PenWhite, BrushWhite);		 //Отображение башни
	print_roof_build(PenWhite, BrushWhite);	 //Отображение крыши башни
	print_sub_build(PenWhite, BrushWhite);	 //Отображение пристройки башни

	DeleteObject(PenWhite);
	DeleteObject(BrushWhite);
};

//Рисование башни в вертикальной иерархии
void vertical_Tower_2::print_sub_build(HPEN color, HBRUSH color_br)
{
	BeginPath(hdc);
	SelectObject(hdc, color_br);

	//Левая пристройка
	//Пристройка башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y + 63);
	LineTo(hdc, X - 90, Y + 63);
	LineTo(hdc, X - 90, Y + 125);
	LineTo(hdc, X, Y + 125);
	LineTo(hdc, X, Y);

	EndPath(hdc);
	FillPath(hdc);

	BeginPath(hdc);

	//Крыша пристройки
	MoveToEx(hdc, X, Y + 35, NULL);
	LineTo(hdc, X - 70, Y + 35);
	LineTo(hdc, X - 90, Y + 63);
	LineTo(hdc, X, Y + 63);
	LineTo(hdc, X, Y + 35);

	EndPath(hdc);
	FillPath(hdc);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	BeginPath(hdc);
	SelectObject(hdc, brush);

	//Окно пристройки
	MoveToEx(hdc, X - 40, Y + 100, NULL);
	LineTo(hdc, X - 40, Y + 80);
	LineTo(hdc, X - 65, Y + 80);
	LineTo(hdc, X - 65, Y + 100);
	LineTo(hdc, X - 40, Y + 100);

	EndPath(hdc);
	FillPath(hdc);

	BeginPath(hdc);
	SelectObject(hdc, color_br);

	//Правая пристройка
	//Пристройка башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 63);
	LineTo(hdc, X + 150, Y + 63);
	LineTo(hdc, X + 150, Y + 125);
	LineTo(hdc, X + 60, Y + 125);
	LineTo(hdc, X + 60, Y);

	EndPath(hdc);
	FillPath(hdc);

	BeginPath(hdc);

	//Крыша пристройки
	MoveToEx(hdc, X + 60, Y + 35, NULL);
	LineTo(hdc, X + 130, Y + 35);
	LineTo(hdc, X + 150, Y + 63);
	LineTo(hdc, X + 60, Y + 63);
	LineTo(hdc, X + 60, Y + 35);

	EndPath(hdc);
	FillPath(hdc);

	BeginPath(hdc);
	SelectObject(hdc, brush);

	//Окно пристройки
	MoveToEx(hdc, X + 100, Y + 100, NULL);
	LineTo(hdc, X + 100, Y + 80);
	LineTo(hdc, X + 100, Y + 80);
	LineTo(hdc, X + 125, Y + 80);
	LineTo(hdc, X + 125, Y + 100);
	LineTo(hdc, X + 100, Y + 100);

	EndPath(hdc);
	FillPath(hdc);

	SelectObject(hdc, color);

	//Левая пристройка
	//Пристройка башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y + 63);
	LineTo(hdc, X - 90, Y + 63);
	LineTo(hdc, X - 90, Y + 125);
	LineTo(hdc, X, Y + 125);
	LineTo(hdc, X, Y);

	//Крыша пристройки
	MoveToEx(hdc, X, Y + 35, NULL);
	LineTo(hdc, X - 70, Y + 35);
	LineTo(hdc, X - 90, Y + 63);
	LineTo(hdc, X, Y + 63);
	LineTo(hdc, X, Y + 35);

	//Окно пристройки
	MoveToEx(hdc, X - 40, Y + 100, NULL);
	LineTo(hdc, X - 40, Y + 80);
	LineTo(hdc, X - 65, Y + 80);
	LineTo(hdc, X - 65, Y + 100);
	LineTo(hdc, X - 40, Y + 100);
	LineTo(hdc, X - 53, Y + 100);
	LineTo(hdc, X - 53, Y + 80);

	//Правая пристройка
	//Пристройка башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 63);
	LineTo(hdc, X + 150, Y + 63);
	LineTo(hdc, X + 150, Y + 125);
	LineTo(hdc, X + 60, Y + 125);
	LineTo(hdc, X + 60, Y);

	//Крыша пристройки
	MoveToEx(hdc, X + 60, Y + 35, NULL);
	LineTo(hdc, X + 130, Y + 35);
	LineTo(hdc, X + 150, Y + 63);
	LineTo(hdc, X + 60, Y + 63);
	LineTo(hdc, X + 60, Y + 35);

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
void vertical_Tower_2::set_visible(HPEN color, HBRUSH color_br)
{
	//делаем перо активным 
	SelectObject(hdc, color);
	print_build(color, color_br);		//Отображение башни

	HBRUSH bru = CreateSolidBrush(RGB(255, 0, 0));
	print_roof_build(color, bru);	//Отображение крыши башни

	bru = CreateSolidBrush(RGB(128, 64, 48));
	print_sub_build(color, bru);	//Отображение пристройки башни
	DeleteObject(bru);

	current_region(X, Y);
};

//Делает невидимой башню в вертикальной иерархии 2
void vertical_Tower_2::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//Белый цвет (сейчас)
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 255, 255));

	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	print_build(PenWhite, BrushWhite);		 //Отображение башни
	print_roof_build(PenWhite, BrushWhite);	 //Отображение крыши башни
	print_sub_build(PenWhite, BrushWhite);	 //Отображение пристройки башни

	DeleteObject(PenWhite);
};

//Левая пристройка в веерной иерархии
void left_construction_Tower::print_sub_build(HPEN color, HBRUSH color_br)
{
	SelectObject(hdc, color_br);
	BeginPath(hdc);

	//Левая пристройка
	//Пристройка башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y + 63);
	LineTo(hdc, X - 90, Y + 63);
	LineTo(hdc, X - 90, Y + 125);
	LineTo(hdc, X, Y + 125);
	LineTo(hdc, X, Y);

	EndPath(hdc);
	FillPath(hdc);

	BeginPath(hdc);

	//Крыша пристройки
	MoveToEx(hdc, X, Y + 35, NULL);
	LineTo(hdc, X - 70, Y + 35);
	LineTo(hdc, X - 90, Y + 63);
	LineTo(hdc, X, Y + 63);
	LineTo(hdc, X, Y + 35);

	EndPath(hdc);
	FillPath(hdc);

	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	BeginPath(hdc);
	SelectObject(hdc, brush);

	//Окно пристройки
	MoveToEx(hdc, X - 40, Y + 100, NULL);
	LineTo(hdc, X - 40, Y + 80);
	LineTo(hdc, X - 65, Y + 80);
	LineTo(hdc, X - 65, Y + 100);
	LineTo(hdc, X - 40, Y + 100);

	EndPath(hdc);
	FillPath(hdc);
	DeleteObject(brush);


	SelectObject(hdc, color);

	//Левая пристройка
	//Пристройка башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y + 63);
	LineTo(hdc, X - 90, Y + 63);
	LineTo(hdc, X - 90, Y + 125);
	LineTo(hdc, X, Y + 125);
	LineTo(hdc, X, Y);

	//Крыша пристройки
	MoveToEx(hdc, X, Y + 35, NULL);
	LineTo(hdc, X - 70, Y + 35);
	LineTo(hdc, X - 90, Y + 63);
	LineTo(hdc, X, Y + 63);
	LineTo(hdc, X, Y + 35);

	//Окно пристройки
	MoveToEx(hdc, X - 40, Y + 100, NULL);
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
void left_construction_Tower::set_visible(HPEN color, HBRUSH color_br)
{
	//делаем перо активным 
	SelectObject(hdc, color);
	print_build(color, color_br);		//Основа башни

	HBRUSH bru = CreateSolidBrush(RGB(255, 0, 0));
	print_roof_build(color, bru);	//Крыша башни

	bru = CreateSolidBrush(RGB(128, 64, 48));
	print_sub_build(color, bru);	//Левая пристройка башни
	DeleteObject(bru);

	current_region(X, Y);
};

//Делает невидимой левую башню в веерной иерархии
void left_construction_Tower::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//Белый цвет (сейчас)
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 255, 255));

	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	print_build(PenWhite, BrushWhite);		//Основа башни
	print_roof_build(PenWhite, BrushWhite);	//Крыша башни
	print_sub_build(PenWhite, BrushWhite);	//Левая пристройка башни

	DeleteObject(PenWhite);
	DeleteObject(BrushWhite);
};

void addition::print_roof_build(HPEN color, HBRUSH color_br)
{
	SelectObject(hdc, color_br);
	BeginPath(hdc);

	//Крыша башни
	LineTo(hdc, X - 50, Y);
	LineTo(hdc, X - 50, Y - 80);
	LineTo(hdc, X + 120, Y - 80);
	LineTo(hdc, X + 120, Y);
	LineTo(hdc, X, Y);

	EndPath(hdc);
	FillPath(hdc);

	SelectObject(hdc, color);
	//Крыша башни
	LineTo(hdc, X - 50, Y);
	LineTo(hdc, X - 50, Y - 80);
	LineTo(hdc, X + 120, Y - 80);
	LineTo(hdc, X + 120, Y);
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y - 80);
	LineTo(hdc, X + 60, Y - 80);
	LineTo(hdc, X + 60, Y);
}

void addition::set_visible(HPEN color, HBRUSH color_br)
{
	//делаем перо активным 
	SelectObject(hdc, color);
	print_build(color, color_br);		//Основа башни

	HBRUSH bru = CreateSolidBrush(RGB(255, 0, 0));
	print_roof_build(color, color_br);	//Крыша башни

	bru = CreateSolidBrush(RGB(128, 64, 48));
	print_sub_build(color, bru);	//Левая пристройка башни
	DeleteObject(bru);

	current_region(X, Y);
}

void addition::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//Белый цвет (сейчас)
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 255, 255));

	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	print_build(PenWhite, BrushWhite);		//Основа башни
	print_roof_build(PenWhite, BrushWhite);	//Крыша башни
	print_sub_build(PenWhite, BrushWhite);	//Левая пристройка башни

	DeleteObject(PenWhite);
	DeleteObject(BrushWhite);
};

//Правая пристройка
void right_construction_Tower::print_sub_build(HPEN color, HBRUSH color_br)
{
	BeginPath(hdc);
	SelectObject(hdc, color_br);

	//Правая пристройка
	//Пристройка башни
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 63);
	LineTo(hdc, X + 150, Y + 63);
	LineTo(hdc, X + 150, Y + 125);
	LineTo(hdc, X + 60, Y + 125);
	LineTo(hdc, X + 60, Y);

	EndPath(hdc);
	FillPath(hdc);

	BeginPath(hdc);

	//Крыша пристройки
	MoveToEx(hdc, X + 60, Y + 35, NULL);
	LineTo(hdc, X + 130, Y + 35);
	LineTo(hdc, X + 150, Y + 63);
	LineTo(hdc, X + 60, Y + 63);
	LineTo(hdc, X + 60, Y + 35);

	EndPath(hdc);
	FillPath(hdc);

	BeginPath(hdc);
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, brush);

	//Окно пристройки
	MoveToEx(hdc, X + 100, Y + 100, NULL);
	LineTo(hdc, X + 100, Y + 80);
	LineTo(hdc, X + 100, Y + 80);
	LineTo(hdc, X + 125, Y + 80);
	LineTo(hdc, X + 125, Y + 100);
	LineTo(hdc, X + 100, Y + 100);

	EndPath(hdc);
	FillPath(hdc);

	SelectObject(hdc, color);

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
void right_construction_Tower::set_visible(HPEN color, HBRUSH color_br)
{
	//HPEN PenGreen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	//делаем перо активным 
	SelectObject(hdc, color);
	print_build(color, color_br);		//Основа башни

	HBRUSH bru = CreateSolidBrush(RGB(0, 255, 0));
	print_roof_build(color, bru);	//Крыша башни

	bru = CreateSolidBrush(RGB(128, 64, 48));
	print_sub_build(color, bru);	//Правая пристройка башни
	DeleteObject(bru);

	current_region(X, Y);
};

//Делает невидимой правую башню в веерной иерархии
void right_construction_Tower::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//Белый цвет (сейчас)
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 255, 255));

	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	print_build(PenWhite, BrushWhite);		//Основа башни
	print_roof_build(PenWhite, BrushWhite);	//Крыша башни
	print_sub_build(PenWhite, BrushWhite);	//Правая пристройка башни

	DeleteObject(PenWhite);
	DeleteObject(BrushWhite);
};

//Получение координат объекта
void Plane::current_region(int X, int Y)
{
	boxheat.start_X = X;
	boxheat.end_X = X + 100;
	boxheat.start_Y = Y + 100;
	boxheat.end_Y = Y;
}

//Крыло
void Plane::print_build(HPEN color, HBRUSH color_br)
{
	BeginPath(hdc);
	SelectObject(hdc, color_br);

	MoveToEx(hdc, X + 55, Y + 55, NULL);
	LineTo(hdc, X + 45, Y + 100);
	LineTo(hdc, X + 35, Y + 100);
	LineTo(hdc, X + 35, Y + 55);

	EndPath(hdc);
	FillPath(hdc);

	SelectObject(hdc, color);

	MoveToEx(hdc, X + 55, Y + 55, NULL);
	LineTo(hdc, X + 45, Y + 100);
	LineTo(hdc, X + 35, Y + 100);
	LineTo(hdc, X + 35, Y + 50);
}

//Корпус
void Plane::print_roof_build(HPEN color, HBRUSH color_br)
{
	BeginPath(hdc);
	SelectObject(hdc, color_br);

	MoveToEx(hdc, X, Get_Y(), NULL);
	LineTo(hdc, X + 20, Get_Y());
	LineTo(hdc, X + 25, Y + 35);
	LineTo(hdc, X + 90, Y + 35);
	LineTo(hdc, X + 100, Y + 50);
	LineTo(hdc, X + 90, Y + 65);
	LineTo(hdc, X + 5, Y + 65);
	LineTo(hdc, X, Get_Y());

	EndPath(hdc);
	FillPath(hdc);

	SelectObject(hdc, color);

	MoveToEx(hdc, X, Get_Y(), NULL);
	LineTo(hdc, X + 20, Get_Y());
	LineTo(hdc, X + 25, Y + 35);
	LineTo(hdc, X + 90, Y + 35);
	LineTo(hdc, X + 100, Y + 50);
	LineTo(hdc, X + 90, Y + 65);
	LineTo(hdc, X + 5, Y + 65);
	LineTo(hdc, X, Get_Y());
}

//Окно
void Plane::print_sub_build(HPEN color, HBRUSH color_br)
{
	BeginPath(hdc);
	SelectObject(hdc, color_br);

	MoveToEx(hdc, X + 70, Y + 35, NULL);
	LineTo(hdc, X + 90, Y + 35);
	LineTo(hdc, X + 100, Y + 50);
	LineTo(hdc, X + 70, Y + 50);
	LineTo(hdc, X + 70, Y + 35);

	EndPath(hdc);
	FillPath(hdc);

	SelectObject(hdc, color);

	MoveToEx(hdc, X + 70, Y + 35, NULL);
	LineTo(hdc, X + 90, Y + 35);
	LineTo(hdc, X + 100, Y + 50);
	LineTo(hdc, X + 70, Y + 50);
	LineTo(hdc, X + 70, Y + 35);
}

//Делает видимым объект
void Plane::set_visible(HPEN color, HBRUSH color_br)
{
	//делаем перо активным 
	SelectObject(hdc, color);

	HBRUSH bru = CreateSolidBrush(RGB(112, 127, 143));
	print_roof_build(color, bru);	//Корпус

	bru = CreateSolidBrush(RGB(253, 233, 16));
	print_build(color, bru);		//Крыло

	bru = CreateSolidBrush(RGB(175, 238, 238));
	print_sub_build(color, bru);	//Окно
	DeleteObject(bru);

	current_region(X, Y);
}

//Делает невидимым объект
void Plane::set_invisible()
{
	//Белый цвет (сейчас)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//Белый цвет (сейчас)
	HBRUSH BrushWhite = CreateSolidBrush(RGB(255, 255, 255));

	//делаем перо активным 
	SelectObject(hdc, PenWhite);
	print_build(PenWhite, BrushWhite);		//Основа башни
	print_roof_build(PenWhite, BrushWhite);	//Крыша башни
	print_sub_build(PenWhite, BrushWhite);	//Левая пристройка башни

	DeleteObject(PenWhite);
	DeleteObject(BrushWhite);
}