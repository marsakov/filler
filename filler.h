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
#include "libft/includes/libft.h"

// typedef struct	s_filler
// {
// 	int			x;
// 	int			y;
// 	int			piece_x;
// 	int			piece_y;
// 	int			n;
// 	int			x_coord;
// 	int			y_coord;
// 	int			p_x;
// 	int			p_y;
// 	char		**map;
// 	char		**piece;
// }				t_filler;


typedef struct	s_data
{
	int			x;
	int			y;
	int			t_x;
	int			t_y;
	char		**arr;
}				t_data;

typedef struct		s_filler
{
	struct	s_data	*piece;
	struct	s_data	*map;
	int				x_result;
	int				y_result;
	int				n;
}					t_filler;

char			**writer(int x, int y, int piece);


/*

# -------------- VM  version 1.1 ------------- #
#                                              #
# 42 / filler VM Developped by: Hcao - Abanlin #
#                                              #
# -------------------------------------------- #
launched ./msakovyc.filler
$$$ exec p1 : [./msakovyc.filler]
launched ./players/abanlin.filler
$$$ exec p2 : [./players/abanlin.filler]
Plateau 14 30:
    012345678901234567890123456789
000 ..............................
001 ..............................
002 ..............................
003 ..............................
004 ......O.......................
005 ......OO......................
006 .......O......................
007 .........................xxxx.
008 ........................xx....
009 ........................x.....
010 ..............................
011 ..............................
012 ..............................
013 ..............................
Piece 2 3:
.**
.*.


*/