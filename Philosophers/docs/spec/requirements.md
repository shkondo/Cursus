# Philosophers 課題仕様書

## 1. 概要

食事する哲学者の問題をシミュレーションするプログラムを作成する。
スレッドの基礎とミューテックスの使い方を学ぶことが目的。

### シミュレーションのルール

- 1人以上の哲学者が円卓に座っている。テーブルの中央にはスパゲッティの大きなボウルがある。
- 哲学者は「食事」「思考」「睡眠」を交互に繰り返す。これらは同時に行えない。
- テーブル上にはフォークが哲学者と同じ数だけ存在する。
- スパゲッティを食べるには左右両方のフォークを取る必要がある。
- 食事を終えたらフォークをテーブルに戻し、睡眠に入る。起きたら思考を始める。
- 哲学者が飢餓で死亡するとシミュレーションは停止する。
- 全ての哲学者は食事をする必要があり、飢えてはならない。
- 哲学者同士はコミュニケーションしない。
- 他の哲学者が死にかけていることを知る手段はない。

## 2. 共通ルール

### 言語・コーディング規約

- C言語で実装すること。
- 42のNorm規約に従うこと。
- 関数が予期せず終了してはならない（セグフォ、バスエラー、ダブルフリー等）。未定義動作は除く。
- ヒープ確保したメモリは全て適切に解放すること。メモリリーク禁止。
- グローバル変数の使用は禁止。

### Makefile

- コンパイルフラグ: `-Wall -Wextra -Werror`、コンパイラは `cc`。
- 不要な再リンクを行わないこと。
- 必須ルール: `$(NAME)`, `all`, `clean`, `fclean`, `re`
- ボーナスパートがある場合は `bonus` ルールを追加する。

### プログラム引数

```
number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| 引数 | 説明 |
|------|------|
| `number_of_philosophers` | 哲学者の人数（= フォークの数） |
| `time_to_die` (ms) | 最後の食事開始（またはシミュレーション開始）から この時間内に食事を開始しなければ死亡 |
| `time_to_eat` (ms) | 食事にかかる時間。この間2本のフォークを保持する |
| `time_to_sleep` (ms) | 睡眠にかかる時間 |
| `number_of_times_each_philosopher_must_eat` (任意) | 全員がこの回数以上食事したらシミュレーション終了。未指定時は哲学者が死亡するまで継続 |

### 哲学者の番号と配置

- 各哲学者は `1` から `number_of_philosophers` の番号を持つ。
- 哲学者1は哲学者`number_of_philosophers`の隣に座る（円卓）。
- 哲学者Nは哲学者N-1とN+1の間に座る。

### ログ出力フォーマット

哲学者の状態変化は以下の形式で出力すること:

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

- `timestamp_in_ms`: 現在のタイムスタンプ（ミリ秒）
- `X`: 哲学者の番号

### ログ出力のルール

- 状態メッセージの出力が他のメッセージと混在（重複表示）してはならない。
- 哲学者の死亡メッセージは、実際の死亡から **10ms以内** に表示すること。

### データ競合

- プログラムにデータ競合（data race）があってはならない。

## 3. 必須パート (Mandatory)

| 項目 | 内容 |
|------|------|
| プログラム名 | `philo` |
| 提出ファイル | `Makefile`, `*.h`, `*.c`（`philo/` ディレクトリ内） |
| 使用可能な外部関数 | `memset`, `printf`, `malloc`, `free`, `write`, `usleep`, `gettimeofday`, `pthread_create`, `pthread_detach`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_destroy`, `pthread_mutex_lock`, `pthread_mutex_unlock` |
| libft使用 | 不可 |

### 必須パート固有ルール

- 各哲学者は **個別のスレッド** として表現する。
- 各哲学者のペアの間にフォークが1本ずつある。つまり:
  - 複数の哲学者がいる場合、各哲学者の左右にフォークが1本ずつある。
  - 哲学者が1人の場合、フォークは1本のみ。
- フォークの複製を防ぐため、各フォークの状態は **ミューテックス** で保護すること。

## 4. ボーナスパート

| 項目 | 内容 |
|------|------|
| プログラム名 | `philo_bonus` |
| 提出ファイル | `Makefile`, `*.h`, `*.c`（`philo_bonus/` ディレクトリ内） |
| 使用可能な外部関数 | `memset`, `printf`, `malloc`, `free`, `write`, `fork`, `kill`, `exit`, `pthread_create`, `pthread_detach`, `pthread_join`, `usleep`, `gettimeofday`, `waitpid`, `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink` |
| libft使用 | 不可 |

### ボーナスパート固有ルール

- フォークは全てテーブルの中央に置かれる。
- フォークはメモリ上に状態を持たず、利用可能なフォークの数は **セマフォ** で表現する。
- 各哲学者は **個別のプロセス** として表現する。ただし、メインプロセスは哲学者として動作してはならない。

### ボーナス評価条件

必須パートが **完璧** に実装されていない場合、ボーナスパートは評価されない。

## 5. 提出・ディレクトリ構成

```
.
├── philo/          # 必須パート
│   ├── Makefile
│   ├── *.h
│   └── *.c
└── philo_bonus/    # ボーナスパート
    ├── Makefile
    ├── *.h
    └── *.c
```

## 6. README要件

リポジトリのルートに `README.md` を英語で作成すること。以下を含む:

1. **最初の1行**: イタリック体で `This project has been created as part of the 42 curriculum by <login>.`
2. **Description**: プロジェクトの目標と概要
3. **Instructions**: コンパイル・実行方法
4. **Resources**: 関連する参考資料一覧と、AIの使用方法・対象箇所の説明

## 7. 評価時の注意事項

- 評価中にプロジェクトの軽微な修正を求められる場合がある。
- 動作変更、数行のコード追記・書き換え、簡単な機能追加など。
- プロジェクトへの実際の理解度を確認するためのもの。
