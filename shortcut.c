/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shortcut.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 18:24:39 by msakovyc          #+#    #+#             */
/*   Updated: 2018/07/31 18:24:44 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	count_stars(t_filler *ptr)
{
	ptr->stars = 0;
	ptr->p_s.y = -1;
	while (++(ptr->p_s.y) < ptr->piece->y)
	{
		ptr->p_s.x = -1;
		while (++(ptr->p_s.x) < ptr->piece->x)
			if (ptr->piece->arr[ptr->p_s.y][ptr->p_s.x] == '*')
				ptr->stars++;
	}
}

int		find_star(t_filler *ptr, int n)
{
	int		i;
	int		j;

	i = (n == 1 || n == 3) ? 0 : ptr->piece->y - 1;
	while (i < ptr->piece->y && i >= 0)
	{
		j = (n == 1 || n == 4) ? 0 : ptr->piece->x - 1;
		while (j < ptr->piece->x && j >= 0)
		{
			if (ptr->piece->arr[i][j] == '*')
			{
				ptr->p_s.x = j;
				ptr->p_s.y = i;
				return (1);
			}
			(n == 1 || n == 4) ? j++ : j--;
		}
		(n == 1 || n == 3) ? i++ : i--;
	}
	return (0);
}

int		fill_map(t_filler p, t_coord c, int n, int counter)
{
	int i;
	int	j;

	i = 0;
	while (c.y + i >= 0 && c.y + i < YM && SYP + i >= 0 && SYP + i < YP)
	{
		j = 0;
		while (c.x + j >= 0 && c.x + j < XM && SXP + j >= 0 && SXP + j < XP)
		{
			if (p.map->arr[c.y + i][c.x + j] != '.' &&
			p.piece->arr[SYP + i][SXP + j] != '.' && !(i == 0 && j == 0))
				return (0);
			if (p.piece->arr[SYP + i][SXP + j] == '*')
				counter++;
			(n == 1 || n == 4) ? j++ : j--;
		}
		if (i == 0 && (((n == 1 || n == 4) && SXP + j == XP) ||
			((n == 2 || n == 3) && SXP + j == -1)))
		{
			c.x = (n == 1 || n == 4) ? c.x - SXP : c.x + (XP - 1 - SXP);
			SXP = (n == 1 || n == 4) ? 0 : XP - 1;
		}
		(n == 1 || n == 3) ? i++ : i--;
	}
	return (counter == p.stars) ? (1) : (0);
}

void	can_place(t_filler *pt, int *shortcut, int p, int current)
{
	if (find_star(pt, 1) && fill_map(*pt, pt->player_coord[p], 1, 0))
	{
		pt->result.x = pt->player_coord[p].x - pt->p_s.x;
		pt->result.y = pt->player_coord[p].y - pt->p_s.y;
		*shortcut = current;
	}
	else if (find_star(pt, 2) && fill_map(*pt, pt->player_coord[p], 2, 0))
	{
		pt->result.x = pt->player_coord[p].x - pt->p_s.x;
		pt->result.y = pt->player_coord[p].y - pt->p_s.y;
		*shortcut = current;
	}
	else if (XY(pt, 3) && fill_map(*pt, pt->player_coord[p], 3, 0))
	{
		pt->result.x = pt->player_coord[p].x - pt->p_s.x;
		pt->result.y = pt->player_coord[p].y - pt->p_s.y;
		*shortcut = current;
	}
	else if (XY(pt, 4) && fill_map(*pt, pt->player_coord[p], 4, 0))
	{
		pt->result.x = pt->player_coord[p].x - pt->p_s.x;
		pt->result.y = pt->player_coord[p].y - pt->p_s.y;
		*shortcut = current;
	}
}

int		shortcut(t_filler *ptr, int p, int e)
{
	int		shortcut;
	int		current;

	shortcut = ptr->map->x + ptr->map->y;
	ft_bzero(&(ptr->result), sizeof(t_coord));
	while (p < ptr->counter_p)
	{
		e = 0;
		while (e < ptr->counter_e)
		{
			current = abs(ptr->player_coord[p].x - ptr->enemy_coord[e].x)
					+ abs(ptr->player_coord[p].y - ptr->enemy_coord[e].y);
			if (current <= shortcut)
				can_place(ptr, &shortcut, p, current);
			e++;
		}
		p++;
	}
	return ((shortcut == ptr->map->x + ptr->map->y) ? 0 : 1);
}
