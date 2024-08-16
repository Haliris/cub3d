/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jteissie <jteissie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 12:03:33 by tsuchen           #+#    #+#             */
/*   Updated: 2024/08/16 14:35:22 by jteissie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	int	map_fd;

	//check for file

	if (ac < 2 || ac > 2)
		return (EXIT_FAILURE);
	map_fd = open(av[1], O_RDONLY);
	if (map_fd < 0)
		return (EXIT_FAILURE);
	if (parse_map(map_fd) == PANIC)
		return (EXIT_FAILURE);
	close(map_fd);
	return (0);
}
