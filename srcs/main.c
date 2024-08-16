/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:03:33 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/16 19:29:07 by jteissie         ###   ########.fr       */
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

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac < 2 || ac > 2)
		return (EXIT_FAILURE);
	if (is_cub_file(av[1]) == FALSE)
		return (EXIT_FAILURE);
	ft_memset(&data, 0, sizeof(t_data));
	data.map_path = av[1];
	data.map_fd = open(av[1], O_RDONLY);
	if (data.map_fd < 0)
		return (EXIT_FAILURE);
	if (parse_map(&data) == PANIC)
		return (EXIT_FAILURE);
	close(data.map_fd);
	return (0);
}
