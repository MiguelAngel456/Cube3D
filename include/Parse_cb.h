/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_cb.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:42:52 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/10 12:34:33 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CB_H
# define PARSE_CB_H

# define FT_INT_MAX 2147483647
# define FT_INT_MIN -2147483648

// LIBRERIAS NECESARIAS
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>

// PARA EL ARRAY DE DIRECCIONES DE IMAGENES
# define NO 0
# define SO 1
# define WE 2
# define EA 3
// PARA EL ARRAY DE COLORES
# define F 0
# define C 1

typedef struct str_data_map
{
	char	**map;//		COPIA DEL MAPA
	char	**pth_img;//	MATRIZ DE TODAS LAS IMAGENES
	char	**clr_rng;//	MATRIZ DE LOS RANGOS DE COLORES
}		t_data_map;

typedef struct str_img_clr
{
	mlx_texture_t	*north_texture; //	TEXTURA DE LOS MUROS DEL NORTE
	mlx_texture_t	*south_texture; //	TEXTURA DE LOS MUROS DEL SUR
	mlx_texture_t	*west_texture; //	TEXTURA DE LOS MUROS DEL OESTE
	mlx_texture_t	*east_texture; //	TEXTURA DE LOS MUROS DEL ESTES
	uint32_t		rgba_ceiling; //	COLOR DEL TECHO
	uint32_t		rgba_floor; //		COLOR DEL SUELO
}		t_img_clr;

// ------------------------Parse_cd.c------------------------
int		init_str_map(char *path, t_data_map *data_map);
// ------------------------map_chequers.c------------------------
int		chr_checker(t_data_map *data_map);
int		check_line_empty(t_data_map *data_map);
int		check_rgb_num(t_data_map *data_map);
int		wall_checker(t_data_map *data_map);
// ------------------------map_chequers2.c------------------------
int		playable_checker(t_data_map *data_map);
int		wall_checker_3(t_data_map *data_map, int x, int i, int size);
int		map_exist(t_data_map *data_map);
// ------------------------texture_colors.c------------------------
int		transform_png(t_img_clr img_clr, t_data_map *data_map);
void	init_img_clr(t_img_clr *img_clr);
void	get_rgba(int alpha, t_data_map *data_map, t_img_clr *img_clr);
// ------------------------Parse_utils.c------------------------
int		matrix_size(char **matrix);
int		check_basic_map(char *map);
void	free_matrix(char **matrix);
void	init_str(t_data_map *data_map);

#endif