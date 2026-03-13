# 作業メモ

## 処理の流れ

1. まず `t_philo philo` を定義
1. スレッドを生成: `t_philo philo` に持たせた `pthread_t thread;`を `create_pthread` に渡す？
1. 排他制御が必要な部分に `pthread_mutex_t mut;` を用意する
   1. この課題だと食事をするタイミング？フォークの本数が決まっている？
1. まず**pthread_mutex_init**を実行。
1. 該当の処理の部分に来たら mutex をロックする: `pthread_mutex_lock`
1. 処理が終わったらアンロック: `pthread_mutex_unlock`
1. 3〜4 を、誰か哲学者が死ぬまでループする。死んだら即座に終了する
