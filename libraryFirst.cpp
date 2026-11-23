#include <iostream>

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
int getInt(const std::string& prompt, int min, int max);
void sampleBook(Book catalog[genresCount][bookPerGenre]);
void displayCatalog(Book catalog[genresCount][bookPerGenre]);

int main(){
    Book catalog[genresCount][bookPerGenre] = {};
    sampleBook(catalog);
    displayMenu();
    int choice = getInt("Enter choice: ", 0, 3);

    switch (choice)
    {
        case 1:
            displayCatalog(catalog); 
            break;
        case 2:
            /* code */
            break;
        case 3:
        /* code */
        break;
        default:
            break;
    }
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
    for(int i = 0; i < 1; i++){
        std::cout << genreNames[i] << std::endl;
        std::cout << "Title | Author | ISBN " << std::endl;
        for(int j = 0; j < 3; j++){
            std::cout << catalog[i][j].title << " | " << catalog[i][j].author << " | " << catalog[i][j].isbn << std::endl;
        }
    }
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
