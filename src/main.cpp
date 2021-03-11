#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void send_email(const string &recipients, const string &message);

void send_im(const string &recipient, const string &message);

vector<string> split(string str, const string& token);

void validate_email_address_or_exit(const string &elem);

static const char *const fake_network_file_name = "/tmp/fake_network.txt";

int main(int argc, char *argv[]) {
    // TODO Make sure command-line args are present before you go asking for them.
    if ((string) argv[1] == "-im") { // It's an IM.
        send_im(argv[2], argv[3]);
    } else { // It's an email.
        if (argc > 2 && ((string) argv[2]).length() > 0) {
            send_email(argv[1], argv[2]);
        } else {
            // TODO Send error messages recipients cerr?
            cout << "Cannot send an email with no body." << endl;
            exit(1);
        }
    }

    return 0;
}

void send_email(const string &recipients,
                const string &message) {
    vector<string> addresses = split(recipients, ",");
    for (auto &elem : addresses) {
        validate_email_address_or_exit(elem);
    }

    // File manipulation code borrowed from https://www.guru99.com/cpp-file-read-write-open.html
    fstream fake_network;
    fake_network.open(fake_network_file_name, ios::out);
    if (!fake_network) {
        cout << "File not created!";
    } else {
        fake_network << "connect smtp" << endl;
        for (auto &elem : addresses) {
            fake_network << "To: " << elem << endl;
        }
        fake_network << endl;
        fake_network << message << endl;
        fake_network << endl;
        fake_network << "disconnect" << endl;

        fake_network.close();
    }
}

void send_im(const string &recipient,
             const string &message) {// File manipulation code borrowed from https://www.guru99.com/cpp-file-read-write-open.html
    validate_email_address_or_exit(recipient);

    fstream fake_network;
    fake_network.open(fake_network_file_name, ios::out);
    if (!fake_network) {
        cout << "File not created!";
    } else {
        fake_network << "connect chat" << endl;
        fake_network << "<" << recipient << ">:-> " << message << endl;
        fake_network << "disconnect" << endl;

        fake_network.close();
    }
}

void validate_email_address_or_exit(const string &elem) {
    if (elem.find('@') == string::npos) {
        cout << elem << ": Invalid email address: no at sign" << endl;
        exit(1);
    }
}

// Borrowed from https://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
vector<string> split(string str, const string& token) {
    vector<string> result;
    while (!str.empty()) {
        int index = str.find(token);
        if (index != string::npos) {
            result.push_back(str.substr(0, index));
            str = str.substr(index + token.size());
            if (str.empty()) {
                result.push_back(str);
            }
        } else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}