/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 11:48:14 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/10/02 14:50:16 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

int		validation(t_hash_tab *h_tab, t_farm *farm, t_hashcodes **hashcodes)
{
	t_coords	*coords;

	coords = NULL;
	farm->start = -1;
	farm->end = -1;
	if (!validate_ants(farm) ||
		!validate_rooms(hashcodes, h_tab, farm, &coords) ||
		!find_and_connect_rooms(farm->line, h_tab, farm->size) ||
		!validate_links(h_tab, farm))
	{
		free_coords(&coords);
		ft_strdel(&farm->line);
		return (0);
	}
	close(farm->newfd);
	farm->h_tab = h_tab;
	farm->hashcodes = *hashcodes;
	free_coords(&coords);
	return (1);
}
