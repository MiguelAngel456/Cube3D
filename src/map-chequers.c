/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-chequers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:20:53 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/03 11:42:22 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parse_cb.h"

static int matrix_size(char  **matrix)
{
	int i;
	
	i = 0;
	while (matrix[i] != NULL)
		i++;
	return (i);
}

int	chr_checker(t_data_map *data_map)
{
	int	i;
	int x;

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
				printf("The map contains wrong character\n");
				return (1);
			}
			x++;
		}
		i++;
	}
	return (0);
}

int check_line_empty(t_data_map *data_map)
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
				return (printf("Empty line(s) in map\n"),1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
int check_rgb_num(t_data_map *data_map)
{
	int		i;
	int		j;
	char	**split;
	
	i = 0;
	while(data_map->clr_rng[i] != NULL)
	{
		if (data_map->clr_rng[i] == NULL)
			return (printf("ceiling or floor color error\n"), 1);
		split = ft_split(data_map->clr_rng[i], ',');
		j = 0;
		while(split[j] != NULL)
		{
			if (ft_atoi(split[j]) < 0 || ft_atoi(split[j]) > 256)
				return (printf("ceiling or floor color range error\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

int	wall_checker(t_data_map *data_map)
{
	int	i;
	int	x;
	int	size;

	size = matrix_size(data_map->map);
	i = 0;
	x = 0;
	while (data_map->map[i] != NULL)
	{
		x = 0;
		while (data_map->map[i][x] != '\0')
		{
			if (i == 0)
			{
				if ((data_map->map[i][x] != '1' && data_map->map[i][x] != ' ' && data_map->map[i][x] != '\n'))
				{
					printf("The map is not closed/surrounded by walls.\n");
					return (1);
				}	
			}
			else
			{
				if (i == size && data_map->map[i][x] != '1')
				{
					printf("The map is not closed/surrounded by walls.\n");
					return (1);
				}
				else if ((x == (int)(ft_strlen(data_map->map[i]) - 1))
						&& (data_map->map[i][x - 1] != '1'))
				{
					printf("The map is not closed/surrounded by walls.\n");
					return (1);
				}
				else if (x == 0 && (data_map->map[i][x] != ' ' && data_map->map[i][x] != '1'))
				{
					printf("The map is not closed/surrounded by walls.\n");
					return (1);
				}
				else if ((data_map->map[i][x] != '1' 
						&& data_map->map[i][x] != ' ')
						&& ((data_map->map[i][x - 1] == ' ' 
						|| data_map->map[i][x + 1] == ' '
						|| data_map->map[i + 1][x] == ' ' 
						|| data_map->map[i - 1][x] == ' ')))
				{
					printf("The map is not closed/surrounded by walls.\n");
					return (1);
				}
			}
			x++;
		}
		i++;
	}
	return (0);
}


