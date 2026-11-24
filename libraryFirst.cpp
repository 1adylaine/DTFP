#include <iostream>

//attributes of book in struct
const int genresCount = 5;
const int bookPerGenre = 10;

struct Book {
    std::string title, author;
    int isbn;
    bool isBarrowed;
};

const std::string genreNames[genresCount] = {
    "Romance",
    "Mystery",
    "Fantasy",
    "Science Fiction",
    "Horror"
};

void displayMenu();
int getInt(const std::string& prompt, int min, int max);
void sampleBook(Book catalog[genresCount][bookPerGenre]);
void displayCatalog(Book catalog[genresCount][bookPerGenre]);
void checkOutBook(Book catalog[genresCount][bookPerGenre]);

int main(){
    Book catalog[genresCount][bookPerGenre] = {};
    sampleBook(catalog);
   int choice;
    do {
        displayMenu();
        choice = getInt("Enter choice: ", 0, 3);
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
        }

    } while (choice != 0);
}

void sampleBook(Book catalog[genresCount][bookPerGenre]){
    catalog[0][0] = {"title1", "author1", 1, false};
    catalog[0][1] = {"title2", "author2", 2, false};
    catalog[0][3] = {"title3", "author3", 3, false};
    
}

void displayMenu(){
    std::cout << "===== LIBRARY CATALOG =====\n";
    std::cout << " [1] View catalog\n";
    std::cout << " [2] Check out book\n";
    std::cout << " [3] Return book\n";
    std::cout << " [0] Exit\n";
}

int getInt(const std::string& prompt, int min, int max){
    int num;
    while(true) {
        std::cout << prompt;
        if(std::cin >> num){
            std::cin.ignore();
            if(num >= min && num <= max) return num;
            std::cout << "Enter " << min << " to " << max << " only.\n";
        }
        else {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input! Try again.\n";
        }
    }
}


void displayCatalog(Book catalog[genresCount][bookPerGenre]){

    // ginawa kong mas organize na stress ako mag debug AHAHAHHAHAHHA
    for(int i = 0; i < genresCount; i++){
        std::cout << genreNames[i] << std::endl;
        for(int j = 0; j < bookPerGenre; j++){
           std::cout << "Title: " << catalog[i][j].title
                     << " | Author: " << catalog[i][j].author
                     << " | ISBN: " << catalog[i][j].isbn
                     << " | " << (catalog[i][j].isBarrowed ?  "[BORROWED]" : "[AVAILABLE]")
                     << " |" << std::endl;
        }
        std::cout<<std::endl;
    }
}

void checkOutBook(Book catalog[genresCount][bookPerGenre]) {
    int isbn;
    std::cout << "Enter ISBN of book to check out: ";
    std::cin >> isbn;

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
