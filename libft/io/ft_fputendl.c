/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputendl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/12 17:13:13 by bdurst            #+#    #+#             */
/*   Updated: 2014/12/12 18:02:24 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	ft_fputendl(char const *s, int fd)
{
	write (fd, s, ft_strlen(s));
	write (fd, "\n", 1);
}
