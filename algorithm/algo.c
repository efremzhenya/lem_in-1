/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfrankly <hfrankly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 15:10:05 by hfrankly          #+#    #+#             */
/*   Updated: 2019/09/13 13:07:35 by hfrankly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	ft_make_room_inf(t_farm *farm)
{
	t_hashcodes	*hc;
	t_hash_tab	*ht;
	t_link		*link;
	t_room		*room;

	hc = farm->hashcodes;
	ht = farm->h_tab;
	while (hc)
	{
		room = ht[hc->hash_code].room;
		while (room)
		{
			if (room->in != NULL)
			{
				room->in->pathlength = 2147483637;
				room->out->pathlength = 2147483637;
			}
			else
				room->pathlength = 2147483637;
			link = room->link;
			room = room->next;
		}
		hc = hc->next;
	}
	room = ht[farm->start].room;
	while (room)
	{
		if (room->status == 's')
		{
			room->pathlength = 0;
			farm->startroom = room;
			break;
		}
		room = room->next;
	}
}

void	ft_bell_ford(t_farm *farm)
{
	t_link		*link;
	t_room		*room;
	t_room		**queue;
	int			iter;
	int			endqueue;
	int			i;
	bool		changes;

	i = 0;
	if (!is_free_path(farm))
		return ;
	ft_make_room_inf(farm);
	changes = true;
	farm->room_count += farm->duplicate_count;
	if (!(queue = (t_room**)malloc(sizeof(t_room*) * farm->room_count)))
		exit(0);
	while (i < farm->room_count)
	{
		iter = 0;
		endqueue = 1;
		queue[0] = farm->startroom;
		changes = false;
		while (iter < farm->room_count && iter < endqueue)
		{
			room = queue[iter];
			link = room->link;
			while (link)
			{
				if (!link->lock && link->room->pathlength > room->pathlength + link->weight)
				{
					link->room->pathlength = room->pathlength + link->weight;
					link->room->prev = room;
					queue[endqueue] = link->room;
					changes = true;
					endqueue++;
				}
				link = link->next;
			}
			iter++;
		}
		if (changes == false)
		{
			free(queue);
			return ;
		}
		if (i == farm->room_count)
		{
			ft_printf("Cycle detected\n");
			exit(0);
		}
		i++;
	}
	farm->room_count -= farm->duplicate_count;
	free(queue);
}

t_room	*ft_return_room(t_farm *farm, char *name)
{
	int		hash;
	t_room	*room;

	hash = hash_func(name, farm->size);
	room = farm->h_tab[hash].room;
	while (room)
	{
		if (room->name == name)
			return (room);
		room = room->next;
	}
	return (NULL);
}

void	ft_refresh_room_links(t_room *room)
{
	t_room	*tmproom;
	t_link	*mainlink;

	mainlink = room->link;
	tmproom = room->out;
	while (tmproom->link)
	{
		if (!tmproom->link->destroy && tmproom->link->room != room->in)
		{
			mainlink->room = tmproom->link->room;
			mainlink = mainlink->next;
		}
		tmproom->link = tmproom->link->next;
	}
	mainlink->room = room->in->link->room;
	mainlink->next = NULL;
}

void	ft_refresh_graph(t_farm *farm)
{
	t_room	*tmp;
	t_room	**queue;
	t_link	*link;
	int		iter;
	int		endqueue;

	iter = 0;
	endqueue = 1;
	if (!(queue = (t_room**)malloc(sizeof(t_room*) * farm->room_count)))
		exit(0);
	queue[0] = farm->endroom;
	while (iter < farm->room_count)
	{
		tmp = queue[iter];
		tmp->was = true;
		if (tmp->in || tmp->out)
			ft_refresh_room_links(tmp);
		link = tmp->link;
		while (link)
		{
			if (link->destroy || link->room->was)
			{
				link = link->next;
				continue;
			}
			if (link->room->outduplicate || link->room->induplicate)
				link->room = ft_return_room(farm, link->room->name);
			queue[endqueue] = link->room;
			endqueue++;
			link = link->next;
		}
		iter++;
	}
	free(queue);
}

void    lem_in(t_farm *farm)
{
	int	pathcount;

	pathcount = 1;
	farm->duplicate_count = 0;
	while (pathcount < 2)
	{
		ft_reverse_shortest_path(farm);
		ft_make_rooms_duplicates(farm);
    	// ft_bell_ford(farm);
		// find_shortest_path(farm);
		pathcount++;
	}
	// ft_refresh_graph(farm);
	// print_links(farm->hashcodes, farm->h_tab);
	ft_show_pathlengthes(farm);
}
