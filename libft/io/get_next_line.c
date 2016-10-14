/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 13:23:10 by bdurst            #+#    #+#             */
/*   Updated: 2015/01/10 21:18:20 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include "string.h"
#include "list.h"
#include "get_next_line.h"

static char		*gnl_get_line(char *str, char **line, char *buff)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] != '\n')
		i++;
	*line = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str && str[i] && str[i] != '\n')
	{
		(*line)[i] = str[i];
		i++;
	}
	(*line)[i] = '\0';
	if (str[i] == '\n')
		i++;
	free(buff);
	return (&str[i]);
}

static t_list	*gnl_init_list(int fd)
{
	t_tools	*tools;

	if (!(tools = (t_tools *)malloc(sizeof(t_tools))))
		return (NULL);
	tools->fd = fd;
	tools->str = NULL;
	return (ft_create_node(tools));
}

static t_tools	*gnl_check_fd(int fd, t_list **list, char **buff)
{
	t_tools	*tools;
	t_list	*tmp;

	tmp = *list;
	if (!(*buff = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (NULL);
	while (tmp)
	{
		tools = (t_tools *)tmp->data;
		if (tools->fd == fd)
			return (tools);
		tmp = tmp->next;
	}
	if (!(tools = (t_tools *)malloc(sizeof(t_tools))))
		return (NULL);
	tools->fd = fd;
	tools->str = NULL;
	ft_node_push_back(list, tools);
	return (tools);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*list = NULL;
	t_tools			*tools;
	char			*buff;
	int				ret;

	if (fd < 0 || !line)
		return (-1);
	if (!list)
		list = gnl_init_list(fd);
	if (BUFF_SIZE < 1 || !(tools = gnl_check_fd(fd, &list, &buff)))
		return (-1);
	ret = BUFF_SIZE;
	while (!(ft_strchr(tools->str, '\n')) && ret == BUFF_SIZE)
	{
		if ((ret = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		buff[ret] = '\0';
		tools->str = ft_strjoin(tools->str, buff);
	}
	tools->str = gnl_get_line(tools->str, line, buff);
	if (!ret && !*(tools->str) && !**line)
		return (0);
	return (1);
}
