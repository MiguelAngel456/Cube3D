/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chequers2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:56:57 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/04 12:50:31 by mfuente-         ###   ########.fr       */
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
		printf("incorrect number of playable characters\n");
		return (1);
	}
	return (0);
}
