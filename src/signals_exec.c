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
	printf("\n");
}

void	handle_sigquit_exec(int sig)
{
	g_signal = sig;
	printf("Quit\n");
}

void	setup_exec_signals(void)
{
	struct sigaction	sa_exec_sigint;
	struct sigaction	sa_exec_sigquit;

	sa_exec_sigint.sa_handler = &handle_sigint_exec;
	sa_exec_sigint.sa_flags = 0;
	sigemptyset(&sa_exec_sigint.sa_mask);
	sigaction(SIGINT, &sa_exec_sigint, NULL);
	sa_exec_sigquit.sa_handler = &handle_sigquit_exec;
	sa_exec_sigquit.sa_flags = 0;
	sigemptyset(&sa_exec_sigquit.sa_mask);
	sigaction(SIGQUIT, &sa_exec_sigquit, NULL);
}

// MARC END
