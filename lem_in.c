/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 19:04:16 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/02 14:47:43 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "lem_in.h"

int		main()
{
	t_farm		*farm;
	t_hash_tab	*h_tab;
	t_hashcodes	*hashcodes;

	hashcodes = NULL;
	if ((farm = (t_farm *)ft_memalloc(sizeof(t_farm)))
		&& (farm->size = count_room(farm)))
	{
		if (!(h_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab )
			* (farm->size * 4))))
			exit(0);
		farm->newfd = open("tmpfd", O_RDONLY);
		if (validation(h_tab, farm, &hashcodes) && bfs(farm))
			lem_in(farm);
		else
			write(2, "ERROR\n", 6);
		farm->h_tab = h_tab;
		farm->hashcodes = hashcodes;
		free_all_structs(hashcodes, h_tab, farm);
		exit(1);
	}
	if (!farm->size)
		free(farm);
	write(2, "ERROR\n", 6);
	return (0);
}
