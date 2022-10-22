// Ethan Van Horn
// A Program to calculate costs for overdue books to an output file
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cmath>
#include <utility>
using namespace std;


// Fill the arrays with the amount of data in the input file
void fill_arrays(string patron_name[], char book_type[], double days_overdue[], int &amount_of_records);

// Fill the fine_cost array with the amount of fines owed per patron
void calculate_fines(double days_overdue[], int amount_of_records, double fine_cost[], char book_type[]);

// Sort the arrays from the highest fine cost to the lowest fine cost
void sort_high_to_low(double days_overdue[], double fine_cost[], char book_type[], string patron_name[], int amount_of_records);

// Send the fine sorted arrays to file output
void send_to_output_high_to_low(double fine_cost[], string patron_name[], int amount_of_records);

// Sort the arrays by the alphabetical order of the patrons names
void sort_alphabetically(double days_overdue[], double fine_cost[], char book_type[], string patron_name[], int amount_of_records);

// Send the alphabetically sorted arrays to file output
void send_to_output_alphabetically(double days_overdue[], double fine_cost[], char book_type[], string patron_name[], int amount_of_records);


int main()
{
  const int MAX_PATRONS = 500;

  string patron_name[MAX_PATRONS];
  char book_type[MAX_PATRONS];
  double days_overdue[MAX_PATRONS];
  double fine_cost[MAX_PATRONS];
  int amount_of_records = 0;

  // calls the fill_arrays function to fill the arrays with the amount of data in the input file
  fill_arrays(patron_name, book_type, days_overdue, amount_of_records);

  // We now have the input file data in our arrays ready to process.

  // calls the calculate_fines function to fill the fine_cost array with the amount of fines owed per patron
  calculate_fines(days_overdue, amount_of_records, fine_cost, book_type);

  // Our fine_cost array is now filled in.

  // calls the sort_high_to_low function to sort the arrays from the highest fine cost to the lowest fine cost
  sort_high_to_low(days_overdue, fine_cost, book_type, patron_name, amount_of_records);

  // The arrays are now sorted by `fine_cost`.

  // calls the send_to_output_high_to_low function to send the fine sorted arrays to file output
  send_to_output_high_to_low(fine_cost, patron_name, amount_of_records);

  // results.txt is now saved to disk with High to Low output.

  // calls the sort_alphabetically function to sort the arrays by the alphabetical order of the patrons names
  sort_alphabetically(days_overdue, fine_cost, book_type, patron_name, amount_of_records);

  // Arrays are now sorted by name alphabetically.

  // calls the send_to_output_alphabetically function to send the alphabetically sorted arrays to file output
  send_to_output_alphabetically(days_overdue, fine_cost, book_type, patron_name, amount_of_records);

  // Alphabetical output appeneded to results.txt.

  return 0;
}

/**
 * Fills all the arrays with the corresponding data from the input file based on the structure of the input file given
 * Counts the amount of items in each array and puts it into the amount_of_records variable for future functions
 * @param patron_name the patron_name array to fill with the Name of the Current Patron in the input file
 * @param book_type the book_type array to fill with either a 'G'eneral or 'R'eserve for calculating the cost later
 * @param days_overdue the days_overdue array to fill with the days overdue a book is for calculating the cost later
 * @param amount_of_records the amount of items in each array used for loops in later functions
 */
void fill_arrays(string patron_name[], char book_type[], double days_overdue[], int &amount_of_records)
{
  const int MAX_STRING_LENGTH = 20;
  const int INITIAL_INDEX = 0;
  const int BOOK_LOCATION = 20;
  const int MOVE_ONE_CHAR = 1;
  ifstream input_file;
  input_file.open("patrons.txt");

  int current_index = INITIAL_INDEX;
  string current_patron;
  //while the input file is not at the eof marker it keeps repeating
  while(input_file.good())
  {
      getline(input_file, current_patron);
      //get patron name
      for(unsigned current_character = 0; current_character < MAX_STRING_LENGTH; current_character++)
      {
          patron_name[current_index] += current_patron.at(current_character);
      }
      //get book type
      book_type[current_index] = static_cast<char>(current_patron.at(BOOK_LOCATION));
      //get days overdue
      days_overdue[current_index] = atof(current_patron.substr(BOOK_LOCATION + MOVE_ONE_CHAR).c_str()); // NOLINT(cert-err34-c)


      current_index++;
      //increments the amount_of_records variable to use in future functions
      amount_of_records++;
  }
}

/**
 * calculates the fines owed by the patron and puts it into the corresponding fine_cost array
 * @param days_overdue the days_overdue array used in calculating the amount of fines owed
 * @param amount_of_records the amount of items in the arrays for loop checking
 * @param fine_cost the fine_cost array to put the calculated fines into
 * @param book_type the book_type array used in calculating the amount of fines owed
 */
void calculate_fines(double days_overdue[], int amount_of_records, double fine_cost[], char book_type[])
{
  const double HOURS_IN_DAY = 24.0;
  const int INITIAL_INDEX = 0;
  const double GENERAL_COST = .15;
  const double RESERVE_COST = .25 * HOURS_IN_DAY;
  unsigned current_index = INITIAL_INDEX;

  //calculates the fine costs for every item in the arrays and puts it into the corresponding index
  for(unsigned i = 0; i < amount_of_records; i++)
  {
    if(book_type[current_index] == 'G')
    {
      fine_cost[current_index] = days_overdue[current_index] * GENERAL_COST;
    }
    else
    {
      fine_cost[current_index] = days_overdue[current_index] * RESERVE_COST;
    }
    fine_cost[current_index] = round(fine_cost[current_index] * 100) / 100.0;
    current_index++;
  }
}

/**
 * Sorts a parallel arrays from the highest fine cost to the lowest fine cost
 * @param days_overdue the days_overdue array used in sorting
 * @param fine_cost the fine_cost array used in sorting
 * @param book_type the book_type array used in sorting
 * @param patron_name the patron_name array used in sorting
 * @param amount_of_records the amount of items in the arrays for loop checking
 */
void sort_high_to_low(double days_overdue[], double fine_cost[], char book_type[], string patron_name[], int amount_of_records)
{
  const int INITIAL_INDEX = 0;
  int index_change;

  //nested for loops to sort the arrays by highest to the lowest fine cost
  for (int current_index = INITIAL_INDEX; current_index < amount_of_records - 1; current_index++) {
    index_change = current_index;

    for (int comparing_index = current_index + 1; comparing_index < amount_of_records; comparing_index++)
    {
      if (fine_cost[comparing_index] > fine_cost[index_change])
      {
        index_change = comparing_index;
      }
    }
    //swaps all parallel arrays to keep them parallel
    swap(fine_cost[current_index], fine_cost[index_change]);
    swap(days_overdue[current_index], days_overdue[index_change]);
    swap(book_type[current_index], book_type[index_change]);
    swap(patron_name[current_index], patron_name[index_change]);
  }
  //Echo Check, uncomment
//  for (int i = 0; i < amount_of_records; i++)
//  {
//    cout << patron_name[i] << endl;
//    cout << days_overdue[i] << endl;
//    cout << book_type[i] << endl;
//    cout << fine_cost[i] << endl;
//  }

}

/**
 * Sends the arrays sorted from the highest fine cost to the lowest fine cost to the output file
 * @param fine_cost the fine_cost array to put into output
 * @param patron_name the patron_name array to put into output
 * @param amount_of_records the amount of items in the arrays for loop checking
 */
void send_to_output_high_to_low(double fine_cost[], string patron_name[], int amount_of_records)
{
  const int INITIAL_INDEX = 0;
  ofstream output_file;
  output_file.open("results.txt");

  output_file << "Customers Listed in Order of Fines (highest to lowest)" << endl;
  output_file << "NAME" << setfill(' ') << setw(51) << "FINE" << endl;
  output_file << setfill('=') << setw(57) << ' ' << endl;

  //outputs all values sorted from the highest fine cost to the lowest
  for(unsigned current_index = INITIAL_INDEX; current_index < amount_of_records; current_index++)
  {
    output_file
      << patron_name[current_index]
      << setfill(' ') << setw(31)
      << "$ ";

    output_file
      // Format the decimal, fixed, 2 decimals, left pad.
      << fixed << setprecision(2) << setfill(' ') << setw(5)
      << fine_cost[current_index]
      << endl;
  }
  cout << endl << endl <<endl;
}

/**
 * Sorts all parallel arrays by the alphabetical sorting of the patron_name array
 * @param days_overdue the days_overdue array to use in sorting the arrays
 * @param fine_cost the fine_cost array to use in sorting the arrays
 * @param book_type the book_type array to use in sorting the arrays
 * @param patron_name the patron_name array to sort alphabetically and keep all arrays parallel
 * @param amount_of_records the amount of items in each array for loop checking
 */
void sort_alphabetically(double days_overdue[], double fine_cost[], char book_type[], string patron_name[], int amount_of_records)
{
  const int INITIAL_INDEX = 0;
  int index_change;

  //nested for loops to sort the arrays in alphabetical order
  for (int current_index = INITIAL_INDEX; current_index < amount_of_records - 1; current_index++) {
    index_change = current_index;

    for (int comparing_index = current_index + 1; comparing_index < amount_of_records; comparing_index++)
    {
      if (patron_name[comparing_index] < patron_name[index_change])
      {
        index_change = comparing_index;
      }
    }
    //swaps all parallel arrays to stay parallel when sorting
    swap(fine_cost[current_index], fine_cost[index_change]);
    swap(days_overdue[current_index], days_overdue[index_change]);
    swap(book_type[current_index], book_type[index_change]);
    swap(patron_name[current_index], patron_name[index_change]);
  }
}

/**
 * Sends the alphabetical sorted list to the file output
 * @param days_overdue the days_overdue array to put into output
 * @param fine_cost the fine_cost array to put into output
 * @param book_type the book_type array to put into output
 * @param patron_name the patron_name array to put into output
 * @param amount_of_records the amount of items in each array for loop checking
 */
void send_to_output_alphabetically(double days_overdue[], double fine_cost[], char book_type[], string patron_name[], int amount_of_records)
{
  const int INITIAL_INDEX = 0;
  ofstream output_file;
  //Opens the output file in APPEND mode, so it doesn't delete all the contents
  output_file.open("results.txt", ofstream::app);

  //New array for turning the book type char into a full word
  string book_type_name[amount_of_records];

  output_file << endl;
  output_file << "Alphabetical List of Customers and Corresponding Fine Info" << endl;
  output_file << "NAME" << setw(25) << "TYPE";
  output_file << setw(9) << "DAYS";
  output_file << setw(17) << "FINE" << endl;
  output_file << setfill('=') << setw(57) << ' ' << endl;

  //turns the char array book_type into a string array to name the book type
  for(unsigned current_index = INITIAL_INDEX; current_index < amount_of_records; current_index++)
  {
    if(book_type[current_index] == 'G')
    {
      book_type_name[current_index] = "General";
    }
    else
    {
      book_type_name[current_index] = "Reserve";
    }
  }

  //Outputs all the data in alphabetical order
  for(unsigned current_index = INITIAL_INDEX; current_index < amount_of_records; current_index++)
  {
    output_file << patron_name[current_index] << setfill(' ') << setw(11);
    output_file << book_type_name[current_index] << setw(8);
    output_file << days_overdue[current_index] << setw(12) << "$ ";
    output_file
      // Format the decimal, fixed, 2 decimals, left pad.
      << fixed << setprecision(2) << setfill(' ') << setw(5)
      << fine_cost[current_index]
      << endl;
  }
}