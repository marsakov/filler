/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 18:41:19 by msakovyc          #+#    #+#             */
/*   Updated: 2018/05/25 18:41:21 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include "../libft/includes/libft.h"
# include "mlx.h"
# include <math.h>

# define GNL(fd, ln) get_next_line(fd, &line)
# define HEIGHT 1200
# define WIDTH 2000

typedef struct			s_window
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					x;
	int					y;
	double				k;
	int					result;
	char				*result1;
	char				*result2;
	char				**map;
}						t_window;

int						writer(t_window *wnd);
int						get_color(char c);
int						change(int n, char c, t_window *wnd);
int						draw(t_window *wnd);
void					create_wind(t_window *wnd, char *line);
void					putpix(t_window *wnd, int x, int y);

#endif
