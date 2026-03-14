# C++ Module 00 - 課題要件

## 共通ルール

### コンパイル
- コンパイラ: `c++`
- フラグ: `-Wall -Wextra -Werror`
- `-std=c++98` でもコンパイルが通ること

### 命名規則・フォーマット
- ディレクトリ名: `ex00`, `ex01`, ..., `exn`
- クラス名: **UpperCamelCase**
- クラスのファイル名はクラス名に合わせる (例: `BrickWall.hpp`, `BrickWall.cpp`)
- 出力メッセージは末尾に改行文字をつけ、標準出力に表示

### 禁止事項
- 外部ライブラリの使用禁止 (C++11以降、Boost等)
- 禁止関数: `*printf()`, `*alloc()`, `free()`
- `using namespace <ns_name>` と `friend` キーワード (明示的に許可されない限り)
- STL (Containers, Algorithms) は Module 08, 09 まで使用禁止

### 設計要件
- メモリリークを避けること (`new` 使用時)
- ヘッダファイルに関数の実装を書かない (関数テンプレートを除く)
- 各ヘッダは独立して使用可能で、インクルードガードを付けること

### Makefile
- C プロジェクトと同じルールが適用される

---

## Exercise 00: Megaphone

| 項目 | 内容 |
|------|------|
| ディレクトリ | `ex00/` |
| 提出ファイル | `Makefile`, `megaphone.cpp` |
| 禁止事項 | なし |

### 要件
- コマンドライン引数を全て大文字に変換して出力するプログラム
- 引数なしの場合は `* LOUD AND UNBEARABLE FEEDBACK NOISE *` を出力

### 動作例
```
$>./megaphone "shhhhh... I think the students are asleep..."
SHHHHH... I THINK THE STUDENTS ARE ASLEEP...
$>./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.
$>./megaphone
* LOUD AND UNBEARABLE FEEDBACK NOISE *
```

### 注意点
- C++ らしい書き方で実装すること

---

## Exercise 01: My Awesome PhoneBook

| 項目 | 内容 |
|------|------|
| ディレクトリ | `ex01/` |
| 提出ファイル | `Makefile`, `*.cpp`, `*.{h, hpp}` |
| 禁止事項 | なし |

### 要件
80年代風の電話帳プログラムを実装する。

### クラス設計

#### Contact クラス
- 電話帳の連絡先1件を表す
- フィールド: first name, last name, nickname, phone number, darkest secret

#### PhoneBook クラス
- Contact の配列を持つ
- 最大 **8件** まで格納可能。9件目を追加する場合は最も古いものを置き換える
- **動的メモリ確保は禁止**

### コマンド

#### ADD
- 連絡先の情報を1フィールドずつ入力させる
- フィールド: first name, last name, nickname, phone number, darkest secret
- 空フィールドは許可しない (保存時に全フィールドが必要)

#### SEARCH
- 保存された連絡先を **4列** の一覧で表示
  - 列: index, first name, last name, nickname
  - 各列は **10文字幅**、パイプ `|` で区切り、**右寄せ**
  - 10文字を超える場合は切り詰めて末尾を `.` に置換
- その後、表示したいエントリの index を入力させる
  - 範囲外や不正な index には適切なエラー処理を行う
  - 正常な場合は全フィールドを1行1項目で表示

#### EXIT
- プログラムを終了 (連絡先は破棄される)

#### その他
- 上記以外の入力は無視する
- コマンド実行後は次のコマンドを待つ
- 実行ファイルには適切な名前をつける

### 参考
- `std::string`, `<iomanip>` の使用が推奨されている

---

## Exercise 02: The Job Of Your Dreams

| 項目 | 内容 |
|------|------|
| ディレクトリ | `ex02/` |
| 提出ファイル | `Makefile`, `Account.cpp`, `Account.hpp`, `tests.cpp` |
| 禁止事項 | なし |
| 必須 | **いいえ** (このモジュールの合格には不要) |

### 要件
- 提供される `Account.hpp`, `tests.cpp`, ログファイルを元に、削除された `Account.cpp` を再現する
- `tests.cpp` をコンパイル・実行し、出力がログファイルと一致すること
  - **タイムスタンプは異なっていてよい** (ログファイルは過去に実行されたもののため)

### Account クラス (Account.hpp より)

#### 静的メンバ変数
- `_nbAccounts`: アカウント総数
- `_totalAmount`: 全アカウントの合計金額
- `_totalNbDeposits`: 全アカウントの入金総回数
- `_totalNbWithdrawals`: 全アカウントの出金総回数

#### 静的メンバ関数
- `getNbAccounts()`: アカウント総数を返す
- `getTotalAmount()`: 合計金額を返す
- `getNbDeposits()`: 入金総回数を返す
- `getNbWithdrawals()`: 出金総回数を返す
- `displayAccountsInfos()`: 全アカウントの集計情報を表示
- `_displayTimestamp()`: タイムスタンプを表示 (private)

#### インスタンスメンバ変数
- `_accountIndex`: アカウントの通し番号
- `_amount`: 残高
- `_nbDeposits`: 入金回数
- `_nbWithdrawals`: 出金回数

#### インスタンスメンバ関数
- `Account(int initial_deposit)`: コンストラクタ (初期入金額を受け取る)
- `~Account()`: デストラクタ
- `makeDeposit(int deposit)`: 入金
- `makeWithdrawal(int withdrawal)`: 出金 (成功時 true, 失敗時 false)
- `checkAmount() const`: 残高を返す
- `displayStatus() const`: アカウントの状態を表示

### 注意点
- デストラクタの呼び出し順序はコンパイラ/OS によって異なる場合がある (逆順になりうる)
- ログファイルの出力フォーマットを正確に再現すること
