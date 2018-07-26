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

#include <stdio.h>
#include <math.h>
#include "libft/includes/libft.h"

# define GNL(fd, ln) get_next_line(fd, &line)

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
	struct	s_data	*piece;
	struct	s_data	*map;
	struct	s_coord	*player_coord;
	struct	s_coord	*enemy_coord;
	int				counter_p;
	int				counter_e;
	int				stars;
	struct s_coord	start_p;
	struct s_coord	result;
	int				n;
}					t_filler;

char				**writer(int x, int y, int piece);


/*

p1
Plateau 15 17:
    01234567890123456
000 .................
001 .................
002 .................
003 .................
004 .................
005 .................
006 .................
007 ....xxXXX........
008 ..O....XXX.......
009 ..OO.....X.......
010 ...OO....XX......
011 ....OOO...XXX....
012 .....OO.....XXX..
013 ......O..........
014 ......OOOOO......
Piece 2 2:
**
**


*/