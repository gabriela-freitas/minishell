/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/11 09:28:36 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	adds the string *add to *str, in position = pos
	output is substr(str, 0, pos) + add + &str[pos]
*/
void add_str(char **str, char *add, int pos)
{
	char *aux;
	char *aux2;

	if (!add)
		return;
	aux = ft_substr(*str, pos, ft_strlen(&(*str)[pos]));
	ft_memmove(&(*str)[pos], add, ft_strlen(add) + 1);
	aux2 = malloc(sizeof(char) * (ft_strlen((*str)) + ft_strlen(aux) + 1));
	ft_memmove(aux2, (*str), ft_strlen((*str)) + 1);
	ft_memmove(aux2 + ft_strlen((*str)), aux, ft_strlen(aux) + 1);
	free(*str);
	*str = ft_strdup(aux2);
	free(aux);
	free(aux2);
}

int expand_one(char **str)
{
	int	i;
	char	*content;
	char	*aux;
	
	i = 0;
	if ((*str)[i] != '$')
		return (0);
	while ((*str)[i] && !ft_isspace((*str)[i]) && !ft_special_char((*str)[i]) && !ft_isquote((*str)[i]))
		i++;
	aux = ft_substr(*str, 1, i);
	printf("name = %s\n", aux);
	content = find_env(aux);
	printf("name = %s\n", content);
	return (ft_strlen(content));
		
}

void next_expand(char **str)
{
	int		i;
	int		j;
	char	*aux;
	char	*aux2;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = i;
		while (str[i] && !ft_isspace(str[i]) && !ft_special_char(str[i]) && !ft_isquote(str[i]))
			i++;
		if (str[i] == '$')
			printf("content length = %s\n", expand_one(&(&str[i])));
		else
			i++;
	}
}



void expand(char **str)
{
	char *aux = *str;
	// int	i = 0;
	// char *arg;

	next_exp(&aux);
	printf("\nSAI DO EXPAND:\n>>>>>>>>>>%s<<<<<<<<<<\n\n", aux);
}
