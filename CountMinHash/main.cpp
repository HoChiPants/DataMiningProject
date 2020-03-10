#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <iterator>
#include <sstream>
using namespace std;
#define t_val 25
#define num_hash_Functions 5

//Self made hash Function to always get the same results for our tests
// takes in word, two prime numbers, then mods it to be the size of the array
int hashFun(string word, int num1, int num2)
{
    long val;
    for (string::size_type i = 0; i < word.size(); i++){
        val += (long(word[i]) * num1 * num2);
    }
    val = abs(val % t_val);
    return val; // or return h % C;
}

int CountMinSketch(string input)
{
    //reads the file
    ifstream file(input);
    string str;
    set <string> set_of_words;

    int a[num_hash_Functions][t_val];

    while (std::getline(file, str)) {

        istringstream iss(str);
        do {
            string subs;
            iss >> subs;

            int y0 = hashFun(subs, 4603, 3181);
            int y1 = hashFun(subs, 3407, 1789);
            int y2 = hashFun(subs, 13, 2693);
            int y3 = hashFun(subs, 2213, 4817);
            int y4 = hashFun(subs, 3119, 4441);

            set_of_words.insert(subs);
            a[0][y0] += 1;
            a[1][y1] += 1;
            a[2][y2] += 1;
            a[3][y3] += 1;
            a[4][y4] += 1;
        } while (iss);
        set<std::string>::iterator it = set_of_words.begin();
        int minhash;
        while (it != set_of_words.end())
        {
            minhash = min(a[0][hashFun(*it, 4603, 3181)], a[1][hashFun(*it, 3407, 1789)]);
            minhash = min(minhash, a[2][hashFun(*it, 13, 2693)]);
            minhash = min(minhash, a[3][hashFun(*it, 2213, 4817)]);
            minhash = min(minhash, a[4][hashFun(*it, 3119, 4441)]);
            // Print the element
            cout << "Word: \t" << (*it) << "\t" << "Value: " << minhash << endl;
            //Increment the iterator
            it++;
        }
    }
    return 1;
}

int main() {
    CountMinSketch("sample.txt");
}
