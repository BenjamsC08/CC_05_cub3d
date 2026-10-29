/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 07:00:16 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/07 15:34:10 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	config_is_complete(t_game *game)
{
	if (!game->assets.path[TEX_NORTH])
		return (FALSE);
	if (!game->assets.path[TEX_SOUTH])
		return (FALSE);
	if (!game->assets.path[TEX_WEST])
		return (FALSE);
	if (!game->assets.path[TEX_EAST])
		return (FALSE);
	if (game->data_desc->floor_color == -1)
		return (FALSE);
	if (game->data_desc->ceiling_color == -1)
		return (FALSE);
	return (TRUE);
}

int	not_a_good_file(int k)
{
	ft_dprintf(2, "Error\n");
	if (k == 0)
		ft_dprintf(2, "Incorrect number of arguments\n");
	if (k == EXT)
		ft_dprintf(2, "Bad extension file\n");
	if (k == OPEN)
		ft_dprintf(2, "Cannot open/read descriptor\n");
	if (k == BAD_COLOR)
		ft_dprintf(2, "Bad color in descriptor 'RRR,GGG,BBB' in decimal\n");
	if (k == BAD_IMAGE)
		ft_dprintf(2, "Cannot open image path in descriptor.\n");
	if (k == LINE)
		ft_dprintf(2, "Something wrong with your descriptor before the map.\n");
	if (k == MAP)
		ft_dprintf(2, "Need to put a position for the player\n");
	return (0);
}

int	error_map(char **map, int j, int i)
{
	ft_dprintf(2, "Error\n");
	ft_dprintf(2, "Something wrong in the map check `%c' in pos x:%d, y:%d\n",
		map[j][i], i, j);
	free_strs(map);
	return (0);
}
