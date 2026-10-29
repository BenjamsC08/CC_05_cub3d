/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 06:58:54 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/15 12:40:53 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	good_file_ext(char *str, const char *ext)
{
	if (!ext)
		return (not_a_good_file(EXT));
	while (*str)
	{
		if (*str == '.' && !ft_strcmp(++str, ext))
			return (1);
		str++;
	}
	return (not_a_good_file(EXT));
}

int	convert_colors(char **strs, t_game *game, char c)
{
	int	i;
	int	tmp;
	int	color;

	i = 0;
	color = 0;
	while (i < 3)
	{
		tmp = ft_atoi(strs[i]);
		if (tmp < 0 || tmp > 255)
			return (0);
		color += tmp;
		if (i != 2)
			color <<= 8;
		i++;
	}
	if (c == 1)
		game->data_desc->floor_color = color;
	else
		game->data_desc->ceiling_color = color;
	return (1);
}

static int	check_file(t_game *game, int fd)
{
	char	*line;
	int		complete;

	line = get_next_line(fd);
	if (!line)
		return (not_a_good_file(OPEN));
	while (line)
	{
		if (ft_strncmp(line, "\n", 1))
		{
			if (!check_line(line, game))
				return (free(line), close_gnl(fd), FALSE);
		}
		free(line);
		complete = config_is_complete(game);
		if (complete)
		{
			if (!extract_map(game, fd))
				return (close_gnl(fd), FALSE);
			break ;
		}
		line = get_next_line(fd);
	}
	return (TRUE);
}

int	load_cub_file(t_game *game, char *str)
{
	int		fd;
	char	*buffer;

	buffer = NULL;
	fd = open(str, O_RDONLY);
	if (fd < 0 || read(fd, buffer, 0) < 0)
		return (not_a_good_file(OPEN));
	if (!check_file(game, fd))
		return (close(fd), 0);
	close (fd);
	game->data_desc->backup_map = ft_strsdup(game->data_desc->map);
	if (!game->data_desc->backup_map)
		return (0);
	return (1);
}

int	init_parser(t_game *game)
{
	game->data_desc = ft_gcalloc(game->gc_head, sizeof(t_data_desc));
	if (!game->data_desc)
		return (0);
	game->data_desc->player = FALSE;
	game->data_desc->floor_color = -1;
	game->data_desc->ceiling_color = -1;
	game->data_desc->door_anim_on = FALSE;
	game->data_desc->door_anim_frame = 0;
	game->data_desc->last_best_time = NULL;
	game->data_desc->prev_best_time = NULL;
	game->data_desc->score_history_path = NULL;
	game->data_desc->new_best_time = FALSE;
	game->data_desc->score_checked = FALSE;
	return (1);
}
