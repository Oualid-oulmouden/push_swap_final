/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ooulmoud <ooulmoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 10:41:12 by ooulmoud          #+#    #+#             */
/*   Updated: 2024/06/23 21:35:47 by ooulmoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------
static void move_min_nbr(t_list **stack_a, int i)
{

	while (i)
	{
		if (i < 0)
		{
			while (i++)
			retate_revers_a(stack_a);
		}
		else if (i > 0)
		{
			while (i--)
				retate_a(stack_a);
		}
		i = 0;
	}
}

static int	binary_search(int *arr, int low, int high, int x)
{
	int	mid;

	mid = low + (high - low) / 2;
	if (high >= low)
	{
		if (arr[mid] == x)
			return (1);
		if (arr[mid] < x)
			return (binary_search(arr, low, mid - 1, x));
		return (binary_search(arr, mid + 1, high, x));
	}
	return (0);
}

static void	make_rotate(t_list **stack_a, size_t i, size_t size)
{
	if (i <= size / 2)
	{
		while (i)
		{
			retate_a(stack_a);
			write(1, "ra\n", 3);
			i--;
		}
	}
	else
	{
		i = size - i;
		while (i)
		{
			retate_revers_a(stack_a);
			write(1, "rra\n", 4);
			i--;
		}
	}
}

void	push_tob(int *lis, t_list **stack_a, t_list **stack_b, int size)
{
	int		i;
	t_list	*tmp;
	i = 0;
	tmp = *stack_a;
	while (tmp)
	{
		if (!binary_search(lis, 0, size, tmp->content))
		{
			make_rotate(stack_a, i, ft_lstsize(*stack_a));
	 		push_to_b(stack_a, stack_b);
			i = 0;
			write(1, "pb\n", 3);
			tmp = *stack_a;
			continue ;
		}
		tmp = tmp->next;
		i++;
	}
	free(lis);
}

void	puch_not_lis(t_list **stack_a, t_list **stack_b)
{
	t_list	*lis;
	int index_of_min_nbr;

	index_of_min_nbr = index_of_min(*stack_a, ft_lstsize(*stack_a));
	if(index_of_min_nbr)
	{
		move_min_nbr(stack_a, index_of_min_nbr);
		lis = find_lis(*stack_a);
		move_min_nbr(stack_a,index_of_min_nbr * -1);
	}
	else
		lis = find_lis(*stack_a);
	if(ft_lstsize(*stack_a) != ft_lstsize(lis))
		push_tob(stack_to_arry(lis, ft_lstsize(lis)),stack_a, stack_b, ft_lstsize(lis));
	free_stack1(lis);
}

//---------------------------------

int	free_memory1(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (0);
}

t_list	*split_space(char *av[], int ac)
{
	int		i;
	char	**tmp;
	t_list	*stack_a;

	i = 1;
	stack_a = NULL;
	while (i < ac)
	{
		tmp = ft_split(av[i], ' ');
		if (!tmp || !(*tmp))
			return (0);
		if (add_to_stack(&stack_a, tmp) == 1)
		{
			free_stack1(stack_a);
			free_memory1(tmp);
			printf("Error\n");
			exit(1);
		}
		free_memory1(tmp);
		i++;
	}
	return (stack_a);
}

int	check_tow_tree(t_list *stack_a)
{
	if (check_sort(stack_a))
	{
		free_stack1(stack_a);
		exit(0);
	}
	if (ft_lstsize(stack_a) == 2)
	{
		two_sort(stack_a);
		free_stack1(stack_a);
		exit(0);
	}
	if (ft_lstsize(stack_a) == 3)
	{
		tree_sort(&stack_a);
		free_stack1(stack_a);
		exit(0);
	}
	return (1);
}

int	main(int ac, char *av[])
{
	t_list	*stack_a;
	t_list	*stack_b;
	int		*t;
	int		*m;

	stack_b = NULL;
	stack_a = split_space(av, ac);
	if (!stack_a)
		return (0);
	if (ft_lstsize(stack_a) <= 3)
		check_tow_tree(stack_a);
	puch_not_lis(&stack_a, &stack_b);
	while (ft_lstsize(stack_b))
	{
		t = stack_to_arry(stack_a, ft_lstsize(stack_a));
		m = get_bestmove(t, stack_b, ft_lstsize(stack_a), ft_lstsize(stack_b));
		make_themove(&stack_a, &stack_b, m);
		free(m);
		free(t);
	}
	sort(&stack_a, ft_lstsize(stack_a));
	free_stack1(stack_b);
	free_stack1(stack_a);
}
