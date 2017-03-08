#/usr/local/bin/python3

import sys
import datetime
import os

def check_date(input_date):
    return False

def parse_date(input_date):
    # Parse date
    return input_date

class journal_entry():
    def __init__(self):
        self.entry_date = datetime.datetime.now()
        self.journal_date = self.get_journal_week()
        self.file_name = self.get_file_name()
        self.line_entry_point = 0
        self.file_buffer = []
        self.directory = "/journal"

    def get_journal_week(self):
        days_to_next_sunday = (7 - self.entry_date.isoweekday())
        self.journal_date = self.entry_date + datetime.timedelta(days_to_next_sunday)
        return self.journal_date

    def get_file_name(self):
        self.file_name = self.journal_date.isoformat()[:10] + " Journal.md"
        return self.file_name

    def open_journal(self):
        if os.path.exists(self.directory + self.file_name):
            self.file = open(self.directory + self.file_name, 'r+')
        else:
            self.file = open(self.directory + self.file_name, 'w+')
            # Write journal template
        return

    def get_journal_template(self):
        template = """{}
Informal
Journal
Joshua Wu

### {}
### {}
### {}
### {}
### {}
### {}
### {}
""".format(self.journal_date.isoformat()[:10],
        (self.journal_date - datetime.timedelta(6)).isoformat()[:10],
        (self.journal_date - datetime.timedelta(5)).isoformat()[:10],
        (self.journal_date - datetime.timedelta(4)).isoformat()[:10],
        (self.journal_date - datetime.timedelta(3)).isoformat()[:10],
        (self.journal_date - datetime.timedelta(2)).isoformat()[:10],
        (self.journal_date - datetime.timedelta(1)).isoformat()[:10],
        (self.journal_date - datetime.timedelta(0)).isoformat()[:10])
        return template

    def find_entry_point(self):
        self.line_entry_point = 0
        if(self.entry_date.isoformat()[:10] == self.journal_date.isoformat()[:10]):
            # Is on a sunday, entry is at the end
            file_length = 0
            for i in open_file:
                file_length += 1
            self.line_entry_point = file_length
            open_file.seek(0)
            return file_length
        else:
            # Searching for the day after the desired entry
            formatted_entry_date = "### " + (self.entry_date + datetime.timedelta(1)).isoformat()[:10]
            for line in self.open_file:
                if line == formatted_entry_date:
                    return self.line_entry_point
                else:
                    self.line_entry_point += 1
        return -1

    def insert_timestamp(self):
        return

    def get_line_entry_point(self):
        return self.line_entry_point

if __name__ == "__main__":
    return
