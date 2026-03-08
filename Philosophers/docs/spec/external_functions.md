# 使用可能な外部関数リファレンス

必須パートで使用が許可されている外部関数のうち、スレッド操作・時刻取得に関する関数をまとめる。

> **注記**: `memset`, `printf`, `malloc`, `free`, `write`, `usleep` は標準Cライブラリ関数のため本ドキュメントでは省略する。

> **ボーナスパートについて**: ボーナス課題では追加で `fork`, `kill`, `exit`, `waitpid`, `sem_open`, `sem_close`, `sem_post`, `sem_wait`, `sem_unlink` が使用可能だが、本ドキュメントでは対象外とする。

---

## 目次

1. [gettimeofday](#1-gettimeofday)
2. [pthread_create](#2-pthread_create)
3. [pthread_detach](#3-pthread_detach)
4. [pthread_join](#4-pthread_join)
5. [pthread_mutex_init](#5-pthread_mutex_init)
6. [pthread_mutex_destroy](#6-pthread_mutex_destroy)
7. [pthread_mutex_lock](#7-pthread_mutex_lock)
8. [pthread_mutex_unlock](#8-pthread_mutex_unlock)

---

## 1. gettimeofday

現在時刻をマイクロ秒精度で取得する。タイムスタンプの算出に使用する。

### ヘッダ

```c
#include <sys/time.h>
```

### プロトタイプ

```c
int	gettimeofday(struct timeval *restrict tp, void *restrict tzp);
```

### 関連する構造体

```c
struct timeval {
    time_t       tv_sec;   /* 秒（1970年1月1日からの経過秒数） */
    suseconds_t  tv_usec;  /* マイクロ秒（0〜999999） */
};
```

### 引数

| 引数 | 説明 |
|------|------|
| `tp` | 現在時刻が格納される `struct timeval` へのポインタ |
| `tzp` | タイムゾーン情報（**廃止済み。常に `NULL` を渡す**） |

### 戻り値

- 成功時: `0`
- 失敗時: `-1`（`errno` がセットされる）

### 本課題での用途

シミュレーション開始時の基準時刻を記録し、ログ出力時に経過ミリ秒を算出するために使う。

```c
/* 経過ミリ秒の算出例 */
struct timeval	now;
long			elapsed_ms;

gettimeofday(&now, NULL);
elapsed_ms = (now.tv_sec - start.tv_sec) * 1000
    + (now.tv_usec - start.tv_usec) / 1000;
```

---

## 2. pthread_create

新しいスレッドを生成する。

### ヘッダ

```c
#include <pthread.h>
```

### プロトタイプ

```c
int	pthread_create(pthread_t *thread, const pthread_attr_t *attr,
        void *(*start_routine)(void *), void *arg);
```

### 引数

| 引数 | 説明 |
|------|------|
| `thread` | 生成されたスレッドのIDが格納される |
| `attr` | スレッド属性。`NULL` でデフォルト属性を使用 |
| `start_routine` | スレッドが実行する関数へのポインタ |
| `arg` | `start_routine` に渡される引数 |

### 戻り値

- 成功時: `0`（`thread` にスレッドIDが格納される）
- 失敗時: エラーコード（`errno` は**セットされない**）

### 主なエラー

| エラーコード | 意味 |
|-------------|------|
| `EAGAIN` | スレッド生成に必要なリソースが不足している |
| `EINVAL` | `attr` の値が不正 |

### 本課題での用途

各哲学者を個別のスレッドとして生成する。

```c
pthread_t	thread;
int			ret;

ret = pthread_create(&thread, NULL, philosopher_routine, (void *)philo);
if (ret != 0)
    /* エラー処理 */
```

---

## 3. pthread_detach

スレッドをデタッチ状態にする。デタッチされたスレッドは終了時に自動的にリソースが回収される。

### ヘッダ

```c
#include <pthread.h>
```

### プロトタイプ

```c
int	pthread_detach(pthread_t thread);
```

### 引数

| 引数 | 説明 |
|------|------|
| `thread` | デタッチするスレッドのID |

### 戻り値

- 成功時: `0`
- 失敗時: エラーコード

### 主なエラー

| エラーコード | 意味 |
|-------------|------|
| `EINVAL` | 対象スレッドがjoin可能な状態でない |
| `ESRCH` | 指定されたスレッドIDが見つからない |

### 注意点

- デタッチしたスレッドに対して `pthread_join` は呼べない。
- スレッドの終了を待つ必要がない場合（例: 監視スレッド）に使う。
- デタッチしても**スレッドの実行は停止しない**。リソース回収のタイミングが変わるだけ。

---

## 4. pthread_join

指定したスレッドの終了を待機する。

### ヘッダ

```c
#include <pthread.h>
```

### プロトタイプ

```c
int	pthread_join(pthread_t thread, void **value_ptr);
```

### 引数

| 引数 | 説明 |
|------|------|
| `thread` | 待機するスレッドのID |
| `value_ptr` | スレッドの戻り値を受け取るポインタ。不要なら `NULL` |

### 戻り値

- 成功時: `0`
- 失敗時: エラーコード

### 主なエラー

| エラーコード | 意味 |
|-------------|------|
| `EINVAL` | 対象スレッドがjoin可能でない |
| `ESRCH` | 指定されたスレッドIDが見つからない |
| `EDEADLK` | デッドロックが検出された（自分自身をjoinしようとした等） |

### 本課題での用途

メインスレッドで全哲学者スレッドの終了を待つ。

```c
int	idx;

idx = 0;
while (idx < num_philos)
{
    pthread_join(threads[idx], NULL);
    idx++;
}
```

### `pthread_join` と `pthread_detach` の使い分け

| 項目 | `pthread_join` | `pthread_detach` |
|------|---------------|-----------------|
| 終了待機 | 呼び出しスレッドがブロックして待つ | 待たない |
| リソース回収 | join時に回収 | 終了時に自動回収 |
| 戻り値の取得 | 可能 | 不可 |
| 併用 | 不可（どちらか一方） | 不可（どちらか一方） |

---

## 5. pthread_mutex_init

ミューテックスを初期化する。

### ヘッダ

```c
#include <pthread.h>
```

### プロトタイプ

```c
int	pthread_mutex_init(pthread_mutex_t *mutex,
        const pthread_mutexattr_t *attr);
```

### 引数

| 引数 | 説明 |
|------|------|
| `mutex` | 初期化するミューテックスへのポインタ |
| `attr` | ミューテックス属性。`NULL` でデフォルト属性を使用 |

### 戻り値

- 成功時: `0`
- 失敗時: エラーコード

### 主なエラー

| エラーコード | 意味 |
|-------------|------|
| `EINVAL` | `attr` の値が不正 |
| `ENOMEM` | メモリ不足 |

### 注意点

- 使用前に必ず初期化すること。
- 静的に確保したミューテックスは `PTHREAD_MUTEX_INITIALIZER` マクロでも初期化可能。
- 既に初期化済みのミューテックスを再度初期化した場合の動作は未定義。

---

## 6. pthread_mutex_destroy

ミューテックスを破棄し、関連リソースを解放する。

### ヘッダ

```c
#include <pthread.h>
```

### プロトタイプ

```c
int	pthread_mutex_destroy(pthread_mutex_t *mutex);
```

### 引数

| 引数 | 説明 |
|------|------|
| `mutex` | 破棄するミューテックスへのポインタ |

### 戻り値

- 成功時: `0`
- 失敗時: エラーコード

### 主なエラー

| エラーコード | 意味 |
|-------------|------|
| `EINVAL` | ミューテックスの値が不正 |
| `EBUSY` | ミューテックスがロックされている |

### 注意点

- **ロック中のミューテックスは破棄できない。** 必ず全スレッドの終了後に呼ぶこと。
- 破棄後に使用した場合の動作は未定義。
- 破棄後に `pthread_mutex_init` で再初期化は可能。

---

## 7. pthread_mutex_lock

ミューテックスをロック（獲得）する。

### ヘッダ

```c
#include <pthread.h>
```

### プロトタイプ

```c
int	pthread_mutex_lock(pthread_mutex_t *mutex);
```

### 引数

| 引数 | 説明 |
|------|------|
| `mutex` | ロックするミューテックスへのポインタ |

### 戻り値

- 成功時: `0`
- 失敗時: エラーコード

### 主なエラー

| エラーコード | 意味 |
|-------------|------|
| `EINVAL` | ミューテックスの値が不正 |
| `EDEADLK` | デッドロックが検出された |

### 動作

- ミューテックスが**未ロック**: 即座にロックを獲得し、呼び出し元がオーナーとなる。
- ミューテックスが**他のスレッドによりロック中**: ロックが解放されるまで呼び出し元スレッドは**ブロック（待機）**する。
- ミューテックスが**自スレッドによりロック中**: デフォルト型ではデッドロックになる。

### 本課題での用途

フォーク（共有資源）へのアクセスを排他制御する。

```c
pthread_mutex_lock(&fork_mutex[left]);
/* フォークを取った旨のログ出力 */
pthread_mutex_lock(&fork_mutex[right]);
/* フォークを取った旨のログ出力 */
/* 食事処理 */
pthread_mutex_unlock(&fork_mutex[right]);
pthread_mutex_unlock(&fork_mutex[left]);
```

---

## 8. pthread_mutex_unlock

ミューテックスのロックを解放する。

### ヘッダ

```c
#include <pthread.h>
```

### プロトタイプ

```c
int	pthread_mutex_unlock(pthread_mutex_t *mutex);
```

### 引数

| 引数 | 説明 |
|------|------|
| `mutex` | ロック解放するミューテックスへのポインタ |

### 戻り値

- 成功時: `0`
- 失敗時: エラーコード

### 主なエラー

| エラーコード | 意味 |
|-------------|------|
| `EINVAL` | ミューテックスの値が不正 |
| `EPERM` | 呼び出し元がロックを保持していない |

### 注意点

- **ロックを獲得したスレッドが解放すること。** 別のスレッドが解放した場合の動作は未定義。
- `pthread_mutex_lock` と必ずペアで使用する。

---

## pthread 関数の共通注意事項

1. **エラーハンドリング**: pthread 系関数は `errno` をセットしない。戻り値が直接エラーコードとなる。
2. **コンパイル**: `-pthread` フラグを付けてコンパイルする。
3. **リソース管理**: `init` したミューテックスは必ず `destroy` する。`create` したスレッドは `join` または `detach` する。

---

## ボーナスパート専用関数（参考）

以下の関数はボーナスパートでのみ使用可能。必須パートでは使用不可。

| 関数 | 用途 |
|------|------|
| `fork` | 子プロセスを生成（哲学者を個別プロセスとして表現） |
| `kill` | プロセスにシグナルを送信 |
| `exit` | プロセスを終了 |
| `waitpid` | 子プロセスの終了を待機 |
| `sem_open` | 名前付きセマフォを生成・オープン |
| `sem_close` | セマフォをクローズ |
| `sem_post` | セマフォの値をインクリメント（シグナル） |
| `sem_wait` | セマフォの値をデクリメント（待機） |
| `sem_unlink` | 名前付きセマフォを削除 |
