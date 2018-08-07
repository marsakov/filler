/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msakovyc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 18:24:17 by msakovyc          #+#    #+#             */
/*   Updated: 2018/07/31 18:24:22 by msakovyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

void	writer(t_window *wnd)
{
	char	*line;
	int		i;

	i = 0;
	GNL(0, &line);
	free(line);
	wnd->map = malloc(sizeof(char*) * wnd->y);
	while (i < wnd->y && GNL(0, &line) > 0)
	{
		wnd->map[i] = malloc(sizeof(char) * (wnd->x));
		ft_strcpy(wnd->map[i++], line + 4);
		free(line);
	}
}

int		get_color(char c)
{
	if (c == '.')
		return (0x000000);
	else if (c == 'O' || c == 'o')
		return (0xb3ffd9);
	else if (c == 'X' || c == 'x')
		return (0xff9999);
	else
		return (0xffffff);
}

int		change(int n, char c, t_window *wnd)
{
	if (c == 'x')
		return ((WIDTH / 2) + (n - wnd->x / 2) * wnd->k);
	else if (c == 'y')
		return ((HEIGHT / 2) + (n - wnd->y / 2) * wnd->k);
	else
		return (0);
}

void	create_wind(t_window *wnd, char *line)
{
	wnd->y = ft_atoi(ft_strchr(line, ' '));
	wnd->x = ft_atoi(ft_strrchr(line, ' '));
	writer(wnd);
	wnd->mlx_ptr = mlx_init();
	wnd->win_ptr = mlx_new_window(wnd->mlx_ptr, WIDTH, HEIGHT, "filler");
	wnd->k = fmin(WIDTH / (wnd->y + 1), HEIGHT / (wnd->x + 1));
	draw(wnd);
}

int		main(void)
{
	char		*line;
	t_window	*wnd;

	while (GNL(0, &line) > 0 && !ft_strstr(line, "Plateau "))
		free(line);
	wnd = malloc(sizeof(t_window));
	create_wind(wnd, line);
	free(line);
	while (GNL(0, &line) > 0)
	{
		if (ft_strstr(line, "Plateau "))
		{
			writer(wnd);
			draw(wnd);
		}
		// if (ft_strstr(line, "== O fin:"))
		// {
		// 	wnd->result = 1;
		// 	wnd->result1 = ft_strdup(line);
		// 	free(line);
		// 	GNL(0, &line);
		// 	wnd->result2 = ft_strdup(line);
		// }
		free(line);
	}
	mlx_loop_hook(wnd->mlx_ptr, draw, wnd);
	mlx_loop(wnd->mlx_ptr);
	return (0);
}
