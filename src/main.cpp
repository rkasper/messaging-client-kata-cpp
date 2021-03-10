#include <iostream>
#include <fstream>

using namespace std;

void send_message(const string &to, const string &message);

int main(int argc, char *argv[]) {
    // TODO Make sure both args are present
    string to = argv[1];

    string message;
    if (argc > 2 && ((string)argv[2]).length() > 0) {
        message = argv[2];
    } else {
        // TODO Send error messages to cerr?
        cout << "Cannot send an email with no body." << endl;
        return 1;
    }

    // TODO Be consistent with logic. Should the action occur if the condition is true or if it's false?
    if (to.find('@') == string::npos) {
        cout << "Invalid email address: no at sign" << endl;
        return 1;
    } else {
        send_message(to, message);
    }

    return 0;
}

void send_message(const string &to,
                  const string &message) {
    // File manipulation code borrowed from https://www.guru99.com/cpp-file-read-write-open.html
    fstream fake_network;
    fake_network.open("/tmp/fake_network.txt", ios::out);
    if (!fake_network) {
        cout << "File not created!";
    } else {
        fake_network << "connect smtp" << endl;
        fake_network << "To: " << to << endl;
        fake_network << endl;
        fake_network << message << endl;
        fake_network << endl;
        fake_network << "disconnect" << endl;

        fake_network.close();
    }
}
