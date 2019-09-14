/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 15:45:43 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/14 15:33:53 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

int		ft_array_size(char **arr)
{
	int		count;

	count = 0;
	while (arr[count])
		count++;
	return (count);
}

int		main(int argc, char **argv)
{
	t_farm		*farm;
	t_hash_tab	*h_tab;
	t_hashcodes	*hashcodes;

	hashcodes = NULL;
	if ((farm = (t_farm *)ft_memalloc(sizeof(t_farm)))
	&& argc == 2 && (farm->size = count_room(argv[1])) &&
	(h_tab = (t_hash_tab *)ft_memalloc(sizeof(t_hash_tab) * (farm->size * 4))))
	{
		farm->fd = open(argv[1], O_RDONLY);
		if (!validation(h_tab, farm, &hashcodes))
		{
			write(2, "ERROR\n", 6);
			exit(0);
		}
		farm->h_tab = h_tab;
		farm->hashcodes = hashcodes;
		vizualizer(farm);
		free_all_structs(hashcodes, h_tab, farm);
		return (1);
	}
	if (!farm->size)
		free(farm);
	write(2, "ERROR\n", 6);
	return (0);
}
