#include "classes 4.h"

extern HDC hdc;//�������� ����������(�������� �������� ���������� � ���� ����������� ����������� ���������)

//������ ������� �����
void Point::set_visible(HPEN color)
{
	SetPixel(hdc, X, Y, RGB(255, 0, 0));		//������ ����� ������������� ������
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));	//������ ����� ������������� ������
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));	//������ ����� ������������� ������
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));//������ ����� ������������� ������
	current_region(X, Y);						//������� ������� ������
};

//������ ��������� �����
void Point::set_invisible()
{
	SetPixel(hdc, X, Y, RGB(0, 0, 0));			//������ ����� ������������� ������
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 0));		//������ ����� ������������� ������
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 0));		//������ ����� ������������� ������
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 0));	//������ ����� ������������� ������
}

//���������� �����
void Point::Move_To(int X, int Y)
{
	set_invisible();
	Set_X(X);
	Set_Y(Y);
	set_visible(pen);
}

//��������� ����
void ball::print_build()
{
	Ellipse(hdc, X - radius, Y - radius, X + radius, Y + radius);
}

//���������� �������������� ������
void ball::current_region(int X, int Y)
{
	boxheat.start_X = X - radius;
	boxheat.end_X = X + radius;
	boxheat.start_Y = Y + radius;
	boxheat.end_Y = Y - radius;
}

//����������� ����
void ball::set_visible(HPEN color)
{
	//������ ���� �������� 
	SelectObject(hdc, color);
	print_build();

	current_region(X, Y);						//������� ������� ������
}

//������������ ����
void ball::set_invisible()
{
	//����� ���� (������)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//������ ���� �������� 
	SelectObject(hdc, PenWhite);
	print_build();

	DeleteObject(PenWhite);
}

//����������� ���������� �������
void upgraded_ball::print_sub_build()
{
	//��������� �����
	MoveToEx(hdc, X, Y, NULL);
};

//����������� ������� ����� �������
void upgraded_ball::print_roof_build()
{
	//��������� �����
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

void upgraded_ball::set_visible(HPEN color)
{
	//������ ���� �������� 
	SelectObject(hdc, color);
	print_build();			//���������� �������� ������
	print_sub_build();		//���������� ����������
	print_roof_build();		//���������� ������� ����� �������

	current_region(X, Y);	//������� ������� ������
};

void upgraded_ball::set_invisible()
{
	//����� ���� (������)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//������ ���� �������� 
	SelectObject(hdc, PenWhite);
	print_build();		//���������� �������� ������
	print_sub_build();	//���������� ����������
	print_roof_build();	//���������� ������� ����� �������

	DeleteObject(PenWhite);
};

//����������� ��������� �����
void Tower::print_build()
{
	//��������� �����
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

//����������� ����� �����
void Tower::print_roof_build()
{
	//����� �����
	LineTo(hdc, X - 30, Y);
	LineTo(hdc, X + 28, Y - 60);
	LineTo(hdc, X + 88, Y);
	LineTo(hdc, X, Y);
}

void Tower::current_region(int X, int Y)
{
	boxheat.start_X = X - 30;
	boxheat.end_X = X + 95;
	boxheat.start_Y = Y + 125;
	boxheat.end_Y = Y - 60;
};

void Tower::print_sub_build()
{}

//������ ������� �����
void Tower::set_visible(HPEN color)
{
	//������ ���� �������� 
	SelectObject(hdc, color);
	print_build();
	print_roof_build();

	current_region(X, Y);
};

//������ ��������� �����
void Tower::set_invisible()
{
	//����� ���� (������)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//������ ���� �������� 
	SelectObject(hdc, PenWhite);
	print_build();
	print_roof_build();

	DeleteObject(PenWhite);
};

//������� ��������������
void vertical_Tower_1::current_region(int X, int Y)
{
	boxheat.start_X = X - 30;
	boxheat.end_X = X + 95;
	boxheat.start_Y = Y + 125;
	boxheat.end_Y = Y - 60;
};

//��������� ����� � ���������
void vertical_Tower_1::print_build()
{
	//��������� �����
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 125);
	LineTo(hdc, X + 40, Y + 125);
	LineTo(hdc, X + 40, Y );
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
	LineTo(hdc, X , Y);
}

//���������� �����
void vertical_Tower_1::print_sub_build()
{};

//����� ����������������
void vertical_Tower_1::print_roof_build()
{
	//����� �����
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

//������ ������� �����
void vertical_Tower_1::set_visible(HPEN color)
{
	//������ ���� �������� 
	SelectObject(hdc, color);
	print_build();		 //����������� �����
	print_roof_build();	 //����������� ����� �����
	print_sub_build();	 //����������� ���������� �����

	current_region(X, Y);
};

//������ ��������� �����
void vertical_Tower_1::set_invisible()
{
	//����� ���� (������)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//������ ���� �������� 
	SelectObject(hdc, PenWhite);
	print_build();		 //����������� �����
	print_roof_build();	 //����������� ����� �����
	print_sub_build();	 //����������� ���������� �����

	DeleteObject(PenWhite);
};

//��������� ����� � ������������ ��������
void vertical_Tower_2::print_sub_build()
{
	//����� ����������
	//���������� �����
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y + 63);
	LineTo(hdc, X - 90, Y + 63);
	LineTo(hdc, X - 90, Y + 125);
	LineTo(hdc, X, Y + 125);

	//����� ����������
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y + 35);
	LineTo(hdc, X - 70, Y + 35);
	LineTo(hdc, X - 90, Y + 63);

	//���� ����������
	MoveToEx(hdc, X - 40, Y + 100, NULL);
	LineTo(hdc, X - 40, Y + 80);
	LineTo(hdc, X - 40, Y + 80);
	LineTo(hdc, X - 65, Y + 80);
	LineTo(hdc, X - 65, Y + 100);
	LineTo(hdc, X - 40, Y + 100);
	LineTo(hdc, X - 53, Y + 100);
	LineTo(hdc, X - 53, Y + 80);

	//������ ����������
	//���������� �����
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 63);
	LineTo(hdc, X + 150, Y + 63);
	LineTo(hdc, X + 150, Y + 125);
	LineTo(hdc, X + 60, Y + 125);

	//����� ����������
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 35);
	LineTo(hdc, X + 130, Y + 35);
	LineTo(hdc, X + 150, Y + 63);

	//���� ����������
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

//������ ������� ����� � ������������ �������� 2
void vertical_Tower_2::set_visible(HPEN color)
{
	//HPEN PenBlue = CreatePen(PS_SOLID, 3, RGB(0, 0, 200));
	//������ ���� �������� 
	SelectObject(hdc, color);
	print_build();		 //����������� �����
	print_roof_build();	 //����������� ����� �����
	print_sub_build();	 //����������� ���������� �����

	current_region(X, Y);
};

//������ ��������� ����� � ������������ �������� 2
void vertical_Tower_2::set_invisible()
{
	//����� ���� (������)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//������ ���� �������� 
	SelectObject(hdc, PenWhite);
	print_build();		 //����������� �����
	print_roof_build();	 //����������� ����� �����
	print_sub_build();	 //����������� ���������� �����

	DeleteObject(PenWhite);
};

//����� ���������� � ������� ��������
void left_construction_Tower::print_sub_build()
{
	//���������� �����
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y + 63);
	LineTo(hdc, X - 90, Y + 63);
	LineTo(hdc, X - 90, Y + 125);
	LineTo(hdc, X, Y + 125);

	//����� ����������
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y + 35);
	LineTo(hdc, X - 70, Y + 35);
	LineTo(hdc, X - 90, Y + 63);

	//���� ����������
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

//������ ������� ����� ����� � ������� ��������
void left_construction_Tower::set_visible(HPEN color)
{
	//������ ���� �������� 
	SelectObject(hdc, color);
	print_build();		//������ �����
	print_roof_build();	//����� �����
	print_sub_build();	//����� ���������� �����

	current_region(X, Y);
};

//������ ��������� ����� ����� � ������� ��������
void left_construction_Tower::set_invisible()
{
	//����� ���� (������)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//������ ���� �������� 
	SelectObject(hdc, PenWhite);
	print_build();		//������ �����
	print_roof_build();	//����� �����
	print_sub_build();	//����� ���������� �����

	DeleteObject(PenWhite);
};

void addition::print_roof_build()
{
	//����� �����
	LineTo(hdc, X - 50, Y);
	LineTo(hdc, X - 50, Y - 80);
	LineTo(hdc, X + 120, Y - 80);
	LineTo(hdc, X + 120, Y);
	LineTo(hdc, X, Y);
	LineTo(hdc, X, Y - 80);
	LineTo(hdc, X + 60, Y - 80);
	LineTo(hdc, X + 60, Y);
}

void addition::set_visible(HPEN color)
{
	//������ ���� �������� 
	SelectObject(hdc, color);
	print_build();		//������ �����
	print_roof_build();	//����� �����
	print_sub_build();	//����� ���������� �����

	current_region(X, Y);
}

void addition::set_invisible()
{
	//����� ���� (������)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//������ ���� �������� 
	SelectObject(hdc, PenWhite);
	print_build();		//������ �����
	print_roof_build();	//����� �����
	print_sub_build();	//����� ���������� �����

	DeleteObject(PenWhite);
};

//������ ����������
void right_construction_Tower::print_sub_build()
{
	//���������� �����
	MoveToEx(hdc, X, Y, NULL);
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 63);
	LineTo(hdc, X + 150, Y + 63);
	LineTo(hdc, X + 150, Y + 125);
	LineTo(hdc, X + 60, Y + 125);

	//����� ����������
	LineTo(hdc, X + 60, Y);
	LineTo(hdc, X + 60, Y + 35);
	LineTo(hdc, X + 130, Y + 35);
	LineTo(hdc, X + 150, Y + 63);

	//���� ����������
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

//������ ������� ������ ����� � ������� ��������
void right_construction_Tower::set_visible(HPEN color)
{
	//HPEN PenGreen = CreatePen(PS_SOLID, 3, RGB(0, 255, 0));
	//������ ���� �������� 
	SelectObject(hdc, color);
	print_build();		//������ �����
	print_roof_build();	//����� �����
	print_sub_build();	//������ ���������� �����

	current_region(X, Y);
};

//������ ��������� ������ ����� � ������� ��������
void right_construction_Tower::set_invisible()
{
	//����� ���� (������)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//������ ���� �������� 
	SelectObject(hdc, PenWhite);
	print_build();		//������ �����
	print_roof_build();	//����� �����
	print_sub_build();	//������ ���������� �����

	DeleteObject(PenWhite);
};

//��������� ��������� �������
void Plane::current_region(int X, int Y)
{
	boxheat.start_X = X;
	boxheat.end_X = X + 100;
	boxheat.start_Y = Y + 100;
	boxheat.end_Y = Y;
}

//�����
void Plane::print_build()
{
	MoveToEx(hdc, X + 55, Y + 55, NULL);
	LineTo(hdc, X + 45, Y + 100);
	LineTo(hdc, X + 35, Y + 100);
	LineTo(hdc, X + 35, Y + 50);
}

//������
void Plane::print_roof_build()
{
	MoveToEx(hdc, X, Get_Y(), NULL);
	LineTo(hdc, X + 20, Get_Y());
	LineTo(hdc, X + 25, Y + 35);
	LineTo(hdc, X + 90, Y + 35);
	LineTo(hdc, X + 100, Y + 50);
	LineTo(hdc, X + 90, Y + 65);
	LineTo(hdc, X + 5, Y + 65);
	LineTo(hdc, X, Get_Y());
}

//����
void Plane::print_sub_build()
{
	MoveToEx(hdc, X + 70, Y + 35, NULL);
	LineTo(hdc, X + 90, Y + 35);
	LineTo(hdc, X + 100, Y + 50);
	LineTo(hdc, X + 70, Y + 50);
	LineTo(hdc, X + 70, Y + 35);
}

//������ ������� ������
void Plane::set_visible(HPEN color)
{
	//������ ���� �������� 
	SelectObject(hdc, color);
	print_build();		//������ �����
	print_roof_build();	//����� �����
	print_sub_build();	//����� ���������� �����

	current_region(X, Y);
}

//������ ��������� ������
void Plane::set_invisible()
{
	//����� ���� (������)
	HPEN PenWhite = CreatePen(PS_SOLID, 3, RGB(255, 255, 255));
	//������ ���� �������� 
	SelectObject(hdc, PenWhite);
	print_build();		//������ �����
	print_roof_build();	//����� �����
	print_sub_build();	//����� ���������� �����

	DeleteObject(PenWhite);
}