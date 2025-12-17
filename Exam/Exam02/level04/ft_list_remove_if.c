/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shkondo <shkondo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 20:35:36 by shkondo           #+#    #+#             */
/*   Updated: 2025/07/20 20:59:52 by shkondo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void *, void *))
{
	t_list	*to_remove;

	if (begin_list == NULL || *begin_list == NULL)
		return ;
	// 現在のノードのデータが削除対象かチェック
	if (cmp((*begin_list)->data, data_ref) == 0)
	{
		to_remove = *begin_list;
		// リストの先頭を次のノードに更新
		*begin_list = (*begin_list)->next;
		// 削除するノードのメモリを解放
		free(to_remove);
		// 再起的に同じ処理を続行(連続する削除対象要素に対応)
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
	{
		ft_list_remove_if(&((*begin_list)->next), data_ref, cmp);
	}
}

// テスト用の比較関数（文字列比較）
int	str_cmp(void *s1, void *s2)
{
	return (strcmp((char *)s1, (char *)s2));
}

// テスト用の比較関数（整数比較）
int	int_cmp(void *a, void *b)
{
	int	*ia;
	int	*ib;

	ia = (int *)a;
	ib = (int *)b;
	return (*ia - *ib);
}

// リストに新しいノードを追加する関数（テスト用）
void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node)
	{
		new_node->data = data;
		new_node->next = *begin_list;
		*begin_list = new_node;
	}
}

// リストを表示する関数（テスト用）
void	print_list(t_list *list)
{
	while (list)
	{
		printf("%s -> ", (char *)list->data);
		list = list->next;
	}
	printf("NULL\n");
}

// メイン関数（テスト用）
int	main(void)
{
	t_list	*list;

	list = NULL;
	// テストデータを追加
	ft_list_push_front(&list, "world");
	ft_list_push_front(&list, "hello");
	ft_list_push_front(&list, "world");
	ft_list_push_front(&list, "42");
	ft_list_push_front(&list, "world");
	printf("削除前のリスト: ");
	print_list(list);
	// "world"を削除
	ft_list_remove_if(&list, "world", str_cmp);
	printf("「world」削除後: ");
	print_list(list);
	return (0);
}
