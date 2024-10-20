/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:36 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/20 13:03:12 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

static void update_movement(t_tests *main, double dir_x, double dir_y)
{
    double   move_x;
    double   move_y;

    move_x = dir_x * SPEED_L;
    move_y = dir_y * SPEED_L;
    if (main->map[(int)(main->ray->pos_x + move_x)][(int)(main->ray->pos_y)] == 0)
        main->ray->pos_x += move_x;
    if (main->map[(int)(main->ray->pos_x)][(int)(main->ray->pos_y + move_y)] == 0)
        main->ray->pos_y += move_y;
}

static void rotate(t_tests *main, int dir)
{
    t_angles angles;

    angles.angle = dir * ROT_SPEED;
    angles.prev_dir_x = main->ray->dir_x;
    angles.prev_plane_x = main->ray->plane_x;
    main->ray->dir_x = angles.prev_dir_x * cos(angles.angle) - main->ray->dir_y * sin(angles.angle);
    main->ray->dir_y = angles.prev_dir_x * sin(angles.angle) + main->ray->dir_y * cos(angles.angle);
    main->ray->plane_x = angles.prev_plane_x * cos(angles.angle) - main->ray->plane_y * sin(angles.angle);
    main->ray->plane_y = angles.prev_plane_x * sin(angles.angle) + main->ray->plane_y * cos(angles.angle);
}

static void hooks(void *param)
{
   t_tests *test;
   
   test = (t_tests *)param;

    if(mlx_is_key_down(test->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(test->mlx);
    else if (mlx_is_key_down(test->mlx, MLX_KEY_W))
    {
        mlx_delete_image(test->mlx, test->img);
        update_movement(test, test->ray->dir_x, test->ray->dir_y);
        test->img = mlx_new_image(test->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(test->mlx, test->img, 0, 0);
        raycast(test->ray, test->map, test);
    }
    else if (mlx_is_key_down(test->mlx, MLX_KEY_S))
    {
        mlx_delete_image(test->mlx, test->img);
        update_movement(test, test->ray->dir_x * -1, test->ray->dir_y * -1);
        test->img = mlx_new_image(test->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(test->mlx, test->img, 0, 0);
        raycast(test->ray, test->map, test);
    }
    else if (mlx_is_key_down(test->mlx, MLX_KEY_A))
    {
        mlx_delete_image(test->mlx, test->img);
        update_movement(test, test->ray->dir_y * -1, test->ray->dir_x);
        test->img = mlx_new_image(test->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(test->mlx, test->img, 0, 0);
        raycast(test->ray, test->map, test);
    }
    else if (mlx_is_key_down(test->mlx, MLX_KEY_D))
    {
        mlx_delete_image(test->mlx, test->img);
        update_movement(test, test->ray->dir_y, test->ray->dir_x * -1);
        test->img = mlx_new_image(test->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(test->mlx, test->img, 0, 0);
        raycast(test->ray, test->map, test);
    }
    else if (mlx_is_key_down(test->mlx, MLX_KEY_LEFT))
    {
        mlx_delete_image(test->mlx, test->img);
        rotate(test, 1);
        test->img = mlx_new_image(test->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(test->mlx, test->img, 0, 0);
        raycast(test->ray, test->map, test);
    }
    else if (mlx_is_key_down(test->mlx, MLX_KEY_RIGHT))
    {
        mlx_delete_image(test->mlx, test->img);
        rotate(test, -1);
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
    raycast.wall_x = 0;
    raycast.tex_x_cord = 0;
    raycast.texs[0] = mlx_load_png("./imgs/sur.png");
    raycast.texs[1] = mlx_load_png("./imgs/este.png");
    raycast.texs[2] = mlx_load_png("./imgs/norte.png");
    raycast.texs[3] = mlx_load_png("./imgs/oeste.png");
    raycast.tex_step = 0;
    raycast.tex_pos = 0;
    *main->ray = raycast;
}

void draw(t_ray *ray, t_tests *main, unsigned int x)
{
    uint8_t		*pixel;
    uint32_t     width;
    
    int y = ray->draw_start;
    while (y < ray->draw_end)
    {
        ray->tex_y_coord = (int)ray->tex_pos;
        ray->tex_pos += ray->tex_step;
        width = ray->texs[ray->side]->width;
        pixel = &ray->texs[ray->side]->pixels[width * ray->tex_y_coord * 4 + ray->tex_x_cord * 4];
        mlx_put_pixel(main->img, x, y, pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
        y++;
    }
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
        //Start from here
        if (ray->side == 0)
            ray->wall_x = ray->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
        else
            ray->wall_x = ray->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
        ray->wall_x -= floor(ray->wall_x);
        ray->tex_x_cord = (int)(ray->wall_x * (float)ray->texs[ray->side]->width);
        ray->tex_x_cord = ray->texs[ray->side]->width - ray->tex_x_cord - 1;
        if (ray->side == 0 && (ray->map_x - ray->pos_x) >= 0)
            ray->side += 2;
        if (ray->side == 1 && (ray->map_y - ray->pos_y) >= 0)
            ray->side += 2;
        ray->tex_step = 1.0 * ray->texs[ray->side]->height / ray->line_height;
        ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * ray->tex_step;
        
        //End here
       draw(ray, main, x);
       x++;
    }
}


