/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfreixo- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/09/02 09:22:38 by mfreixo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	adds the string *add to *str, in position = pos
	output is substr(str, 0, pos) + add + &str[pos]
*/
static void	subs_str(char **str, char *add, int pos, int len)
{
	char	*last;
	char	*first;
	char	*join;

	ft_memmove(&(*str)[pos], &(*str)[pos + len + 1],
		ft_strlen(&(*str)[pos + len + 1]) + 1);
	if (!add)
		return ;
	last = ft_substr(*str, pos, ft_strlen(&(*str)[pos]));
	first = ft_substr(*str, 0, pos);
	join = ft_strjoin(first, add);
	free(*str);
	*str = ft_strjoin(join, last);
	free(join);
	free(last);
	free(first);
	free(add);
}

/*	receives the position in *str, after $ where the new variable starts
	expands it and alters *str, to change the variable name to its content
*/
int	expand_one(char **str, int pos, int len)
{
	char	*content;
	char	*name;
	int		new_pos;

	name = ft_substr(*str, pos, len);
	if (!ft_strncmp(name, "?", 2))
		content = ft_itoa((base()->errnumb));
	else
		content = ft_strdup(find_env(name));
	free(name);
	new_pos = ft_strlen(content);
	subs_str(str, content, pos -1, len);
	return (new_pos);
}

/*
	*str at position pos has a $
	this function searches for the end of argument's and
	expands it
*/
void	next_exp(char **str, int *pos)
{
	int	i;
	int	j;

	i = *pos;
	while ((*str)[i] && !ft_special_char((*str)[i]))
		i++;
	if ((*str)[i++] == '$')
	{
		j = i;
		while ((*str)[i] && !ft_special_char((*str)[i])
			&& !ft_isspace((*str)[i]))
			i++;
	}
	if ((*str)[i] == '?')
	{
		*pos += expand_one(str, j, 1);
	}
	else
		*pos += expand_one(str, j, i - j);
}

void	expand_aux(char **str, int *i, int *open_quotes)
{
	int		j;
	char	*str1;

	j = *i;
	str1 = *str;
	if (str1[j] == '\"')
		*open_quotes = (*open_quotes + 1) % 2;
	if (str1[j] == '\'' && *open_quotes == FALSE)
	{
		while (str1[++j] != '\'')
			;
		j++;
	}
	else if (str1[j] == '$')
	{
		if (!str1[j + 1] || (ft_special_char(str1[j + 1])
				&& str1[j + 1] != '?') || (ft_isspace(str1[j + 1])))
			j++;
		else
			next_exp(str, &j);
	}
	else
		j++;
	*i = j;
}

/*	changes the value of *str to its expanded version - when a valid $ is found
	we change $NAME for its content in env
*/
void	*expand(char *str)
{
	int	i;
	int	open_quotes;

	i = 0;
	open_quotes = FALSE;
	while (str[i])
	{
		if (!ft_strchr(&str[i], '$'))
			return ((void *)str);
		while (str[i] && str[i] != '$' && !ft_isquote(str[i]))
			i++;
		expand_aux(&str, &i, &open_quotes);
	}
	return ((void *)str);
}
