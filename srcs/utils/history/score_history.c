/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   score_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:19:25 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/15 09:07:59 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_score_file(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (TRUE);
	while (line)
	{
		if (is_time_format(line))
		{
			close_gnl(fd);
			game->data_desc->last_best_time = ft_gc_addnode(game->gc_head,
					ft_strndup(line, 5));
			if (!game->data_desc->last_best_time)
				return (free(line), FALSE);
			game->data_desc->prev_best_time = ft_gc_addnode(game->gc_head,
					ft_strndup(line, 5));
			break ;
		}
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	return (TRUE);
}

static char	*build_score_file(char *map_name)
{
	char	*potential_path;

	potential_path = NULL;
	if (!map_name || !*map_name)
		return (NULL);
	potential_path = ft_strdup(map_name);
	if (!potential_path)
		return (NULL);
	potential_path = ft_strfjoin(potential_path, ".score");
	if (!potential_path)
		return (NULL);
	return (potential_path);
}

int	load_score_history(t_game *game, char *map_name)
{
	int		history_read_fd;

	if (!map_name || !*map_name)
		return (FALSE);
	game->data_desc->score_history_path = ft_gc_addnode(game->gc_head,
			build_score_file(map_name));
	if (!game->data_desc->score_history_path)
		return (FALSE);
	history_read_fd = open(game->data_desc->score_history_path, O_RDONLY);
	if (history_read_fd > -1)
	{
		if (!read_score_file(game, history_read_fd))
			return (close(history_read_fd), FALSE);
		close(history_read_fd);
	}
	return (TRUE);
}

int	write_best_time_in_score_history(t_game *game, char *new)
{
	int		write_fd;
	char	*tmp;

	if (!new || !is_time_format(new) || !game->data_desc->score_history_path)
		return (FALSE);
	write_fd = open(game->data_desc->score_history_path,
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (write_fd < 0)
	{
		if (errno == EACCES)
			ft_dprintf(2, "Error\nPermission denied : could not write in %s\n",
				game->data_desc->score_history_path);
		return (FALSE);
	}
	ft_dprintf(write_fd, "%s\n", new);
	close(write_fd);
	tmp = ft_strdup(new);
	if (!tmp)
		return (FALSE);
	game->data_desc->last_best_time = ft_gc_addnode(game->gc_head, tmp);
	return (TRUE);
}

//  1 = new < last
// -1 = new > last
//  0 = error
int	handle_score_history(t_game *game)
{
	char	*time_str;
	t_uint	time;

	game->data_desc->new_best_time = FALSE;
	time = get_cd_time(game);
	if (MAX_TIME < TIME_MAX)
		time = MAX_TIME - time;
	else
		time = TIME_MAX - time;
	time_str = time_to_str(time);
	if (!time_str)
		return (FALSE);
	if (is_time_format(time_str) && is_better_time(game, time_str) == TRUE)
	{
		game->data_desc->new_best_time = TRUE;
		write_best_time_in_score_history(game, time_str);
	}
	if (time_str)
	{
		free(time_str);
		time_str = NULL;
	}
	return (TRUE);
}
