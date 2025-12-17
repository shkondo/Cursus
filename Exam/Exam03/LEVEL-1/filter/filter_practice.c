#define _GNU_RESOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	char	*tmp_buffer;
	char	*input_buffer;
	char	*search_str;
	ssize_t	bytes_read;
	size_t	search_len;
	size_t	total_size;
	size_t	buffer_size;
	char	*current_pos;
	char	*buffer_end;
	char	*found;

	if (argc != 2 || !argv[1][0])
		return (1);
	buffer_size = 4096;
	total_size = 0;
	input_buffer = NULL;
	search_str = argv[1];
	search_len = strlen(argv[1]);
	while (1)
	{
		tmp_buffer = realloc(input_buffer, total_size + buffer_size);
		if (!tmp_buffer)
		{
			perror("Error");
			free(input_buffer);
			return (1);
		}
		input_buffer = tmp_buffer;
		bytes_read = read(0, input_buffer + total_size, buffer_size);
		if (bytes_read < 0)
		{
			perror("Error");
			free(input_buffer);
			return (1);
		}
		if (bytes_read == 0)
			break ;
		total_size += buffer_size;
	}
	current_pos = input_buffer;
	buffer_end = input_buffer + total_size;
	while (current_pos < buffer_end)
	{
		found = memmem(current_pos, buffer_end - current_pos, search_str,
				search_len);
		if (found)
		{
			write(1, current_pos, found - current_pos);
			for (size_t i = 0; i < search_len; i++)
				write(1, "*", 1);
			current_pos = found + search_len;
		}
		else
		{
			write(1, current_pos, buffer_end - current_pos);
			break ;
		}
		free(input_buffer);
		return (0);
	}
}
