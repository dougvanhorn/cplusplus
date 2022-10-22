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

    selection_sort_by_fine(records)
    print()
    print('By manual sort fine')
    print('-' * 79)
    for record in records:
        print(record)


def selection_sort_by_fine(records):
    # Algorithm:
    # https://en.wikipedia.org/wiki/Selection_sort
    # Given list of size n.
    # Start at the first element, i.
    # Traverse i+1..n, to get the index of the largest element largest_i
    # Swap the largest element for the first postion.
    print()
    record_count = len(records)

    # Outer loop goes from 0 to n-1.
    for left_index in range(0, record_count - 1):
        print(' '.join([str(record.get_fine()) for record in records]))
        # Left index?
        index_of_greatest_fine = left_index

        # Inner loop 
        for comparing_index in range(left_index+1, record_count):
            print(f'    {records[comparing_index].get_fine()} > {records[index_of_greatest_fine].get_fine()}?')
            if records[comparing_index].get_fine() > records[index_of_greatest_fine].get_fine():
                print(f'        moving index_of_greatest_fine from {index_of_greatest_fine} to {comparing_index}')
                index_of_greatest_fine = comparing_index
        
        print(f'left_index[{left_index}]: {records[left_index].get_fine()}')
        print(f'index_of_greatest_fine[{index_of_greatest_fine}]: {records[index_of_greatest_fine].get_fine()}')
        print()
        records[left_index], records[index_of_greatest_fine] = records[index_of_greatest_fine], records[left_index]


if __name__ == '__main__':
    main()