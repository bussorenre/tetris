#include <stdio.h>

#define BOARD_HEIGHT 20
#define BOARD_WIDTH  10


void clearConsole() {
    printf("\x1b[2J");
    return;
}

void printBoard(int height, int width, char *board)
{
    int i,j;

    // 画面全体を真っ白にする
    clearConsole();

    for (i = 0; i < height; i++) {
        printf("|");
        for (j = 0; j < width; j++) {
            // ブロックがあればブロックを表示
            // ブロックがなければスペースで対応
            printf(" ");
        }
        printf("|\n");
    }

    // 最下行にも枠線を描画する
    printf("-");
    for (j = 0; j < width; j++) {
        printf("-");
    }
    printf("-\n");

    return;
}




int main(int argc, char *argv[])
{
    char board[BOARD_HEIGHT][BOARD_HEIGHT] = {0};

    // 盤面を表示する
    printBoard(BOARD_HEIGHT, BOARD_WIDTH, board);
    return 0;
}
