/*
 *
 * Simple Program intended to create template for journals
 * and automatically open them in sublime after creation
 * with cursor at the required location. Automatically logs
 * timestamp of the entry.
 */

#include <iostream>
#include <ctime>
#include <fstream>
#include <string.h>
#include <sys/stat.h>
#include <exception>
#include <stdexcept>
using namespace std;

/*
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

	std::fstream test_stream;
	test_stream.open("/User/Josh/Downloads/test.txt", std::ios::out);
	test_stream << "Amazing journal" << std::endl;
	test_stream.close();
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
	std::fstream fs;

	if (journal_time.tm_wday != 0)
	{
		//Journal time is now set to the journal name
		journal_time.tm_mday += 7 - journal_time.tm_wday;
		mktime(&journal_time);
	}
	//create file name for next sunday
	strftime(file_name, strlen("1970-01-01 Journal.md"), "%F Journal.md", &journal_time);
	/*
	 * PATH! Edit this for your computer. Note that spaces **DO NOT NEED TO BE ESCAPED**
	 */
	char path[256] = "/Users/Josh/Google Drive/Informal/Journal/";
	strcat(path, file_name);
	/*
	 *
	 */

	//Check if file exists
	struct stat buf;
	if (stat(path, &buf) == -1)
	{
		//File does not exist
		std::cout << path << " does not exist. Creating new file." << std::endl;
		fs.open(path, std::ios::out);
		fs.close();
	}
	std::cout << "Attempting to open path: \"" << path << "\"" << std::endl << std::endl;
	fs.open(path, std::ios::in | std::ios::out | std::ios::app);

	if (!fs.is_open())
	{
		std::cout << "Something has happened! :S" << std::endl 
		<< "File could not be opened" << std::endl;
		throw std::runtime_error("File could not be opened\n");
	}
	// write current date/time to journal after date entry
	// open in sublime with cursor at line below logging
	fs.close();
	return 0;
}
