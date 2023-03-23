/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbutarbu <rbutarbu@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:30:03 by rbutarbu          #+#    #+#             */
/*   Updated: 2023/02/15 22:03:54 by rbutarbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void ft_handler(int signal, siginfo_t *info, void *s)
{
    static int bit;
    static int i;

    (void)info;
    (void)s;

    if (signal == SIGUSR1)
        i |= (0x01 << bit);
        
    bit++;
    if (bit == 8)
    {
        ft_printf("%c", i);
        bit = 0;
        i = 0;
        kill(info->si_pid, SIGUSR2); 
    }
}

int main (int argc, char **argv)
{
    int pid;

    struct sigaction sig;
 
    (void)argv;
    if (argc != 1)
    {
        ft_printf("WRONG FORMAT. Try ./server");
        return (0);
    }
    pid = getpid();
    ft_printf("PID : %d \n", pid);
    ft_printf("Waiting for a message \n");
    sig.sa_sigaction = ft_handler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    while (argc == 1)
    {
        sigaction(SIGUSR1, &sig, NULL);
        sigaction(SIGUSR2, &sig, NULL);
        pause();
    }
    return (0);
}