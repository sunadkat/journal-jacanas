#include <iostream>
#include <ctime>
#include <fstream>
#include <string.h>
using namespace std;
/*
 * Simple Program intended to create template for journals
 * and automatically open them in sublime after creation
 * with cursor at the required location. Automatically logs
 * timestamp of the entry.
 * REFERENCE FOR MY PURPOSES
 * Sublime accepts argument ':line-number:column-number' to indicate position for the cursor.
 */

bool validate_date(char const date_to_validate[]){
	//Ahaha get it?                 ^^^^
	if (strlen(date_to_validate) > 10)
	{
		//Date length is longer than expected
		printf("Input is longer than expected\n");
		return false;
	}
	for (unsigned int i = 0; i < strlen(date_to_validate); ++i)
	{
		//0123-56-89
		if (i == 4 || i == 7)
		{
			if(date_to_validate[i] != '-')
			{
				return false;
			}
		}
		else if(date_to_validate[i] > 57 || date_to_validate[i] < 48)
		{
			return false;
		}
	}
	return true;
}

/*
 * First argument is the date which will be written for
 * second argument is '-n', passed to sublime to open in a new window if necessary
 */
int main(int argc, char const *argv[])
{
	time_t raw_time = time(NULL);
	struct tm target_time = *localtime(&raw_time); //Date which is to be written about, defaults to current time
	struct tm journal_time = *localtime(&raw_time);
	// struct tm current_time = *localtime(&raw_time);
	//check for arguments to program
	if (argc > 1 && strcmp(argv[1], "-n")) //If the user has entered something other than 'journal -n'
	{
		if (validate_date(argv[1]))
		{
			strptime(argv[1], "%F", &journal_time); //Copying input into the journal_time
		}
		else
		{
			if(1) //Intended to use REGEX, check for "REG_NOMATCH"
			{
				printf("Invalid Argument %s, not in format ISO8601\n",argv[1] );
			}
			else
			{
				printf("Error\n");
			}
		}
	}
	mktime(&journal_time);
	target_time = journal_time; //Making target_time and journal time equivalent
	//check for existing journal for specified week (containing date)
	char file_name[] = "1970-01-01 Journal.md";
	std::ifstream fs;
	// for (int i = 0; i < 7 && !fs.is_open; ++i)
	// {
	// 	//Go through the current day and seven days plus to check for existing journal
	// 	journal_time.tm_mday += i;
	// 	mktime(&journal_time);
	// 	strftime(file_name, strlen("1970-01-01 Journal.md"), "%Y-%M-%D Journal.md", &journal_time);
	// 	journal_time.tm_mday -= i;
	// }
	//Find difference between target time and next sunday
	if (journal_time.tm_wday != 0)
	{
		//Journal time is now set to the journal name
		journal_time.tm_mday += 7 - journal_time.tm_wday;
		mktime(&journal_time);
	}
	//create file name for next sunday
	strftime(file_name, strlen("1970-01-01 Journal.md"), "%F Journal.md", &journal_time);
	//Attempt to open file
	// char path[256] = "/Users/Josh/Google\\ Drive/Informal/Journal/";
	char path[0];
	printf("Attempting to open: \"%s%s\"\n",path, file_name );
	fs.open(strcat(path,file_name), ios::in | ios::out);
	if (!fs.is_open())
	{
		printf("%s not found, attemping to make %s\n",file_name, file_name );
		//create new file using file_name
		//open file
	}
	// write current date/time to journal after date entry
	// open in sublime with cursor at line below logging
	return 0;
}
