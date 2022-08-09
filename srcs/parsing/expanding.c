/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/09 01:33:21 by mfreixo-         ###   ########.fr       */
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

void expand_one(char **str)
{
	int i;
	int j;
	char *var;
	char *content;

	printf("to expand: >>>%s<<<\n", *str);
	i = 0;
	j = i;
	int k = 1;
	while ((*str)[i])
	{
		printf("Entrei aqui %d\n", k++);
		while ((*str)[i] && (*str)[i] != '$')
			i++;
		if (!(*str)[i])
			break;
		j = i;
		while ((*str)[++i] && !ft_isquote((*str)[i]) && (*str)[i] != '$' && !ft_special_char((*str)[i]) && !ft_isspace((*str)[i]))
			; // i++;
		var = ft_substr((*str), j + 1, i - j);
		printf("var = %s\n", var);
		content = ft_strdup(find_env(var));
		printf("content = %s\n", content);
		memmove(&(*str)[j], &(*str)[i], i - j + 1);
		printf("STRRRR= %s\n", *str);
		i = j + ft_strlen(content);
		add_str(str, content, j);
		printf("after expand = >>>%s<<<<\n", (*str));
	}
}

char *next_exp(char **str)
{
	int i;
	int j;
	char *aux;
	char *to_exp;

	i = 0;
	j = i;
	while ((*str)[i])
	{
		while ((*str)[i] && !ft_isquote((*str)[i]) && (*str)[i] != '$' && !ft_special_char((*str)[i]) && !ft_isspace((*str)[i]))
			i++;
		if (!(*str)[i])
			return (NULL);
		if ((*str)[i] == '$')
		{
			j = i++;
			while ((*str)[i] && !ft_isquote((*str)[i]) && (*str)[i] != '$' && !ft_special_char((*str)[i]) && !ft_isspace((*str)[i]))
				i++;
			to_exp = ft_substr((*str), j, i - j);
			aux = ft_strdup(to_exp);
			free(to_exp);
			memmove(&(*str)[j], &(*str)[i], i - j + 2);
			printf("after memmove = %s\n", (*str));
			expand_one(&aux);
			add_str(str, aux, j);
			printf("after to_exp = !!!>>%s<<!!!\n", (*str));
			i = j + ft_strlen(aux);
			printf("i = %d, j = %d\n", i, j);
			free(aux);
			// printf("\n\n%s\n\n", str);
			// printf("after expand1 = %s\n", to_exp);
			// free(to_exp);
		}
		else if (ft_isquote((*str)[i]))
		{
			aux = ft_strchr_valid(&(*str)[i + 1], (*str)[i]);
			if (!aux) // os quotes nao foram fechados
				return (NULL);
			if ((*str)[i] != '\'') // nao e suposto expandir o que esta dentro das aspas simples
			{
				to_exp = ft_substr((*str), i, (size_t)aux - (size_t)&(*str)[i] + 1);
				expand_one(&to_exp);
				memmove(&(*str)[j], &(*str)[i], ft_strlen(&(*str)[i]) + 1);
				add_str(str, to_exp, j);
				printf("\n\n%s\n\n", (*str));
				// printf("after expand2 = %s\n", to_exp);
				// free(to_exp);
			}
			i += (size_t)aux - (size_t)&(*str)[i] + 1;
			j = i;
		}
		else
			i++;
	}
	return (NULL);
}

void expand(char **str)
{
	char *aux = *str;
	// int	i = 0;
	// char *arg;

	next_exp(&aux);
	printf("\nSAI DO EXPAND:\n>>>>>>>>>>%s<<<<<<<<<<\n\n", aux);
}
