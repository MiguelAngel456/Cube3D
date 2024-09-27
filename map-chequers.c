/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map-chequers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:20:53 by mfuente-          #+#    #+#             */
/*   Updated: 2024/09/27 11:31:37 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse_cb.h"

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
				else if ((x == (ft_strlen(data_map->map[i]) - 1))
						&& (data_map->map[i][x - 1] != '1'))
				{
					printf("The map is not closed/surrounded by walls5.\n");
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
					printf("The map is not closed/surrounded by walls4.\n");
					return (1);
				}
			}
			x++;
		}
		i++;
	}
	return (0);
}

int check_space(t_data_map *data_map)
{
	
}


int	main(void)
{
	t_data_map	data_map;

	data_map.pth_img = malloc(sizeof(char *) * 5);
	if (data_map.pth_img == NULL)
	{
		printf("Error al asignar memoria para pth_img\n");
		return (1);
	}
	data_map.pth_img[4] = NULL;
	data_map.clr_rng = malloc(sizeof(char *) * 3);
	if (data_map.clr_rng == NULL)
	{
		printf("Error al asignar memoria para pth_img\n");
		return (1);
	}
	data_map.clr_rng[2] = NULL;
	data_map.map = NULL;
	init_str_map("./prueba.cub", &data_map);
	//*************PRUEBA********************
	if (chr_checker(&data_map) == 1 || wall_checker(&data_map) == 1)
	{
		free_matrix(data_map.pth_img);
		free_matrix(data_map.clr_rng);
		free_matrix(data_map.map);
		exit(EXIT_FAILURE);		
	}
	//*********LIBERAR MEMORIA***************
	free_matrix(data_map.pth_img);
	free_matrix(data_map.clr_rng);
	free_matrix(data_map.map);
	return (0);
}
