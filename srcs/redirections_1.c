/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/23 14:38:04 by jabenjam          #+#    #+#             */
/*   Updated: 2020/11/06 14:11:19 by jabenjam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int		which_redirection(t_all *all, int *start)
{
	if (!ft_strncmp(all->toks->value + *start, "=>", 2) ||
		!ft_strncmp(all->toks->value + *start, "=<", 2))
		*start += (!ft_strncmp(all->toks->value + *start, "=>>", 3) ? 3 : 2);
	else if (!ft_strncmp(all->toks->value + *start, ">>", 2))
		all->red = O_A;
	else if (!ft_strncmp(all->toks->value + *start, ">", 1))
		all->red = O_T;
	else if (!ft_strncmp(all->toks->value + *start, "<", 1))
		all->red = I_R;
	if (all->red == O_A || all->red == O_T || all->red == I_R)
	{
		all->toks->end = (all->toks->end == ft_strlen(all->toks->value) ?
						*start : all->toks->end);
		if (all->red == I_R || all->red == O_T)
			*start += 1;
		else if (all->red == O_A)
			*start += 2;
		if (all->toks->next && all->toks->value[(*start)] == '\0')
		{
			all->toks = all->toks->next;
			all->toks->ignore = 1;
			all->toks = all->toks->previous;
		}
	}
	return (0);
}

char	*ft_dup_until_red(char *src)
{
	int		i;
	char	*dup;

	i = 0;
	dup = NULL;
	if (src[i])
	{
		while (src[i])
		{
			if (ft_isinset("<>", src[i]) == 1)
				break ;
			i++;
		}
		dup = malloc(sizeof(char) * (i + 1));
		i = 0;
		while (src[i] && src[i] != '<' && src[i] != '>')
		{
			dup[i] = src[i];
			i++;
		}
		dup[i] = '\0';
	}
	return (dup);
}

char	*get_filename(t_tok **toks, int *start)
{
	char	*file;

	file = NULL;
	while (file == NULL)
	{
		if (toks == NULL || (*toks)->value == NULL)
			break ;
		if ((*toks)->value[*start] == '\0' && (*toks)->next != NULL)
		{
			(*toks) = (*toks)->next;
			*start = 0;
		}
		if ((*toks)->whole == 2)
		{
			file = ft_strdup((*toks)->value);
			break ;
		}
		if ((*toks)->value[*start] != '\0')
		{
			file = ft_dup_until_red((*toks)->value + *start);
			*start += ft_strlen(file);
			break ;
		}
	}
	return (file);
}

void	get_redirections(t_all *all)
{
	int		start;
	char	*file;

	start = 0;
	file = NULL;
	while (all->toks)
	{
		while (all->toks->value && ft_strlen(all->toks->value + start))
		{
			printf("all->toks->value + %d=[%s]\n", start, all->toks->value + start);
			which_redirection(all, &start);
			printf("all->red=[%d]\n", all->red);
			if (all->red == 0)
				start++;
			else if (all->red)
				file = get_filename(&all->toks, &start);
			if (file)
			{
				all->reds = new_red(all, all->reds, all->red, file);
				free(file);
				file = NULL;
			}
			all->red = 0;
		}
		start = 0;
		all->toks = all->toks->next;
	}
}

int		handle_redirections(t_all *all)
{
	t_tok	*head;

	head = all->toks;
	all->reds = NULL;
	if (!all->toks)
		return (-1);
	get_redirections(all);
	process_reds(all);
	all->toks = head;
	return (1);
}
