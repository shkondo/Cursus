# practice.c レビュー — 当初の実装の問題点

元の `practice.c` を題材に、何が問題だったかを分類して解説する。

---

## 1. コンパイルが通らないエラー

### 1-1. 条件式の論理ミス (main:112)

```c
if (argc != 5 || argc != 6)   // 常に true になる
```

`argc` は必ず 5 か 6 のどちらか「ではない」ため、OR だと常に真。

```c
// 修正
if (argc != 5 && argc != 6)
```

### 1-2. 関数ポインタ構文の誤り (philo_init:15)

```c
void philo_init(int number_of_philosophers, (void *)philo_exec(philo), t_philo *philo)
```

C の関数ポインタ引数はこう書けない。正しくは:

```c
void philo_init(int nb, void (*func)(t_philo *), t_philo *philo)
```

ただし、この課題では関数ポインタを引数に渡す設計自体が不要。
各哲学者スレッドのルーチンは `pthread_create` の第3引数で直接渡せばよい。

### 1-3. printf のシングルクォート (print_timestamp:84)

```c
printf('%d %d has taken a fork', elapsed_ms, philo->id);
```

C の文字列リテラルはダブルクォート `"..."` を使う。`'...'` は文字定数（char）。

### 1-4. 未宣言の変数 `start` (print_timestamp:82)

```c
elapsed_ms = (now.tv_sec - start.tv_sec) * 1000 ...
```

`start` はどこにも宣言されていない。シミュレーション開始時刻は
グローバル（禁止）ではなく、構造体に保持して渡す必要がある。

### 1-5. 構造体を値渡ししてポインタ操作 (count_to_die:87)

```c
int count_to_die(t_philo philo, int time_to_die)
{
    thread = philo->thread;  // philo は値なのに -> は使えない
```

`t_philo philo`（値渡し）なら `philo.thread`。
`philo->thread` を使いたいなら `t_philo *philo`（ポインタ渡し）にする。

### 1-6. data_init の引数が 5 個 (data_init:101)

```c
void data_init(int number_of_philosophers, int time_to_die, int time_to_eat,
    int time_to_sleep, int number_of_times_of_each_philosopher_must_eat)
```

42 Norm では関数の引数は **最大 4 個**。構造体ポインタ 1 つにまとめるべき。

---

## 2. 実行時に壊れるバグ

### 2-1. malloc 失敗時に free (main:116)

```c
tmp = malloc(...);
if (!tmp)
{
    free(tmp);   // NULL を free している（無害だが無意味）
    return (1);
}
```

`malloc` が `NULL` を返したらそのまま `return (1)` でよい。

### 2-2. argv[5] の無条件アクセス (main:122)

```c
data_init(ft_atoi(argv[1]), ft_atoi(argv[2]), ft_atoi(argv[3]),
    ft_atoi(argv[4]), ft_atoi(argv[5]));
```

`argc == 5` の場合 `argv[5]` は存在しない。
5番目の引数は任意なので、`argc == 6` のときだけアクセスする必要がある。

### 2-3. 未初期化の mutex を lock (philo_meal:38)

```c
pthread_mutex_t mut;
pthread_mutex_lock(&mut);  // init していない → 未定義動作
```

mutex は使用前に必ず `pthread_mutex_init()` で初期化する。
そもそも関数内のローカル mutex では他スレッドと排他制御できない。

### 2-4. 未初期化変数 time の比較 (count_to_die:95)

```c
int time;
// time に値を代入していない
if (time > time_to_die)
```

未初期化変数の読み取りは未定義動作。

### 2-5. 無限ループ (philo_init:25, philo_meal:41, philo_sleep:58)

```c
while (count < number_of_philosophers)  // count が変化しない
while (data->time_to_eat)               // 値が変化しない
while (data->time_to_sleep)             // 値が変化しない
```

いずれもループ変数を更新していないため無限ループになる。
`time_to_eat` はミリ秒の定数値であり、ループの条件に使うものではない。
正しくは `usleep` / `precise_sleep` で時間経過を待つ。

---

## 3. 設計・アーキテクチャの問題

### 3-1. 「フォーク」の扱いが不正確

```c
philo->fork += 1;  // int 値のインクリメントで「フォーク取得」を表現
```

フォークは哲学者間の **共有資源** であり、各フォークに対応する mutex を
lock/unlock することで排他制御する。整数のインクリメントでは他スレッドとの
排他制御にならない。

**正しいモデル:**
- フォークの数 = 哲学者の数
- 哲学者 N の左フォーク = forks[N]、右フォーク = forks[(N+1) % 総数]
- フォーク取得 = `pthread_mutex_lock(&forks[idx])`
- フォーク返却 = `pthread_mutex_unlock(&forks[idx])`

### 3-2. スレッドの生成が 1 回だけ

```c
ret = pthread_create(&thread, NULL, philosopher_routine, (void *)philo);
while (count < number_of_philosophers) { ... }
```

`pthread_create` がループの外にあるため、スレッドが 1 つしか生成されない。
哲学者の数だけループ内で `pthread_create` を呼ぶ必要がある。

### 3-3. 死亡判定がスレッド内にない

`count_to_die` は「各哲学者スレッド内で自分の死亡を判定する」設計に見えるが、
これだと死亡した哲学者自身が報告する必要がある（死んだら動けない）。

**正しい設計:** メインスレッドで **監視ループ** を回し、全哲学者の
`最終食事時刻` を定期的にチェックして死亡判定する。

### 3-4. ログ出力の排他制御がない

```c
printf('%d %d has taken a fork', elapsed_ms, philo->id);
```

複数スレッドが同時に `printf` を呼ぶとメッセージが混在する。
出力用の mutex でログ全体を保護する必要がある。

### 3-5. シミュレーション停止の仕組みがない

哲学者が死亡したとき、または全員が規定回数食事したとき、
全スレッドに「停止」を通知するフラグが必要。
mutex で保護したフラグを各スレッドが定期的にチェックする設計にする。

---

## 4. 正しい設計のまとめ

```
メインスレッド                   哲学者スレッド (N個)
─────────────                   ──────────────────
引数パース                       ┌→ フォーク取得 (mutex lock x2)
構造体初期化                     │  食事 (usleep)
mutex 初期化                     │  フォーク返却 (mutex unlock x2)
pthread_create x N               │  睡眠 (usleep)
  ↓                              │  思考
監視ループ                       └─ sim_stop なら終了
  各哲学者の最終食事時刻チェック
  死亡 or 全員完食 → sim_stop = 1
  ↓
pthread_join x N
mutex destroy
free
```

**重要な原則:**
1. 共有データへのアクセスは必ず mutex で保護する
2. mutex はグローバルに管理し、init → 使用 → destroy のライフサイクルを守る
3. `usleep` で時間を待つ（ビジーループではなく）
4. デッドロック防止: フォーク取得順序を統一する（奇数/偶数で分ける）
