# 4. 一列揃ったら消す

このセクションでやることは以下の２つです。

 - 一列揃ったらその列を削除する。
 - 消した列数だけ、上からブロックを下に落とす。

まずは、消す所から始めましょう

## 一列揃ったらその列を削除する

一列が埋まっているかどうかを判別する関数``checkDeleteLine``関数を用意します。以下のような具合に

```
int checkDeleteLine(int h, int height, int width, char board[height][width])
{
    int x;
    for (x = 0; x < width; x++){
        if (board[h][x] == 0) {
            return 0;
        }
    }
    return 1;
}
```

この関数は、int型の戻り値を返します。戻り値が1の時は一列削除出来る。
戻り値が0の時は、一列削除できない。となっています。


同様に、実際に一列削除する関数``deleteLine``関数を用意しましょう。

```
void deleteLine(int h, int height, int width, char board[height][width])
{
    int x;
    for (x = 0; x < width; x++){
        board[h][x] = 0;
    }
    return;
}
```

簡単ですね。指定された行の値を全て0にするだけです。

早速、これらの関数を使って、ボードから一列揃った行を削除する関数``deleteIfGather``関数を作ってあげましょう。以下のようになります。


```
void deleteIfGather(int height, int width, char board[height][width])
{
    int x, y;
    for (y = 0; y < height; y++) {
        if ( checkDeleteLine(y, height, width, board)) {
            deleteLine(y, height, width, board);
        }
    }
    return;
}
```


はい、これで準備が整いました。実際にmain 関数からdeleteIfGahther関数を呼び出してみましょう。

変更する部分はmain関数のcase65 上を押したときの処理ですね。
以下のようになります。

```
        case 65: // 上をおした時
            fallBlock(BOARD_HEIGHT, BOARD_WIDTH, b, board);
            b = setNewBlock(BOARD_WIDTH);
            // この行を追加
            deleteIfGather(BOARD_HEIGHT, BOARD_WIDTH, board);
            break;
```


## 一列消したら、上から詰めるように降ってくるようにする。

さて、ここまで完成して実行させると、たしかにブロックは消えるものの、歯抜けみたいな形になります。先程作成した``deleteLine``関数を改良して、消えた行から上の行全てのブロックが降ってくるようにしましょう。

改良後のdeleteLine は以下のようになります。


```
// 実際に一列を削除する
void deleteLine(int h, int height, int width, char board[height][width])
{
    int x;
    // h行目を削除する
    for (x = 0; x < width; x++){
        board[h][x] = 0;
    }

    // h行目から上を全て１段下にさげる。
    for ( h = h; h > 0; h--) {
        for (x = 0; x < width; x++) {
            board[h][x] = board[h-1][x];
        }
    }
    return;
}

```


さて、ココまでやってきて分かってきたと思いますが、C言語においては、機能をわかりやすいように分ける。という事が非常に大切です。何もかもmain に書き込むと、わかりにくくなってしまい、後々「この機能を追加したい」というときに「どこを直せば良いんだっけ？」「ここをいじったらあっちも直さなきゃ」「しっちゃかめっちゃかになってきたーうわー」という事がよくあります。

なので、「機能を関数にわける」というのはぜひマスターしてください。

ここまで約200行。ここでようやく折り返し地点。がんばろう！





