/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:04:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/17 20:15:37 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*find_best_path(t_path *path)
{
	int		lines;
	t_path	*best;

	lines = path->lines;
	best = path;
	path = path->next;
	while (path)
	{
		if (path->lines < lines)
		{
			lines = path->lines;
			best = path;
		}
		path = path->next;
	}
	return (best);
}

int		main(void)
{
	t_farm		*farm;

	if ((farm = (t_farm *)ft_memalloc(sizeof(t_farm)))
		&& (farm->size = count_room('a')))
	{
		if (!(farm->h_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab)
			* (farm->size * 4))))
			exit(0);
		farm->fd = open("input_data", O_RDONLY);
		if ((farm->ret = validation(farm->h_tab, farm, &farm->hashcodes)) >= 0)
		{
			while (farm->ret)
				if (!bellman_ford(farm, farm->path)
					|| !(farm->ret = create_paths(farm, &farm->path)))
					break ;
			run_ants(farm, find_best_path(farm->path));
		}
		else
			write(2, "ERROR\n", 6);
		exit(1);
	}
	if (!farm->size)
		free(farm);
	write(2, "ERROR\n", 6);
	return (0);
}
