/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfierlaf <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 15:03:49 by mfierlaf          #+#    #+#             */
/*   Updated: 2018/10/26 14:53:58 by mfierlaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/libft.h"

static int			taille(char const *s, char c)
{
	int k;
	int l;

	k = 0;
	l = 0;
	if (s[0] != c)
		k++;
	while (s[l] != '\0')
	{
		if (s[l] == c && s[l + 1] != c && s[l + 1] != '\0')
			k++;
		l++;
	}
	return (k);
}

static	int			longeur(char const *s, char c, int i)
{
	int l;

	l = 0;
	while (s[i] != c && s[i] != '\0')
	{
		l++;
		i++;
	}
	return (l);
}

static	void		ft_free(char **final, int cpt)
{
	while (cpt >= 0)
	{
		free(final[cpt]);
		final[cpt] = NULL;
		cpt--;
	}
	free(final);
	final = NULL;
}

static	char		**allo(char const *s, char c)
{
	int		k;
	int		l;
	char	**final;
	int		i;
	int		cpt;

	cpt = -1;
	i = 0;
	k = taille(s, c);
	if ((final = ((char**)malloc(sizeof(char*) * (k + 1)))) == NULL)
		return ((void*)0);
	while (s[i] != '\0' && cpt++ <= k)
	{
		while (s[i] == c)
			i++;
		l = longeur(s, c, i);
		if ((final[cpt] = ((char*)malloc(sizeof(char) * (l + 1)))) == NULL)
		{
			ft_free(final, cpt);
			return ((void*)0);
		}
		i += l - 1;
		i++;
	}
	return (final);
}

char				**ft_strsplit(char const *s, char c)
{
	char	**final;
	int		i;
	int		j;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	final = allo(s, c);
	if (final == NULL)
		return (NULL);
	while (*s)
	{
		j = 0;
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		while (*s != c && *s != '\0')
			final[i][j++] = *s++;
		final[i][j] = '\0';
		i++;
	}
	final[i] = NULL;
	return (final);
}
