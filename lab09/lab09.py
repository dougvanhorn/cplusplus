#!/usr/bin/env python3
# Lab 9, Python style.

import collections
import decimal
import enum


# This is a fixed width file, sort of.
# In the real world, the last field would have the same width on all lines.  In this file, the last
# field has a varying width.  And techniclly the location column would be 2 chars.
#
# Field position and width are as follows:
#
# Name          Pos   Length  Type
# last, first   0     20      string
# location      21    1       string
# Days overdue  23    eol     float
INPUT_FILENAME = 'patrons.txt'

OVERDUE_FINE_GENERAL = decimal.Decimal('.15')
OVERDUE_FINE_RESERVE = decimal.Decimal('6')  # 24 * .25?
COST_QUANTIZE = decimal.Decimal('.01')

class BookType(enum.Enum):
    """Define our types of books as an enum.
    """
    General = 'G'
    Reserve = 'R'


class Record:
    """A Class to encapsulate Record data and behavior.
    """
    @staticmethod
    def from_input(input_record):
        record = Record()
        record.patron_name = input_record[:20].strip()
        record.book_type = BookType(input_record[20:21])
        record.days_overdue = decimal.Decimal(input_record[22:])
        return record

    def __init__(self):
        self.patron_name = None
        self.book_type = None
        self.days_overdue = None

    def __str__(self):
        return f'{self.patron_name:<20}  {self.book_type.name:<9}  {self.days_overdue:>5}  ${self.get_fine():>5}'

    def get_fine(self):
        # Default to General Fine.
        fine = OVERDUE_FINE_GENERAL
        if self.book_type == BookType.Reserve:
            fine = OVERDUE_FINE_RESERVE
        cost = self.days_overdue * fine
        cost = cost.quantize(COST_QUANTIZE)
        return cost


def main():
    with open(INPUT_FILENAME, mode='r') as fp:
        raw_data = fp.read()

    records = []
    rows = raw_data.split('\n')
    for row in rows:
        record = Record.from_input(row)
        records.append(record)

    print('From input')
    print('-' * 79)
    for record in records:
        print(record)

    records.sort(key=lambda record: record.get_fine(), reverse=True)
    print()
    print('By fine')
    print('-' * 79)
    for record in records:
        print(record)

    records.sort(key=lambda record: record.patron_name)
    print()
    print('By patron name')
    print('-' * 79)
    for record in records:
        print(record)


if __name__ == '__main__':
    main()