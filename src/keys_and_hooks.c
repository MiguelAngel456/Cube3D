/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_and_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:41:02 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/23 17:05:41 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

static void	update_movement(t_render *main, double dir_x, double dir_y);
static void	rotate(t_render *main, int dir);

void	hooks(void *param)
{
	t_render	*main;

	main = (t_render *)param;
	if (mlx_is_key_down(main->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(main->mlx);
	else if (mlx_is_key_down(main->mlx, MLX_KEY_W))
	{
		mlx_delete_image(main->mlx, main->img);
		update_movement(main, main->ray->dir_x, main->ray->dir_y);
		raycast(main->ray, main->data_map, main);
	}
	else if (mlx_is_key_down(main->mlx, MLX_KEY_S))
	{
		mlx_delete_image(main->mlx, main->img);
		update_movement(main, main->ray->dir_x * -1, main->ray->dir_y * -1);
		raycast(main->ray, main->data_map, main);
	}
	else if (mlx_is_key_down(main->mlx, MLX_KEY_A))
	{
		mlx_delete_image(main->mlx, main->img);
		update_movement(main, main->ray->dir_y * -1, main->ray->dir_x);
		raycast(main->ray, main->data_map, main);
	}
	else if (mlx_is_key_down(main->mlx, MLX_KEY_D))
	{
		mlx_delete_image(main->mlx, main->img);
		update_movement(main, main->ray->dir_y, main->ray->dir_x * -1);
		raycast(main->ray, main->data_map, main);
	}
	else if (mlx_is_key_down(main->mlx, MLX_KEY_LEFT))
	{
		mlx_delete_image(main->mlx, main->img);
		rotate(main, 1);
		raycast(main->ray, main->data_map, main);
	}
	else if (mlx_is_key_down(main->mlx, MLX_KEY_RIGHT))
	{
		mlx_delete_image(main->mlx, main->img);
		rotate(main, -1);
		raycast(main->ray, main->data_map, main);
	}
}

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
