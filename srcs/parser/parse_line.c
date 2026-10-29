/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 07:01:42 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/07 13:30:21 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	try_to_open_image(t_game *game, char *path_img)
{
	int		img_w;
	int		img_h;
	void	*ptr;

	img_w = W_WIDTH;
	img_h = W_HEIGHT;
	ptr = mlx_xpm_file_to_image(game->mlx, path_img, &img_w, &img_h);
	if (!ptr)
		return (0);
	mlx_destroy_image(game->mlx, ptr);
	return (1);
}

static int	texture_id_from_prefix(const char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (TEX_NORTH);
	if (!ft_strncmp(line, "SO ", 3))
		return (TEX_SOUTH);
	if (!ft_strncmp(line, "WE ", 3))
		return (TEX_WEST);
	if (!ft_strncmp(line, "EA ", 3))
		return (TEX_EAST);
	if (!ft_strncmp(line, "DO ", 3))
		return (TEX_DOOR_CLOSED);
	return (-1);
}

static int	parse_and_store_texture_path(t_game *game, char *line, int tex_id)
{
	char	*trimmed;
	char	*path;

	trimmed = ft_gc_addnode(game->gc_head, ft_remove_charset(line, "\n"));
	if (!trimmed)
		return (0);
	path = trimmed + 3;
	while (*path && ft_iswhitespace(*path))
		path++;
	if (!*path)
		return (0);
	if (game->assets.path[tex_id])
		return (0);
	if (!try_to_open_image(game, path))
		return (0);
	game->assets.path[tex_id] = ft_gc_addnode(game->gc_head, ft_strdup(path));
	if (!game->assets.path[tex_id])
		return (0);
	return (1);
}

static int	extract_color(t_game *game, char *line)
{
	char	**strs;
	char	c;

	if (!ft_strncmp(line, "F ", 2))
		c = 1;
	else
		c = 2;
	line += 2;
	if (!line)
		return (0);
	while (*line && ft_iswhitespace(*line))
		line++;
	if (!line)
		return (0);
	strs = ft_split(line, ',');
	if (!strs)
		return (0);
	if (ft_strslen(strs) != 3)
		return (free_strs(strs), 0);
	if (!convert_colors(strs, game, c))
		return (free_strs(strs), 0);
	return (free_strs(strs), 1);
}

int	check_line(char *line, t_game *game)
{
	int		tex_id;

	tex_id = texture_id_from_prefix(line);
	if (tex_id >= 0)
	{
		if (!parse_and_store_texture_path(game, line, tex_id))
			return (not_a_good_file(BAD_IMAGE));
		return (1);
	}
	if (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2))
	{
		if (!extract_color(game, line))
			return (not_a_good_file(BAD_COLOR));
		return (1);
	}
	return (not_a_good_file(OPEN));
}
