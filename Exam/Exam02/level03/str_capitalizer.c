/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_capitalizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:44:03 by shkondo           #+#    #+#             */
/*   Updated: 2025/08/07 11:50:40 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int is_alpha(char c)
{
  return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int is_separator(char c)
{
  return (c == ' ' || c == '\t');
}

char	to_upper(char c)
{
  if(c >= 'a' && c <= 'z')
    return (c - 32);
  return c;
}

int	to_lower(char c)
{
  if(c >= 'A' && c <= 'Z')
    return (c + 32);
  return c;
}

void capitalize_string(char *str)
{
  int i;
  int in_word;
  char c;

  i = 0;
  in_word = 0;
  while(str[i])
  {
    if(is_separator(str[i]))
    {
      in_word = 0;
      write(1, &str[i], 1);
    }
    else if(is_alpha(str[i]))
    {
      if(!in_word)
      {
        c = to_upper(str[i]);
        in_word = 1;
      }
      else
        c = to_lower(str[i]);
      write(1, &c, 1);
    }
    else
    {
      in_word = 0;
      write(1, &str[i], 1);
    }
    i++;
  }
}

int	main(int ac, char **av)
{
	int	i;

	if (ac < 2)
	{
		write(1, "\n", 1);
		return (0);
	}
	
		i = 1;
		while (i < ac)
		{
    capitalize_string(av[i]);
    write(1, "\n", 1);
    i++;
		}	
	return (0);
}
