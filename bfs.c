/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:57:30 by vhazelnu          #+#    #+#             */
/*   Updated: 2019/08/30 13:22:11 by vhazelnu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	dequeue(t_queue **queue)
{
	t_queue *head;

	head = *queue;
	*queue = (*queue)->next;
	free(head);
	head = NULL;
}

void	enqueue(t_queue **queue, t_room *room, t_queue **last)
{
	t_queue	*new;

	if (!*queue)
	{
		if (!(*queue = (t_queue *)ft_memalloc(sizeof(t_queue))))
			exit(0);
		(*queue)->room = room;
		(*last) = (*queue);
	}
	else
	{
		if (!(new = (t_queue *)ft_memalloc(sizeof(t_queue))))
			exit(0);
		new->room = room;
		(*last)->next = new;
		(*last) = new;
	}
}

t_room	*find_start(t_room *room)
{
	while (room)
	{
		if (room->status == 's')
		{
			room->bfs_lvl = -1;
			return (room);
		}
		room = room->next;
	}
	return (NULL);
}

int		assign_lvl(t_queue *queue, t_room *room, t_queue *last)
{
	t_link	*link;
	int		ret;

	ret = 0;
	while (queue)
	{
		link = room->link;
		ret = link->room->status == 'e' ? 1 : ret;
		printf("%s\nbfs lvl: %d\n", room->name, room->bfs_lvl);
		while (link)
		{
			printf("link with: %s\n", link->room->name);
			if (!link->room->bfs_lvl)
			{
				enqueue(&queue, link->room, &last);
				link->room->bfs_lvl = room->bfs_lvl == -1 ?
					room->bfs_lvl + 2 : room->bfs_lvl + 1;
			}
			link = link->next;
		}
		printf("--------------\n");
		dequeue(&queue);
		room = queue ? queue->room : room;
	}
	pritnf("\n");
	return (ret);
}

int		bfs(t_farm *farm)
{
	t_queue	*queue;
	t_queue	*last;
	t_room	*room;
	int		ret;

	queue = NULL;
	room = find_start(farm->h_tab[farm->start].room);
	enqueue(&queue, room, &last);
	return (assign_lvl(queue, room, last));
}