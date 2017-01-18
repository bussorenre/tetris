#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define BOARD_HEIGHT 20
#define BOARD_WIDTH  10


// getch - コンソールへの一文字入力を受け取る
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// clearConsole - コンソールを全部クリアする
void clearConsole() {
    printf("\x1b[2J");
    return;
}

// printBoard - テトリスの盤面を表示する
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
    int ch;
    char board[BOARD_HEIGHT][BOARD_HEIGHT] = {0};

    while (1) {
        // 入力を受け取る
        ch = getch();

        // 盤面を表示する
        printBoard(BOARD_HEIGHT, BOARD_WIDTH, board);

        // 入力を受け取り、信号番号を表示させる。
        printf("input : %d\n", ch);
    }
    return 0;
}
