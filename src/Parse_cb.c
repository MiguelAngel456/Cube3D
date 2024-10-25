/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_cb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:42:24 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/25 17:22:05 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

static void	save_map(char *path, int j, int count_line, t_data_map *data_map)
{
	int		fd;
	int		i;
	int		x;
	char	*line;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	x = 0;
	while ((line))
	{
		if (i >= (j - count_line))
		{
			data_map->map[x] = ft_strdup(line);
			x++;
		}
		i++;
		free(line);
		line = get_next_line(fd);
	}
	data_map->map[x] = NULL;
	free(line);
	close(fd);
}

static void	save_data(char *line, int *i, char **pth, int pos)
{
	char	**aux;
	char	*punt_n;
	int		pos_n;

	aux = ft_split(line, ' ');
	if (ft_strncmp(aux[0], "NO", 2) == 0 || ft_strncmp(aux[0], "SO", 2) == 0
		|| ft_strncmp(aux[0], "WE", 2) == 0 || ft_strncmp(aux[0], "EA", 2) == 0)
	{
		punt_n = ft_strchr(aux[1], '\n');
		pos_n = punt_n - aux[1];
		aux[1][pos_n] = '\0';
	}
	pth[pos] = ft_strdup(aux[1]);
	free_matrix(aux);
	(*i)++;
}

int	aux(char *line, int cont[3], t_data_map *data_map, int count_line)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && cont[0] <= 4)
		save_data(line, &cont[0], data_map->pth_img, NO);
	else if (ft_strncmp(line, "SO ", 3) == 0 && cont[0] <= 4)
		save_data(line, &cont[0], data_map->pth_img, SO);
	else if (ft_strncmp(line, "WE ", 3) == 0 && cont[0] <= 4)
		save_data(line, &cont[0], data_map->pth_img, WE);
	else if (ft_strncmp(line, "EA ", 3) == 0 && cont[0] <= 4)
		save_data(line, &cont[0], data_map->pth_img, EA);
	else if ((ft_strncmp(line, "F ", 2) == 0) && cont[1] <= 2)
		save_data(line, &cont[1], data_map->clr_rng, F);
	else if ((ft_strncmp(line, "C ", 2) == 0) && cont[1] <= 2)
		save_data(line, &cont[1], data_map->clr_rng, C);
	else if (cont[0] == 4 && cont[1] == 2 && line[0] != '\n')
		count_line++;
	cont[2]++;
	return (count_line);
}

static int	check_order(t_data_map *data_map)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data_map->pth_img[i] == NULL)
			return (1);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		if (data_map->clr_rng[i] == NULL)
			return (1);
		i++;
	}
	return (0);
}

int	init_str_map(char *path, t_data_map *data_map)
{
	int		fd;
	int		cont[3];
	int		count_line;

	cont[0] = 0;
	cont[1] = 0;
	cont[2] = 0;
	fd = open(path, O_RDONLY);
	count_line = 0;
	count_line = get_line(fd, cont, count_line, data_map);
	close(fd);
	if (check_order(data_map) == 1)
		return (printf("Error\nThe order or existence of map elements\n"), 1);
	data_map->map = malloc(sizeof(char *) * (count_line + 1));
	if (data_map->map == NULL)
	{
		free_matrix_size(data_map->pth_img, 4);
		free_matrix_size(data_map->clr_rng, 2);
		return (printf("Error\nError al asignar memoria para map\n"), 1);
	}
	save_map(path, cont[2], count_line, data_map);
	return (0);
}
