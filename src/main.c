/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:36 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/10 19:39:04 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

static void hooks(void *param)
{
   t_tests *test;
   
   test = (t_tests *)param;

    if(mlx_is_key_down(test->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(test->mlx);
    else if (mlx_is_key_down(test->mlx, MLX_KEY_W))
    {
        mlx_delete_image(test->mlx, test->img);
        test->ray->pos_x += test->ray->dir_x * 0.15;
        test->ray->pos_y += test->ray->dir_y * 0.15;
        test->img = mlx_new_image(test->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(test->mlx, test->img, 0, 0);
        raycast(test->ray, test->map, test);
    }
}

static void skybox(t_tests *main)
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
}

static void set_orientation(t_ray *raycast, char *argv[])
{
    if (argv[1][0] == 'N')
    {
        raycast->dir_x = -1;
        raycast->dir_y = 0;
        raycast->plane_x = 0;
        raycast->plane_y = 0.66;
    }
    else if (argv[1][0] == 'S')
    {
        raycast->dir_x = 1;
        raycast->dir_y = 0;
        raycast->plane_x = 0;
        raycast->plane_y = -0.66;
    }
    else if (argv[1][0] == 'E')
    {
        raycast->dir_x = 0;
        raycast->dir_y = 1;
        raycast->plane_x = 0.66;
        raycast->plane_y = 0;
    }
    else
    {
        raycast->dir_x = 0;
        raycast->dir_y = -1;
        raycast->plane_x = -0.66;
        raycast->plane_y = 0;
    }
}

static void init_ray(t_tests *main, char *argv[]) 
{
    t_ray raycast;

    raycast.pos_x = 6.5;
    raycast.pos_y = 6.5;  
    raycast.map_x = (int)raycast.pos_x; 
    raycast.map_y = (int)raycast.pos_y; 
    set_orientation(&raycast, argv);
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
    *main->ray = raycast;
}

int	main(int argc, char *argv[])
{
    t_tests main;
    
    if (argc != 2)
        return (1);
    int map[SIZE][SIZE] = 
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
    ft_memcpy(main.map, map, sizeof(map));
    main.mlx = mlx_init(WIDTH, HEIGHT, "cube3D", true);
    if (!main.mlx)
        return(1);
    skybox(&main);
    main.img = mlx_new_image(main.mlx, WIDTH, HEIGHT);
    if (!main.img || (mlx_image_to_window(main.mlx, main.img, 0, 0) < 0))
		return (1);
    mlx_loop_hook(main.mlx, hooks, &main);
    main.ray = malloc(sizeof(t_ray));
    init_ray(&main ,argv);
    raycast(main.ray, map, &main);
    mlx_loop(main.mlx);
	mlx_terminate(main.mlx);
    free(main.ray);
	return (0);
}

void raycast(t_ray *ray, int map[SIZE][SIZE], t_tests *main)
{
    unsigned int x;

    x = 0;
    while(x < WIDTH)
    {
        get_ray_dir(ray, x);
        get_step_and_side_dist(ray);
        dda(ray, map);
        get_height(ray);
        int y = ray->draw_start;
        while (y < ray->draw_end)
        {
            mlx_put_pixel(main->img, x, y, 255 << 24 | 255 << 16 | 255 << 8 | 255);
            y++;
        }
        x++;
    }
}
