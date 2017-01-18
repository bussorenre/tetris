# 2. ユーザー入力を受け取る

コンソール上でユーザー入力を受け取るには、scanfやgetsやfgetsなどの方法がありますが、ここでは``getch`` を使います。

ただ、このgetch関数はwindows にしか存在しない関数なので、mac の場合は自ら作成する必要があります。

具体的には以下のようなコードになります。

```main.c
#include <termios.h>
#include <unistd.h>

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
```

このコードに関して深くは開設しませんが、コンソールに対して「ICANON」「ECHO」というフラグをオフにしてあげてgetchar すると、Enter の入力を待たずに入力が入ってき、画面上にも表示されなくなります。


これらを踏まえて以下のようにmain関数を変更します。


```main.c
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

```

なお、このプログラムを実行させると、Ctrl-Cを押して強制終了しないと終了しません。（Ctrl-Cを押すことを、今後C-c と表記します）

ここまでのサンプルは``phase2.c`` にあります。
