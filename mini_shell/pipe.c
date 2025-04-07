#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char **split_pipe(char *str, char c, int index)
{
	int 
}
int main()
{
    char *input = "echo '|' | grep hello > file.txt | ls";

    char **cmds = ft_split_pipe(input);
    int i = 0;

    while (cmds[i])
    {
        printf("Command %d: [%s]\n", i, cmds[i]);
        i++;
    }

    return 0;
}
