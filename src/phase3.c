#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define BOARD_HEIGHT 20
#define BOARD_WIDTH  10


typedef struct {
    int x;
}PLAYABLE_BLOCK;



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
void printBoard(int height, int width, PLAYABLE_BLOCK b, char board[height][width])
{
    int i,j;

    // 画面全体を真っ白にする
    clearConsole();

    // 現在操作しているブロックを最上位段に表示する
    printf(" ");
    for (j = 0; j < b.x; j++) {
        printf(" ");
    }
    printf("@");
    for (j = b.x+1; j < width; j++) {
        printf(" ");
    }
    printf(" \n");


    // 盤面を表示する
    for (i = 0; i < height; i++) {
        printf("|");
        for (j = 0; j < width; j++) {
            // ブロックがあればブロックを表示
            if( board[i][j] != 0) {
                printf("@");
            } else {
                printf(" ");
            }
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

// setNewBlock - プレイヤーが操作可能な新たなブロックを返す
PLAYABLE_BLOCK setNewBlock(int width)
{
    PLAYABLE_BLOCK b;
    b.x = width/2;
    return b;
}

void moveBlockRight(PLAYABLE_BLOCK *b, int width)
{
    b->x = b->x+1 >= width ? width-1 : b->x + 1;
    return;
}

void moveBlockLeft(PLAYABLE_BLOCK *b, int width)
{
    b->x = b->x-1 <= 0 ? 0 : b->x - 1;
    return;
}

int fallBlock(int height, int width, PLAYABLE_BLOCK b, char board[height][width])
{
    int y;
    for (y = 1; y < height; y++) {
        if(board[y][b.x] != 0) {
            break;
        }
    }
    board[y-1][b.x] = 1;
    return 0;
}


int main(int argc, char *argv[])
{
    int ch;
    char board[BOARD_HEIGHT][BOARD_WIDTH] = {0};
    PLAYABLE_BLOCK b;

    b = setNewBlock(BOARD_WIDTH);

    while (1) {
        // 入力を受け取る
        ch = getch();
        switch(ch) {
        case 67: // 右をおした時
            moveBlockRight(&b, BOARD_WIDTH);
            break;
        case 68: // 左をおした時
            moveBlockLeft(&b, BOARD_WIDTH);
            break;
        case 65: // 上をおした時
            fallBlock(BOARD_HEIGHT, BOARD_WIDTH, b, board);
            b = setNewBlock(BOARD_WIDTH);
            break;
        default:
            break;

        }

        // 盤面を表示する
        printBoard(BOARD_HEIGHT, BOARD_WIDTH, b, board);

        // 入力を受け取り、信号番号を表示させる。
        printf("input : %d\n", ch);
    }
    return 0;
}
