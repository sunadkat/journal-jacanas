#include <stdio.h>
#include <string.h>
#include <time.h>
/*
 * Simple Program intended to create template for journals
 * and automatically open them in sublime after creation 
 * with cursor at the required location. Automatically logs 
 * timestamp of the entry.
 * REFERENCE FOR MY PURPOSES
 * Sublime accepts argument ':line-number:column-number' to indicate position for the cursor. 
 *
 * First argument is the date which will be written for
 * second argument is '-n', passed to sublime to open in a new window if necessary
 */
int main(int argc, char const *argv[])
{
	time_t target_time = time(); //Date which is to be written about, defaults to current time
	time_t current_time = time(); //Date of current logging
	//check for arguments to program
	if (argc > 2 && !strcmp(argv[1], "-n")); //If the user has entered something other than 'journal -n'
	{
		//TODO: Verify input
		if (//Input Verified)
		{
			//TODO: Parse Input
		}
	}
	//check for existing journal for specified week (containing date)
	//if no journal create from template
	//write current date/time to journal after date entry
	//open in sublime with cursor at line below logging
	return 0;
}