/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vizualizer1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 23:17:24 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/14 15:33:31 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/visual.h"

t_room		*ft_find_ant_room(t_farm *farm, char *str)
{
	t_hashcodes	*hc;
	t_room		*room;
	int			nbr;

	hc = farm->hashcodes;
	nbr = ft_atoi(str);
	while (hc)
	{
		room = farm->h_tab[hc->hash_code].room;
		while (room)
		{
			if (room->antnbr == nbr)
				return (room);
			room = room->next;
		}
		hc = hc->next;
	}
	room = farm->h_tab[farm->start].room;
	while (room)
	{
		if (room->status == 's')
			return (room);
		room = room->next;
	}
	return (NULL);
}

int			ft_get_link_length(const t_room *src, const t_room *dst)
{
	return (sqrt(pow(dst->x - src->x, 2) + pow(dst->y - src->y, 2)));
}

void		free_arr(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void		ft_get_ants(t_sdl *sdl)
{
	int			i;
	t_hash_tab	*ht;
	t_hashcodes	*hc;

	i = -1;
	ht = sdl->farm->h_tab;
	hc = sdl->farm->hashcodes;
	while (++i < sdl->arrsize)
	{
		sdl->ants[i].srcroom = ft_find_ant_room(sdl->farm, &sdl->cmdline[i][1]);
		sdl->ants[i].dstroom = sdl->farm->h_tab[hash_func(&sdl->cmdline[i][3],
		sdl->farm->size)].room;
		sdl->ants[i].x = sdl->ants[i].srcroom->x;
		sdl->ants[i].y = sdl->ants[i].srcroom->y;
		sdl->ants[i].radius = 10;
	}
}

void		ft_events(t_sdl *sdl, bool *pause)
{
	if (sdl->e->type == SDL_QUIT ||
	(sdl->e->type == SDL_KEYDOWN && sdl->e->key.keysym.sym == SDLK_ESCAPE))
		exit(0);
	if ((sdl->e->type == SDL_KEYDOWN
	&& sdl->e->key.keysym.sym == SDLK_SPACE))
	{
		*pause = (*pause) ? 0 : 1;
		Mix_PauseMusic();
	}
}
