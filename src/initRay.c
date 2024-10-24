/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initRay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:49:13 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/24 17:14:18 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

static t_ray	init_coord_and_dir(t_data_map *map_data);
static void		set_orientation_n_s(t_ray *raycast, t_data_map *data_map);
static void		set_orientation_w_e(t_ray *raycast, t_data_map *data_map);

void	init_ray(t_render *main, t_data_map *map_data)
{
	t_ray	raycast;

	raycast = init_coord_and_dir(map_data);
	set_orientation_n_s(&raycast, map_data);
	set_orientation_w_e(&raycast, map_data);
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
	raycast.texs[NO] = map_data->textures[NO];
	raycast.texs[SO] = map_data->textures[SO];
	raycast.texs[EA] = map_data->textures[EA];
	raycast.texs[WE] = map_data->textures[WE];
	raycast.tex_step = 0;
	raycast.tex_pos = 0;
	*main->ray = raycast;
	main->data_map = map_data;
}

static t_ray	init_coord_and_dir(t_data_map *map_data)
{
	t_ray	raycast;

	raycast.pos_x = (double)(map_data->chrx + 0.5);
	raycast.pos_y = (double)(map_data->chry + 0.5);
	raycast.map_x = (int)raycast.pos_x;
	raycast.map_y = (int)raycast.pos_y;
	raycast.camera_x = 0;
	raycast.ray_dir_x = 0;
	raycast.ray_dir_y = 0;
	raycast.map_x = 0;
	raycast.map_y = 0;
	raycast.side_dist_x = 0;
	raycast.side_dist_y = 0;
	raycast.delta_dist_x = 0;
	raycast.delta_dist_y = 0;
	return (raycast);
}

static void	set_orientation_n_s(t_ray *raycast, t_data_map *data_map)
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
}

static void	set_orientation_w_e(t_ray *raycast, t_data_map *data_map)
{
	if (data_map->chr == 'W')
	{
		raycast->dir_x = 0;
		raycast->dir_y = -1;
		raycast->plane_x = -0.66;
		raycast->plane_y = 0;
	}
	else if (data_map->chr == 'E')
	{
		raycast->dir_x = 0;
		raycast->dir_y = 1;
		raycast->plane_x = 0.66;
		raycast->plane_y = 0;
	}
}
