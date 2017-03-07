#/usr/local/bin/python3

import sys
import datetime

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
        self.line_entry_point = self.find_entry_point()
        self.file_buffer = []
        self.directory = ""
        self.file

    def get_journal_week(self):
        days_from_last_sunday = (self.entry_date.weekday() + 1)%7
        self.journal_date = self.entry_date - datetime.timedelta(days_from_last_sunday)
        return self.journal_date

    def get_file_name(self):
        self.file_name = self.journal_date.isoformat()[:10] + " Journal.md"
        return self.file_name

    def open_journal(self):
        if os.path.exists(self.directory + self.file_name):
            self.file = open(self.directory + self.filename, 'r+')
        else:
            self.file = open(self.directory + self.filename, 'w+')
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
"""
        return template
    def find_entry_point(self):
        self.line_entry_point = 0
        formatted_entry_date = "### " + self.entry_date.isoformat()[:10]
        for line in self.open_file:
            self.line_entry_point += 1
            file_buffer.append(line)
            if line == formatted_entry_date:
                return self.line_entry_point
        return -1

    def insert_timestamp(self):
        return

    def get_line_entry_point(self):
        return self.line_entry_point

if __name__ == "__main__":
    return
