#include "filler.h"

char	**writer(int x, int y, int piece)
{
	char	**map;
	char	*line;
	int		i;

	// int fd = open("test", O_WRONLY | O_APPEND);
	i = 0;
	map = malloc(sizeof(char*) * y);
	while (i < y && GNL(0, &line) > 0)
	{
		map[i] = malloc(sizeof(char) * (x + 1));
		if (piece)
			ft_strcpy(map[i++], line);
		else
			ft_strcpy(map[i++], line + 4);
		// /////////////////////
		// write(fd, line, ft_strlen(line));
		// write(fd, "\n", 1);
		// ////////////////////
		free(line);
	}
	return (map);
}

void	count_stars(t_filler *ptr)
{
	ptr->stars = 0;
	ptr->start_p.y = -1;
	while (++(ptr->start_p.y) < ptr->piece->y)
		ptr->start_p.x = -1;
		while (++(ptr->start_p.x) < ptr->piece->x)
			if (ptr->piece->arr[ptr->start_p.y][ptr->start_p.x] == '*')
				ptr->stars++;

	ptr->start_p.y = -1;
	while (++(ptr->start_p.y) < ptr->piece->y)
		ptr->start_p.x = -1;
		while (++(ptr->start_p.x) < ptr->piece->x)
			if (ptr->piece->arr[ptr->start_p.y][ptr->start_p.x] == '*')
				return ;
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

void	mem_elems(t_filler *ptr)
{
	t_coord coord;
	int		p;
	int		e;

	p = 0;
	e = 0;
	coord.y = 0;
	while (coord.y < ptr->map->y)
	{
		coord.x = 0;
		while (coord.x < ptr->map->x)
		{
			if (ptr->map->arr[coord.y][coord.x] == 'O')
				(ptr->n == 1 ? ptr->player_coord[p++] = coord :
					ptr->enemy_coord[e++] = coord);
			else (ptr->map->arr[coord.y][coord.x] == 'X')
				(ptr->n == 2 ? ptr->player_coord[p++] = coord :
					ptr->enemy_coord[e++] = coord);
			coord.x++;
		}
		coord.y++;
	}
}

int		coord_valid(t_filler p, t_coord coord)
{
	int i;
	int	j;
	int counter;

	i = 0;
	while (coord.y + i >= 0 && coord.y + i < p.map->y && p.start_p.y + i >= 0 && p.start_p.y + i < p.piece->y)
	{
		j = 0;
		while (coord.x + j >= 0 && coord.x + j < p.map->x && p.start_p.x + j >= 0 && p.start_p.x + j < p.piece->x)
		{
			if (p.map->arr[coord.y + i][coord.x + j] != '.' &&
	p.piece->arr[p.start_p.y + i][p.start_p.x + j] != '.' && !(i == 0 && j == 0))
				 return (0);
			else if (p.piece->arr[p.start_p.y + i][p.start_p.x + j] == '*')
				counter++; 
			j++;
		}
		if (i == 0 && p.start_p.x + j == p.piece->x)
		{
			coord.x -= p.start_p.x;
			p.start_p.x = 0;
		}
		i++;
	}
	return (counter == p.stars) ? (1) : (0);
}

int		shortcut(t_filler *ptr)
{
	int		p;
	int		e;
	int		shortcut;
	int		current;

	shortcut = 0;
	p = 0;
	ft_bzero(&(ptr->result), sizeof(t_coord));
	while (p < ptr->counter_p)
	{
		e = 0;
		while (e < ptr->counter_p)
		{
			current = fabs(ptr->player_coord[p].x - ptr->enemy_coord[e].x)
					+ fabs(ptr->player_coord[p].y - ptr->enemy_coord[e].y);
			if (current <= shortcut && coord_valid(*ptr, ptr->player_coord[p]))
			{
				ptr->result = ptr->player_coord[p];
				shortcut = current;
			}
			e++;
		}
		p++;
	}
	return (shortcut);
}

void	loop_writer(char *line, t_filler *ptr)
{
	// int fd = open("test", O_WRONLY | O_APPEND);
	// ///////////////
	// write(fd, line, ft_strlen(line));
	// write(fd, "\n", 1);
	// ///////////////
	ptr->map->y = ft_atoi(ft_strchr(line, ' '));
	ptr->map->x = ft_atoi(ft_strrchr(line, ' '));
	free(line);
	GNL(0, &line);
	// ////////////////
	// write(fd, line, ft_strlen(line));
	// write(fd, "\n", 1);
	// ////////////////
	free(line);
	ptr->map->arr = writer(ptr->map->x, ptr->map->y, 0);

	GNL(0, &line);
	// ///////////////
	// write(fd, line, ft_strlen(line));
	// write(fd, "\n", 1);
	// //////////////
	ptr->piece->y = ft_atoi(ft_strchr(line, ' '));
	ptr->piece->x = ft_atoi(ft_strrchr(line, ' '));
	ptr->piece->arr = writer(ptr->piece->x, ptr->piece->y, 1);
	count_stars(ptr);
	count_elems(ptr);
	mem_elems(ptr);
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
		ft_putnbr(ptr.result.y - ptr.start_p.y);
		ft_putchar(' ');
		ft_putnbr(ptr.result.x - ptr.start_p.x);
		ft_putchar('\n');
	}
	return (0);
}