/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 21:50:39 by shkondo           #+#    #+#             */
/*   Updated: 2025/11/01 21:50:45 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// compute the distance between two points
float	distance(float a[2], float b[2])
{
	return (sqrtf((b[0] - a[0]) * (b[0] - a[0]) + (b[1] - a[1]) * (b[1]
				- a[1])));
}

float	generate(ssize_t dep, float *best, ssize_t size, int *path, bool *used,
		float (*array)[2])
{
	int		idx1;
	int		idx2;
	float	temp;

	temp = 0;
	if (dep == size)
	{
		for (int i = 0; i < size; i++)
		{
			idx1 = path[i];
			idx2 = path[(i + 1) % size];
			temp += distance(array[idx1], array[idx2]);
		}
		if (temp <= *best)
			*best = temp;
	}
	for (int i = 0; i < size; i++)
	{
		if (!used[i])
		{
			path[dep] = i;
			used[i] = true;
			generate(dep + 1, best, size, path, used, array);
			used[i] = false;
		}
	}
}

float	tsp(float (*array)[2], ssize_t size)
{
	float	best_distance;
	int		*path;
	bool	*used;

	best_distance = INFINITY;
	used = calloc(size, sizeof(bool));
	path = malloc((size) * sizeof(int));
	if (!used || !path)
		return (0);
	generate(0, &best_distance, size, path, used, array);
	return (best_distance);
}

ssize_t	file_size(FILE *file)
{
	char	*buffer;
	size_t	n;
	ssize_t	ret;

	buffer = NULL;
	n = 0;
	errno = 0;
	for (ret = 0; getline(&buffer, &n, file) != -1; ret++)
;
free(buffer);
if (errno || fseek(file, 0, SEEK_SET))
	return (-1);
return (ret);
}

int	retrieve_file(float (*array)[2], FILE *file)
{
	int	tmp;

	for (size_t i = 0; (tmp = fscanf(file, "%f, %f\n", array[i] + 0, array[i]
				+ 1)) != EOF; i++)
		if (tmp != 2)
		{
			errno = EINVAL;
			return (-1);
		}
	if (ferror(file))
		return (-1);
	return (0);
}

int	main(int ac, char **av)
{
	char	*filename;
	FILE	*file;
	ssize_t	size;

	filename = "stdin";
	file = stdin;
	if (ac > 1)
	{
		filename = av[1];
		file = fopen(filename, "r");
	}
	if (!file)
	{
		fprintf(stderr, "Error opening %s: %m\n", filename);
		return (1);
	}
	size = file_size(file);
	if (size == -1)
	{
		fprintf(stderr, "Error reading %s: %m\n", filename);
		fclose(file);
		return (1);
	}
	float(*array)[2] = calloc(size, sizeof(float[2]));
	if (!array)
	{
		fprintf(stderr, "Error: %m\n");
		fclose(file);
		return (1);
	}
	if (retrieve_file(array, file) == -1)
	{
		fprintf(stderr, "Error reading %s: %m\n", av[1]);
		fclose(file);
		free(array);
		return (1);
	}
	if (ac > 1)
		fclose(file);
	printf("%.2f\n", tsp(array, size));
	free(array);
	return (0);
}
