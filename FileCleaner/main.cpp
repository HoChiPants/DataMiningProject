#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <chrono>
#include <algorithm>

namespace fs = std::experimental::filesystem;
using namespace std;

bool issymbol(char s) {
    return s == '.'
           || s == ','
           || s == '['
           || s == ']'
           || s == '{'
           || s == '}'
           || s == '+'
           || s == '='
           || s == '*'
           || s == '!'
           || s == '@'
           || s == '#'
           || s == '$'
           || s == '%'
           || s == '^'
           || s == '&'
           || s == '('
           || s == ')'
           || s == '-'
           || s == '_'
           || s == '<'
           || s == '>'
           || s == '<'
           || s == '?'
           || s == '/'
           || s == '\''
           || s == '"'
           || s == ';'
           || s == ':'
           || s == '0'
           || s == '1'
           || s == '2'
           || s == '3'
           || s == '4'
           || s == '5'
           || s == '6'
           || s == '7'
           || s == '8'
           || s == '9'
           || s == '`'
           || s == '~'
           || s == '@'
           || s == '#'
           || s == '$'
           || s == '%'
           || s == '^'
           || s == '&'
           || s == '*';
}

bool BothAreSpaces(char lhs, char rhs) {
    return (lhs == rhs) && (lhs == ' ');
}

void cleanWhitespace(string filename) {
    ifstream in("Temp" + filename);
    ofstream out;
    out.open("Clean" + filename);

    string line;
    while(getline(in, line)) {
        string::iterator new_end = std::unique(line.begin(), line.end(), BothAreSpaces);
        line.erase(new_end, line.end());

        // trim trailing spaces
        size_t endpos = line.find_last_not_of(" \t");
        size_t startpos = line.find_first_not_of(" \t");
        if( std::string::npos != endpos )
        {
            line = line.substr( 0, endpos+1 );
            line = line.substr( startpos );
        }
        else {
            line.erase(std::remove(std::begin(line), std::end(line), ' '), std::end(line));
        }

        // trim leading spaces
        startpos = line.find_first_not_of(" \t");
        if( string::npos != startpos )
        {
            line = line.substr( startpos );
        }

        if (! line.empty())
            out << line << endl;
    }

    in.close();
    out.close();

    fs::path dir = "Temp" + filename;
    fs::remove(dir);
}

int main(int argc, char** argv) {
    auto start = chrono::steady_clock::now();

    for(int i = 1; i < argc; i++) {
        string line;
        ifstream file(argv[i]);
        ofstream out;
        string outfilename = "Temp" + string(argv[i]);
        out.open(outfilename, ofstream::out);

        if (file.is_open()) {

            for (int i = 0; i < 8; i++)
                file.get();

            char back = file.get();
            char current = file.get();
            char forward;

            while(file.get(forward)) {
                if (current == '\n') {
                    if (back == '"' && forward == '"') {
                        out << tolower(current, locale());
                    }
                    else {
                        if(back != ' ' && forward != ' ')
                            out << ' ';
                    }
                } else if (issymbol(current)) {
                    if(back != ' ' && forward != ' ')
                        out << ' ';
                } else {
                    out << tolower(current, locale());
                }

                back = current;
                current = forward;
            }
            if(!issymbol(forward) && forward != ' ')
                out << tolower(forward, locale());

            file.close();
            out.close();

            cleanWhitespace(string(argv[i]));
            cout << argv[i] << " complete." << endl;
        }
        else {
            cout << "Unable to open file ";
            cout << argv[i] << endl;
        }
    }

    auto end = chrono::steady_clock::now();

    cout << "Elapsed time: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " seconds." << endl;
    return 0;
}
