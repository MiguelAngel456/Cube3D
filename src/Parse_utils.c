/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:34:15 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/08 11:38:27 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parse_cb.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
		i++;
	return (i);
}

void	init_str(t_data_map *data_map)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data_map->pth_img[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		data_map->clr_rng[i] = NULL;
		i++;
	}
}
