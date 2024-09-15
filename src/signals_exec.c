/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:21:42 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/08/30 20:21:44 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// MARC START

#include "minishell.h"

void	handle_sigint_exec(int sig)
{
	g_signal = sig;
	//printf("setting execution signals\n");
	printf("\n");
	/* rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay(); */
	// should not exit the shell
}

void	handle_sigquit_exec(int sig)
{
	g_signal = sig;
	// do we really need to create a core dump ???
	printf("Quit (core dumped)\n");
	// should not exit the shell
}

void	setup_exec_signals(void)
{
	struct sigaction sa_exec_sigint;
	sa_exec_sigint.sa_handler = &handle_sigint_exec;
	sa_exec_sigint.sa_flags = 0;
	sigemptyset(&sa_exec_sigint.sa_mask);
	sigaction(SIGINT, &sa_exec_sigint, NULL);
	struct sigaction sa_exec_sigquit;
	sa_exec_sigquit.sa_handler = &handle_sigquit_exec;
	sa_exec_sigquit.sa_flags = 0;
	sigemptyset(&sa_exec_sigquit.sa_mask);
	sigaction(SIGQUIT, &sa_exec_sigquit, NULL);
}

// MARC END
