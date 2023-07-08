#include "classes 4.h"

//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

static HWND GetConcolWindow()
{
	char str[128];
	// char title[128]="xxxxxxxxxxxxxxxxxx";
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";	//����� ������ Windows
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str)); // �������� ��������� ����
	SetConsoleTitle(title);						// ���������� ����� ��������� ����
	Sleep(100);									// ���� ����� ��������� ���� (100 ��);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);// ���������� ���������� ����
	SetConsoleTitle((LPWSTR)str);				//���������� ������� ���������

	return hwnd;//������� ���������� ����
}//end GetConcolWindow()

//������� ����� �� ������� ������
static void PressKey(int VkCode)
{
	while (1)
		if (KEY_DOWN(VkCode))
			break;
}

//�������� ������������
static void check(int& i, Point*& current, std::vector <ball*>& BALL, Tower* collisions[6][6])
{
	//for �������� ������������ �� �����������
	for (int j = 0; j < BALL.size(); ++j)
	{
		//if ��������, ��� ������� �����������
		if (current->get().end_X < BALL[j]->get().start_X
			|| current->get().start_X > BALL[j]->get().end_X
			|| current->get().end_Y > BALL[j]->get().start_Y
			|| current->get().start_Y < BALL[j]->get().end_Y)
		{
			//��� ������������
		}
		else
		{
			current->set_invisible();

			//��������� ����� ������ �� ����� ������
			collisions[i][j]->Move_To(current->Get_X(), current->Get_Y());

			current = collisions[i][j];				//����� ������ �� ������� 
			i = j;

			current->set_visible(current->pen_color(), current->Brush_color());
		}
	}
};

//���������� ������ current
static void Drag(int& i, Point*& current, std::vector <Tower*>& Tow, std::vector <ball*>& BALL, Tower* collisions[6][6])
{
	current = Tow[i];				//��������� �� ������� ����� Tower

	//while 7 - �����
	while (!KEY_DOWN(55))
	{
		// A - �����
		if (KEY_DOWN(65))
		{
			current->Move_To(current->Get_X() - 20, current->Get_Y());

			check(i, current, BALL, collisions);	//�������� ������������
		}
		// W - �����
		else if (KEY_DOWN(87))
		{
			current->Move_To(current->Get_X(), current->Get_Y() - 20);

			check(i, current, BALL, collisions);	//�������� ������������
		}
		// D - ������
		else if (KEY_DOWN(68))
		{
			current->Move_To(current->Get_X() + 20, current->Get_Y());
			check(i, current, BALL, collisions);	//�������� ������������

		}
		// S - ����
		else if (KEY_DOWN(83))
		{
			current->Move_To(current->Get_X(), current->Get_Y() + 20);
			check(i, current, BALL, collisions);	//�������� ������������
		}

		//for ��������� ���� �����
		for (int i = 0; i < BALL.size(); i++)
		{
			BALL[i]->set_visible(BALL[i]->pen_color(), BALL[i]->Brush_color());
		}

		Sleep(1);
	}
}
