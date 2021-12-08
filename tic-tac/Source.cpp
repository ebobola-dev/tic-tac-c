#include <stdio.h>
#include <locale.h>
#include <Windows.h>

#define LINE printf(" |%c%c%c|%c%c%c|%c%c%c|\n", 5060, 5060, 5060, 5060, 5060, 5060, 5060, 5060, 5060)
#define NEWLINE printf("\n")

void printField(void);
void clearField(void);
int choiceIsCorrect(int, int);
void setChoice(char, int, int);
void changePlayer(char*);
int checkWin(void);

char field[3][3] = {
	{' ', ' ', ' '},
	{' ', ' ', ' '},
	{' ', ' ', ' '},
};

int main(void) {
	unsigned int chRow = 0, chCol = 0, enterCount, trash = 0, cont = 1;
	char player = 'x';

	while (cont) {
		chRow = 0, chCol = 0;
		player = 'x';
		clearField();
		while (1) {
			system("cls");
			NEWLINE;
			printField();
			NEWLINE;
			if (checkWin()) {
				changePlayer(&player);
				printf("PLAYER \"%c\" WINS!!!", player);
				NEWLINE;
				break;
			}
			if (checkDraw()) {
				printf("DRAW((((");
				NEWLINE;
				break;
			}
			do {
				printf("Player \"%c\", enter your choice(ROW COL - example: 3 2) : ", player);
				enterCount = scanf("%d%d", &chRow, &chCol);
				while (trash = getchar() != '\n');
				if (enterCount < 2) {
					printf("Enter only numbers!\n");
				}
			} while (enterCount < 2 || !choiceIsCorrect(chRow, chCol));
			setChoice(player, chRow, chCol);
			changePlayer(&player);
		}
		NEWLINE;
		printf("Do you want to play again? 0 - quit: ");
		scanf_s("%d", &cont);
		while (trash = getchar() != '\n');
	}
	return 0;
}

void printField(void) {
	LINE;
	printf(" | %c | %c | %c |\n", field[0][0], field[0][1], field[0][2]);
	LINE;
	printf(" | %c | %c | %c |\n", field[1][0], field[1][1], field[1][2]);
	LINE;
	printf(" | %c | %c | %c |\n", field[2][0], field[2][1], field[2][2]);
	LINE;
}

void clearField(void) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			field[row][col] = ' ';
		}
	}
}

int choiceIsCorrect(int row, int col) {
	if (row > 3 || col > 3 || row < 1 || col < 1) return 0;
	return field[row - 1][col - 1] == ' ';
}

void setChoice(char player, int row, int col) {
	field[row - 1][col - 1] = player;
}

void changePlayer(char* player) {
	*player = *player == 'x' ? 'o' : 'x';
}

int checkWin(void) {
	for (int i = 0; i < 3; i++) {
		if ((field[i][0] == field[i][1] && field[i][1] == field[i][2]) && field[i][0] != ' ') return 1;
		if ((field[0][i] == field[1][i] && field[1][i] == field[2][i]) && field[0][i] != ' ') return 1;
	}
	if ((field[0][0] == field[1][1] && field[1][1] == field[2][2]) && field[0][0] != ' ') return 1;
	if ((field[0][2] == field[1][1] && field[1][1] == field[2][0]) && field[0][2] != ' ') return 1;
	return 0;
}

int checkDraw(void) {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			if (field[row][col] == ' ') return 0;
		}
	}
	return 1;
}