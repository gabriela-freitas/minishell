/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gafreita <gafreita@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 13:10:37 by gafreita          #+#    #+#             */
/*   Updated: 2022/10/31 16:18:52 by gafreita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	recursive_heredoc(t_pipex *command, char ***out_heredoc, int i);
static int	tempfile_heredoc(t_pipex *command, char **out_heredoc);
static int	open_infiles(t_pipex *cmd);
static int	open_infiles(t_pipex *cmd);
//open files
//redirect outputs
//make heredoc

/* allocs memory to an array of strings that will store the HEREDOC */
static void	recursive_heredoc(t_pipex *command, char ***out_heredoc, int i)
{
	char	*line;

	line = readline("heredoc> ");
	if (!ft_strncmp(line, (char *)command->heredoc, ft_strlen(line) + 1))
	{
		*out_heredoc = malloc(sizeof(char *) * (i + 1));
		if (!(*out_heredoc))
		{
			parse_error_message("Malloc", "error", errno);
			return ;
		}
		free(line);
		line = NULL;
	}
	else
		recursive_heredoc(command, out_heredoc, i + 1);
	(*out_heredoc)[i] = line;
}

/* writes the content of heredoc in a pipe and changes the content of heredoc
var to the pipe_fd instead of the delimiter string
*/
static int	tempfile_heredoc(t_pipex *command, char **out_heredoc)
{
	int	i;

	if (!out_heredoc)
		return (0);
	command->fd[IN] = open(TEMP_FILE, O_WRONLY | O_CREAT | O_ASYNC, 0644);
	if (command->fd[IN] < 0)
	{
		parse_error_message(TEMP_FILE, "Could not open file", 1);
		return (0);
	}
	i = -1;
	while (out_heredoc[++i])
		ft_putendl_fd(out_heredoc[i], command->fd[IN]);
	close(command->fd[IN]);
	command->fd[IN] = open(TEMP_FILE, O_RDONLY | O_ASYNC);
	if (command->fd[IN] < 0)
	{
		parse_error_message(TEMP_FILE, "Could not open file", 1);
		return (0);
	}
	free_split(out_heredoc);
	return (1);
}

/* Define where the command will read its output:
	If < , its a file
	If << , its the heredoc (READ end of the pipe)
	else , the standard input */
static int	open_infiles(t_pipex *cmd)
{
	char	**out_heredoc;

	out_heredoc = NULL;
	if (cmd->heredoc)
	{
		recursive_heredoc(cmd, &out_heredoc, 0);
		if (!tempfile_heredoc(cmd, out_heredoc))
			return (FALSE);
	}
	else
		cmd->fd[IN] = STD;
	if (*cmd->input)
	{
		if (!access(TEMP_FILE, F_OK))
			unlink(TEMP_FILE);
		cmd->fd[IN] = open(cmd->input[0], cmd->in_mode, 0644);
		if (cmd->fd[IN] < 0)
		{
			parse_error_message(cmd->input[0], \
			": No such file or directory", 1);
			return (FALSE);
		}
	}
	return (TRUE);
}

/* Define where the command will write its output:
	If specified, open outfiles, and the last one will be the new output fd
	Otherwise, it will be the standard output*/
static int	open_outfiles(t_pipex *cmd)
{
	int		i;

	if (cmd->output && *cmd->output)
	{
		i = -1;
		while (cmd->output[++i])
		{
			cmd->fd[OUT] = open(cmd->output[i], cmd->out_mode, 0644);
			if (cmd->fd[OUT] < 0)
			{
				parse_error_message(cmd->output[i], "Could not open file", 1);
				return (FALSE);
			}
		}
	}
	else
		cmd->fd[OUT] = STD;
	return (TRUE);
}

/// @brief
/// @param command
/// @return
int	open_files(t_pipex *cmd)
{
	if (cmd->redir)
	{
		if (open_infiles(cmd))
		{
			if (!open_outfiles(cmd))
				return (FALSE);
		}
		else
			return (FALSE);
	}
	else
	{
		cmd->fd[IN] = STD;
		cmd->fd[OUT] = STD;
	}
	return (TRUE);
}
