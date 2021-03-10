#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    string to = "World!";
    if (argc > 1)
    {
        to = argv[1];
    }

    cout << "Hello, " << to << endl;

    return 0;
}
