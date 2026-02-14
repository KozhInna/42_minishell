/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikozhina <ikozhina@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 01:08:08 by mzhivoto          #+#    #+#             */
/*   Updated: 2026/02/14 14:56:04 by ikozhina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_prompt(t_cmd_input *cmd, t_data *data)
{
	cmd->input = readline("minishell$ ");
	if (g_sig_received)
	{
		g_sig_received = 0;
		data->status = ERR_INTERUPTED_SIGINT;
		if (cmd->input)
		{
			free(cmd->input);
			cmd->input = NULL;
		}
		return (-2);
	}
	if (!cmd->input)
	{
		printf("exit\n");
		return (-1);
	}
	if (cmd->input[0] == '\0')
	{
		data->status = 0;
		free(cmd->input);
		cmd->input = NULL;
		return (0);
	}
	return (1);
}

void	shell_loop(t_data *data, t_command **commands)
{
	t_cmd_input	cmd_input;
	int			prompt_res;

	ft_memset(&cmd_input, 0, sizeof(t_cmd_input));
	while (!data->exit_f)
	{
		g_sig_received = 0;
		prompt_res = read_prompt(&cmd_input, data);
		if (prompt_res == -1)
			break ;
		if (prompt_res == -2 || prompt_res == 0)
			continue ;
		if (cmd_input.input && cmd_input.input[0] != '\0')
			add_history(cmd_input.input);
		*commands = parse_input(*commands, data, cmd_input.input);
		free(cmd_input.input);
		if (!(*commands))
			continue ;
		execute(data, *commands);
		free_command_list(*commands);
	}
}

int	main(int ac, char **av, char **env)
{
	t_data		data;
	t_command	*commands;

	commands = NULL;
	(void)av;
	if (ac < 1)
		return (1);
	if (init_data(&data, env) != 0)
	{
		cleanup_data(&data);
		return (1);
	}
	set_prompt_signals();
    rl_event_hook = rl_signal_handler;
	shell_loop(&data, &commands);
	cleanup_data(&data);
	return (data.status);
}
