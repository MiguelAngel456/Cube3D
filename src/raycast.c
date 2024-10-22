/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:36 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/22 17:41:12 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

static void update_movement(t_render *main, double dir_x, double dir_y)
{
    double   move_x;
    double   move_y;

    move_x = dir_x * SPEED_L;
    move_y = dir_y * SPEED_L;
    if (main->data_map->map[(int)(main->ray->pos_x + move_x)][(int)(main->ray->pos_y)] == '0')
        main->ray->pos_x += move_x;
    if (main->data_map->map[(int)(main->ray->pos_x)][(int)(main->ray->pos_y + move_y)] == '0')
        main->ray->pos_y += move_y;
}

static void rotate(t_render *main, int dir)
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
   t_render *main;
   
   main = (t_render *)param;

    if(mlx_is_key_down(main->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(main->mlx);
    else if (mlx_is_key_down(main->mlx, MLX_KEY_W))
    {
        mlx_delete_image(main->mlx, main->img);
        update_movement(main, main->ray->dir_x, main->ray->dir_y);
        main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(main->mlx, main->img, 0, 0);
        raycast(main->ray, main->data_map, main);
    }
    else if (mlx_is_key_down(main->mlx, MLX_KEY_S))
    {
        mlx_delete_image(main->mlx, main->img);
        update_movement(main, main->ray->dir_x * -1, main->ray->dir_y * -1);
        main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(main->mlx, main->img, 0, 0);
        raycast(main->ray, main->data_map, main);
    }
    else if (mlx_is_key_down(main->mlx, MLX_KEY_A))
    {
        mlx_delete_image(main->mlx, main->img);
        update_movement(main, main->ray->dir_y * -1, main->ray->dir_x);
        main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(main->mlx, main->img, 0, 0);
        raycast(main->ray, main->data_map, main);
    }
    else if (mlx_is_key_down(main->mlx, MLX_KEY_D))
    {
        mlx_delete_image(main->mlx, main->img);
        update_movement(main, main->ray->dir_y, main->ray->dir_x * -1);
        main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(main->mlx, main->img, 0, 0);
        raycast(main->ray, main->data_map, main);
    }
    else if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT))
    {
        mlx_delete_image(main->mlx, main->img);
        rotate(main, 1);
        main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(main->mlx, main->img, 0, 0);
        raycast(main->ray, main->data_map, main);
    }
    else if (mlx_is_key_down(main->mlx, MLX_KEY_RIGHT))
    {
        mlx_delete_image(main->mlx, main->img);
        rotate(main, -1);
        main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT);
        mlx_image_to_window(main->mlx, main->img, 0, 0);
        raycast(main->ray, main->data_map, main);
    }
}

static void skybox(t_render *main, t_data_map *data_map)
{
    mlx_image_t *skybox;
    //Check possible errors in new image
    skybox = mlx_new_image(main->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(main->mlx, skybox, 0, 0);
    for (unsigned int y = 0; y < HEIGHT; y++)
    {
        for (unsigned int x = 0; x < WIDTH; x++)
        {
            if (y < HEIGHT/2)
                mlx_put_pixel(skybox, x, y, data_map->rgba_ceiling);
            else
                mlx_put_pixel(skybox, x, y, data_map->rgba_floor);
        }
    }
}

static void set_orientation(t_ray *raycast, t_data_map *data_map)
{
    if (data_map->chr == 'N')
    {
        raycast->dir_x = -1;
        raycast->dir_y = 0;
        raycast->plane_x = 0;
        raycast->plane_y = 0.66;
    }
    else if (data_map->chr == 'S')
    {
        raycast->dir_x = 1;
        raycast->dir_y = 0;
        raycast->plane_x = 0;
        raycast->plane_y = -0.66;
    }
    else if (data_map->chr == 'E')
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

static void init_ray(t_render *main, t_data_map *map_data) 
{
    t_ray raycast;

    raycast.pos_x = (double)(map_data->chrx + 0.5);
    raycast.pos_y = (double)(map_data->chry + 0.5);  
    raycast.map_x = (int)raycast.pos_x; 
    raycast.map_y = (int)raycast.pos_y; 
    set_orientation(&raycast, map_data);
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
    //Might need to change this later
    raycast.texs[NO] = map_data->textures[NO];
    raycast.texs[SO] = map_data->textures[SO];
    raycast.texs[EA] = map_data->textures[EA];
    raycast.texs[WE] = map_data->textures[WE];
    //Implement checks for failures
    /*raycast.texs[0] = mlx_load_png("./imgs/onePiece.png");
    raycast.texs[1] = mlx_load_png("./imgs/este.png");
    raycast.texs[2] = mlx_load_png("./imgs/norte.png");
    raycast.texs[3] = mlx_load_png("./imgs/oeste.png");*/
    raycast.tex_step = 0;
    raycast.tex_pos = 0;
    *main->ray = raycast;
    main->data_map = map_data;
}

void draw(t_ray *ray, t_render *main, unsigned int x)
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
        //Last parameter was harcoded to 255 to prevent trasnparent pngs
        mlx_put_pixel(main->img, x, y, pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | 255);
        y++;
    }
}

void	init_mlx(t_data_map	*data_map)
{
    t_render main;
    
    main.mlx = mlx_init(WIDTH, HEIGHT, "cube3D", true);
    //Later implement error handling logic
    /*if (!main.mlx)
        return(1);*/
    skybox(&main, data_map);
    main.img = mlx_new_image(main.mlx, WIDTH, HEIGHT);
    //Later implement error handling logic
    /*if (!main.img || (mlx_image_to_window(main.mlx, main.img, 0, 0) < 0))
		return (1);*/
    mlx_image_to_window(main.mlx, main.img, 0, 0);
    mlx_loop_hook(main.mlx, hooks, &main);
    //Implement malloc check
    main.ray = malloc(sizeof(t_ray));
    init_ray(&main, data_map);
    raycast(main.ray, data_map, &main);
    mlx_loop(main.mlx);
	mlx_terminate(main.mlx);
    free(main.ray);
}

void raycast(t_ray *ray, t_data_map *data_map, t_render *main)
{
    unsigned int x;

    x = 0;
    while(x < WIDTH)
    {
        get_ray_dir(ray, x);
        get_step_and_side_dist(ray);
        dda(ray, data_map);
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