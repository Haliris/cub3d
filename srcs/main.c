/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:03:33 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/16 18:20:24 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//check for file extension (.cub);

int	main(int ac, char *av[])
{
	t_data	data;

	if (ac < 2 || ac > 2)
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
