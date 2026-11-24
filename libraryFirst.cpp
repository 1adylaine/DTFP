#include <iostream>
#include <iomanip>

//attributes of book in struct
const int genresCount = 5;
const int bookPerGenre = 10;

struct Book {
    std::string title, author;
    int isbn;
    bool isBarrowed;
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
void checkOutBook(Book catalog[genresCount][bookPerGenre]);

int main(){
    Book catalog[genresCount][bookPerGenre] = {};
    sampleBook(catalog);
    int choice;
    do {
        displayMenu();
        choice = getInt("Enter choice: ");
        switch (choice) {
            case 1:
                displayCatalog(catalog);
                std::cout << "\nPress Enter to return to menu...";
                std::cin.get();
                break;
            case 2:
                checkOutBook(catalog);
                break;
            case 3:
                /*code*/
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

    catalog[1][0] = {"title6", "author1", 1, false};
    catalog[1][1] = {"title7", "author2", 2, false};
    catalog[1][2] = {"title8", "author3", 3, false};
    catalog[1][3] = {"title9", "author4", 4, false};
    catalog[1][4] = {"title10", "author5", 5, false};

    catalog[2][0] = {"title11", "author1", 1, false};
    catalog[2][1] = {"title12", "author2", 2, false};
    catalog[2][2] = {"title13", "author3", 3, false};
    catalog[2][3] = {"title14", "author4", 4, false};
    catalog[2][4] = {"title15", "author5", 5, false};

    catalog[3][0] = {"title16", "author1", 1, false};
    catalog[3][1] = {"title17", "author2", 2, false};
    catalog[3][2] = {"title18", "author3", 3, false};
    catalog[3][3] = {"title19", "author4", 4, false};
    catalog[3][4] = {"title20", "author5", 5, false};

    catalog[4][0] = {"title21", "author1", 1, false};
    catalog[4][1] = {"title22", "author2", 2, false};
    catalog[4][2] = {"title23", "author3", 3, false};
    catalog[4][3] = {"title24", "author4", 4, false};
    catalog[4][4] = {"title25", "author5", 5, false};
}

void displayMenu(){
    std::cout << "===== LIBRARY CATALOG =====\n";
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
    // ginawa kong mas organize na stress ako mag debug AHAHAHHAHAHHA
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

void checkOutBook(Book catalog[genresCount][bookPerGenre]){
    int isbn = getInt("Enter ISBN of book to check out: ");

    for (int i = 0; i < genresCount; i++) {
        for (int j = 0; j < bookPerGenre; j++) {

            if (catalog[i][j].isbn == isbn) {

                if (catalog[i][j].isBarrowed) {
                    std::cout << "Book is already borrowed.\n";
                } else {
                    catalog[i][j].isBarrowed = true;
                    std::cout << "Book checked out successfully.\n";
                }

                return;
            }
        }
    }

    std::cout << "Book not found.\n";
}
//left on sample display.. to be continued iomanip for display.

/*required feature: 
    2d book storation - by shelves and 5 slot per shelves
    checking out function 
    returning book

    additional:
        other than hard coded book, an add book function. 
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