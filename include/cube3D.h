/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:35:59 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/21 15:47:38 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# ifndef WIDTH
#  define WIDTH 1280
# endif
# ifndef HEIGHT
#  define HEIGHT 720
# endif
# ifndef INFINITE
#  define INFINITE 1e30
# endif
# ifndef SIZE
#  define SIZE 8
# endif
# ifndef SPEED_L
#  define SPEED_L 0.05
# endif
# ifndef ROT_SPEED
#  define ROT_SPEED 0.04
# endif

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_ray
{
	double			pos_y;
	double			pos_x;
	int				map_x;
	int				map_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	bool			hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			wall_x;
	int				tex_x_cord;
	int				tex_y_coord;
	double			tex_step;
	double			tex_pos;
	mlx_texture_t	*texs[4];
}					t_ray;

typedef struct s_angles
{
	double			angle;
	double			prev_dir_x;
	double			prev_plane_x;
}					t_angles;

typedef struct s_tests
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				map[SIZE][SIZE];
	t_ray			*ray;
}					t_tests;

void				get_ray_dir(t_ray *ray, unsigned int x);
void				get_step_and_side_dist(t_ray *ray);
void				dda(t_ray *ray, int map[SIZE][SIZE]);
void				get_height(t_ray *ray);
void				raycast(t_ray *ray, int map[SIZE][SIZE], t_tests *main);
#endif/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:35:59 by juestrel          #+#    #+#             */
/*   Updated: 2024/10/07 18:11:46 by juestrel         ###   ########.fr       */
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
# ifndef INFINITE
#  define INFINITE 1e30
# endif

# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_tests
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_tests;

typedef struct s_ray
{
	double pos_y; // Might need to delete later from this struct
	double pos_x; // Might need to delete later from this struct
	int map_x;    // Might need to delete later from this struct
	int map_y;    // Might need to delete later from this struct
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	bool		hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

void			get_ray_dir(t_ray *ray, unsigned int x);
void			get_step_and_side_dist(t_ray *ray);
void			dda(t_ray *ray, int map[8][8]);
void			get_height(t_ray *ray);
#endif