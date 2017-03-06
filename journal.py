#/usr/bin/env python

import sys
import datetime
class journal_entry():
    def __init__(self):
        self.entry_date = datetime.datetime.now()
        self.journal_date = self.get_journal_week()
        self.file_name = self.get_file_name()
        self.line_entry_point = self.find_entry_point()
        self.file_buffer = []
        self.directory = ""
        self.file

    def get_journal_week(self):
        days_from_last_sunday = (self.entry_day.weekday() + 1)%7
        self.journal_date = self.entry_day - datetime.timedelta(days_from_last_sunday)
        return self.journal_date

    def get_file_name(self):
        self.file_name = self.journal_date[:10] + " Journal.md"
        return self.file_name
    def find_entry_point(self):
        self.line_entry_point = 0
        formatted_entry_date = "### 2017-01-01" # TODO Placeholder entry
        for line in self.open_file:
            self.line_entry_point += 1
            file_buffer.append(line)
            if line == formatted_entry_date:
                return self.line_entry_point
        return -1
if __name__ == "__main__":
    # Check for number of arguments
    # Parse Options
    # Parse Input Date
    print sys.argv
