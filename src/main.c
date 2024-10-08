/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:46:10 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/08 14:37:42 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parse_cb.h"

int	main(void)
{
	t_data_map	data_map;
    t_img_clr   img_clr;

	init_img_clr(&img_clr);
	data_map.pth_img = NULL;
	data_map.clr_rng = NULL;
	data_map.map = NULL;
	data_map.pth_img = malloc(sizeof(char *) * 5);
	if (data_map.pth_img == NULL)
	{
		printf("Error al asignar memoria para pth_img\n");
		return (1);
	}
	data_map.clr_rng = malloc(sizeof(char *) * 3);
	if (data_map.clr_rng == NULL)
	{
		printf("Error al asignar memoria para clr_rng\n");
		return (1);
	}
	init_str(&data_map);
	data_map.map = NULL;
	if (init_str_map("./prueba.cub", &data_map) == 1)
	{
		free_matrix(data_map.pth_img);
		free_matrix(data_map.clr_rng);
		exit(EXIT_FAILURE);		
	}
	// -------------PRUEBA-------------
	//printf("%d\n", wall_checker(&data_map));
	if (map_exist(&data_map) == 1)
	{
		free_matrix(data_map.pth_img);
		free_matrix(data_map.clr_rng);
		free_matrix(data_map.map);
		exit(EXIT_FAILURE);		
	}
	if ( playable_checker(&data_map) == 1 || check_rgb_num(&data_map) || chr_checker(&data_map) == 1 || check_line_empty(&data_map) == 1 || wall_checker(&data_map) == 1 )
	{
		free_matrix(data_map.pth_img);
		free_matrix(data_map.clr_rng);
		free_matrix(data_map.map);
		exit(EXIT_FAILURE);		
	}
/* 	if (transform_png(img_clr, &data_map) == 1)
    {
        free_matrix(data_map.pth_img);
		free_matrix(data_map.clr_rng);
		free_matrix(data_map.map);
		exit(EXIT_FAILURE);		
    } */
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < (int)ft_strlen(data_map.pth_img[i]); j++)
		{
			printf("%c", data_map.pth_img[i][j]);
		}
		printf("\n");
	}
	// -------------LIBERAR MEMORIA-------------
	if (data_map.pth_img != NULL) {
		free_matrix(data_map.pth_img);
	}
	if (data_map.clr_rng != NULL) {
		free_matrix(data_map.clr_rng);
	}
	if (data_map.map != NULL) {
		free_matrix(data_map.map); 
	}
	return (0);
}