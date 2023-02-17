#include "../include/fdf.h"

void	print_map(t_map *map)
{
	int x = 0;
	int y = 0;
	while (y < map->sizey)
	{
		while (x < map->sizex)
		{
			printf("%d\t", map->map[y][x].z);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
}

int	main(int ac, char **av)
{
	t_map	*map;
	if (ac != 2)
		return (write(2, "Error\n", 6), 1);
	map = parser(av[1]);
	print_map(map);
	//if (!map)
	//	return (write(2, "Error\n", 6), 1);
	init_mlx_me();
	return (0);
}