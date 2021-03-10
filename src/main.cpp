#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void send_message(const vector<string> &recipients, const string &message);
vector<string> split(string str, string token);

int main(int argc, char *argv[]) {
    // TODO Make sure both command-line args are present
    vector<string> recipients = split(argv[1], ",");

    string message;
    if (argc > 2 && ((string)argv[2]).length() > 0) {
        message = argv[2];
    } else {
        // TODO Send error messages recipients cerr?
        cout << "Cannot send an email with no body." << endl;
        return 1;
    }

    for(auto & elem : recipients) {
        if (elem.find('@') == string::npos) {
            cout << elem << ": Invalid email address: no at sign" << endl;
            return 1;
        }
    }

    send_message(recipients, message);

    return 0;
}

void send_message(const vector<string> &recipients,
                  const string &message) {
    // File manipulation code borrowed from https://www.guru99.com/cpp-file-read-write-open.html
    fstream fake_network;
    fake_network.open("/tmp/fake_network.txt", ios::out);
    if (!fake_network) {
        cout << "File not created!";
    } else {
        fake_network << "connect smtp" << endl;
        for(auto & elem : recipients) {
            fake_network << "To: " << elem << endl;
        }
        fake_network << endl;
        fake_network << message << endl;
        fake_network << endl;
        fake_network << "disconnect" << endl;

        fake_network.close();
    }
}

// Borrowed from https://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
vector<string> split(string str, string token){
    vector<string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
    return result;
}