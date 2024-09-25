/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:35:59 by juestrel          #+#    #+#             */
/*   Updated: 2024/09/25 19:33:59 by juestrel         ###   ########.fr       */
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

#endif