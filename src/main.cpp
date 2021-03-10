#include <iostream>
#include <fstream>

using namespace std;

int main(__unused int argc, char *argv[]) {
    string to = argv[1];
    string message = argv[2];

    if (to.find('@') == string::npos) {
        cout << "Invalid email address: no at sign" << endl;
    }
    else
    {
        // File manipulation code borrowed from https://www.guru99.com/cpp-file-read-write-open.html
        fstream fake_network;
        fake_network.open("/tmp/fake_network.txt", ios::out);
        if (!fake_network) {
            cout << "File not created!";
        }
        else {
            fake_network << "connect smtp" << endl;
            fake_network << "To: " << to << endl;
            fake_network << endl;
            fake_network << message << endl;
            fake_network << endl;
            fake_network << "disconnect" << endl;

            fake_network.close();
        }
    }

    return 0;
}
