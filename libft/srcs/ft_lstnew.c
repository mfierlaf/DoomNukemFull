/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 13:21:21 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/29 15:58:12 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*new;

	if ((new = (t_list*)malloc(sizeof(t_list))) == NULL)
		return ((void*)0);
	if (content != NULL)
	{
		if ((new->content = (t_list*)malloc(sizeof(content) * content_size))
			== NULL)
		{
			return ((void*)0);
		}
		new->content = ft_memcpy(new->content, (void*)content, content_size);
		new->content_size = content_size;
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	new->next = NULL;
	return (new);
}
