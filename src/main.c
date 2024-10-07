/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:36 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/02 19:22:56 by juestrel         ###   ########.fr       */
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
}*/

static void hooks(void *param)
{
   t_tests *test = (t_tests *)param;

    if(mlx_is_key_down(test->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(test->mlx);
    /*if (mlx_is_key_down(test->mlx, MLX_KEY_W))
        test->img->instances[0].y -= 5;
    if (mlx_is_key_down(test->mlx, MLX_KEY_S))
        test->img->instances[0].y += 5;
    if (mlx_is_key_down(test->mlx, MLX_KEY_D))
        test->img->instances[0].x += 5;
    if (mlx_is_key_down(test->mlx, MLX_KEY_A))
        test->img->instances[0].x -= 5;*/
}

/*static void skybox(t_tests *main)
{
    mlx_image_t *skybox;

    skybox = mlx_new_image(main->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(main->mlx, skybox, 0, 0);
    for (unsigned int y = 0; y < HEIGHT; y++)
    {
        for (unsigned int x = 0; x < WIDTH; x++)
        {
            if (y < HEIGHT/2)
                mlx_put_pixel(skybox, x, y, 0 << 24 | 0 << 16 | 255 << 8 | 255);
            else
                mlx_put_pixel(skybox, x, y, 0 << 24 | 255 << 16 | 0 << 8 | 255);
        }
    }
    
}*/

static t_ray init_ray(void) 
{
    t_ray raycast;

    raycast.pos_x = 6; //Might need to erase from struct later on
    raycast.pos_y = 6;  //Might need to erase from struct later on
    raycast.map_x = (int)raycast.pos_x; //Might need to erase from struct later on
    raycast.map_y = (int)raycast.pos_y;  //Might need to erase from struct later on
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
    raycast.perp_wall_dist = 0;
    raycast.step_x = 0;
    raycast.step_y = 0;
    raycast.hit = false;
    raycast.side = 0;
    raycast.line_height = 0;
    raycast.draw_start = 0;
    raycast.draw_end = 0;
    return (raycast);
}

int	main(void)
{
    t_tests main;
    int map [8][8] = 
    {
        {1, 1, 1, 1, 1, 1, 1, 1,},
        {1, 0, 1, 0, 0, 0, 0, 1,},
        {1, 0, 1, 0, 0, 0, 0, 1,},
        {1, 0, 1, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 1,},
        {1, 0, 0, 0, 0, 1, 0, 1,},
        {1, 0, 0, 0, 0, 0, 0, 1,},
        {1, 1, 1, 1, 1, 1, 1, 1,},
    };

    (void)map;

    main.mlx = mlx_init(WIDTH, HEIGHT, "cube3D", true);
    if (!main.mlx)
        return(1);
    //skybox(&main);
    main.img = mlx_new_image(main.mlx, WIDTH, HEIGHT);
    if (!main.img || (mlx_image_to_window(main.mlx, main.img, 0, 0) < 0))
		return (1);
    //cube_draw(main.img);
    mlx_loop_hook(main.mlx, hooks, &main);
    t_ray ray = init_ray();
    for (unsigned int x = 0; x < WIDTH; x++)
    {
        get_ray_dir(&ray, x);
        get_step_and_side_dist(&ray);
        dda(&ray, map);
        if (ray.side == 0)
            ray.perp_wall_dist = ray.side_dist_x - ray.delta_dist_x;
        else
            ray.perp_wall_dist = ray.side_dist_y - ray.delta_dist_y;
        get_height(&ray);
        int y = ray.draw_start;
        while (y < ray.draw_end)
        {
            mlx_put_pixel(main.img, x, y, 255 << 24 | 255 << 16 | 255 << 8 | 255);
            y++;
        }
    }
    mlx_loop(main.mlx);
	mlx_terminate(main.mlx);
	return (0);
}
