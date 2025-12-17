#include <stdio.h> // printfのため（デバッグ用）
#include <stdlib.h>
#include <unistd.h>

void	print_array(int *arr, int len, const char *label)
{
	printf("%s: [", label);
	for (int i = 0; i < len; i++)
		printf("%d ", arr[i]);
	printf("]\n");
}

void	sorted(char *str)
{
	char	tmp;

	printf("\n=== ソート開始: %s ===\n", str);
	for (int i = 0; str[i]; i++)
	{
		for (int j = i + 1; str[j]; j++)
		{
			if (str[i] > str[j]) // 昇順ソート
			{
				printf("交換: str[%d]='%c' <-> str[%d]='%c'\n", i, str[i], j,
					str[j]);
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
				printf("  結果: %s\n", str);
			}
		}
	}
	printf("=== ソート完了: %s ===\n\n", str);
}

void	print_indent(int depth)
{
	for (int i = 0; i < depth; i++)
		printf("  ");
}

void	perm(char *str, char *res, int *used, int dep, int len)
{
	print_indent(dep);
	printf("深さ%d: ", dep);
	// 現在の状態を表示
	printf("res=[");
	for (int i = 0; i < dep; i++)
		printf("%c", res[i]);
	for (int i = dep; i < len; i++)
		printf("_");
	printf("] used=");
	print_array(used, len, "");
	if (dep == len)
	{
		print_indent(dep);
		printf("★ 完成! → ");
		write(1, res, len);
		write(1, "\n", 1);
		return ;
	}
	for (int i = 0; i < len; i++)
	{
		if (used[i])
		{
			print_indent(dep + 1);
			printf("str[%d]='%c' はスキップ（使用済み）\n", i, str[i]);
			continue ;
		}
		print_indent(dep + 1);
		printf("str[%d]='%c' を選択\n", i, str[i]);
		used[i] = 1;
		res[dep] = str[i];
		perm(str, res, used, dep + 1, len);
		print_indent(dep + 1);
		printf("str[%d]='%c' を解放（バックトラック）\n", i, str[i]);
		used[i] = 0;
	}
}

int	main(int argc, char **argv)
{
	int		len;
	char	*str;
	char	*res;
	int		*used;

	if (argc != 2)
	{
		printf("使用法: %s <文字列>\n", argv[0]);
		return (1);
	}
	len = 0;
	while (argv[1][len])
		len++;
	str = malloc(len + 1);
	res = malloc(len + 1);
	used = calloc(len, sizeof(int));
	if (!str || !res || !used)
	{
		free(str);
		free(res);
		free(used);
		return (1);
	}
	for (int i = 0; i < len; i++)
		str[i] = argv[1][i];
	str[len] = '\0';
	printf("入力: %s\n", str);
	sorted(str);
	printf("順列生成開始（辞書順）\n");
	printf("================================\n");
	perm(str, res, used, 0, len);
	free(str);
	free(res);
	free(used);
	return (0);
}
