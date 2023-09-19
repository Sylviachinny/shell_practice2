#include "main.h"
#include "headerfile.h"

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0
 */

int main()
{
	const char *inputString = "apple,banana,cherry,grape";
       char delimiter = ',';

       pathe_helper help;
       help.path = inputString;
       help.delim = delimiter;

       /*call path_to_list to split the inputString*/
       directory_n *resultlist = path_to_list(NULL, help);
       
       if (resultList)
       {
	       /*print the resulting list*/
	       directory_n *current = resultList;
	       while (current)
	       {
		       printf("%s\n", current->path);
		       current = current->link;
	       }

	       /*free the memory allocated for the list 
		* (assuming you habve a free_dir function)*/
       }
       return 0;
}
