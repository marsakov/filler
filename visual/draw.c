#include "visual.h"

void	putpix(t_window *wnd, int x, int y)
{
	int		m;
	int		n;
	int		i;
	int		j;

	mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr, change(x, 'x', wnd),
				change(y, 'y', wnd), get_color(wnd->map[y][x]));
	if (wnd->map[y][x] && wnd->map[y][x] != '.' && x != wnd->x - 1 &&
		y != wnd->y - 1 && !(i = 0))
		while (change(y, 'y', wnd) + i++ < change(y + 1, 'y', wnd) && !(j = 0))
			while (change(x, 'x', wnd) + j++ < change(x + 1, 'x', wnd))
				mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr,
					change(x, 'x', wnd) + j, change(y, 'y', wnd) + i,
					get_color(wnd->map[y][x]));
	if (x != wnd->x - 1 && (m = -1))
		while (change(x, 'x', wnd) + m++ < change(x + 1, 'x', wnd))
				mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr,
					change(x, 'x', wnd) + m, change(y, 'y', wnd),
					0xffffff);
	if (y != wnd->y - 1 && (n = -1))
		while (change(y, 'y', wnd) + n++ < change(y + 1, 'y', wnd))
				mlx_pixel_put(wnd->mlx_ptr, wnd->win_ptr,
					change(x, 'x', wnd), change(y, 'y', wnd) + n,
					0xffffff);
}

int		draw(t_window *wnd)
{
	int		y;
	int		x;

	y = -1;
	mlx_clear_window(wnd->mlx_ptr, wnd->win_ptr);
	while (++y < wnd->y && (x = -1))
		while (++x < wnd->x)
			putpix(wnd, x, y);
	// if (wnd->result)
	// {
	// 	mlx_string_put(wnd->mlx_ptr, wnd->win_ptr, 10, 10, 0xb3ffd9, wnd->result1);
	// 	mlx_string_put(wnd->mlx_ptr, wnd->win_ptr, 10, 30, 0xff9999, wnd->result2);
	// }
	mlx_do_sync(wnd->mlx_ptr);
	return (1);
}