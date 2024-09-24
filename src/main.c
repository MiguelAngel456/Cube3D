/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:36 by juestrel          #+#    #+#             */
/*   Updated: 2024/09/24 19:17:13 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"
#include <stdio.h> //Borrar luego

static void close_window(void *param)
{
    if(mlx_is_key_down((mlx_t *)param, MLX_KEY_ESCAPE))
        mlx_close_window((mlx_t *)param);
}

int	main(void)
{
    mlx_t *mlx = mlx_init(1920, 1080, "cube3D", true);
    if (!mlx)
        return(1);
    mlx_image_t *img = mlx_new_image(mlx, 1000, 1000);
    if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return (1);
    mlx_loop_hook(mlx, close_window, mlx);
    mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
