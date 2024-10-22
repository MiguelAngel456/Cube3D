/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textCalc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:41:51 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/22 18:44:29 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

void	text_calc(t_ray *ray)
{
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
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->tex_step;
}
