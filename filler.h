/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 16:42:22 by msakovyc          #+#    #+#             */
/*   Updated: 2018/07/03 16:42:24 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <math.h>
# include "libft/includes/libft.h"

# define GNL(fd, ln) get_next_line(fd, &line)
# define SYP p.p_s.y
# define SXP p.p_s.x
# define YP p.piece->y
# define XP p.piece->x
# define YM p.map->y
# define XM p.map->x
# define XY(pt, z) pt->piece->x > 1 && pt->piece->y > 1 && find_star(pt, z)

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_data
{
	int				x;
	int				y;
	char			**arr;
}					t_data;

typedef struct		s_filler
{
	struct s_data	*piece;
	struct s_data	*map;
	struct s_coord	*player_coord;
	struct s_coord	*enemy_coord;
	int				counter_p;
	int				counter_e;
	int				stars;
	struct s_coord	p_s;
	struct s_coord	result;
	int				n;
}					t_filler;

char				**writer(int x, int y, int piece);
void				count_elems(t_filler *ptr);
void				mem_elems(t_filler *ptr, int p, int e);
void				loop_writer(char *line, t_filler *ptr);

void				count_stars(t_filler *ptr);
int					find_star(t_filler *ptr, int n);
int					fill_map(t_filler p, t_coord c, int n, int counter);
int					can_place(t_filler *pt, int *shortcut, int p, int current);
int					shortcut(t_filler *ptr, int p, int e);

#endif
