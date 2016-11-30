/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 00:07:50 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/23 04:28:02 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*reallocf(void *p, size_t size)
{
	void *newp;

	malloc_debug(HEADER, "-- REALLOCF --", "");
	pthread_mutex_lock(&g_thread_safe.mutex_reallocf);
	newp = realloc(p, size);
	if (!newp)
		free(p);
	return (unlock_fct_with_return(newp, &g_thread_safe.mutex_reallocf));
}
