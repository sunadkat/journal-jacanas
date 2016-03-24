/*
 *
 * Simple Program intended to create template for journals
 * and automatically open them in sublime after creation
 * with cursor at the required location. Automatically logs
 * timestamp of the entry.
 */

#include <iostream>
#include <sstream>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <string.h>
#include <sys/stat.h>
#include <exception>
#include <stdexcept>
#include <vector>
using namespace std;

/*
 * REFERENCE FOR MY PURPOSES
 * Sublime accepts argument ':line-number:column-number' to indicate position for the cursor.
 */
int journal_raw_template(char path[],tm target_time, tm journal_time){
	std::fstream fs;
	fs.open(path, std::ios::in | std::ios::out | std::ios::app);
	//Currently template is hard coded, will not be in the distant future.
	char temp_date[] = "1969-12-31";
	strftime(temp_date, strlen("1970-01-01"), "%F", &journal_time);
	// Creating header
	fs 	<< temp_date << std::endl
		<< "Informal" << std::endl
		<< "Journal" << std::endl
		<< "Joshua Wu" << std::endl << std::endl;
	// Creating date headings
	for (int i = 6; i >= 0; --i)
	{
		journal_time.tm_mday -= i;
		mktime(&journal_time);
		strftime(temp_date, strlen("1970-01-01"), "%F", &journal_time);
		journal_time.tm_mday += i;
		fs << "###" << temp_date << std::endl;
	}
	fs.close();
	return 0;
}

int journal_timestamp_open(char path[],tm target_time, tm journal_time){
	std::fstream fs;
	fs.open(path, std::ios::in | std::ios::out);
	string line_buffer;
	time_t raw_time = time(NULL);
	struct tm tm_timestamp = *localtime(&raw_time); //tm_timestamp contains current time for timestamp
	// Copying the journal text into a string
	std::string journal_text;
	journal_text.assign( (std::istreambuf_iterator<char>(fs) ),
                       (std::istreambuf_iterator<char>()    ) );
	// check if the entry should be in the middle of the document
	int entry_pos;
	if (mktime(&target_time) != mktime(&journal_time))
	{
		target_time.tm_mday += 1;
		char entry_date[] = "1969-12-31";
		strftime(entry_date, strlen("1970-01-01"), "%F", &target_time); //String is entry date plus one
		entry_pos = journal_text.rfind(entry_date, journal_text.length());
		entry_pos = journal_text.rfind("\n", entry_pos -2 );
		// entry_pos -= 3; // Moving back three characters (the hash symbols)
	}
	else // Or at the end
	{
		entry_pos = journal_text.length();
	}
	// entry_pos is now indicating where to insert text
	mktime(&target_time);
	//Setting search strings and timestamp
	char journal_date[] = "1969-12-31";
	char timestamp[] = "1969-12-31T23:59";
	strftime(timestamp, strlen("1969-12-31T23:59"), "%FT%R", &tm_timestamp); //String is formatted for current timestamp
	strftime(journal_date, strlen("1970-01-01"), "%F", &journal_time); //String is entry date plus one

	std::string timestamp_formatted = "\n";
	timestamp_formatted.append(timestamp);
	timestamp_formatted.append("\n\n");
	journal_text.insert(entry_pos, timestamp_formatted);
	// std::cout << journal_text << endl;
	fs.close();
	fs.open(path, std::ios::out); // open in write only mode
	fs << journal_text;
	fs.close();
	int line_number = 0;
	for (int i = 0; i < entry_pos; ++i)
	{
		if (journal_text[i] == '\n')
		{
			line_number++;
		}
	}
	char program_call[100];
	for (int i = 0; i < 100; ++i)
	{
		program_call[i] = 0;
	}
	int j = 0;
	char path_escaped[256];
	for (unsigned int i = 0; i < strlen(path); ++i)
	{
		if (path[i] == ' ')
		{
			path_escaped[j] = '\\';
			j++;
			path_escaped[j] = ' ';
			j++;
		}
		else
		{
			path_escaped[j] = path[i];
			j++;
		}
	}
	snprintf(program_call, 100, "subl %s:%d:%d -n", path_escaped, line_number + 3,0);
	program_call[strlen(program_call)] = 0;
	std::cout << program_call << endl;
	// char column_selector[100];
	// char subl[100];
	// snprintf(subl, 100, "subl");
	// char n[100];
	// snprintf(n, 100, "-n");
	// snprintf(column_selector, 100, ":0:%d" ,entry_pos);
	// char* args[] = {subl, path_escaped, column_selector, n};
	// int pid = fork();
	// if (pid == 0)
	// {
	// 	execvp(args[0], args);
	// }
	system(program_call);
	return 0;
}

int journal_timestamp_open_no_write(char path[],tm target_time, tm journal_time){
	std::fstream fs;
	fs.open(path, std::ios::in | std::ios::out);
	string line_buffer;
	time_t raw_time = time(NULL);
	struct tm tm_timestamp = *localtime(&raw_time); //tm_timestamp contains current time for timestamp
	// entry_pos is now indicating where to insert text
	mktime(&target_time);
	//Setting search strings and timestamp
	char journal_date[] = "1969-12-31";
	char timestamp[] = "1969-12-31T23:59";
	strftime(timestamp, strlen("1969-12-31T23:59"), "%FT%R", &tm_timestamp); //String is formatted for current timestamp
	strftime(journal_date, strlen("1970-01-01"), "%F", &journal_time); //String is entry date plus one
	// std::cout << journal_text << endl;
	fs.close();

	char program_call[100];
	for (int i = 0; i < 100; ++i)
	{
		program_call[i] = 0;
	}
	int j = 0;
	char path_escaped[256];
	for (unsigned int i = 0; i < strlen(path); ++i)
	{
		if (path[i] == ' ')
		{
			path_escaped[j] = '\\';
			j++;
			path_escaped[j] = ' ';
			j++;
		}
		else
		{
			path_escaped[j] = path[i];
			j++;
		}
	}
	snprintf(program_call, 100, "subl %s -n", path_escaped);
	program_call[strlen(program_call)] = 0;
	std::cout << program_call << endl;
	// char column_selector[100];
	// char subl[100];
	// snprintf(subl, 100, "subl");
	// char n[100];
	// snprintf(n, 100, "-n");
	// snprintf(column_selector, 100, ":0:%d" ,entry_pos);
	// char* args[] = {subl, path_escaped, column_selector, n};
	// int pid = fork();
	// if (pid == 0)
	// {
	// 	execvp(args[0], args);
	// }
	system(program_call);
	return 0;
}

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
		else if(date_to_validate[i] > 57 || date_to_validate[i] < 48) //ASCII Values representing decimal numbers
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
	struct tm journal_time = *localtime(&raw_time);//Date of the journal itself
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
	// Check for -o arguments
	// -o: opens document without timestamp or setting to write
	// -y: sets the day to one day before input (typically yesterday)
	bool flag_open = false;
	if (argc > 1)
	{
		for (int i = 0; i < argc; ++i)
		{
			if (!strcmp(argv[i], "-o"))
			{
				flag_open = true;
			}
			else if(!strcmp(argv[i], "-y"))
			{
				journal_time.tm_mday -= 1;
				mktime(&journal_time);
			}
		}
	}
	mktime(&journal_time);
	target_time = journal_time; //Making target_time and journal time equivalent
	//check for existing journal for specified week (containing date)
	char file_name[] = "1970-01-01 Journal.md";
	std::fstream fs;
	mktime(&target_time);
	if (journal_time.tm_wday != 0)
	{
		//Journal time is now set to the journal name
		journal_time.tm_min = 0;
		journal_time.tm_hour = 0;
		journal_time.tm_mday += 7 - journal_time.tm_wday;
		mktime(&journal_time);
	}
	if (journal_time.tm_wday != 0)
	{
		char file_name_error[] = "1970-01-01 Journal.md";
		strftime(file_name_error, strlen("1970-01-01 Journal.md"), "%F Journal.md", &journal_time);
		printf("%s is the file attempted to be opened\n", file_name_error);
		throw "File to open not set to the Sunday of the week!\n";
	}
	//create file name for next sunday
	strftime(file_name, strlen("1970-01-01 Journal.md"), "%F Journal.md", &journal_time);
	/*
	 * PATH! Edit this for your computer. Note that spaces **DO NOT NEED TO BE ESCAPED**
	 */
	char path[256] = "/Users/Josh/Google Drive/Informal/Journal/";
	/*
	 *
	 */
	strcat(path, file_name);
	//Check if file exists
	struct stat buf;
	if (stat(path, &buf) == -1)
	{
		//File does not exist
		std::cout << path << " does not exist. Creating new file." << std::endl;
		fs.open(path, std::ios::out);
		//Write template
		journal_raw_template(path, target_time, journal_time);
		fs.close();
	}
	else
	{
		std::cout << path << " exists" << endl;
	}
	std::cout << "Attempting to open path: \"" << path << "\"" << std::endl << std::endl;
	fs.open(path, std::ios::in | std::ios::out | std::ios::app);

	if (!fs.is_open())
	{
		std::cout << "Something has happened! :S" << std::endl 
		<< "File could not be opened" << std::endl;
		throw std::runtime_error("File could not be opened\n");
	}
	if(!flag_open)
	{
		journal_timestamp_open(path, target_time, journal_time);
	}
	else
	{
		journal_timestamp_open_no_write(path, target_time, journal_time);
	}
	// write current date/time to journal after date entry
	// open in sublime with cursor at line below logging
	fs.close();
	return 0;
}
