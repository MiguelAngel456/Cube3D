/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_cb.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:42:52 by mfuente-          #+#    #+#             */
/*   Updated: 2024/09/24 14:01:07 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CB_H
# define PARSE_CB_H

# define FT_INT_MAX 2147483647
# define FT_INT_MIN -2147483648

// LIBRERIAS NECESARIAS
# include "libft/libft.h"
# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
//# include "./MLX42/include/MLX42/MLX42.h"

typedef struct str_data_map
{
	char	**map;// COPIA DEL MAPA
	char	**pth_img;// MATRIZ DE TODAS LAS IMAGENES
	char	**clr_rng;// MATRIZ DE LOS RANGOS DE COLORES
}	t_data_map;

#endif