#include <iostream>
#include <string>

using namespace std;

enum Color {RED, BLUE, BABY_SHIT_GREEN};

typedef struct MyStruct {

    private: string firstName     = "John";
    private: string lastName      = "Titor";
    private: int    age           = 38;
    private: Color favouriteColor = BABY_SHIT_GREEN;

    public: string getName() {
        printf("My name is %s %s\n", this->firstName, this->lastName);
    }

    public: string getAge() {
        printf("I am %d years old\n", this->age);
    }
};

int main() {
    MyStruct ms;
    ms.getName();
    ms.getAge();

    ms.age = 20; // Throws error since it is private
}