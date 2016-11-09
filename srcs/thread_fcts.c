/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_fcts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdurst <bdurst@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 01:14:17 by bdurst            #+#    #+#             */
/*   Updated: 2016/11/09 02:26:35 by bdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*unlock_fct_with_return(void *ptr, pthread_mutex_t *mutex)
{
	pthread_mutex_unlock(mutex);
	return (ptr);
}
