/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:36 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/22 18:54:13 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

static void	update_movement(t_render *main, double dir_x, double dir_y)
{
	double	move_x;
	double	move_y;

	move_x = dir_x * SPEED_L;
	move_y = dir_y * SPEED_L;
	if (main->data_map->map[(int)(main->ray->pos_x
			+ move_x)][(int)(main->ray->pos_y)] == '0')
		main->ray->pos_x += move_x;
	if (main->data_map->map[(int)(main->ray->pos_x)][(int)(main->ray->pos_y
			+ move_y)] == '0')
		main->ray->pos_y += move_y;
}

static void	rotate(t_render *main, int dir)
{
	t_angles	angles;

	angles.angle = dir * ROT_SPEED;
	angles.prev_dir_x = main->ray->dir_x;
	angles.prev_plane_x = main->ray->plane_x;
	main->ray->dir_x = angles.prev_dir_x * cos(angles.angle) - main->ray->dir_y
		* sin(angles.angle);
	main->ray->dir_y = angles.prev_dir_x * sin(angles.angle) + main->ray->dir_y
		* cos(angles.angle);
	main->ray->plane_x = angles.prev_plane_x * cos(angles.angle)
		- main->ray->plane_y * sin(angles.angle);
	main->ray->plane_y = angles.prev_plane_x * sin(angles.angle)
		+ main->ray->plane_y * cos(angles.angle);
}

static void	hooks(void *param)
{
	t_render	*main;

	main = (t_render *)param;
	if (mlx_is_key_down(main->mlx, MLX_KEY_ESCAPE))
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

static void	skybox(t_render *main, t_data_map *data_map)
{
	mlx_image_t	*skybox;

	// Check possible errors in new image
	skybox = mlx_new_image(main->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(main->mlx, skybox, 0, 0);
	for (unsigned int y = 0; y < HEIGHT; y++)
	{
		for (unsigned int x = 0; x < WIDTH; x++)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(skybox, x, y, data_map->rgba_ceiling);
			else
				mlx_put_pixel(skybox, x, y, data_map->rgba_floor);
		}
	}
}
void	draw(t_ray *ray, t_render *main, unsigned int x)
{
	uint8_t		*pixel;
	uint32_t	width;
	int			y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		ray->tex_y_coord = (int)ray->tex_pos;
		ray->tex_pos += ray->tex_step;
		width = ray->texs[ray->side]->width;
		pixel = &ray->texs[ray->side]->pixels[width * ray->tex_y_coord * 4
			+ ray->tex_x_cord * 4];
		// Last parameter was harcoded to 255 to prevent trasnparent pngs
		mlx_put_pixel(main->img, x, y,
			pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | 255);
		y++;
	}
}

void	init_mlx(t_data_map *data_map)
{
	t_render	main;

	main.mlx = mlx_init(WIDTH, HEIGHT, "cube3D", true);
	// Later implement error handling logic
	/*if (!main.mlx)
		return(1);*/
	skybox(&main, data_map);
	main.img = mlx_new_image(main.mlx, WIDTH, HEIGHT);
	// Later implement error handling logic
	/*if (!main.img || (mlx_image_to_window(main.mlx, main.img, 0, 0) < 0))
		return (1);*/
	mlx_image_to_window(main.mlx, main.img, 0, 0);
	mlx_loop_hook(main.mlx, hooks, &main);
	// Implement malloc check
	main.ray = malloc(sizeof(t_ray));
	init_ray(&main, data_map);
	raycast(main.ray, data_map, &main);
	mlx_loop(main.mlx);
	mlx_terminate(main.mlx);
	free(main.ray);
}

void	raycast(t_ray *ray, t_data_map *data_map, t_render *main)
{
	unsigned int	x;

	x = 0;
	while (x < WIDTH)
	{
		get_ray_dir(ray, x);
		get_step_and_side_dist(ray);
		dda(ray, data_map);
		get_height(ray);
		text_calc(ray);
		draw(ray, main, x);
		x++;
	}
}
