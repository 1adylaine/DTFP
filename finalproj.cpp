#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <queue>

//fixed side for the 2D array of books sorted by genre.
const int genresCount = 5;
const int bookPerGenre = 10;

//Rebresents a book in the library catalog with its attributes;
struct Book {
    std::string title, author;
    int isbn;
    bool isBorrowed;

    std::queue<int> waitingList; //queque for borrowing currently unavailable book.
};

//Represents users who borrows and returns book with a limit.
struct User {
    int id;
    int borrowed[3];
    int count;
};

//fixed array of sample genre of books.
const std::string genreNames[genresCount] = {
    "Romance",
    "Horror",
    "Mystery",
    "Science Fiction",
    "Fantasy"
};

void displayMenu(); //Displays the main menu of library system.
int getInt(const std::string& prompt); //gets and validates the integer input from user.
void sampleBook(Book catalog[genresCount][bookPerGenre]); //predefined sample books stored in the 2d.
void displayCatalog(Book catalog[genresCount][bookPerGenre]); //Displays data in user-friendly way.

Book* findBook(Book catalog[genresCount][bookPerGenre], int isbn); //for accessing the book in the 2d when barrowing and returning
int findUser(const std::vector<User>& user, int id); //find user used for multiple process such as assign the book and putting limit.
void addBarrowed(User& u, int isbn); //records the barrowed book to the user.

void checkOutBook(Book catalog[genresCount][bookPerGenre], std::vector<User>& user);
void returnBook(Book catalog[genresCount][bookPerGenre], std::vector<User>& user);

int main(){
    Book catalog[genresCount][bookPerGenre] = {};
    std::vector<User> users;

    sampleBook(catalog);
    int choice;
    do {
        displayMenu();
        choice = getInt("Enter choice: ");
        std::cout << std::endl;
        switch (choice) {
            case 1:
                std::system("clear"); //cls for windows
                displayCatalog(catalog);
                break;
            case 2:
                std::system("clear");
                displayCatalog(catalog);
                checkOutBook(catalog, users);
                break;
            case 3:
                std::system("clear");
                returnBook(catalog, users);
                break;
            case 0:
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Range 0 - 3 only. Try again.\n";
                break;
        }

    } while (choice != 0);
}

void displayMenu(){
    std::cout << "\n===== LIBRARY CATALOG =====\n";
    std::cout << " [1] View catalog\n";
    std::cout << " [2] Check out book\n";
    std::cout << " [3] Return book\n";
    std::cout << " [0] Exit\n";
}

int getInt(const std::string& prompt) {
    int num;
    while (true) {
        std::cout << prompt;
        if (std::cin >> num) {
            std::cin.ignore(1000, '\n');
            return num;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid! Try again.\n";
    }
}

void displayCatalog(Book catalog[genresCount][bookPerGenre]){
    //for the display spaces formating.
    const int lineWidth = 86;
    const int titleW = 26, authorW = 24, isbnW = 12, statusW = 11;
    for(int i = 0; i < genresCount; i++){
        int inner = lineWidth - 2;
        int space = inner - genreNames[i].length();
        int left = space / 2;
        int right = space - left;
        
        std::cout << std::string(lineWidth, '=') << "\n";
        std::cout << "|" << std::string(left, ' ') << genreNames[i] << std::string(right, ' ') << "|\n";
        std::cout << std::string(lineWidth, '=') << "\n";

        std::cout << std::left
            << "| " << std::setw(titleW)  << "Title"
            << " | " << std::setw(authorW) << "Author"
            << " | " << std::setw(isbnW)   << "ISBN"
            << " | " << std::setw(statusW) << "Status" << " |\n";
        std::cout << std::string(lineWidth, '-') << "\n";
        for(int j = 0; j < bookPerGenre; j++){
            if (catalog[i][j].title.empty()) continue;
            std::cout << std::left
                << "| " << std::setw(titleW)  << catalog[i][j].title
                << " | " << std::setw(authorW) << catalog[i][j].author
                << " | " << std::setw(isbnW)   << catalog[i][j].isbn
                << " | " << std::setw(statusW) << (catalog[i][j].isBorrowed ? "[BORROWED]" : "[AVAILABLE]")
                << " |\n";
        }
        std::cout << std::string(lineWidth, '-') << "\n\n";
    }
}

//for accessing the book using ISBN when users checks out or returns them.
Book* findBook(Book catalog[genresCount][bookPerGenre], int isbn){
    if(isbn == 0) return nullptr;
    for (int i = 0; i < genresCount; i++){
        for (int j = 0; j < bookPerGenre; j++){
            if (catalog[i][j].isbn == isbn) {
                return &catalog[i][j];
            }
        }
    }
    return nullptr;
}

//find the user and access them by returning their index position or -1 for not existing users.
int findUser(const std::vector<User>& user, int id){
    for(int i = 0; i < user.size(); i++){
        if(id == user[i].id){
            return i;
        }
    }
    return -1;
}

//records the barrowed book to the user. Use for checkout and reused again in queque process.
void addBarrowed(User& user, int isbn){
    user.borrowed[user.count] = isbn;
    user.count++;
}

void checkOutBook(Book catalog[genresCount][bookPerGenre], std::vector<User>& user){
    int userId = getInt("Enter user ID to borrow a book: ");
    int userIndex = findUser(user, userId);

    //adds the user to the users vector if new.
    if (userIndex == -1) {
        user.push_back({userId, {0, 0, 0}, 0});
        userIndex = user.size() - 1;
    }

    char answer;
    do {
        if(user[userIndex].count >= 3){ // 3 IS MORETHAN ENOUGH
            std::cout << "Limit reached. Return a book first.\n";
            return;
        }
        
        int isbn = getInt("\nEnter ISBN of book to check out: ");
        Book* book = findBook(catalog, isbn);

        if(book == nullptr){
            std::cout << "Book not found.\n\n";
        }
        else if(book->isBorrowed){ //uses queque and lines up user to borrow the book next if its currently unavailable.
            std::cout << "Book is already borrowed.\n\n";
            std::cout << "Would you like to join the waiting list? (Y/N): "; // checking if willing to wait habang nasa iba pa
            std::cin >> answer;

            if(answer == 'Y' || answer == 'y'){ 
                book->waitingList.push(userId);
                std::cout << "Added to waiting list.\n";
                std::cout << "--- Queue number: " << book->waitingList.size() << " ---\n\n";
            }
        }
        else {
            book->isBorrowed = true;
            addBarrowed(user[userIndex], isbn);
            std::cout << "Book checked out successfully.\n\n";
        }

        if(user[userIndex].count < 3){
            std::cout << "Borrow another book? (Y/N): ";
            std::cin >> answer;
        }
    }while(answer == 'Y' || answer == 'y');
}

void returnBook(Book catalog[genresCount][bookPerGenre], std::vector<User>& user){
    int userId = getInt("Enter user ID to return a book: ");
    int userIndex = findUser(user, userId);

    if(userIndex == -1){
        std::cout << "User not found.\n";
        return;
    }

    std::cout << "Borrowed Books ISBN code: \n";
    //return to main menu if a user with no borrowed books try the return option.
    if(user[userIndex].count == 0){
        std::cout << "No books to return.\n";
        return;
    }
    //displays the list of borrowed books of the user.
    for(int i = 0; i < user[userIndex].count; i++){
        std::cout << i + 1 << ". " << user[userIndex].borrowed[i] << std::endl;
    }

    char answer;
    do {
        answer = 'N';
        int isbn = getInt("\nEnter the ISBN of book you want to return: ");

        Book* book = findBook(catalog, isbn);

        //ask the user to try again if they input invalid book ISBN.
        if(book == nullptr){
            std::cout << "Book not found.\n\n";
            std::cout << "Do you want to try again? [Y/N]: ";
            std::cin >> answer;
        }

        //remove the return book from the users array of borrowed book by shifting their position.
        for(int i = 0; i < user[userIndex].count; i++){
            if(user[userIndex].borrowed[i] == isbn){
                for(int j = i; j < user[userIndex].count - 1; j++){
                    user[userIndex].borrowed[j] = user[userIndex].borrowed[j + 1];
                }
                user[userIndex].borrowed[user[userIndex].count - 1] = 0;
                user[userIndex].count--;

                //checks if the book have a waiting list to give the book to that next person using the FIFO function.
                if(!book->waitingList.empty()){
                    int nextUser = book->waitingList.front();
                    int userIndex = findUser(user, nextUser);

                    //returns to main menu if the waited list user already reach the maximum in borrowing book.
                    if(user[userIndex].count = 3){ 
                        return;
                    }

                    book->waitingList.pop(); //removes the first one in from the waitlist.

                    std::cout << "Book returned.\n\n";
                    std::cout << "Book passed to the next person on the waiting list: " << nextUser << std::endl;
                    addBarrowed(user[userIndex], isbn);
                    return;
                }
                else {
                    book->isBorrowed = false;
                    std::cout << "Book returned.\n\n";
                    //ask the user if they want to return a book again while they still have remaining borrowed book.
                    if(user[userIndex].count != 0){
                        std::cout << user[userIndex].count <<" remaining barrowed book. Do you want to return another book? [Y/N]: ";
                        std::cin >> answer;
                    }
                    else {
                        return;
                    }
                }
            }
        }
    }while(answer == 'Y' || answer == 'y');
    
    return;
}

void sampleBook(Book catalog[genresCount][bookPerGenre]){
    catalog[0][0] = {"The Notebook", "Nicholas Sparks", 1001, false};
    catalog[0][1] = {"It Ends with Us", "Colleen Hoover", 1002, false};
    catalog[0][2] = {"Me Before You", "Jojo Moyes", 1003, false};
    catalog[0][3] = {"The Fault in Our Stars", "John Green", 1004, false};
    catalog[0][4] = {"After", "Anna Todd", 1005, false};

    catalog[1][0] = {"Dracula", "Bram Stoker", 2001, false};
    catalog[1][1] = {"Frankenstein", "Mary Shelley", 2002, false};
    catalog[1][2] = {"Carrie", "Stephen King", 2003, false};
    catalog[1][3] = {"It", "Stephen King", 2004, false};
    catalog[1][4] = {"Coraline", "Neil Gaiman", 2005, false};

    catalog[2][0] = {"Inferno", "Dan Brown", 3001, false};
    catalog[2][1] = {"The Reversal", "Michael Connelly", 3002, false};
    catalog[2][2] = {"In The Woods", "Tana French", 3003, false};
    catalog[2][3] = {"Magpie Murders", "Anthony Horowits", 3004, false};
    catalog[2][4] = {"The Cuckoo's Calling", "Robert Galbraith", 3005, false};

    catalog[3][0] = {"Solaris", "Stanislaw Lem", 4001, false};
    catalog[3][1] = {"2001", "Arthur C. Clarke", 4002, false};
    catalog[3][2] = {"Wool", "Hugh Howey", 4003, false};
    catalog[3][3] = {"Leviathan", "Scott Westerfeld", 4004, false};
    catalog[3][4] = {"Robot", "Adam Wisniewski Snerg", 4005, false};

    catalog[4][0] = {"Eragon", "Christopher Paolini", 5001, false};
    catalog[4][1] = {"Stardust", "Neil Gaiman", 5002, false};
    catalog[4][2] = {"Uprooted", "Naomi Novik", 5003, false};
    catalog[4][3] = {"Legendbord", "Tracy Deonn", 5004, false};
    catalog[4][4] = {"Graceling", "Kristin Cashore", 5005, false};
}
//Version number 3

/*required feature: 
    2d book storation - by shelves and 5 slot per shelves -> change to by genre
    checking out function -> done MVP
    returning book -> done MVP

    additional:
        other than hard coded book, an add book function. -> aborted
        search function that then has a check out as sub-function. 

    advance:
        different types of displaying. "sorting" 
*/

/*To do:
    6.	Library Catalog: Create a program to manage a library catalog. 
    Use a struct to represent books 
    with attributes like title, author, and ISBN. 
    Use a 2D array to store multiple books and 
    implement functions for checking out and returning books. 
*/

/*Checkings:
    check runtime
*/