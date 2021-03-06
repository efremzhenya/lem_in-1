/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_optimal_paths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:37:41 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/18 14:09:27 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*
** Here we are calculating how many
** paths should we use to get our ants
** to the end-vertex by the least steps
** as possible.
*/

int		expression(t_path *path, int i)
{
	int		curr;
	int		result;

	curr = i;
	result = 0;
	while (i > 0)
	{
		i--;
		result += path[curr].steps - path[i].steps;
	}
	return (result);
}

int		count_optimal_paths(t_path *path, int ants)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	if (path->size == 1)
		return (1);
	while (i < path->size)
	{
		if (ants > expression(path, i))
			size++;
		else
			break ;
		i++;
		ants--;
	}
	return (size);
}
