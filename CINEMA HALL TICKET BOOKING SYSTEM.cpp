#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROWS 5
#define COLS 10

// Structure to hold seat information
typedef struct {
    int row;
    int col;
    int booked;
    char name[50];
} Seat;

Seat cinema[ROWS][COLS];

// Function prototypes
void initializeSeats();
void displaySeats();
void bookTicket();
void cancelTicket();
void showBookedTickets();
void totalCollection();
void menu();

// Global variable
int ticket_price = 150;

int main() {
    int choice;
    initializeSeats();

    while (1) {
        menu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: displaySeats(); break;
            case 2: bookTicket(); break;
            case 3: cancelTicket(); break;
            case 4: showBookedTickets(); break;
            case 5: totalCollection(); break;
            case 0:
                printf("\nThank you for using the Cinema Booking System!\n");
                exit(0);
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Initialize all seats to empty
void initializeSeats() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cinema[i][j].row = i + 1;
            cinema[i][j].col = j + 1;
            cinema[i][j].booked = 0;
            strcpy(cinema[i][j].name, "Empty");
        }
    }
}

// Display seat layout
void displaySeats() {
    printf("\n========= Cinema Hall Seat Layout =========\n");
    printf("  (O = Available, X = Booked)\n\n    ");
    for (int j = 0; j < COLS; j++)
        printf("%2d ", j + 1);
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf("Row %d ", i + 1);
        for (int j = 0; j < COLS; j++) {
            if (cinema[i][j].booked)
                printf(" X ");
            else
                printf(" O ");
        }
        printf("\n");
    }
}

// Book a ticket
void bookTicket() {
    int row, col;
    char name[50];

    displaySeats();
    printf("\nEnter row number (1-%d): ", ROWS);
    scanf("%d", &row);
    printf("Enter seat number (1-%d): ", COLS);
    scanf("%d", &col);
    getchar();

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        printf("\nInvalid seat selection!\n");
        return;
    }

    if (cinema[row - 1][col - 1].booked) {
        printf("\nSorry, this seat is already booked.\n");
        return;
    }

    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    cinema[row - 1][col - 1].booked = 1;
    strcpy(cinema[row - 1][col - 1].name, name);

    printf("\n✅ Seat successfully booked!\n");
    printf("Name: %s\nSeat: Row %d, Seat %d\nPrice: ₹%d\n", name, row, col, ticket_price);
}

// Cancel a ticket
void cancelTicket() {
    int row, col;
    displaySeats();
    printf("\nEnter row number to cancel (1-%d): ", ROWS);
    scanf("%d", &row);
    printf("Enter seat number to cancel (1-%d): ", COLS);
    scanf("%d", &col);

    if (row < 1 || row > ROWS || col < 1 || col > COLS) {
        printf("\nInvalid seat selection!\n");
        return;
    }

    if (!cinema[row - 1][col - 1].booked) {
        printf("\nThis seat is not booked yet.\n");
        return;
    }

    cinema[row - 1][col - 1].booked = 0;
    strcpy(cinema[row - 1][col - 1].name, "Empty");
    printf("\n❌ Ticket canceled successfully.\n");
}

// Show all booked tickets with details
void showBookedTickets() {
    int count = 0;
    printf("\n======= Booked Tickets =======\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (cinema[i][j].booked) {
                count++;
                printf("Seat: Row %d, Col %d | Name: %s\n",
                       cinema[i][j].row, cinema[i][j].col, cinema[i][j].name);
            }
        }
    }

    if (count == 0)
        printf("No tickets booked yet.\n");
    else
        printf("\nTotal booked tickets: %d\n", count);
}

// Show total collection and summary
void totalCollection() {
    int booked = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (cinema[i][j].booked)
                booked++;
        }
    }

    int total = booked * ticket_price;
    printf("\n======= Cinema Summary =======\n");
    printf("Total Seats: %d\n", ROWS * COLS);
    printf("Booked Seats: %d\n", booked);
    printf("Available Seats: %d\n", (ROWS * COLS) - booked);
    printf("Total Collection: ₹%d\n", total);
}

// Display main menu
void menu() {
    printf("\n=========================================\n");
    printf("🎟  CINEMA HALL TICKET BOOKING SYSTEM\n");
    printf("=========================================\n");
    printf("1. View Seat Layout\n");
    printf("2. Book Ticket\n");
    printf("3. Cancel Ticket\n");
    printf("4. Show Booked Tickets\n");
    printf("5. Total Collection\n");
    printf("0. Exit\n");
}