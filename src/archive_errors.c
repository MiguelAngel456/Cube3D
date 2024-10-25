/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:18:12 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/25 19:18:04 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

void	free_matrix_size(char **matrix, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		if (matrix[i] != NULL)
			free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	errors(char **argv, t_data_map *data_map)
{
	if (init_str_map(argv[1], data_map) == 1)
	{
		free_matrix_size(data_map->pth_img, 4);
		free_matrix_size(data_map->clr_rng, 2);
		exit(EXIT_FAILURE);
	}
	if (check_basic_map(argv[1]) == 1 || map_exist(data_map) == 1)
	{
		free_struc_data(data_map);
		exit(EXIT_FAILURE);
	}
	if (playable_checker(data_map) == 1 || check_rgb_num(data_map)
		|| chr_checker(data_map) == 1 || check_line_empty(data_map) == 1
		|| wall_checker(data_map) == 1 || transform_png(data_map) == 1)
	{
		free_struc_data(data_map);
		exit(EXIT_FAILURE);
	}
}

int	check_num(char *num)
{
	int	i;

	i = 0;
	while (num[i] != '\0')
	{
		if (num[i] != '\n')
		{
			if (ft_atoi(&num[i]) == 0 && ft_strncmp(&num[i], "0", 1) != 0)
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_cf(char **split, int *j)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		if ((ft_atoi(split[i]) < 0 || ft_atoi(split[i]) > 256)
			|| check_num(split[i]) == 1)
		{
			free_matrix(split);
			return (printf("Error\nceiling/floor color range error\n"), 1);
		}
		i++;
	}
	(*j) = i;
	return (0);
}
