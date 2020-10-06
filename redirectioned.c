/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectioned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgilber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:38:32 by chgilber          #+#    #+#             */
/*   Updated: 2020/09/20 19:02:13 by chgilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int		croco(t_all *all)
{
	int	i;
	int	here;

	here = all->data - all->countpipe;
	
	all->red = (O_CREAT | O_TRUNC | O_RDWR);	// '>'
	all->red = (O_CREAT | O_APPEND | O_RDWR);	// '>>'
	all->red = (O_RDWR);						// '<'
	return (0);
}
