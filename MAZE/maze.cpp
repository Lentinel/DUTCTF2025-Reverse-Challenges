#include <iostream>  
#include <cstdlib>
#include <cstring>

using namespace std;
int mapp[60][60];
void mkdata() {
    memset(mapp, 0, sizeof(mapp));
    int seed = 15532;
    srand(seed);
    for (int i = 1; i <= 50; i++)
        for (int j = 1; j <= i; j++)
            mapp[i][j] = rand() % 19492025;
}
void oops(string info) {
    cout << info;
    exit(-1);
}
int main() {
    cout << "Now you are in a maze. Figure out how to get the maximum:\n";
    mkdata();
    string a;
    cin >> a;
    if (a.size() != 49)
        oops("Are you lost in the maze???");
    else {
        int x, y;
        long long score = mapp[1][1];
        x = y = 1;
        for (int i = 0; i < a.size(); i++) {
            x += 1;
            if (a[i] != 'A' && a[i] != 'B' && a[i] != 'C')
                oops("Invalid movement! What are you doing?");
            else {
                switch (a[i]) {
                    case 'A':
                        y -= 1;
                        break;
                    case 'B':
                        y += 1;
                        break;
                    default:
                        break;
                }
                if (y <= 0)
                    oops("Perhaps you've come to the wrong place...");
            }
            score += mapp[x][y];
        }
        cout << "\nScore: " << score;
        cout << "\n\nWhat you've got is DUTCTF{" << a <<"}\n\n\n\n\n\n";
        system("pause");  
    return 0;
    }
}
