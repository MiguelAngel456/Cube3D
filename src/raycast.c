/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:30:36 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/23 17:04:35 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

static void	skybox(t_render *main, t_data_map *data_map);
static void	draw(t_ray *ray, t_render *main, unsigned int x);

void	init_mlx(t_data_map *data_map)
{
	t_render	main;

	main.mlx = mlx_init(WIDTH, HEIGHT, "cube3D", true);
	if (!main.mlx)
		free_struc_data(data_map);
	skybox(&main, data_map);
	mlx_loop_hook(main.mlx, hooks, &main);
	main.ray = malloc(sizeof(t_ray));
	if (main.ray == NULL)
		free_struc_data(data_map);
	init_ray(&main, data_map);
	raycast(main.ray, data_map, &main);
	mlx_loop(main.mlx);
	mlx_terminate(main.mlx);
	free(main.ray);
}

static void	skybox(t_render *main, t_data_map *data_map)
{
	mlx_image_t		*skybox;
	unsigned int	x;
	unsigned int	y;

	y = 0;
	skybox = mlx_new_image(main->mlx, WIDTH, HEIGHT);
	if (!skybox || (mlx_image_to_window(main->mlx, skybox, 0, 0) < 0))
		ray_failure(data_map);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(skybox, x, y, data_map->rgba_ceiling);
			else
				mlx_put_pixel(skybox, x, y, data_map->rgba_floor);
			x++;
		}
		y++;
	}
}

void	raycast(t_ray *ray, t_data_map *data_map, t_render *main)
{
	unsigned int	x;

	main->img = mlx_new_image(main->mlx, WIDTH, HEIGHT);
	if (!main->img || (mlx_image_to_window(main->mlx, main->img, 0, 0) < 0))
	{
		free(ray);
		ray_failure(data_map);
	}
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

static void	draw(t_ray *ray, t_render *main, unsigned int x)
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
		mlx_put_pixel(main->img, x, y,
			pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | 255);
		y++;
	}
}

void	ray_failure(t_data_map *map_data)
{
	free_struc_data(map_data);
	exit(EXIT_FAILURE);
}
