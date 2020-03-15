#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <vector>
#include <limits>
#include <stdio.h>
#include <ctype.h>
using namespace std;
#define t_val 100000 //100,000
#define num_hash_Functions 5

//This is a comparator for sorting the vector from highest value to lowest value
struct comp
{
    template<typename T>
    bool operator()(const T& l, const T& r) const{
        if (l.second != r.second){
            return l.second > r.second;
        }
        return l.first>r.first;
    }
};

//Get the min between two unsigned ints
unsigned min(unsigned x, unsigned y)
{
    return (x < y) ? x : y;
}


//takes in input which is a filepath and filename for what to call the file once the algorithm has ran
vector<pair<string, int>> CountMinSketch(string input, string filename)
{
    //Declare variables

    //Open the file
    ifstream file(input);
    //A hasher for the strings
    hash<string> hasher;
    //Starting string
    string str;
    //This is for debugging
    int counter = 0;
    //to save all the values
    unordered_map<string, int> umap;
    // initilize the matrix
    unsigned a[num_hash_Functions][t_val];
    // iterate over the text file
    while (getline(file, str)) {
        // a set for the words in the set
        set <string> set_of_words;
        istringstream iss(str);
        // do this while there are strings to read
        do {
            string subs;
            iss >> subs;

            //check to see if all characters are english letters, if not break out.
            int i = 0;
            bool isword = true;
            while(subs[i]){
                if(!isalpha(subs[i]))
                {
                    isword = false;
                    break;
                }
                i++;
            }
            if(!isword)
            {
                continue;
            }

            // increase each of the indexes for each of the words.
            set_of_words.insert(subs);
            a[0][hasher(subs + "QxLUF1bgIAdeQX") % t_val] += 1;
            a[1][hasher(subs + "bv5PehSMfV11Cd") % t_val] += 1;
            a[2][hasher(subs + "YYLmfY6IehjZMQ") % t_val] += 1;
            a[3][hasher(subs + "c11083b4b0a774") % t_val] += 1;
            a[4][hasher(subs + "08eac03b80adc3") % t_val] += 1;
        } while (iss);

        //get the list of the words that have been added in this string
        set<string>::iterator it = set_of_words.begin();

        while (it != set_of_words.end())
        {
            //set the highest amount possible for a minnumindex that way it will always chose the smaller
            unsigned minnumindex = numeric_limits<int>::max();
            string word = *it;

            //debugging
//            if( word == "repo")
//            {
//                int here;
//            }

            // get the minimum of the indexes
            minnumindex = min(minnumindex, a[0][hasher(word + "QxLUF1bgIAdeQX") % t_val]);
            minnumindex = min(minnumindex, a[1][hasher(word + "bv5PehSMfV11Cd") % t_val]);
            minnumindex = min(minnumindex, a[2][hasher(word + "YYLmfY6IehjZMQ") % t_val]);
            minnumindex = min(minnumindex, a[3][hasher(word + "c11083b4b0a774") % t_val]);
            minnumindex = min(minnumindex, a[4][hasher(word + "08eac03b80adc3") % t_val]);
            minnumindex = minnumindex;

            // update that word in the dictionary
            if(umap[word] == 0)
            {
                umap[word] = minnumindex;
            }
            else if(umap[word] > minnumindex)
            {
                umap[word] = minnumindex;
            }
            it++;
        }
        //this is for debugging
        if (counter % 100000 == 0)
            cout<< counter << endl;
        counter++;
    }
    // put all the data into a vector and then organize it using a set and write that to a file
    vector<pair<string, int>> answers;
    ofstream outfile;
    set<pair<string,int>, comp> set(umap.begin(), umap.end());
    outfile.open(filename + "Data.txt", ios_base::app);
    for ( auto const &pair: set) {
        //cout<< pair.first << "," << pair.second << '\n';
        outfile << pair.first << "," << pair.second << '\n';
        answers.push_back(make_pair(pair.first, pair.second));
    }

    outfile << '\n' << '\n' << "--------------------------NEW FIle--------------------------"<< '\n' << '\n';
    outfile.close();
    return answers;
}

template<typename T>
vector<T> slice (vector<T> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;
    vector<T> vec(first, last);
    return vec;
}

int main() {
    vector<pair<string, int>> Words_Count;
    vector<pair<string, int>> Total_Count;
    vector<pair<string, int>> Result;
    Total_Count = CountMinSketch("/Users/austinstephens/Desktop/clean_data/C/C1.txt", "C0");
    Result = slice(Total_Count, 0, 100);
    Words_Count.insert(Words_Count.end(), Result.begin(), Result.end());
    Total_Count =CountMinSketch("/Users/austinstephens/Desktop/clean_data/C/C1.txt", "C1");
    Result = slice(Total_Count, 0, 100);
    Words_Count.insert(Words_Count.end(), Result.begin(), Result.end());
    Total_Count =CountMinSketch("/Users/austinstephens/Desktop/clean_data/C/C2.txt", "C2");
    Result = slice(Total_Count, 0, 100);
    Words_Count.insert(Words_Count.end(), Result.begin(), Result.end());
    Total_Count =CountMinSketch("/Users/austinstephens/Desktop/clean_data/C/C3.txt", "C3");
    Result = slice(Total_Count, 0, 100);
    Words_Count.insert(Words_Count.end(), Result.begin(), Result.end());
    Total_Count =CountMinSketch("/Users/austinstephens/Desktop/clean_data/C/C4.txt", "C4");
    Result = slice(Total_Count, 0, 100);
    Words_Count.insert(Words_Count.end(), Result.begin(), Result.end());
    Total_Count =CountMinSketch("/Users/austinstephens/Desktop/clean_data/C/C5.txt", "C5");
    Words_Count.insert(Words_Count.end(), Result.begin(), Result.end());
    Total_Count =CountMinSketch("/Users/austinstephens/Desktop/clean_data/C/C6.txt", "C6");
    Result = slice(Total_Count, 0, 100);
    Words_Count.insert(Words_Count.end(), Result.begin(), Result.end());
    Total_Count =CountMinSketch("/Users/austinstephens/Desktop/clean_data/C/C7.txt", "C7");
    Result = slice(Total_Count, 0, 100);
    Words_Count.insert(Words_Count.end(), Result.begin(), Result.end());
    Total_Count =CountMinSketch("/Users/austinstephens/Desktop/clean_data/C/C8.txt", "C8");
    Result = slice(Total_Count, 0, 100);
    Words_Count.insert(Words_Count.end(), Result.begin(), Result.end());
    Total_Count =CountMinSketch("/Users/austinstephens/Desktop/clean_data/C/C9.txt", "C9");
    Result = slice(Total_Count, 0, 100);
    Words_Count.insert(Words_Count.end(), Result.begin(), Result.end());


    //Words_Count = CountMinSketch("../sample.txt","sameple");

    ofstream outfile;
    set<pair<string,int>, comp> set(Words_Count.begin(), Words_Count.end());
    outfile.open("TotalData.txt", ios_base::app);
    for ( auto const &pair: set) {
        outfile << pair.first << "," << pair.second << '\n';
        Words_Count.push_back(make_pair(pair.first, pair.second));
    }

    outfile << '\n' << '\n' << "--------------------------NEW FIle--------------------------"<< '\n' << '\n';
    outfile.close();
    return 0;

}


