/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:52:06 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/04 11:35:00 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Parse_cb.h"

void	init_img_clr(t_img_clr *img_clr)
{
	img_clr->north_texture = NULL;
	img_clr->south_texture = NULL;
	img_clr->west_texture = NULL;
	img_clr->east_texture = NULL;
	img_clr->rgba_ceiling = 0;
	img_clr->rgba_floor = 0;
}

int	transform_png(t_img_clr img_clr, t_data_map *data_map)
{
	img_clr.north_texture = mlx_load_png(data_map->pth_img[NO]);
	if (img_clr.north_texture == NULL)
		return (printf("Error with the load north textures\n"), 1);
	img_clr.south_texture = mlx_load_png(data_map->pth_img[SO]);
	if (img_clr.south_texture == NULL)
		return (printf("Error with the load south textures\n"), 1);
	img_clr.west_texture = mlx_load_png(data_map->pth_img[WE]);
	if (img_clr.west_texture == NULL)
		return (printf("Error with the load west textures\n"), 1);
	img_clr.east_texture = mlx_load_png(data_map->pth_img[EA]);
	if (img_clr.east_texture == NULL)
		return (printf("Error with the load east textures\n"), 1);
	return (0);
}
// colores //RR,VV,AA
// Saco los numeros del string a int
// Los voy pasando a un uint32_t
// moviendo los bit hacia la izquierda dependiendo de cual sea
// 1º-> 24 posiciones, 2º-> 16 posiciones, 3º-> 8 posiciones
// y al final un int llamado alpha que es la opacidad

static int	*colors_int(char *text)
{
	int		*rgb;
	char	**split;

	split = ft_split(text, ',');
	rgb = malloc(sizeof(int *) * 4);
	rgb[0] = ft_atoi(split[0]);
	rgb[1] = ft_atoi(split[1]);
	rgb[2] = ft_atoi(split[2]);
	rgb[3] = '\0';
	free_matrix(split);
	return (rgb);
}

void	get_rgba(int alpha, t_data_map *data_map, t_img_clr *img_clr)
{
	uint32_t	rgba;
	int			*colors;

	colors = colors_int(data_map->clr_rng[C]);
	rgba = 0;
	rgba += (unsigned int)colors[0] << 24;
	rgba += (unsigned int)colors[1] << 16;
	rgba += (unsigned int)colors[2] << 8;
	rgba += alpha;
	img_clr->rgba_ceiling = rgba;
	free(colors);
	colors = colors_int(data_map->clr_rng[F]);
	rgba = 0;
	rgba += (unsigned int)colors[0] << 24;
	rgba += (unsigned int)colors[1] << 16;
	rgba += (unsigned int)colors[2] << 8;
	rgba += alpha;
	img_clr->rgba_floor = rgba;
	free(colors);
}
