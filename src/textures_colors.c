/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:52:06 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/21 16:28:03 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

void	init_img_clr(t_data_map *data_map)
{
	data_map->textures[NO] = NULL;
	data_map->textures[SO] = NULL;
	data_map->textures[EA] = NULL;
	data_map->textures[WE] = NULL;
	data_map->rgba_ceiling = 0;
	data_map->rgba_floor = 0;
	data_map->map = NULL;
	data_map->pth_img = NULL;
	data_map->clr_rng = NULL;
}

int	transform_png(t_data_map *data_map)
{
	//TO DO: Free memory of png when there are errors
	data_map->textures[NO] = mlx_load_png(data_map->pth_img[NO]);
	if (data_map->textures[NO] == NULL)
		return (printf("Error\nError with the load north textures\n"), 1);
	data_map->textures[SO] = mlx_load_png(data_map->pth_img[SO]);
	if (data_map->textures[SO] == NULL)
		return (printf("Error\nError with the load south textures\n"), 1);
	data_map->textures[WE] = mlx_load_png(data_map->pth_img[WE]);
	if (data_map->textures[WE] == NULL)
		return (printf("Error\nError with the load west textures\n"), 1);
	data_map->textures[EA] = mlx_load_png(data_map->pth_img[EA]);
	if (data_map->textures[EA] == NULL)
		return (printf("Error\nError with the load east textures\n"), 1);
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

void	get_rgba(int alpha, t_data_map *data_map)
{
	uint32_t	rgba;
	int			*colors;

	colors = colors_int(data_map->clr_rng[C]);
	rgba = 0;
	rgba += (unsigned int)colors[0] << 24;
	rgba += (unsigned int)colors[1] << 16;
	rgba += (unsigned int)colors[2] << 8;
	rgba += alpha;
	data_map->rgba_ceiling = rgba;
	free(colors);
	colors = colors_int(data_map->clr_rng[F]);
	rgba = 0;
	rgba += (unsigned int)colors[0] << 24;
	rgba += (unsigned int)colors[1] << 16;
	rgba += (unsigned int)colors[2] << 8;
	rgba += alpha;
	data_map->rgba_floor = rgba;
	free(colors);
}
