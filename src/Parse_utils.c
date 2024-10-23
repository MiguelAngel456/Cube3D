/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfuente- <mfuente-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:34:15 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/23 18:24:14 by mfuente-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
		i++;
	return (i);
}

void	init_str(t_data_map *data_map)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		data_map->pth_img[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 3)
	{
		data_map->clr_rng[i] = NULL;
		i++;
	}
}

int	check_basic_map(char *map)
{
	int	fd;
	int	i;

	i = ft_strlen(map);
	while (i > 0)
	{
		if (map[i] == '.')
			break ;
		i--;
	}
	if (ft_strncmp(map + i, ".cub", ft_strlen(map)) != 0)
		return (printf("Error\nthe extension of the map is wrong\n"), 1);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (printf("Error\nthe archive dont  exist\n"), 1);
	close(fd);
	return (0);
}

int	get_line(int fd, int cont[3], int count_line, t_data_map *data_map)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		count_line = aux(line, cont, data_map, count_line);
		free(line);
		line = get_next_line(fd);
	}
	return (count_line);
}
