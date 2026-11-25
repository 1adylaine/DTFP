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
Book* findBook(Book catalog[genresCount][bookPerGenre], int isbn);
int findUser(const std::vector<User>& user, int id);
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
                std::system("clear");
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

void sampleBook(Book catalog[genresCount][bookPerGenre]){
    catalog[0][0] = {"The Notebook", "Nicholas Sparks", 1, false};
    catalog[0][1] = {"It Ends with Us", "Colleen Hoover", 2, false};
    catalog[0][2] = {"Me Before You", "Jojo Moyes", 3, false};
    catalog[0][3] = {"The Fault in Our Stars", "John Green", 4, false};
    catalog[0][4] = {"After", "Anna Todd", 5, false};

    catalog[1][0] = {"Dracula", "Bram Stoker", 6, false};
    catalog[1][1] = {"Frankenstein", "Mary Shelley", 7, false};
    catalog[1][2] = {"Carrie", "Stephen King", 8, false};
    catalog[1][3] = {"It", "Stephen King", 9, false};
    catalog[1][4] = {"Coraline", "Neil Gaiman", 10, false};

    catalog[2][0] = {"Inferno", "Dan Brown", 11, false};
    catalog[2][1] = {"The Reversal", "Michael Connelly", 12, false};
    catalog[2][2] = {"In The Woods", "Tana French", 13, false};
    catalog[2][3] = {"Magpie Murders", "Anthony Horowits", 14, false};
    catalog[2][4] = {"The Cuckoo's Calling", "Robert Galbraith", 15, false};

    catalog[3][0] = {"Solaris", "Stanislaw Lem", 16, false};
    catalog[3][1] = {"2001", "Arthur C. Clarke", 17, false};
    catalog[3][2] = {"Wool", "Hugh Howey", 18, false};
    catalog[3][3] = {"Leviathan", "Scott Westerfeld", 19, false};
    catalog[3][4] = {"Robot", "Adam Wisniewski Snerg", 20, false};

    catalog[4][0] = {"Eragon", "Christopher Paolini", 21, false};
    catalog[4][1] = {"Stardust", "Neil Gaiman", 22, false};
    catalog[4][2] = {"Uprooted", "Naomi Novik", 23, false};
    catalog[4][3] = {"Legendbord", "Tracy Deonn", 24, false};
    catalog[4][4] = {"Graceling", "Kristin Cashore", 25, false};
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
                << " | " << std::setw(statusW) << (catalog[i][j].isBarrowed ? "[BORROWED]" : "[AVAILABLE]")
                << " |\n";
        }
        std::cout << std::string(lineWidth, '-') << "\n\n";
    }
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

int findUser(const std::vector<User>& user, int id){
    for(int i = 0; i < user.size(); i++){
        if(id == user[i].id){
            return i;
        }
    }
    return -1;
}

void checkOutBook(Book catalog[genresCount][bookPerGenre], std::vector<User>& user){
    int userId = getInt("Enter user ID to borrow a book: ");
    int userIndex = findUser(user, userId);

    if(userIndex == -1){
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
                book->waitingList.push(userId);
                std::cout << "Added to waiting list.\n";
                std::cout << "Queue number: " << book->waitingList.size() << std::endl;
                user.push_back({userId, {0, 0, 0}, 0});
            }
            return;
        }
        else {
            book->isBarrowed = true;
            std::cout << "Book checked out successfully.\n";
            user.push_back({userId, {isbn, 0, 0}, 1});
        }
        return;
    }

    if(user[userIndex].count >= 3){
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
            book->waitingList.push(user[userIndex].id);
            std::cout << "Added to waiting list.\n";
            std::cout << book->waitingList.front();
            std::cout << "Queue number: " << book->waitingList.size() << std::endl;
        }
        return;
    }
    else {
        book->isBarrowed = true;
        user[userIndex].barrowed[user[userIndex].count] = isbn;
        user[userIndex].count++;
        std::cout << "Book checked out successfully.\n";
    }
}

void returnBook(Book catalog[genresCount][bookPerGenre], std::vector<User>& user){
    int userId = getInt("Enter user ID to return a book: ");
    int userIndex = findUser(user, userId);

    if(userIndex == -1){
        std::cout << "User not found.\n";
        return;
    }

    std::cout << "Borrowed Books ISBN code: \n";
    for(int i = 0; i < user[userIndex].count; i++){
        std::cout << i + 1 << ". " << user[userIndex].barrowed[i] << std::endl;
    }

    int isbn = getInt("\nEnter the ISBN of book you want to return: ");

    Book* book = findBook(catalog, isbn);
    if(book == nullptr){
        std::cout << "Book not found.\n";
    }

    for(int i = 0; i < user[userIndex].count; i++){
        if(user[userIndex].barrowed[i] == isbn){
            for(int j = i; j < user[userIndex].count - 1; j++){
                user[userIndex].barrowed[j] = user[userIndex].barrowed[j + 1];
            }
            user[userIndex].barrowed[user[userIndex].count - 1] = 0;
            user[userIndex].count--;

            if(!book->waitingList.empty()){
                int nextUser = book->waitingList.front();
                book->waitingList.pop();

                std::cout << "Book returned.\n";
                std::cout << "Book reserved for User ID: " << nextUser << std::endl;
            }
            else {
                book->isBarrowed = false;
                std::cout << "Book returned.\n";
            }
            return;
        }
    }
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