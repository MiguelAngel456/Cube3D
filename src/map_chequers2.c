/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chequers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:56:57 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/09 18:36:26 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parse_cb.h"

int	playable_checker(t_data_map *data_map)
{
	int	i;
	int	x;
	int	cont;

	i = 0;
	cont = 0;
	while (data_map->map[i] != NULL)
	{
		x = 0;
		while (data_map->map[i][x] != '\0')
		{
			if (data_map->map[i][x] == 'N' || data_map->map[i][x] == 'S'
				|| data_map->map[i][x] == 'E' || data_map->map[i][x] == 'W')
				cont++;
			x++;
		}
		i++;
	}
	if (cont < 1 || cont > 1)
	{
		printf("Error\nincorrect number of playable characters\n");
		return (1);
	}
	return (0);
}

int	wall_checker_3(t_data_map *data_map, int x, int i, int size)
{
	int	row_len;

	row_len = ft_strlen(data_map->map[i]);
	if (i == size && data_map->map[i][x] != '1')
		return (printf("Error\nThe map is not surrounded by walls.\n"), 1);
	else if ((x == row_len - 1) && (data_map->map[i][x - 1] != '1'))
		return (printf("Error\nThe map is not surrounded by walls.\n"), 1);
	else if (x == 0 && (data_map->map[i][x] != ' '
		&& data_map->map[i][x] != '1'))
		return (printf("Error\nThe map is not surrounded by walls.\n"), 1);
	return (0);
}

int	map_exist(t_data_map *data_map)
{
	if (data_map->map[1] == NULL)
		return (printf("Error\nThe map is empty.\n"), 1);
	return (0);
}
