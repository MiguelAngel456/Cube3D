/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juestrel <juestrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:46:10 by mfuente-          #+#    #+#             */
/*   Updated: 2024/10/21 16:27:19 by juestrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3D.h"

/*static void skybox(t_tests *main, t_img_clr *img_clr)
{
    mlx_image_t *skybox;

    skybox = mlx_new_image(main->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(main->mlx, skybox, 0, 0);
    for (unsigned int y = 0; y < HEIGHT; y++)
    {
        for (unsigned int x = 0; x < WIDTH; x++)
        {
            if (y < HEIGHT/2)
                mlx_put_pixel(skybox, x, y, img_clr->rgba_floor);
            else
                mlx_put_pixel(skybox, x, y, img_clr->rgba_ceiling);
        }
    }
}*/

/*static void hooks(mlx_key_data_t keydata, void *param)
{
    t_tests *test = (t_tests *)param;

    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
        mlx_close_window(test->mlx);
}*/

int	main(void)
{
	t_data_map	data_map;	

	init_img_clr(&data_map);
	data_map.pth_img = malloc(sizeof(char *) * 5);
	if (data_map.pth_img == NULL)
	{
		printf("Error al asignar memoria para pth_img\n");
		return (1);
	}
	data_map.clr_rng = malloc(sizeof(char *) * 3);
	if (data_map.clr_rng == NULL)
	{
		printf("Error al asignar memoria para clr_rng\n");
		return (1);
	}
	init_str(&data_map);
	data_map.map = NULL;
	if (init_str_map("./prueba.cub", &data_map) == 1)
	{
		free_matrix(data_map.pth_img);
		free_matrix(data_map.clr_rng);
		exit(EXIT_FAILURE);		
	}
	// -------------PRUEBA-------------
	//printf("%d\n", wall_checker(&data_map));
	if (check_basic_map("./prueba.cub") == 1)
	{
		free_matrix(data_map.pth_img);
		free_matrix(data_map.clr_rng);
		free_matrix(data_map.map);
		exit(EXIT_FAILURE);		
	}
	if (map_exist(&data_map) == 1)
	{
		free_matrix(data_map.pth_img);
		free_matrix(data_map.clr_rng);
		free_matrix(data_map.map);
		exit(EXIT_FAILURE);		
	}
	if ( playable_checker(&data_map) == 1 || check_rgb_num(&data_map) || chr_checker(&data_map) == 1 || check_line_empty(&data_map) == 1 || wall_checker(&data_map) == 1 )
	{
		free_matrix(data_map.pth_img);
		free_matrix(data_map.clr_rng);
		free_matrix(data_map.map);
		exit(EXIT_FAILURE);		
	}
	if (transform_png(&data_map) == 1)
    {
        free_matrix(data_map.pth_img);
		free_matrix(data_map.clr_rng);
		free_matrix(data_map.map);
		exit(EXIT_FAILURE);		
    }
//	for (int i = 0; i < 4; i++)
//	{
//		for (int j = 0; j < (int)ft_strlen(data_map.pth_img[i]); j++)
//		{
//			printf("%c", data_map.pth_img[i][j]);
//		}
//		printf("\n");
//	}
	get_rgba(255, &data_map);

    // Inicializar mlx
    /*mlx = mlx_init(WIDTH, HEIGHT, "so_long", false);
    if (mlx == NULL) {
        printf("Error initializing mlx\n");
        return (1);
    }
    // Inicializar estructura t_tests
    main.mlx = mlx;
    main.img = NULL;
	skybox(&main, &img_clr);
    mlx_key_hook(mlx, hooks, &main);
    mlx_loop(mlx);
    mlx_terminate(mlx);*/
	// -------------LIBERAR MEMORIA-------------
	if (data_map.pth_img != NULL) {
		free_matrix(data_map.pth_img);
	}
	if (data_map.clr_rng != NULL) {
		free_matrix(data_map.clr_rng);
	}
	if (data_map.map != NULL) {
		free_matrix(data_map.map); 
	}
	return (0);
}