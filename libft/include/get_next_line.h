/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 20:03:39 by bdurst            #+#    #+#             */
/*   Updated: 2015/01/31 16:13:08 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 30000

int				get_next_line(int const fd, char **line);

typedef struct	s_tools
{
	int			fd;
	char		*str;
}				t_tools;

#endif
