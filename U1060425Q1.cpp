/*******************
Nathan Romeo
U1060425
Assignment 2 - Q1
*******************/

#include <iostream>
#include <iomanip>

// Constant values for plane rows and seats
const int PLANE_ROWS = 13;
const int PLANE_SEATS = 6;

using namespace std;

// Function declarations
void initialise_seats(char available_seats[PLANE_ROWS][PLANE_SEATS]);
void print_seats(char available_seats[PLANE_ROWS][PLANE_SEATS]);
void booking_message(char available_seats[PLANE_ROWS][PLANE_SEATS]);
bool greeting_menu(char available_seats[PLANE_ROWS][PLANE_SEATS]);
bool user_menu(char available_seats[PLANE_ROWS][PLANE_SEATS]);
bool check_seat(char available_seats[PLANE_ROWS][PLANE_SEATS], int row_number, int seat_index);

int main(){

    char available_seats[PLANE_ROWS][PLANE_SEATS];  // Two dimensional array for plane seats

    initialise_seats(available_seats);              // Initialise array for the plane seats

    bool continue_menu = true; // Flag to control the menu loop

    // Enter user menu loop until user wants to exit
    while (continue_menu) {    
        continue_menu = user_menu(available_seats);
    }

    return 0;
}

void initialise_seats(char available_seats[PLANE_ROWS][PLANE_SEATS]){ 
/****************************************************************
 * Initialise a two-dimensional array representing the rows and 
 * seats of an airplane.
 *
 * Assigns a char to the array index value representing 'available'.
 *
 * Char: *
*****************************************************************/

    const char AVAILABLE_SEAT_CHARACTER = '*';                        // The character that denotes an available seat

    for (int row = 0; row < PLANE_ROWS; row++) {                      // Iterate through each row and seat in plane
        for (int seat = 0; seat < PLANE_SEATS; seat++) {
            available_seats[row][seat] = AVAILABLE_SEAT_CHARACTER;    // Set value as AVAILABLE_SEAT_CHARACTER
        }
    }
}

void print_seats(char available_seats[PLANE_ROWS][PLANE_SEATS]){
/******************************************************************
 * Prints the diagram of available seats in plane to user's screen.
 *
 * Prints legend corresponding to available seat and occupied seat.
 *
 *   Format:
 *            A  B  C    D  E  F
 *   Row   1: *  X  *    *  *  *
 *   Row   2: *  *  *    *  X  *
 *   ...
 *   Row  13: *  *  *    *  *  *
 *   * -- available seat
 *   X -- occupied seat
*******************************************************************/

    cout << right << setw(27) << "A  B  C    D  E  F" << endl;      // Print header for columns
    for (int row = 0; row < PLANE_ROWS; row++){
        cout  << "Row  "  << setw(2) << right << row + 1 << ": ";   // Print row heading, number right aligned
        for (int seat = 0; seat < PLANE_SEATS; seat++){
            cout << available_seats[row][seat] << "  ";             // Output seat value from array and add space for next seat
            if (seat == 2){
                cout << "  ";                                       // Add extra space for centre aisle
            }
        }
        cout << endl;
    }
    cout << "* -- available seat" << endl << "X -- occupied seat" << endl << endl;
}

void booking_message(char available_seats[PLANE_ROWS][PLANE_SEATS]){
/*******************************************************
 * This function prints the booking menu, including the
 * available seats and the explanation for first class,
 * business class, and economy class.
*******************************************************/   
    
    cout << "This program assigns seats for a commercial airplane." << endl;

    cout << "The current seat assignments are as follows." << endl;

    print_seats(available_seats); // Print the diagram of available seats to the user

    cout << "Rows 1 and 2 are for first class passengers." << endl <<
            "Rows 3 through 7 are for business class passengers." << endl <<
            "Rows 8 through 13 are for economy class passengers." << endl;

}

bool greeting_menu(char available_seats[PLANE_ROWS][PLANE_SEATS]){
/*************************************************************************************
 * The initial greeting menu to be shown on the first run of the program.
 *
 * Prints initial booking message and asks if the user wishes to book a seat.
 * Prompts the user again if invalid response is given.
 *
 * @param char available_seats[PLANE_ROWS][PLANE_SEATS] - The array of plane seats.
 *
 * @return - True if user wishes to book a seat, false if program should be terminated.
**************************************************************************************/    

    booking_message(available_seats); // Print booking message

    cout << "To reserve a seat enter Y/y(Yes), N/n(No): ";
    bool answered = false;      // Flag to check for valid user response

    // Ask user if they want to reserve a seat  
    while (!answered){
    char user_reserving_seat;   // Char for user response
        // Get user input
        string input;
        getline(cin, input);    

        // Check if user entered 1 character
        if (input.length() == 1){
            user_reserving_seat = input[0];             // Assign response to user_reserving_seat
        }

        if (toupper(user_reserving_seat) == 'Y'){       // User response YES
            answered = true;
            return true;
        }
        else if (toupper(user_reserving_seat) == 'N'){  // User response NO
            cout << "Thank you for using the service. See you next time!" << endl; 
            answered = true;                
            return false;                               // Exit loop
        }
        else                                            // Invalid input, prompt again
            cout << "Invalid response. Please try again." << endl 
                 << "To reserve a seat enter Y/y(Yes), N/n(No): "; 
    }
    return false;
}

bool user_menu(char available_seats[PLANE_ROWS][PLANE_SEATS]){
/************************************************************************************
 * The main user menu.
 *
 * Asks user for ticket type, desired row and desired seat.
 * Prompts the user again if invalid response is given.
 *
 * @param char available_seats[PLANE_ROWS][PLANE_SEATS] - The array of plane seats.
 *
 * @return - True if menu should be restarted, false if program should be terminated.
*************************************************************************************/    

    static bool first_selection = true; // Flag to check if first selection has been made

    if (first_selection){
        if (!greeting_menu(available_seats)){   // If user selects 'N' in greeting menu
            return false;                       // Stop looping through user menu
        }
 
    }
    first_selection = false;    // First selection has been made, do not show greeting menu again
    
    static char user_ticket_type ='x';  // Char representing user ticket type, 'x' if unknown

    // Variables for min and max range of row numbers for each ticket type
    int row_number_min = 0;     
    int row_number_max = 0;

    bool answered = false;              // Flag to check for valid user response

    if (user_ticket_type != 'x'){       // If user ticket type is known
        answered = true;                // Do not prompt again
    }

    // Get user ticket type if not known

    while (!answered){

        cout << endl << "Enter ticket type: F/f (first class); (B/b) (business class); E/e (economy class): ";
        // Get user input
        string input;
        getline(cin, input);    

        // Check if user entered 1 character
        if (input.length() == 1){
            user_ticket_type = toupper(input[0]);    // Assign response to user_ticket_type

        }
        // Continue if user entered valid ticket type
        if (user_ticket_type == 'F' or user_ticket_type == 'B' or user_ticket_type == 'E'){
            answered = true;
            cout << endl;
        }
    }

    // Print valid user rows

    switch (user_ticket_type)
    {
    case 'F':   // First Class                          
        cout << "Enter Row Number 1 - 2: ";
        row_number_min = 1;
        row_number_max = 2;
        break;
    case 'B':   // Business Class
        cout << "Enter Row Number 3 - 7: ";
        row_number_min = 3;
        row_number_max = 7;
        break;
    case 'E':   // Economy Class
        cout << "Enter Row Number 8 - 13: ";
        row_number_min = 8;
        row_number_max = 13;
        break;
    default:
        cout << "Invalid response. Please try again." << endl;  // Prompt user again and continue loop
    }

    // Get desired row from user
    int desired_user_row;
    answered = false;   // Reset flag to check for valid user response

    while (!answered){
        
        // Get user input
        string input;
        getline(cin, input);    

        cout << endl;

        // Try to convert user input to integer, display error if user did not enter a valid integer value
        try
        {
            desired_user_row = stoi(input); // Convert input to integer

            if (desired_user_row >= row_number_min and desired_user_row <= row_number_max){   // Check if input is within allowed range of rows
                answered = true;     // Valid response, break from loop
            }
            else{
                cout << "Invalid row for your ticket type. Please enter a row between " 
                    << row_number_min << " and " << row_number_max << ": "; 
            }
        }
        catch(...)  // User did not input integer
        {
            cout << "Invalid response. Please enter a number between "  
                << row_number_min << " and " << row_number_max << ": ";    // Reprompt user
        }

    }
    
    // Get desired seat from user
    char desired_user_seat;
    answered = false;   // Reset flag to check for valid user response
    
    while (!answered){    
    cout << "Enter seat number (A to F): ";

        // Get user input
        string input;
        getline(cin, input);    

        cout << endl;

        // Check if user entered 1 character
        if (input.length() ==1){
            desired_user_seat = (input[0]);    // Assign response to user_ticket_type

            // Check if response within range A-F
            if (desired_user_seat >= 'A' and desired_user_seat <= 'F'){
                answered = true;

                int seat_index = static_cast<int>(desired_user_seat) - 65;  // Convert seat to index for array

                if (check_seat(available_seats, desired_user_row-1, seat_index)){
                    available_seats[desired_user_row-1][seat_index] = 'X';
                    cout << "This seat is reserved for you." << endl;

                    print_seats(available_seats);
                } else {
                    cout << "*#*#*#*# This seat is occupied *#*#*#*#" << endl << "Make another selection." << endl; 
                    print_seats(available_seats);
                    return true;
                }
            } else {
                continue;   // Reprompt if invalid response or non-capital letter entered
            }
        }
    }

    user_ticket_type = 'x'; // Reset user ticket type

    // Ask user if they want to book another seat
    booking_message(available_seats);

    char reserve_new_seat = 'x';    // Char to indicate user selection, default 'x' to refesh value each loop
    answered = false;       // Reset flag to check for valid user response

    while (!answered){
    cout << "Reserve another seat Y/y(Yes), N/n(No): ";
        // Get user input
        string input;
        getline(cin, input);    

        // Check if user entered 1 character
        if (input.length() == 1){
            reserve_new_seat = input[0];             // Assign response to user_reserving_seat
        }

        if (toupper(reserve_new_seat) == 'Y'){       // User response YES
            answered = true;
            return true;
        }
        else if (toupper(reserve_new_seat) == 'N'){  // User response NO
            cout << "Thank you for using the service. Your flights have been booked. Safe flying!";
            return false;                    // Terminate menu function
        }
        else                                 // Invalid response. Prompt user again
            cout << "Invalid response. Please try again." << endl;         
    }

    return true;        // Loop through menu again
}

bool check_seat(char available_seats[PLANE_ROWS][PLANE_SEATS], int row_number, int seat_index){
/**********************************************************************************
 * Checks if users desired seat is free and returns bool.
 *
 * @param char available_seats[PLANE_ROWS][PLANE_SEATS] - The array of plane seats.
 * @param int row_number - The user requested row number
 * @param int seat_index - The user requested seat number
 *
 * @return - True if seat is available, otherwise false.
**********************************************************************************/

    if (available_seats[row_number][seat_index] == '*'){
        return true;
    }
    return false;
}