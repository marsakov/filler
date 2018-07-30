#include "filler.h"

char	**writer(int x, int y, int piece)
{
	char	**map;
	char	*line;
	int		i;
	
	i = 0;
	map = malloc(sizeof(char*) * y);
	while (i < y && GNL(0, &line) > 0)
	{
		map[i] = malloc(sizeof(char) * (x + 1));
		if (piece)
			ft_strcpy(map[i++], line);
		else
			ft_strcpy(map[i++], line + 4);
		free(line);
	}
	return (map);
}

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

void	count_elems(t_filler *ptr)
{
	int		i;
	int		j;

	ptr->counter_p = 0;
	ptr->counter_e = 0;
	i = 0;
	while (i < ptr->map->y)
	{
		j = 0;
		while (j < ptr->map->x)
		{
			if (ptr->map->arr[i][j] == 'O')
				(ptr->n == 1 ? ptr->counter_p++ :
					ptr->counter_e++);
			else if (ptr->map->arr[i][j] == 'X')
				(ptr->n == 2 ? ptr->counter_p++ :
					ptr->counter_e++);
			j++;
		}
		i++;
	}
	ptr->player_coord = malloc(sizeof(t_coord) * ptr->counter_p);
	ptr->enemy_coord = malloc(sizeof(t_coord) * ptr->counter_e);
}

void	mem_elems(t_filler *ptr, int p, int e)
{
	t_coord coord;

	coord.y = -1;
	while (++coord.y < ptr->map->y)
	{
		coord.x = -1;
		while (++coord.x < ptr->map->x)
		{
			if (ptr->map->arr[coord.y][coord.x] == 'O')
			{
				if (ptr->n == 1)
					ptr->player_coord[p++] = coord;
				else
					ptr->enemy_coord[e++] = coord;
			}
			else if (ptr->map->arr[coord.y][coord.x] == 'X')
			{
				if (ptr->n == 2)
					ptr->player_coord[p++] = coord;
				else
					ptr->enemy_coord[e++] = coord;
			}
		}
	}
}

int		fill_map(t_filler p, t_coord c, int n, int counter)
{
	int i;
	int	j;

	i = 0;
	while (c.y + i >= 0 && c.y + i < Ym && sYp + i >= 0 && sYp + i < Yp)
	{
		j = 0;
		while (c.x + j >= 0 && c.x + j < Xm && sXp + j >= 0 && sXp + j < Xp)
		{
			if (p.map->arr[c.y + i][c.x + j] != '.' &&
			p.piece->arr[sYp + i][sXp + j] != '.' && !(i == 0 && j == 0))
				 return (0);
			if (p.piece->arr[sYp + i][sXp + j] == '*')
				counter++; 
			(n == 1 || n == 4) ? j++ : j--;
		}
		if (i == 0 && (((n == 1 || n == 4) && sXp + j == Xp) ||
			((n == 2 || n == 3) && sXp + j == -1)))
		{
			c.x = (n == 1 || n == 4) ? c.x - sXp : c.x + (Xp - 1 - sXp);
			sXp = (n == 1 || n == 4) ? 0 : Xp - 1;
		}
		(n == 1 || n == 3) ? i++ : i--;
	}
	return (counter == p.stars) ? (1) : (0);
}

void	mem_res(t_filler *ptr, int *shortcut, int p, int current)
{
	ptr->result.x = ptr->player_coord[p].x - ptr->p_s.x;
	ptr->result.y = ptr->player_coord[p].y - ptr->p_s.y;
	*shortcut = current;
}

int		shortcut(t_filler *ptr)
{
	int		p;
	int		e;
	int		shortcut;
	int		current;

	shortcut = ptr->map->x + ptr->map->y;
	p = 0;
	ft_bzero(&(ptr->result), sizeof(t_coord));
	while (p < ptr->counter_p)
	{
		e = 0;
		while (e < ptr->counter_e)
		{
			current = abs(ptr->player_coord[p].x - ptr->enemy_coord[e].x)
					+ abs(ptr->player_coord[p].y - ptr->enemy_coord[e].y);
			if (current <= shortcut)
			{
				if (find_star(ptr, 1) && fill_map(*ptr, ptr->player_coord[p], 1, 0))
					mem_res(ptr, &shortcut, p, current);
				else if (find_star(ptr, 2) && fill_map(*ptr, ptr->player_coord[p], 2, 0))
					mem_res(ptr, &shortcut, p, current);
				else if (ptr->piece->x > 1 && ptr->piece->y > 1 && find_star(ptr, 3) && fill_map(*ptr, ptr->player_coord[p], 3, 0))
					mem_res(ptr, &shortcut, p, current);
				else if (ptr->piece->x > 1 && ptr->piece->y > 1 && find_star(ptr, 4) && fill_map(*ptr, ptr->player_coord[p], 4, 0))
					mem_res(ptr, &shortcut, p, current);
			}
			e++;
		}
		p++;
	}
	return ((shortcut == ptr->map->x + ptr->map->y) ? 0 : 1);
}

void	loop_writer(char *line, t_filler *ptr)
{
	ptr->map->y = ft_atoi(ft_strchr(line, ' '));
	ptr->map->x = ft_atoi(ft_strrchr(line, ' '));
	free(line);
	GNL(0, &line);
	free(line);
	ptr->map->arr = writer(ptr->map->x, ptr->map->y, 0);
	GNL(0, &line);
	ptr->piece->y = ft_atoi(ft_strchr(line, ' '));
	ptr->piece->x = ft_atoi(ft_strrchr(line, ' '));
	ptr->piece->arr = writer(ptr->piece->x, ptr->piece->y, 1);
	count_stars(ptr);
	count_elems(ptr);
	mem_elems(ptr, 0, 0);
	if (!shortcut(ptr))
	{
		ft_putstr("0 0\n");
		exit(0);
	}
}

int		main(void)
{
	char		*line;
	t_filler	ptr;


	ptr.map = (t_data*)malloc(sizeof(t_data));
	ptr.piece = (t_data*)malloc(sizeof(t_data));

	GNL(0, &line);
	ptr.n = *(ft_strchr(line,'p') + 1) - '0';
	free(line);
	while (GNL(0, &line) > 0)
	{
		loop_writer(line, &ptr);
		ft_putnbr(ptr.result.y);
		ft_putchar(' ');
		ft_putnbr(ptr.result.x);
		ft_putchar('\n');
	}
	return (0);
}