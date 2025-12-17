/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:18:51 by shkondo           #+#    #+#             */
/*   Updated: 2025/08/03 15:34:44 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/**
  * // first_wordフラグで最初の単語を判定
  * 1.先頭の空白をスキップ
  * 2. 文字列を走査しながら：
  * - 単語の開始を検出
  * - 最初の単語でなければスペース3つを出力
  * - 単語全体を出力
  * - 先頭の空白をスキップ
  */ 

int is_space(char c)
{
  return (c == ' ' || c == '\t');
}

int main(int ac, char **av)
{
  int i = 0;
  int first_word = 1;
  if(ac == 2)
  {
    while(av[1][i])
    {
      while(is_space(av[1][i]))
        i++;
      while(av[1][i])
      {
        if(!is_space(av[1][i]))
        {
          if(!first_word)
            write(1, "   ", 3);
          first_word = 0;
      
          while(av[1][i] && !is_space(av[1][i]))
          {
            write(1, &av[1][i], 1);
            i++;
          }
        }
        else
          while(is_space(av[1][i]))
            i++;
      }
    }
  }
  write(1, "\n", 1);
return (0);
}
