/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 00:07:50 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/09 01:39:43 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*reallocf(void *p, size_t size)
{
	void *newp;

	malloc_debug(HEADER, "-- REALLOCF --", "");
	newp = realloc(p, size);
	free(p);
	return (newp);
}
