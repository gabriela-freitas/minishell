/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/08 18:39:15 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	adds the string *add to *str, in position = pos
	output is substr(str, 0, pos) + add + &str[pos]
*/
void	add_str(char **str, char *add, int pos)
{
	char	*aux;
	char	*aux2;

	if (!add)
		return ;
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

void expand_str(char *str) //Marta norminette
{
	int i;
	int j;
	char	*aux;
	char	*content;

	i = -1;
	// printf("\nstr para expandir = %s\n", str);
	while (str[++i])
	{
		if (str[i] == '$')
		{
			j = i;
			while (str[i + 1] && !ft_isspace(str[++i]) && !ft_isquote(str[i]) && !ft_special_char(str[i]))
				;
			if (str[i])
			{
				aux = ft_substr(str, j + 1, i - j);
				// printf("VAR= %sKK\n", aux);
				content = ft_strdup(find_env(aux));
				// printf("CONTENT= %s\n", content);
				if (content)
					ft_memmove(&str[j], &str[i + 1], ft_strlen(&str[i]) + 1);
				// printf("CONTENT= %s\n", str);
				add_str(&str, content, j);
				// printf("expanded str = %s\n", str);
				i += ft_strlen(content) - 1;
			}
			else
			{
				i++;
				aux = ft_substr(str, j + 1, i - j);
				content = ft_strdup(find_env(aux));
				if (content)
					ft_memmove(&str[j], &str[i], ft_strlen(&str[i]) + 1);
				add_str(&str, content, j);
				printf("expanded str = %s\n", str);
				break ;
			}
		}
	}
}

void cut_str(char **str) //Marta norminette
{
	int i;
	int j;
	char *aux;

	i = -1;
	j = 0;

	while ((*str)[i + 1])
	{
		while ((*str)[i + 1] && !ft_isspace((*str)[++i]) && !ft_isquote((*str)[i]) && !ft_special_char((*str)[i]))
			;
		if (ft_isquote((*str)[i]))
		{
			j = i;
			i = ft_strlen((*str)) - ft_strlen(ft_strchr_valid(&((*str)[i + 1]), (*str)[i]));
			if ((*str)[i] == '\'')
			{
				i++;	
				continue ;
			}
			else
			{
				aux = ft_substr(*str, j, i - j);
				// printf("substr = %s\n", aux);
				expand_str(aux);
			}
			if (!(*str)[i])
				break ;
		}
		else
		{
			aux = ft_substr(*str, j, i - j + 1);
			printf("aux = %s\n", aux);
			// return ;
			expand_str(aux);
			i++;
		}
	}
}
