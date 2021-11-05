/*
 * 행맨 게임
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
 * 함수 선언
 */
// 커서 이동 함수
void gotoxy(int x, int y);

// 기본 배경(처형대, 밑줄 등) 출력 함수
void Background();

// 답 입력받기
void Answer();

// 행맨 몸 관리 함수
void Body(int* bodyCount);

// 글자 대조 함수
int Compare(char take);

// 글자 맞췄을 때 함수
void Correct(int len_ptr, char take);


/*
 * 변수 선언
 */
char answer[MAX];   // 답 받는 변수
char player[MAX];   // 맞춘 답 저장 변수
int count = 0;      // 답 글자 수
int body = 0;
int* bodyCount = &body;  // 행맨 몸 count에 쓰일 변수
int success = 0;   // 성공 횟수
char already;   // 이미 맞춘 문자인지 확인하기 위한 변수




int main() {
	// 정답 입력받고 문자 개수만큼 칸 출력
	Answer();
	// 기본 필드 출력(처형대, 답 칸)
	Background();

	gotoxy(0, 1);
	printf("영문자를 하나씩 입력하여 정답을 맞춰보세요. \n");

	// 게임 시작
	char take;
	while(1) {
		gotoxy(0, 2);
		scanf_s("%c", &take, 1);
		rewind(stdin);   // 입력 버퍼 비우기
		Compare(take);
		

		// 정답 맞췄을 때
		if (success == (count - 1)) {
			gotoxy(0, HANGMAN + 3);
			printf("정답을 맞췄습니다!\n");
			printf("3초 뒤 게임을 종료합니다.\n");
			Sleep(3000);
			printf("Bye~\n");
			exit(0);
		}
		else if (*bodyCount > 6)
		{
			gotoxy(0, HANGMAN + 3);
			printf("게임 실패! 다음에 다시 도전하세요~");
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
	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

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
	printf("생각한 단어를 입력하세요: \n");
	fgets(answer, MAX, stdin);
	rewind(stdin);
	system("cls");
}

int Compare(char take)
{
	// 맞췄을 때
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
			printf("이미 맞춘 문자입니다\n");
			return 1;
		}
	}
	else
	{
		// 틀렸을 때
		printf("틀렸습니다!");
		*bodyCount += 1;
		gotoxy(ANSWER_WIDTH + (*bodyCount), 5);
		printf("%c", take);   // 틀린 문자 출력
		// Body 함수 호출
		Body(bodyCount);
		return 0;
	}
}


void Body(int* bodyCount) {
	// case만들어서 bodyCount이용 -> 몸 늘리기
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
		printf("＼ ");
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
		printf("＼");
		break;
	default:
		break;
	}
}

void Correct(int len_ptr, char take)
{
	int location_a = count - len_ptr;   // 전체 문자열 길이 - ptr길이
	printf("맞췄습니다!");
	gotoxy(ANSWER_WIDTH + location_a, HANGMAN + 3);
	player[location_a] = take;
	printf("%c", take);
}