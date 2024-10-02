/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:52:06 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/01 18:23:56 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parse_cb.h"


void transform_png(t_img_clr img_clr, t_data_map *data_map)
{   
    img_clr.north_texture = mlx_load_png(&data_map[NO]);
    img_clr.north_texture = mlx_load_png(&data_map[SO]);
    img_clr.north_texture = mlx_load_png(&data_map[WE]);
    img_clr.north_texture = mlx_load_png(&data_map[EA]);
}
//colores //RR,VV,AA
//1.- tranformar cada numero en hexadecimal
//2.- fusionarlos con FF