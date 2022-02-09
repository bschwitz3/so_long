/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:25:33 by bschwitz          #+#    #+#             */
/*   Updated: 2022/02/08 17:23:51 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_player_move(t_data *data, char position, int direction)
/* met la bonne orientation du joueur */
{
	if (position == 'y' && direction == UP)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_up,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}
	if (position == 'x' && direction == LEFT)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_left,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}
	if (position == 'y' && direction == DOWN)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_down,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}
	if (position == 'x' && direction == RIGHT)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img->player_right,
			(data->p_x * IMG_W), (data->p_y * IMG_H));
	}
}

static void	ft_collect(t_data *data, char pos, int dir)
/* collecte les binchs et les degage de la map */
{
	data->collected++;
	data->map->map[data->p_y][data->p_x] = '0';
	mlx_put_image_to_window(data->mlx, data->win, data->img->background,
		(data->p_x * IMG_W), (data->p_y * IMG_H));
	ft_player_move(data, pos, dir);
}

void	ft_move(t_data *data, char pos, int dir)
/* check si le move est ok et move si oui */
{
	mlx_put_image_to_window(data->mlx, data->win, data->img->background,
		(data->p_x * IMG_W), (data->p_y * IMG_H));
	if (pos == 'y' && data->map->map[data->p_y + 1 * dir][data->p_x] != '1'
		&& (data->map->map[data->p_y + 1 * dir][data->p_x] != 'E'
		|| data->collected == data->map->beer))
		data->p_y = data->p_y + 1 * dir;
	else if (pos == 'x' && data->map->map[data->p_y][data->p_x + 1 * dir] != '1'
		&& (data->map->map[data->p_y][data->p_x + 1 * dir] != 'E'
		|| data->collected == data->map->beer))
		data->p_x = data->p_x + 1 * dir;
	else if (pos == 'y' && data->map->map[data->p_y + 1 * dir][data->p_x] == 'E'
		&& data->collected != data->map->beer)
		printf("Collect all beers before leaving\n");
	else if (pos == 'x' && data->map->map[data->p_y][data->p_x + 1 * dir] == 'E'
		&& data->collected != data->map->beer)
		printf("Collect all beers before leaving\n");
	ft_player_move(data, pos, dir);
	if (data->map->map[data->p_y][data->p_x] == 'C')
		ft_collect(data, pos, dir);
	mlx_do_sync(data->mlx);
	printf("You moved %d times.\n", ++data->counter);
}
