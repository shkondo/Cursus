/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rostring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 19:58:20 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/20 20:30:53 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int is_space(char c)
{
  return (c == ' ' || c == '\t');
}

void rostring(char *str)
{
  int i;
  int first_word_start;
  int first_word_end;
  int has_other_words;

  i = 0;
  has_other_words = 0;

  while(str[i] && is_space(str[i]))
    i++;

  // 最初の単語の開始位置を記録
  first_word_start = i;
  // 最初の単語の終了位置を見つける
  while(str[i] && !is_space(str[i]))
    i++;
  first_word_end = i -1;

  // 残りの単語があるかチェック
  while(str[i] && is_space(str[i]))
    i++;
  if(str[i])
    has_other_words = 1; // フラグを立てる
  // 2番目以降を先に出力
  if(has_other_words)
  {
    // 最初の単語の後の空白をスキップ
    i = first_word_end + 1;
    while(str[i] && is_space(str[i]))
      i++;
    // 残りの単語を出力
    while(str[i])
    {
      if(is_space(str[i]))
      {
        // 複数の空白を一つの空白にまとめる
        write(1, " ", 1);
        while(str[i] && is_space(str[i]))
          i++;
      }
      else {
      write(1, &str[i], 1);
        i++;
      }
    }
    // 最初の単語の前にスペースを追加
    write(1, " ", 1);
  }
  // 最初の単語を出力
  i = first_word_start;
  while(i <= first_word_end)
  {
    write(1, &str[i], 1);
    i++;
  }
}

int main(int ac,  char **av)
{
  if(ac >= 2 && av[1][0] != '\0')
    rostring(av[1]);
  write(1, "\n", 1);
return (0);
}
