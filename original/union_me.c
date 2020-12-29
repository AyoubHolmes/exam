/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union_me.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 13:26:13 by knabouss          #+#    #+#             */
/*   Updated: 2020/12/11 12:00:21 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc == 3)
    {
        int i;
        int j;
        char used[255];
        
        i = 0;
        while(i < 255)
        {
            used[i] = 0;
            i++;
        }
        i = 1;
        while(i < 3)
        {
            j = 0;
            while(argv[i][j])
            {
                if (used[(unsigned char)argv[i][j]] == 0)
                {
                    write(1, &argv[i][j], 1);
                    used[(unsigned char)argv[i][j]] = 1;
                }
                j++;
            }
            i++;
        }
    }
    write(1, "\n", 1);
    return (0);
}