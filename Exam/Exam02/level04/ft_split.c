/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 12:57:45 by shkondo           #+#    #+#             */
/*   Updated: 2025/08/09 14:34:21 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	is_charset(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *str)
{
	int		i;
	size_t	len;
	char	*res;

	i = 0;
	len = ft_strlen(str) + 1;
	res = (char *)malloc(len * sizeof(char));
	if (!res)
		return (NULL);
	while (!is_charset(str[i]))
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	count_words(char *str)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (str[i])
	{
		while (is_charset(str[i]))
			i++;
		while (!is_charset(str[i]))
		{
			if (in_word == 0)
			{
				count++;
				in_word = 1;
			}
			i++;
		}
		in_word = 0;
	}
	return (count);
}

char	**ft_split(char *str)
{
	int		i;
	int		j;
	char	**res;

	res = (char **)malloc((count_words(str) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	j = 0;
	while (str[i])
	{
		while (is_charset(str[i]))
			i++;
		res[j] = ft_strdup(&str[i]);
		i++;
	}
	res[j] = 0;
	return (res);
}

int	main(int ac, char **av)
{
	char	**res;
	int		i;

	if (ac == 3)
	{
		res = ft_split(av[1]);
		while (res[i])
		{
			printf("%s", res[i]);
			i++;
		}
	}
	printf("\n");
	return (0);
}
