//
// Created by james.gill24 on 21/11/2024.
//


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// subroutines for the main menu and quit function
void mainMenu();
void quit();

// subroutines for check in
void checkIn();
int roomChoice();
void dateOfBirth(int row);
void inputGuests(int row);
void chooseBoard(int row);
void lengthOfStay(int row);
void newspaperChoice(int row);

// subroutines for check out
void checkOut();
int checkUser();
float calculateRoomCost(int row);
float calculateBoardCost(int row);
float addNewspaperCost(int row);
void removeData(int row);

// global variables

    // 1d arrays
int roomRates[6] = {100, 100, 85, 75, 75, 50}; // data stored [room1, room2, room3, room4, room5, room6]
int boardRates[3] = {20, 15, 5}; // data stored [F, H, B]

    // 2d arrays
char * strDetails[][5] = {
    {"","","","",""}, // bookingID, firstName, surname, boardChoice, newspaper
    {"","","","",""},
    {"","","","",""},
    {"","","","",""},
    {"","","","",""},
    {"","","","",""}
};

int intDetails[][7] = {
    {1, 0, 0, 0, 0, 0, 0}, //roomNumber, adults, children, stayLength, dob[0], dob[1], dob[2]
    {2, 0, 0, 0, 0, 0, 0},
    {3, 0, 0, 0, 0, 0, 0},
    {4, 0, 0, 0, 0, 0, 0},
    {5, 0, 0, 0, 0, 0, 0},
    {6, 0, 0, 0, 0, 0, 0}
};

// subroutines for the menu
int main() { // where program starts, and loops back to after checking in/out
    char start;
    printf("\n\nWelcome to Kashyyk Hotel\n\n");
    printf("Press enter to continue.");
    fflush(stdin);
    scanf("%c", &start);
    mainMenu();
    return 0;
}

void mainMenu() { // main menu giving 4 options as to how to continue with the program
    char option;
    printf("\n\na) Check In\nb) Book a Dinner Table\nc) Check Out\nd) Quit");
    printf("\n\nWhat would you like to do?(a,b,c,d): ");
    fflush(stdin);
    scanf("%c", &option);
    switch (option) {
        case 'a':
            checkIn();
        case 'b':
            break;
        case 'c':
            checkOut();
        break;
        case 'd':
            quit();
        break;
        default:
            printf("Invalid Input");
        main();
        break;
    }
}

void quit() { // goes back to start of program if quit
    char answer;
    printf("Do you wish to exit from the main menu?(y/n): ");
    fflush(stdin);
    scanf("%c", &answer);
    if (answer == 'y' || answer == 'Y') {
        main();
    }
    else {
        mainMenu();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void checkIn() { // start of checking in, user inputs name and surname here and it creates the bookingID, it also calls all other check in functions
    int row;
    row = roomChoice() - 1;

    char firstName[30], surname[30], bookingID[33];

    printf("\nPlease enter your first name:");
    fflush(stdin);
    scanf("%s", &firstName);
    printf("Please enter your surname:");
    fflush(stdin);
    scanf("%s", &surname);
    strDetails[row][1] = firstName;
    strDetails[row][2] = surname;

    strcpy(bookingID, surname);
    char srandNumb[33];
    srand(time(NULL));
    int randNumb = (rand() % 899) + 100;
    sprintf(srandNumb,"%d", randNumb);
    strcat(bookingID, srandNumb);
    printf("\nYour bookingID is %s", bookingID);
    printf("\nPlease remember your bookingID, you will need it for checking out.\n", bookingID);
    strDetails[row][0] = bookingID;

    dateOfBirth(row);
    inputGuests(row);
    chooseBoard(row);
    lengthOfStay(row);
    newspaperChoice(row);

    main();
}

int roomChoice() { // this allows the user to pick a room or display the fact that there is no more rooms available
    int roomNumber = 0;
    bool available = false;
    for(int i = 0; i < 6; i++) {
        if(intDetails[i][3] == 0) {
            printf("\nRoom %d is available for $%d", intDetails[i][0], roomRates[i]);
            available = true;
        }
    }
    if (available) {
        do {
            printf("\nEnter which room you would like:");
            fflush(stdin);
            scanf("%d", &roomNumber);
        }while(roomNumber < 1 || roomNumber > 6);
    }else {
        printf("\nThere are no rooms available.");
        mainMenu();
    }
    return roomNumber;
}

void dateOfBirth(int row) { // this prompts the user to enter their date of birth and stores it in the 2d array
    do{printf("\nPlease enter your date of birth in format DD MM YYYY:");
        fflush(stdin);
        scanf("%d %d %d", &intDetails[row][4], &intDetails[row][5], &intDetails[row][6]);
    }while(intDetails[row][4] < 1 || intDetails[row][4] > 31 || intDetails[row][5] < 1 || intDetails[row][5] > 12 || intDetails[row][6] > 2006);
}

void inputGuests(int row) { // this gets the user to input how many people are staying and how many of those are children
    int totalGuests, children;
    printf("Please enter the amount of guests:");
    fflush(stdin);
    scanf("%d", &totalGuests);
    while(totalGuests < 1 || totalGuests > 4) {
        printf("you must have no more than 4 guests.\nEnter a valid amount of guests:");
        fflush(stdin);
        scanf("%d", &totalGuests);
    }
    printf("\nPlease enter the amount of children (16 or below):");
    fflush(stdin);
    scanf("%d", &children);
    while(children < 0 || children >= totalGuests) {
        printf("Invalid.\nPlease enter a valid amount of children:");
        fflush(stdin);
        scanf("%d", &children);
    }
    intDetails[row][1] = totalGuests - children;
    intDetails[row][2] = children;
}

void chooseBoard(int row) { // this lets the user pick which board type they would like
    char boardChoice;
    char * board;
    do {
        printf("\nDo you want a full-board meal($20) (F), half-board meal($15) (H) or a B&B($5) (B):");
        fflush(stdin);
        scanf("%s", &boardChoice);
        switch (boardChoice) {
            case 'F':
                board = "F";
                break;
            case 'H':
                board = "H";
                break;
            case 'B':
                board = "B";
                break;
            default:
                printf("Invalid option");
        }
    }while(boardChoice != 'F' && boardChoice != 'H' && boardChoice != 'B');
    strDetails[row][3] = board;
}

void lengthOfStay(int row) { // this allows the user to input how long they are staying for
    int stayLength = 0;
    do{printf("\nHow many days is your stay?");
        fflush(stdin);
        scanf("%d", &stayLength);
    }while(stayLength < 1);
    intDetails[row][3] = stayLength;
}

void newspaperChoice(int row) { // this lets the user decide whether they would like a daily newspaper or not
    char newsChoice;
    char * newspaper;
    do {
        printf("\nDo you want a daily newspaper ($5.50 one time payment)? Y/N:");
        fflush(stdin);
        scanf("%c", &newsChoice);
        switch (newsChoice) {
            case 'Y':
                newspaper = "T";
            break;
            case 'N':
                newspaper = "F";
            break;
            default:
                printf("Invalid option");
        }
    } while (newsChoice != 'Y' && newsChoice != 'N');
    strDetails[row][4] = newspaper;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////


void checkOut() { // this is the start of check out where it prints everything and calls all the other functions before working out the total price and displaying it
    int detailsRowNum = checkUser();
    float roomTotal = calculateRoomCost(detailsRowNum);
    printf("\n$%.2f - Room Cost\n- 10 percent discount for >65s -", roomTotal);
    float boardTotal = calculateBoardCost(detailsRowNum);
    printf("\n$%.2f - Board Cost\n- 50 percent discount for children -", boardTotal);
    float newspaperTotal = addNewspaperCost(detailsRowNum);
    if (newspaperTotal > 0) {
        printf("\n$%.2f - Additional Newspaper Cost", newspaperTotal);
    }
    printf("\n--------------------------------------------------");
    float total = roomTotal + boardTotal + newspaperTotal;
    printf("\nThe total cost is $%.2f", total);
    printf("\n\nPress enter to continue.");
    char answer;
    fflush(stdin);
    scanf("%c", &answer);
    removeData(detailsRowNum);
    mainMenu();
}

int checkUser() { // figures out which row of the data to use for the rest of the check out process
    char bookingID[33];
    int rowNum = 10;
    while (rowNum == 10) {
        printf("\n\nEnter booking ID to begin checking out: ");
        fflush(stdin);
        scanf("%s", &bookingID);
        for (int i = 0; i <= 5; i++) {
            if (strcmp(bookingID, strDetails[i][0]) == 0) {
                rowNum = i;
            }
        }
        if (rowNum == 10) {
            printf("\nYou entered an incorrect booking ID, try again.");
        }
    }
    printf("\nThe main user is %s %s.", strDetails[rowNum][1], strDetails[rowNum][2]);
    char answer;
    printf("\nPress enter to continue.");
    fflush(stdin);
    scanf("%c", &answer);
    return rowNum;
}

float calculateRoomCost(int row) { // this calculates the room cost for the whole stay
    float roomTotal = (float)roomRates[(intDetails[row][0]-1)];
    if(2024 - intDetails[row][6] > 65) { // 10% discount for >65s
        roomTotal *= 0.9;
    }
    roomTotal *= (float)intDetails[row][3];
    return roomTotal;
}

float calculateBoardCost(int row) { // this calculates the board cost for the whole stay
    char * boardChoice = strDetails[row][3];
    float boardTotal = 0;
    if(strcmp(boardChoice, "F") == 0) {
        boardTotal = ((float)intDetails[row][1] * (float)boardRates[0]) + ((float)intDetails[row][2] * (float)boardRates[0] * 0.5);
    }                  // ^ calculation for adults                              ^ calculation for children
    else if (strcmp(boardChoice, "H") == 0) {
        boardTotal = ((float)intDetails[row][1] * (float)boardRates[1]) + ((float)intDetails[row][2] * (float)boardRates[1] * 0.5);
    }                  // ^ calculation for adults                              ^ calculation for children
    else {
        boardTotal = ((float)intDetails[row][1] * (float)boardRates[2]) + ((float)intDetails[row][2] * (float)boardRates[2] * 0.5);
    }                  // ^ calculation for adults                              ^ calculation for children
    boardTotal = boardTotal * intDetails[row][3];
    return boardTotal;
}

float addNewspaperCost(int row) { // this adds the price of $5.50 if the user has had daily newspapers
    float newspaperTotal = 0.0;
    if (strDetails[row][4] == "T") {
        newspaperTotal = 5.5;
    }
    return newspaperTotal;
}

void removeData(int row) { // this clears the data of the user that has just checked out so the room becomes available for a new guest
    for(int i = 0; i < 5; i++) {
        strDetails[row][i] = "";
    }
    for(int i = 1; i < 7; i++) {
        intDetails[row][i] = 0;
    }
}
