/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newget_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/23 16:26:09 by lguarda           #+#    #+#             */
/*   Updated: 2015/02/23 11:04:39 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			lin(const char *str)
{
	char	*ptr;

	ptr = (char*)str;
	while (*ptr != '\n' && *ptr)
		ptr++;
	return (ptr - str);
}

static char			*ft_realloc(char **line, char *ptr, int cur)
{
	char	*new;

	new = (char*)malloc(sizeof(char) * (ft_strlen(*line) + cur + 1));
	if (new)
	{
		ft_strcpy(new, *line);
		ft_strncat(new, ptr, cur);
		free(*line);
	}
	return (new);
}

static void			single(char *ptr, int *cur, char **line)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (*cur + 1));
	str[*cur] = '\0';
	ft_memcpy(str, ptr, *cur);
	*line = str;
}

static int			multi(char **ptr, t_read *rd, char **line, char *buff)
{
	int		i;

	i = 1;
	*line = ft_strnew(ft_strlen(*ptr) + 1);
	ft_strcpy(*line, *ptr);
	while (i)
	{
		i = read(rd->fd, buff, BUFF_SIZE);
		buff[i] = '\0';
		*ptr = buff;
		rd->cur = lin(*ptr);
		*line = ft_realloc(line, *ptr, rd->cur);
		if (rd->cur + (*ptr - buff) != BUFF_SIZE)
			break ;
	}
	return (i);
}

int					get_next_line(int const fd, char **line)
{
	static char		buff[BUFF_SIZE + 1];
	static char		*ptr;
	static int		i;
	static t_read	rd;

	rd.fd = fd;
	if (!rd.cur)
	{
		if ((i = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1 + (rd.cur = 0));
		buff[i] = '\0';
		ptr = buff;
	}
	else
		ptr = ptr + rd.cur;
	if (!(rd.cur = lin(ptr)) && i < BUFF_SIZE && (rd.cur + (ptr - buff) == i))
		return ((rd.cur = 0));
	if ((rd.cur + (ptr - buff)) == BUFF_SIZE)
		i = multi(&ptr, &rd, line, buff);
	else
		single(ptr, &rd.cur, line);
	rd.cur++;
	if (i < BUFF_SIZE && ptr - buff == i)
		return ((rd.cur = 0));
	return (1);
}
