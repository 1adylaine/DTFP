#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <queue>

//attributes of book in struct
const int genresCount = 5;
const int bookPerGenre = 10;

struct Book {
    std::string title, author;
    int isbn;
    bool isBarrowed;

     std::queue<int> waitingList;
};

struct User {
    int id;
    int barrowed[3];
    int count;
};

//
const std::string genreNames[genresCount] = {
    "Romance",
    "Mystery",
    "Fantasy",
    "Science Fiction",
    "Horror"
};

void displayMenu();
int getInt(const std::string& prompt);
void sampleBook(Book catalog[genresCount][bookPerGenre]);
void displayCatalog(Book catalog[genresCount][bookPerGenre]);

bool verifyUser(const User& user, int id);

Book* findBook(Book catalog[genresCount][bookPerGenre], int isbn);

void checkOutBook(Book catalog[genresCount][bookPerGenre], User& user);
void returnBook(Book catalog[genresCount][bookPerGenre], User& user);

void displayQueueRecords(Book catalog[genresCount][bookPerGenre]);

int main(){
    Book catalog[genresCount][bookPerGenre] = {};
    User user = {101, {0, 0, 0}, 0};
    std::vector<Book> barrowedBooks;

    sampleBook(catalog);
    int choice;
    do {
        displayMenu();
        choice = getInt("Enter choice: ");
        std::cout << std::endl;
        switch (choice) {
            case 1:
                std::system("clear");
                displayCatalog(catalog);
                break;
            case 2:
                std::system("clear");
                displayCatalog(catalog);
                checkOutBook(catalog, user);
                break;
            case 3:
                std::system("clear");
                returnBook(catalog, user);
                break;
            case 4:
                std::system("clear");
                displayQueueRecords(catalog);
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

void sampleBook(Book catalog[genresCount][bookPerGenre]){
    catalog[0][0] = {"title1", "author1", 1, false};
    catalog[0][1] = {"title2", "author2", 2, false};
    catalog[0][3] = {"title4", "author4", 4, false};
    catalog[0][4] = {"title5", "author5", 5, false};

    catalog[1][0] = {"title6", "author1", 6, false};
    catalog[1][1] = {"title7", "author2", 7, false};
    catalog[1][2] = {"title8", "author3", 8, false};
    catalog[1][3] = {"title9", "author4", 9, false};
    catalog[1][4] = {"title10", "author5", 10, false};

    catalog[2][0] = {"title11", "author1", 11, false};
    catalog[2][1] = {"title12", "author2", 12, false};
    catalog[2][2] = {"title13", "author3", 13, false};
    catalog[2][3] = {"title14", "author4", 14, false};
    catalog[2][4] = {"title15", "author5", 15, false};

    catalog[3][0] = {"title16", "author1", 16, false};
    catalog[3][1] = {"title17", "author2", 17, false};
    catalog[3][2] = {"title18", "author3", 18, false};
    catalog[3][3] = {"title19", "author4", 19, false};
    catalog[3][4] = {"title20", "author5", 20, false};

    catalog[4][0] = {"title21", "author1", 21, false};
    catalog[4][1] = {"title22", "author2", 22, false};
    catalog[4][2] = {"title23", "author3", 23, false};
    catalog[4][3] = {"title24", "author4", 24, false};
    catalog[4][4] = {"title25", "author5", 25, false};
}

void displayMenu(){
    std::cout << "\n===== LIBRARY CATALOG =====\n";
    std::cout << " [1] View catalog\n";
    std::cout << " [2] Check out book\n";
    std::cout << " [3] Return book\n";
    std::cout << " [4] View Queue Records\n";
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
    const int lineWidth = 80;
    const int titleW = 26, authorW = 18, isbnW = 12, statusW = 11;
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
                << " | " << std::setw(statusW) << (catalog[i][j].isBarrowed ? "[BORROWED]" : "[AVAILABLE]")
                << " |\n";
        }
        std::cout << std::string(lineWidth, '-') << "\n\n";
    }
}

bool verifyUser(const User& user, const std::string& prompt){
    int id = getInt(prompt);
    if(id != user.id) {
        std::cout << "User not found.\n";
        return false;
    }
    return true;
}

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

void checkOutBook(Book catalog[genresCount][bookPerGenre], User& user){
    if(!verifyUser(user, "Enter user ID to check out book: ")) return;

    if(user.count >= 3){
        std::cout << "Limit reached. Return a book first.\n";
        return;
    }
    
    int isbn = getInt("Enter ISBN of book to check out: ");
    Book* book = findBook(catalog, isbn);

    if(book == nullptr){
        std::cout << "Book not found.\n";
    }
    else if(book->isBarrowed){
         char choice;
    std::cout << "Book is already borrowed.\n";
    std::cout << "Would you like to join the waiting list? (Y/N): ";
    std::cin >> choice;

    if(choice == 'Y' || choice == 'y'){
        book->waitingList.push(user.id);
        std::cout << "Added to waiting list.\n";
    }
    }
    else {
        book->isBarrowed = true;
        user.barrowed[user.count] = isbn;
        user.count++;
        std::cout << "Book checked out successfully.\n";
    }
}

void returnBook(Book catalog[genresCount][bookPerGenre], User& user){
    if(!verifyUser(user, "Enter user ID to return book: ")) return;

    std::cout << "Borrowed Books ISBN code: \n";
    for(int i = 0; i < user.count; i++){
        std::cout << i + 1 << ". " << user.barrowed[i] << std::endl;
    }

    int isbn = getInt("\nEnter the ISBN of book you want to return: ");

    Book* book = findBook(catalog, isbn);
    if(book == nullptr){
        std::cout << "Book not found.\n";
    }
    for(int i = 0; i < user.count; i++){
        if(user.barrowed[i] == isbn){
            for(int j = i; j < user.count - 1; j++){
                user.barrowed[j] = user.barrowed[j + 1];
            }
            user.barrowed[user.count - 1] = 0;
            user.count--;

                if(!book->waitingList.empty()){
                int nextUser = book->waitingList.front();
                book->waitingList.pop();

                std::cout << "Book returned.\n";
                std::cout << "Book reserved for User ID: "
                        << nextUser << std::endl;
                }
                else{
                    book->isBarrowed = false;
                    std::cout << "Book returned and is now available.\n";
}
        }
    }
}

void displayQueueRecords(Book catalog[genresCount][bookPerGenre]){
    std::cout << "\n===== QUEUE RECORDS =====\n";

    for(int i = 0; i < genresCount; i++){
        for(int j = 0; j < bookPerGenre; j++){

            if(catalog[i][j].title.empty())
                continue;

            if(!catalog[i][j].waitingList.empty()){

                std::queue<int> temp =
                    catalog[i][j].waitingList;

                std::cout << "\nBook: "
                          << catalog[i][j].title
                          << " (ISBN: "
                          << catalog[i][j].isbn
                          << ")\n";

                std::cout << "Waiting Users: ";

                while(!temp.empty()){
                    std::cout << temp.front();

                    temp.pop();

                    if(!temp.empty())
                        std::cout << " -> ";
                }

                std::cout << std::endl;
            }
        }
    }
}
//Covered all basic function but no edge cases yet.

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