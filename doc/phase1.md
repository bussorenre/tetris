
# 1. 盤面を作り表示する

まずは盤面を作り表示します。

本家テトリスの盤面は、縦20マス、横10マスで構成されておりますが、ココではどんなサイズでも構いません。

ここでは、盤面サイズの定義に``#define``を使います。

```main.c
#define BOARD_HEIGHT 20
#define BOARD_WIDTH  10
```

また、盤面の状況を描画するための、関数``printBoard``を作成します。これは、ボードの縦幅、横幅、そしてボードのデータそのものを受け取って、画面上にボードをprintfで描画するための関数です。

```main.c
void printBoard(int height, int width, char *board)
{
    int i,j;

    // 画面全体を全部初期化する
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
```

``clearConsole``は自作の関数で、内容は以下のようになってます。

```main.c
void clearConsole() {
    printf("\x1b[2J");
    return;
}
```

これは、ターミナルを制御する特殊なエスケープシーケンスをprintfで出力しており、他にも以下のようなエスケープシーケンスが存在します。

[ANSIエスケープコード - コンソール制御 - 碧色工房](http://www.mm2d.net/main/prog/c/console-02.html)

ここで出て来るESCを入力するために、``\x1b``を利用しています。ASCIIコードで16進数で1b というのがESCに当たるためです。詳しくは[ASCII文字コード ： IT用語辞典](http://e-words.jp/p/r-ascii.html)を見てください。

ここまで完成すると、phase1.cのようなコードになり、実行すると以下のような文字列が画面上に出力されます。


```phase1
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
|          |
------------

```

