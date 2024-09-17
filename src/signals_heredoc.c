/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrodenbu <mrodenbu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 20:21:18 by mrodenbu          #+#    #+#             */
/*   Updated: 2024/08/30 20:21:19 by mrodenbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// MARC START

#include "minishell.h"

void	handle_sigint_hd_child(int sig)
{
	g_signal = sig;
	exit (1);
}

void	handle_sigint_hd_main(int sig)
{
	g_signal = sig;
	printf("^C\n");
}

void	setup_heredoc_signals_main(void)
{
	struct sigaction	sa_hd_sigint_main;

	sa_hd_sigint_main.sa_handler = &handle_sigint_hd_main;
	sa_hd_sigint_main.sa_flags = 0;
	sigemptyset(&sa_hd_sigint_main.sa_mask);
	sigaction(SIGINT, &sa_hd_sigint_main, NULL);
}

void	setup_heredoc_signals_child(void)
{
	struct sigaction	sa_hd_sigint_child;

	sa_hd_sigint_child.sa_handler = &handle_sigint_hd_child;
	sa_hd_sigint_child.sa_flags = SA_RESTART;
	sigemptyset(&sa_hd_sigint_child.sa_mask);
	sigaction(SIGINT, &sa_hd_sigint_child, NULL);
}

// MARC END
