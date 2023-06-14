/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaimad <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 20:33:28 by ohaimad           #+#    #+#             */
/*   Updated: 2023/06/14 18:57:15 by ohaimad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**convert_env(t_list_env *env, char **envp)
{
	int			i;
	t_list_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->c)
			i++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (env)
	{
		if (env->c)
		{
			envp[i] = ft_strjoin(env->variable, "=");
			if (env->content)
				envp[i] = ft_strjoin(envp[i], env->content);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*join_args(t_cmd_lines *cmd)
{
	char	*arg;

	arg = ft_strjoin("/", cmd->cmd_line[0]);
	return (arg);
}

char	*path_split(t_cmd_lines *cmd)
{
	char	**split;
	char	*path;
	char	*res;
	char	*str;
	int		i;

	i = 0;
	if (access(cmd->cmd_line[0], F_OK) == 0)
		return (cmd->cmd_line[0]);
	path = print_env(&cmd->infos->env, "PATH");
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->cmd_line[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		return (NULL);
	}
	split = ft_split(path, ':');
	str = join_args(cmd);
	while (split[i])
	{
		res = ft_strjoin(split[i], str);
		if (access(res, F_OK) == 0)
			break ;
		free(res);
		i++;
	}
	if (access(res, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(cmd->cmd_line[0], 2);
		ft_putstr_fd("\n", 2);
		res = NULL;
	}
	free(str);
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (res);
}

void	ft_execution(t_cmd_lines *lines, int fd[2])
{
	char	*path;
	pid_t	pid;
	int		status;
	int		old;
	char	**envp;

	old = fd[0];
	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	else if (pid == 0)
	{
		if (old != -1)
		{
			dup2(old, 0);
			close(old);
		}
		if (lines->next)
			dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		if (builts_in(lines, &lines->infos->env))
			exit(0);
		envp = convert_env(lines->infos->env, envp);
		path = path_split(lines);
		if (execve(path, lines->cmd_line, envp) < 0)
			exit(0);
	}
	else
	{
		waitpid(pid, &status, WNOHANG);
		close(old);
		close(fd[1]);
	}
	return ;
}
