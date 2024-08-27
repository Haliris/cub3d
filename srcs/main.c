/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:03:33 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/27 15:12:10 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	cleanup(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
		free(data->mlx);
	mlx_destroy_display(data->mlx);
}

static int	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->map_path = av[1];
	data->map_fd = open(av[1], O_RDONLY);
	if (data->map_fd < 0)
	{
		ft_putstr_fd("Could not open map file!\n", STDERR_FILENO);
		return (PANIC);
	}
	return (SUCCESS);
}

static int	game_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (PANIC);
	data->window = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	if (!data->window)
	{
		cleanup(data);
		return (PANIC);
	}
	return (SUCCESS);
}

void	start_game(t_data *data)
{

}

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac < 2 || ac > 2)
		return (EXIT_FAILURE);
	if (is_cub_file(av[1]) == FALSE)
		return (EXIT_FAILURE);
	if (init_data(&data) == PANIC)
		return (EXIT_FAILURE);
	if (parse_map(&data) == PANIC)
		return (EXIT_FAILURE);
	if (game_init(&data) == PANIC)
		return (EXIT_FAILURE);
	start_game(&data);
	cleanup(&data);
	close(data.map_fd);
	return (0);
}
