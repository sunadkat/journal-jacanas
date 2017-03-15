#Utilities
This is a collection of tools and scripts which were useful to me or fun to make.
##Journal
This will create simple journal templates and open them if they already exist. Examples of journal templates will be shown below. Journals are in markdown format.

**NOTE** if you use atom put the whitespace back the way you found it!

**WARNING** This currently uses a system call to run "subl" which should open up sublime with some arguments. This is very unsafe. Use at your own risk.

2016-02-21

Foldername

Journal

John Smith

###2016-02-15
2016-02-15T23:02
This is a journal entry. The program will log the above date, open sublime, and set the cursor to the position just under this timestamp.

###2016-02-16
2016-02-22T16:18
If the program is called with an ISO8601 date as the first argument, the journal will open the *week* which contains that day and timestamp under the date, setting the cursor under it. 


###2016-02-17
.
.
.
###2016-02-21
