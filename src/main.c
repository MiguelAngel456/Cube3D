/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:36 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/01 20:17:57 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

/*static void cube_draw(mlx_image_t *img)
{
    unsigned int color = 255 << 24 | 255 << 16 | 0 << 8 | 255;
    unsigned int size = 16;

    for (unsigned int y = 0 ; y < size; y++)
    {
        for (unsigned int x = 0; x < size; x++) 
            mlx_put_pixel(img, x, y, color);
    }
    img->instances[0].y += HEIGHT/2;
    img->instances[0].x += WIDTH/2;
}

static void hooks(void *param)
{
   t_tests *test = (t_tests *)param;

    if(mlx_is_key_down(test->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(test->mlx);
    if (mlx_is_key_down(test->mlx, MLX_KEY_W))
        test->img->instances[0].y -= 5;
    if (mlx_is_key_down(test->mlx, MLX_KEY_S))
        test->img->instances[0].y += 5;
    if (mlx_is_key_down(test->mlx, MLX_KEY_D))
        test->img->instances[0].x += 5;
    if (mlx_is_key_down(test->mlx, MLX_KEY_A))
        test->img->instances[0].x -= 5;
}*/

static t_ray init_ray(void) 
{
    t_ray raycast;

    raycast.dir_x = -1;
    raycast.dir_y = 0;
    raycast.plane_x = 0;
    raycast.plane_y = 0.66;
    raycast.camera_x = 0;
    raycast.ray_dir_x = 0;
    raycast.ray_dir_y = 0;
    raycast.map_x = 0;
    raycast.map_y = 0;
    raycast.side_dist_x = 0;
    raycast.side_dist_y = 0;
    raycast.delta_dist_x = 0;
    raycast.delta_dist_y = 0;
    raycast.perpWallDist = 0;
    raycast.step_x = 0;
    raycast.step_y = 0;
    raycast.hit = false;
    raycast.side = 0;
}

int	main(void)
{
    t_tests main;

    main.mlx = mlx_init(1920, 1080, "cube3D", true);
    if (!main.mlx)
        return(1);
    main.img = mlx_new_image(main.mlx, 16, 16);
    if (!main.img || (mlx_image_to_window(main.mlx, main.img, 0, 0) < 0))
		return (1);
    //cube_draw(main.img);
    //mlx_loop_hook(main.mlx, hooks, &main);
    t_ray ray = init_ray();
    mlx_loop(main.mlx);
	mlx_terminate(main.mlx);
	return (0);
}
