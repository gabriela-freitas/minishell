/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/10 23:04:06 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	finds the quotes given by c, (" or ') in str, starting in pos = i
	pos is given as pointer so its value is altered to be used in next_arg
*/
static int    check_quotes(char *str, char c, int *i)  //em caso de erro devolve -1
{
	char *aux;
	int j;

	j = *i;
	if (!str[j])
		return (-1);
	if (j > 0)
	{
		if (str[j - 1] && str[j - 1] == '\\')
		{
			ft_memmove(&str[j - 1], &str[j], ft_strlen(&str[j]) + 1);
			*i = j;
			return (0);
		}
	}
	if (str[j])
	{
		ft_memmove(&str[j], &str[j + 1], ft_strlen(&str[j + 1]) + 1);
		aux = ft_strchr_valid(&str[j], c);
		if (!aux)
			return (-1);
		*i += ft_strlen(&str[j]) - ft_strlen(aux);
		ft_memmove(aux, aux + 1, ft_strlen(aux + 1) + 1);
	}
	else
		return (-1);
	return (0);
}

/*returns the next arg, it can end in valid space, be delimited by ", '*/
static char    *next_arg(char *str)
{
	int i;
	char *aux;
	char c;

	i = 0;
	while (str[i])
	{
		while (str[i] && !ft_isspace(str[i]) && !ft_isquote(str[i]) && str[i] != '\\' && str[i] != '$')
			i++;
		if (!str[i] || ft_isspace(str[i]))
			return (ft_substr(str, 0, i));
		else if (str[i] == '\\' && str[i + 1] && ft_isspace(str[i + 1]))
			ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
		else if (ft_isquote(str[i]))
		{
			if (check_quotes(str, str[i], &i) == -1)
				return (0);
			if (!str[i])
				return (ft_substr(str, 0, i));
			continue;
		}
		i++;
	}
	return (NULL);
}

/*	returns an array of args, first is the command to be executed,
	then it's its arguments
	this is the last parsing, args are ready to be executed
*/
static char **split_command(char *str)
{
	int i;
	char    *aux;
	int     k;
	char    **split;

	k = 0;
	i = 0;
	// printf("%s\n", str);
	// cut_str(&str); //este expand nao esta a funcionar
	// printf("%s\n", str);
	// return(NULL);
	split = malloc(sizeof(char*) * 2);
	split[0] = '\0';
	while (str[i])
	{
		aux = next_arg(&str[i]);
		if (!aux)
		{
			free_split(split);
			split = NULL;
			break ;
		}
		i += ft_strlen(aux);
		add_split(&split, &k, aux);
		if (!str[i])
			break;
		i++;
	}
	return (split);
}

/*	given the list of commands (a command ends with pipe of end of input from terminal),
	splits it, into valid arguments and executes */
void	second_parse(void)
{
	t_list	*temp;
	int		i;

	i = -1;
	temp = base()->div_pipes;
	base()->pipe.num_cmds = ft_lstsize(temp);
	base()->pipe.cmds = malloc(sizeof(char **) * (base()->pipe.num_cmds + 1));
	while (temp)
	{
		base()->pipe.cmds[++i] = split_command((char *)temp->content);
		temp = temp->next;
		// execute(base()->pipe.cmds[i]);
	}
	base()->pipe.cmds[++i] = NULL;
	printf("HEY\n");
	pipex(); //adaptar o pipeex
	i = -1;
	while (base()->pipe.cmds[++i])
		free_split(base()->pipe.cmds[i]);
	free_split(base()->pipe.cmds[i]);
	free(base()->pipe.cmds);
	ft_lstclear(&(base()->div_pipes), free); //esta a dar double free aqui, nao sei bem pq
}
