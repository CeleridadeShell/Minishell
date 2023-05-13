/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccamargo <ccamargo@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:21:13 by ccamargo          #+#    #+#             */
/*   Updated: 2023/05/13 16:22:33 by ccamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	fix_sigint_multiple_pipes(int sig)
{
	(void)sig;
	printf("\n");
}

/**
*@brief Handles the main signals for the minishell (first one tells that the
*signal is ignored, the second one changes the signal behavior)
*@signal SIGINT (ctrl + c) - close the program
*@signal SIGQUIT (crtl + \) - quit the program/SIG_IGN - tells thesignal is to
*be ignored
*@param none
*@return none.
*/
void	fix_sigint_exec(void)
{
	struct sigaction	sig_int;

	sig_int.sa_handler = &fix_sigint_multiple_pipes;
	sig_int.sa_flags = SA_RESTART;
	sigemptyset(&sig_int.sa_mask);
	sigaction(SIGINT, &sig_int, NULL);
}

void	handle_signal_child(void)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	sig_int.sa_handler = &sigint_handler_child;
	sig_int.sa_flags = SA_RESTART;
	sigemptyset(&sig_int.sa_mask);
	sigaction(SIGINT, &sig_int, NULL);
	sig_quit.sa_handler = SIG_DFL;
	sig_quit.sa_flags = SA_RESTART;
	sigemptyset(&sig_quit.sa_mask);
	sigaction(SIGQUIT, &sig_quit, NULL);
}
