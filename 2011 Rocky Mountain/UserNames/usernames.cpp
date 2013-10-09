#include <iostream>
#include <cctype>
#include <map>

using namespace std;

int main() {
    int N, M, ct = 0;
    while(cin >> N >> M && N && M && ++ct) {
        map<string, int> namesDB;
        string line;
        getline(cin, line);
        cout << "Case " << ct << endl;
        for (int i = 0; i < N; ++i)
        {
            string user = "";
            getline(cin, line);
            int sep = line.find_last_of(" ");
            for (int i = 0; i < sep; ++i) {
                if (islower(tolower(line[i]))) {
                    user += tolower(line[i]);
                    break;
                }
            }
            for (int i = sep; i < line.length() && user.length() < M; ++i) {
                if (islower(tolower(line[i]))) {
                    user += tolower(line[i]);
                }
            }
            map<string, int>::iterator userIt = namesDB.find(user);
            if (userIt == namesDB.end()) {
                namesDB[user] = 0;
                cout << user << endl;
            }
            else {
                userIt->second++;
                if ((userIt->second < 10 && user.length() == M) || (userIt->second >= 10 && user.length() == (M -1)))
                    user = user.substr(0, user.length()-1);
                else if (userIt->second >= 10 && user.length() == M)
                    user = user.substr(0, user.length()-2);
                cout << user << userIt->second << endl;
            }
        }
    }
}