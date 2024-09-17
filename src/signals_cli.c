/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_cli.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:21:30 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/08/30 20:21:34 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// MARC START

#include "minishell.h"

void	handle_sigint_cli(int sig)
{
	g_signal = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_cli_signals(void)
{
	struct sigaction	sa_cli_sigint;
	struct sigaction	sa_cli_sigquit;

	sa_cli_sigint.sa_handler = &handle_sigint_cli;
	sa_cli_sigint.sa_flags = SA_RESTART;
	sigemptyset(&sa_cli_sigint.sa_mask);
	sigaction(SIGINT, &sa_cli_sigint, NULL);
	sa_cli_sigquit.sa_handler = SIG_IGN;
	sa_cli_sigquit.sa_flags = 0;
	sigemptyset(&sa_cli_sigquit.sa_mask);
	sigaction(SIGQUIT, &sa_cli_sigquit, NULL);
}

// MARC END
