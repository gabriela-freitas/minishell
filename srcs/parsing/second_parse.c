/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:05:51 by gafreita          #+#    #+#             */
/*   Updated: 2022/08/04 22:00:51 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//expand variables from env

char	*find_env(char	*name)
{
	t_env	*aux;

	aux = base()->env_split;
	while (aux->next)
	{
		if (!ft_strncmp(name, aux->name, ft_strlen(name)))
			return (aux->content);
		aux = aux->next;
	}
	return (NULL);
}

char	**split_command(char	*cmd)
{
	char	*sub_str;
	char	*begin;
	char	**cmd_split;
	int		i;

	begin = cmd;
	i = 1;
	while (*cmd)
	{
		if (*cmd == '\"' || *cmd == '\'')
		{
			begin = ft_strchr((cmd + 1), *cmd);
			sub_str = ft_substr(cmd, 0, (size_t)begin - (size_t)cmd);
			begin++;
			cmd += (size_t)begin - (size_t)cmd;
		}
		else if (*cmd == ' ')
		{
			sub_str = ft_substr(cmd, 0, (size_t)begin - (size_t)cmd);
			begin = cmd + 1;
		}
		cmd_split[i++] = sub_str;
		cmd_split = ft_my_realloc(cmd_split, sizeof(char **) * (i + 1));
		cmd_split[i] = '\0';
		cmd++;
	}
	cmd_split[i] = '\0';
	return (cmd_split);
}

void	second_parse(void)
{
	t_list	*temp;
	char	**split;

	temp = base()->cmds;
	while (temp)
	{
		split = split_command((char *)temp->content);
		while (split)
		{
			printf(">>%s\n", *split);
			split++;
		}
		temp = temp->next;
	}
}
