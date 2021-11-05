/*
 * ��� ����
 * 2021-11-06
*/


#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>


/*
 * Define
 */
#define HANGMAN 20
#define ANSWER_WIDTH 70
#define MAX 1000

/*
 * �Լ� ����
 */
// Ŀ�� �̵� �Լ�
void gotoxy(int x, int y);

// �⺻ ���(ó����, ���� ��) ��� �Լ�
void Background();

// �� �Է¹ޱ�
void Answer();

// ��� �� ���� �Լ�
void Body(int* bodyCount);

// ���� ���� �Լ�
int Compare(char take);

// ���� ������ �� �Լ�
void Correct(int len_ptr, char take);


/*
 * ���� ����
 */
char answer[MAX];   // �� �޴� ����
char player[MAX];   // ���� �� ���� ����
int count = 0;      // �� ���� ��
int body = 0;
int* bodyCount = &body;  // ��� �� count�� ���� ����
int success = 0;   // ���� Ƚ��
char already;   // �̹� ���� �������� Ȯ���ϱ� ���� ����




int main() {
	// ���� �Է¹ް� ���� ������ŭ ĭ ���
	Answer();
	// �⺻ �ʵ� ���(ó����, �� ĭ)
	Background();

	gotoxy(0, 1);
	printf("�����ڸ� �ϳ��� �Է��Ͽ� ������ ���纸����. \n");

	// ���� ����
	char take;
	while(1) {
		gotoxy(0, 2);
		scanf_s("%c", &take, 1);
		rewind(stdin);   // �Է� ���� ����
		Compare(take);
		

		// ���� ������ ��
		if (success == (count - 1)) {
			gotoxy(0, HANGMAN + 3);
			printf("������ ������ϴ�!\n");
			printf("3�� �� ������ �����մϴ�.\n");
			Sleep(3000);
			printf("Bye~\n");
			exit(0);
		}
		else if (*bodyCount > 6)
		{
			gotoxy(0, HANGMAN + 3);
			printf("���� ����! ������ �ٽ� �����ϼ���~");
			break;
		}
	}
	return 0;
}

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Background() {
	gotoxy(HANGMAN, 3);
	printf("\n");
	printf("    _______________ \n");
	printf("   ||              |\n");
	printf("   ||              |\n");
	printf("   ||              |\n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("   ||               \n");
	printf("�ѤѤѤѤѤѤѤѤѤ�\n");

	int i = 0;
	while (answer[i] != 0) {
		if (answer[i] == NULL)
			count--;
		count++;
		i++;
	}

	gotoxy(ANSWER_WIDTH, 23);
	for (int k = 0; k < count-1; k++)
		printf("_");
	Sleep(500);
}

void Answer()
{
	printf("������ �ܾ �Է��ϼ���: \n");
	fgets(answer, MAX, stdin);
	rewind(stdin);
	system("cls");
}

int Compare(char take)
{
	// ������ ��
	char* ptr = strchr(answer, take);

	already = strchr(player, take);
	if (ptr != NULL) {
		if (already == NULL) {
			success += 1;
			Correct(strlen(ptr), take);
			return 1;
		}
		else
		{
			printf("�̹� ���� �����Դϴ�\n");
			return 1;
		}
	}
	else
	{
		// Ʋ���� ��
		printf("Ʋ�Ƚ��ϴ�!");
		*bodyCount += 1;
		gotoxy(ANSWER_WIDTH + (*bodyCount), 5);
		printf("%c", take);   // Ʋ�� ���� ���
		// Body �Լ� ȣ��
		Body(bodyCount);
		return 0;
	}
}


void Body(int* bodyCount) {
	// case���� bodyCount�̿� -> �� �ø���
	switch (*bodyCount) {
	case 1:
		gotoxy(HANGMAN - 1, 8);
		printf("O");
		break;
	case 2:
		gotoxy(HANGMAN - 1, 9);
		printf("I");
		break;
	case 3:
		gotoxy(HANGMAN - 2, 10);
		printf("�� ");
		break;
	case 4:
		gotoxy(HANGMAN, 10);
		printf("/");
		break;
	case 5:
		gotoxy(HANGMAN - 2, 11);
		printf("/");
		break;
	case 6:
		gotoxy(HANGMAN, 11);
		printf("��");
		break;
	default:
		break;
	}
}

void Correct(int len_ptr, char take)
{
	int location_a = count - len_ptr;   // ��ü ���ڿ� ���� - ptr����
	printf("������ϴ�!");
	gotoxy(ANSWER_WIDTH + location_a, HANGMAN + 3);
	player[location_a] = take;
	printf("%c", take);
}