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

typedef struct	s_filler
{
	int			x;
	int			y;
	int			n;
	int			x_coord;
	int			y_coord;
	char		**map;
	char		**piece;
}				t_filler;

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
Plateau 15 17:
    01234567890123456
000 .................
001 .................
002 .................
003 .................
004 .................
005 .................
006 .................
007 .................
008 ..O..............
009 .................
010 .................
011 .................
012 ..............X..
013 .................
014 .................
Piece 2 1:
*
*


*/