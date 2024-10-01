/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:35:59 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/01 20:23:04 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# ifndef WIDTH
#  define WIDTH 1920
# endif
# ifndef HEIGHT
#  define HEIGHT 1080
# endif

# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_tests
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_tests;

typedef struct s_ray
{
	double		pos_Y;
	double		pos_X;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perpWallDist;
	int			step_x;
	int			step_y;
	bool		hit;
	int			side;
}				t_ray;

void			get_ray_dir(t_ray *ray, unsigned int x);

#endif