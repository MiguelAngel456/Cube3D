/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:46:10 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/23 16:15:22 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

void	free_struc_data(t_data_map *data_map)
{
	int	i;

	i = 0;
	free_matrix(data_map->pth_img);
	free_matrix(data_map->clr_rng);
	free_matrix(data_map->map);
	while (i < 4)
	{
		mlx_delete_texture(data_map->textures[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data_map	data_map;

	if (argc != 2)
		return (printf("Numero de argumentos incorrecto.\n"), 1);
	init_img_clr(&data_map);
	data_map.pth_img = malloc(sizeof(char *) * 5);
	if (data_map.pth_img == NULL)
		return (printf("Error al asignar memoria para pth_img\n"), 1);
	data_map.clr_rng = malloc(sizeof(char *) * 3);
	if (data_map.clr_rng == NULL)
		return (printf("Error al asignar memoria para clr_rng\n"), 1);
	init_str(&data_map);
	errors(argv, &data_map);
	get_rgba(255, &data_map);
	init_mlx(&data_map);
	free_struc_data(&data_map);
	return (0);
}
