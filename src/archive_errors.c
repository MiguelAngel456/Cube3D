/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   archive_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:18:12 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/23 16:42:32 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

void	errors(char **argv, t_data_map *data_map)
{
	if (init_str_map(argv[1], data_map) == 1)
	{
		free_matrix(data_map->pth_img);
		free_matrix(data_map->clr_rng);
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
