/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsuchen <tsuchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:03:33 by tsuchen           #+#    #+#             */
/*   Updated: 2024/09/02 17:28:23 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	print_data(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	printf("Player position  x: %.2f, y: %.2f\n", data->p_pos.x, data->p_pos.y);
// 	printf("Player direction x: %.2f, y: %.2f\n", data->p_dir.x, data->p_dir.y);
// 	printf("Map path is: %s\n", data->map_path);
// 	printf("Map output:\n");
// 	while (data->map[i])
// 	{
// 		printf("%s", data->map[i]);
// 		i++;
// 	}
// 	printf("Map bound: %zu\n", data->map_bound);
// 	printf("Map width: %zu\n", data->map_width);
// }

static t_bool	is_cub_file(char *file)
{
	uint32_t	index;

	index = 0;
	if (!file)
		return (FALSE);
	while (file[index] && file[index] != '.')
		index++;
	if (ft_strncmp(&file[index], FILE_EXTENSION, 5) == 0)
		return (TRUE);
	ft_putstr_fd("Bad file extension, expected .cub map file.\n", STDERR_FILENO);
	return (FALSE);
}

static int	init_data(t_data *data, char *map_file)
{
	ft_memset(data, 0, sizeof(t_data));
	data->map_path = map_file;
	data->map_fd = open(map_file, O_RDONLY);
	if (data->map_fd < 0)
	{
		ft_putstr_fd("Could not open map file!\n", STDERR_FILENO);
		return (PANIC);
	}
	data->map_width = 0;
	return (SUCCESS);
}

void	start_game(t_data *data)
{
	mlx_loop_hook(data->mlx, rc_rendering, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, &key_events, data);
	mlx_hook(data->window, DestroyNotify, StructureNotifyMask, &cleanup, data);
	mlx_hook(data->window, MotionNotify, PointerMotionMask, &mouse_move, data);
	mlx_loop(data->mlx);
}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac < 2 || ac > 2)
		return (EXIT_FAILURE);
	if (is_cub_file(av[1]) == FALSE)
		return (EXIT_FAILURE);
	if (init_data(&data, av[1]) == PANIC)
		return (EXIT_FAILURE);
	if (parse_map(&data) == PANIC)
		return (EXIT_FAILURE);
	if (game_init(&data) == PANIC)
		return (EXIT_FAILURE);
	start_game(&data);
	cleanup(&data);
	return (0);
}
