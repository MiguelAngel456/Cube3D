/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_chequers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:20:53 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/22 17:06:39 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

int	chr_checker(t_data_map *data_map)
{
	int	i;
	int	x;

	x = 0;
	i = 0;
	while (data_map->map[i] != NULL)
	{
		x = 0;
		while (data_map->map[i][x] != '\0')
		{
			if (data_map->map[i][x] != '1' && data_map->map[i][x] != '0'
				&& data_map->map[i][x] != ' ' && data_map->map[i][x] != 'N'
				&& data_map->map[i][x] != 'S' && data_map->map[i][x] != 'E'
				&& data_map->map[i][x] != 'W' && data_map->map[i][x] != '\n')
			{
				printf("Error\nThe map contains wrong character\n");
				return (1);
			}
			x++;
		}
		i++;
	}
	return (0);
}

int	check_line_empty(t_data_map *data_map)
{
	int	i;
	int	j;

	i = 0;
	while (data_map->map[i] != NULL)
	{
		j = 0;
		while (data_map->map[i][j] != '\0')
		{
			if (ft_strlen(data_map->map[i]) == 1 && data_map->map[i][j] == '\n')
			{
				return (printf("Error\nEmpty line(s) in map\n"), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_rgb_num(t_data_map *data_map)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	while (data_map->clr_rng[i] != NULL)
	{
		if (data_map->clr_rng[i] == NULL)
			return (printf("Error\nceiling or floor color error\n"), 1);
		split = ft_split(data_map->clr_rng[i], ',');
		j = 0;
		while (split[j] != NULL)
		{
			if (ft_atoi(split[j]) < 0 || ft_atoi(split[j]) > 256)
			{
				free_matrix(split);
				printf("Error\n");
				return (printf("ceiling or floor color range error\n"), 1);
			}
			j++;
		}
		i++;
		free_matrix(split);
	}
	return (0);
}

static int	wall_checker_2(t_data_map *data_map, int x, int i, int size)
{
	if (wall_checker_3(data_map, x, i, size) == 1)
		return (1);
	else if ((data_map->map[i][x] != '1'
		&& data_map->map[i][x] != ' '
		&& data_map->map[i][x] != '\n')
		&& ((data_map->map[i][x - 1] == ' '
		|| data_map->map[i][x + 1] == ' '
		|| ((int)ft_strlen(data_map->map[i + 1]) > x
		&& data_map->map[i + 1][x] == ' ')
		|| ((int)ft_strlen(data_map->map[i - 1]) > x
		&& data_map->map[i - 1][x] == ' '))))
	{
		return (printf("Error\nThe map is not surrounded by walls.\n"), 1);
	}
	else if ((data_map->map[i][x] != '1'
		&& data_map->map[i][x] != ' '
		&& data_map->map[i][x] != '\n')
		&& ((data_map->map[i][x - 1] == ' '
		|| data_map->map[i][x + 1] == ' '
		|| ((int)ft_strlen(data_map->map[i + 1]) <= x)
		|| ((int)ft_strlen(data_map->map[i - 1]) <= x))))
	{
		return (printf("Error\nThe map is not surrounded by walls.\n"), 1);
	}
	return (0);
}

int	wall_checker(t_data_map *data_map)
{
	int	i;
	int	x;
	int	size;
	int len;
	
	size = matrix_size(data_map->map);
	i = 0;
	while (data_map->map[i] != NULL)
	{
		x = 0;
		len = ft_strlen(&data_map->map[i][x]);
		while (data_map->map[i][x] != '\0')
		{
			if (i == 0)
			{
				//printf("%s---\n", data_map->map[i]);
				if ((data_map->map[i][x] != '1' && data_map->map[i][x] != ' '
						&& data_map->map[i][x] != '\n'))
					return (printf("Error\nthe map isnt surrounded by walls1.\n"), 1);
			}
			else
				if (wall_checker_2(data_map, x, i, size) == 1)
					return (1);
			x++;
		}
		i++;
	}
	return (0);
}
