# 3. １つのブロックを落とす

さて、ここからが本番です。ブロックを落とします。
複雑な形のブロックを落とす前に、まずは幅１マス、高さ１マスの小さなブロックを落とします。

本家テトリスでは、十字キーの上を押すとブロックが一番下まで落ちてきます。十字キーの左右を押すと、ブロックが左に、右に、移動します。

それぞれ、``fallBlock``, ``moveBlockRight``, ``moveBlockLeft`` 関数を用意します。

また、ゲームの一番はじめ、及び、ブロックを一番下に置いた時に、次のブロックを呼び出すための関数 ``setNewBlock``も作成します。

また、前回作成したgetch でユーザーのキー入力を受け取れる状態になっているので、switch（またはif-else）で、ユーザーの入力を受け取った後、上記関数を呼び出すようにしましょう。

プロトタイプとしては、以下のようになります。


```

int setNewBlock() {
    return 0;
}

int moveBlockRight() {
    return 0;
}

int moveBlockLeft() {
    return 0;
}

int fallBlock() {
    return 0;
}


int main(int argc, char *argv[])
{
    int ch;
    char board[BOARD_HEIGHT][BOARD_HEIGHT] = {0};
    
    setNewBlock();

    while (1) {
        // 入力を受け取る
        ch = getch();
        switch(ch) {
        case 67: // 右をおした時
            moveBlockRight();
            break;
        case 68: // 左をおした時
            moveBlockLeft();
            break;
        case 65: // 上をおした時
            fallBlock();
            setNewBlock();
            break;
        default:
            break;

        }

        // 盤面を表示する
        printBoard(BOARD_HEIGHT, BOARD_WIDTH, board);

        // 入力を受け取り、信号番号を表示させる。
        printf("input : %d\n", ch);
    }
    return 0;
}

```

あくまでこれはプロトタイプです。コレでは全然不十分です。これらの関数の中身をしっかり用意してあげる必要があります。


## ブロックの情報を構造体にまとめ上げる。

プレイヤーが操作するブロックが持つ情報を以下のようにまとめ上げます。


```
typedef struct {
    int x;
}PLAYABLE_BLOCK;
```

まだ要素がx座標しか無いので、「別に構造体にしなくてもええやん」と思うかもしれませんが、後々重要になってきますので、今は我慢してください。


## setNewBlock で新しいPLAYABLE_BLOCK を返すようにする。

```
// setNewBlock - プレイヤーが操作可能な新たなブロックを返す
PLAYABLE_BLOCK setNewBlock(int width)
{
    PLAYABLE_BLOCK b;
    b.x = width/2;
    return b;
}

```

先程作成したPLAYABLE_BLOCK 構造体を返す関数になりました。

## printBoard 関数に、現在のブロックを表示させるロジックを追記する。

```
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
            if(board[i][j] != 0) {
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

```

変更点は、PLAYABLE_BLOCKを引数に取るようになったことと、画面最上部に、プレイヤーが操作しているブロックが表示されるようになった事です。

## moveBlockRightとmoveBlockLeft を実装する。

これは非常に簡単ですが、今回は実装にポインタを使います。最終的には以下のようなコードになります。

注意すべき点は、ただx座標を+1、-1するだけでは不十分で、左右の壁に当たった時、行き過ぎないように計算する必要があります。


```
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


```


さて、このコード、ポインタになれていないと見るのが少々しんどいかもしれません。なんで``*b.x`` じゃなくて``b->x`` やねんと。確かに``(*b).x``と記述することも可能ですが、これはC言語ではこういうふうに書くもんなんだと諦めてもらうしか無いです。構造体のポインタのメンバ変数にアクセスするときは、アロー演算子（``->``）を利用します。



## ついにブロックをボード上に落とす

```
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
```

下にブロックがあれば、その上にブロックを置く。地味にこの処理を素で一発で書くのは難しい。試行錯誤されたし。


ここまでで、約150行！まだまだ先は長いががんばろう！

