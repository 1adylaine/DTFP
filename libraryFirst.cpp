#include <iostream>

//attributes of book in struct
struct Book {
    std::string title;
    std::string author;
    int isbn;
    bool isBarrowed;
};

void displayMenu();
int getInt(const std::string& prompt, int min, int max);

int main(){
    displayMenu();
    int choice = getInt("Enter choice: ", 0, 3);
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
