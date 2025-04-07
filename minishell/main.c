#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LIBFT/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

void	free2d(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		free(array[i++]);
	free(array);
}


int main()
{
    char *input;
    int  in = 0;
    int  out = 0;
    char *copy;
    char **insplit;
//       |  <  >   >> <<
    while (1)
	{
		input = readline("Minishell >> ");
		copy = ft_strdup(input);
		insplit = ft_split(input, ' ');
		int i = 0;
    	while (insplit[i])
		{
       		printf(">> %s\n", insplit[i]);
       		// free(input);
			i++;
		}
		printf("==>%s\n", copy);
	}
    return 0;
}
