# 死亡メッセージの競合状態 (Race Condition)

## 問題の概要

死亡判定後のメッセージ出力と `sim_stop` フラグのセットがアトミックでなかったため、
「died」メッセージの後に他の哲学者のメッセージが出力される可能性があった。

## 修正前のコード

```c
if (time_since_meal > table->time_to_die)
{
    print_status(&table->philos[idx], MSG_DIED);  // (A) print_lock 取得 → 出力 → 解放
    set_sim_stop(table);                           // (B) stop_lock 取得 → sim_stop = 1 → 解放
    return (1);
}
```

### 何が起きるか

```
時間軸 →

モニタースレッド:     (A) print_lock 取得 → "died" 出力 → print_lock 解放  ...  (B) sim_stop = 1
哲学者スレッド:                                             ↑ ここで print_lock を取得
                                                            sim_stop はまだ 0 なので出力してしまう
```

(A) で `print_lock` を解放してから (B) で `sim_stop` をセットするまでの間に、
他のスレッドが `print_status` を呼ぶと:

1. `print_lock` を取得できる (モニターはもう解放済み)
2. `is_sim_stopped` は `0` を返す (まだセットされていない)
3. **「died」の後にメッセージが出力される**

Subject には「A displayed state message should not overlap with another message」とあり、
死亡後のメッセージ出力は評価で減点対象になり得る。

## 修正後のコード

```c
if (time_since_meal > table->time_to_die)
{
    pthread_mutex_lock(&table->print_lock);        // (1) print_lock 取得
    set_sim_stop(table);                           // (2) sim_stop = 1 (print_lock 保持中)
    printf("%ld %d %s\n", get_time() - table->start_time,
        table->philos[idx].id, MSG_DIED);          // (3) "died" 出力
    pthread_mutex_unlock(&table->print_lock);      // (4) print_lock 解放
    return (1);
}
```

### なぜこれで解決するか

```
時間軸 →

モニタースレッド:     (1) print_lock 取得 → (2) sim_stop = 1 → (3) "died" 出力 → (4) print_lock 解放
哲学者スレッド:       print_lock 待ち...                                          ↑ ここでやっと取得
                                                                                  sim_stop == 1 → 出力しない
```

`print_lock` を保持したまま `sim_stop` をセットするので、
他のスレッドが `print_status` に入ったときには必ず `sim_stop == 1` になっている。

## ロック順序に関する補足

この修正により、`check_death` 内のロック取得順序は:

```
meal_lock (取得→解放) → print_lock (取得) → stop_lock (取得→解放) → print_lock (解放)
```

一方、`print_status` (哲学者スレッドが使う) のロック順序は:

```
print_lock (取得) → stop_lock (取得→解放) → print_lock (解放)
```

`print_lock → stop_lock` の順序が一貫しており、
`meal_lock` は他のロックと同時に保持されないため、デッドロックは発生しない。

## 学んだこと

- **フラグのセットと出力はアトミックに行う**: 「状態変更」と「その状態に基づく出力」を
  別々のロックで行うと、間に他スレッドが割り込む余地が生まれる
- **ロック順序を意識する**: 複数の mutex を使う場合、全スレッドで取得順序を統一しないと
  デッドロックの原因になる (次節の補足も参照)
- **print_lock の中で sim_stop をセットする理由**: 出力の排他制御に使っている
  print_lock を「出力可否の判定とフラグ変更」まで含めて保護範囲にすることで、
  判定と出力の間に状態が変わることを防ぐ

## 補足: デッドロック防止の2つのアプローチ

上記の「ロック順序の統一」は、デッドロック防止の手法の1つに過ぎない。
本プロジェクトでは、リソースの性質に応じて2つの異なるアプローチを使い分けている。

### 1. ロック順序の統一 — print_lock / stop_lock

異なる役割のロックを複数スレッドがネストして取得するケース。
全スレッドで `print_lock → stop_lock` の順序を統一することで、
スレッド A が `print_lock → stop_lock` の順に待ち、
スレッド B が `stop_lock → print_lock` の順に待つという循環を防ぐ。

### 2. 循環待ちの破壊 — フォーク (偶数/奇数)

フォークは円環状に並んだ同種のリソースで、全員が同じ方向に取ると循環待ちが発生する:

```
全員が左→右で取る場合:
哲学者1: fork[0] 取得 → fork[1] 待ち
哲学者2: fork[1] 取得 → fork[2] 待ち
哲学者3: fork[2] 取得 → fork[0] 待ち  ← 1が持ってる → デッドロック
```

偶数/奇数で取得方向を逆にすると、隣同士が同じフォークを先に取り合わないので循環が断ち切れる:

```
哲学者1(奇数): fork[0] → fork[1]
哲学者2(偶数): fork[2] → fork[1]  ← 競合する fork[1] を「後」に取る
```

これは「順序の統一」ではなく、デッドロック成立に必要な4条件の1つである
**循環待ち (circular wait)** を壊すアプローチ。

### 比較

| | フォーク | print_lock / stop_lock |
|---|---|---|
| 構造 | 円環状に並んだ同種のリソース | 異なる役割のロック |
| 手法 | 循環待ちの破壊 (偶数/奇数) | 取得順序の統一 |
| 防ぐもの | 全員が隣のフォークを待つ循環 | A→B と B→A のネスト競合 |

どちらもデッドロックの4条件 (相互排他・保持と待機・横取り不可・循環待ち) の
いずれかを崩すという点では同じ考え方に基づいている。
