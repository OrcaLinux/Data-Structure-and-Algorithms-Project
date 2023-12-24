#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

enum error_type { incorrect_tag, empty_field, no_error, closing_tag_with_missing_opening_tag , opening_tag_with_missing_closing_tag};

using namespace std;

class error_detect {
public:
    int offset ;
    int line_number ;
    int tagLength ;
    string tagInfo ;
    int tagIdx ;
    error_type error;

    error_detect(int offset, int line_number, int tagLength, const string &tagInfo, int tagIdx, error_type error)
        : offset(offset), line_number(line_number), tagLength(tagLength), tagInfo(tagInfo), tagIdx(tagIdx), error(error) {}
};

vector<string> tokenizeFileFromTextInput(const string &textInput) {
    vector<string> tokens;
    bool insideTag = false;

    for (char c : textInput) {
        if (c == '<') {
            tokens.push_back(string(1, c));
            insideTag = true;
        } else if (c == '>') {
            tokens.back() += c;
            insideTag = false;
        } else if (insideTag)
            tokens.back() += c;
    }

    return tokens;
}

    vector <string> tokenizeFileFromFileLoc( const string& fileLocation ){
        vector <string> tokens ;
        bool insideTag = false;
        fstream fs;
        fs.open(fileLocation);
        if (!fs.is_open()) return tokens; //error opening file, maybe here add sth so an error msg appears in gui
        string line;
        while(getline(fs,line)){
             for (char c : line){
                  if(c == '<'){
                       tokens.push_back(string(1,c));
                       insideTag = true;
                    }

                  else if(c == '>'){
                        tokens.back() += c;
                        insideTag = false;
                    }

                  else if (insideTag) tokens.back() += c;
             }
        }
        fs.close();
        return tokens;
}

string FileToString(const string& fileLocation) {
    ifstream fileStream(fileLocation);


    ostringstream oss;
    oss << fileStream.rdbuf(); // Read the entire file into the stringstream
    fileStream.close();

    return oss.str();
}

bool bool_errorDetection(const vector<string> &tokens) {
    stack<string> stackDetect;
    for (const string &token : tokens) {
        if (token.front() == '<' && token.back() == '>') {
            if (token[1] == '/') {
                if (stackDetect.empty()) {
                    return false; // detected an error: closing tag without an opening tag
                } else {
                    string openingtag = stackDetect.top();
                    stackDetect.pop();
                    string closingtag = token.substr(2, token.length() - 3);
                    if (openingtag != closingtag) {
                        return false; // mismatched opening and closing tags
                    }
                }
            } else {
                stackDetect.push(token.substr(1, token.length() - 2));
            }
        }
    }
    return stackDetect.empty();
}

vector<error_detect> int_errorDetection(const vector<string> &tokens) {
    vector<error_detect> errors;
    stack<string> stackDetect;
    stack<int> stackIdx;
    string openingtag;
    string closingtag;
    int index_in_stack;

    for (size_t i = 0; i < tokens.size(); ++i) {
        const string &token = tokens[i];

        if (token.front() == '<' && token.back() == '>') {
            if (token[1] == '/') {
                if (stackDetect.empty()) {
                    errors.emplace_back(-1, -1, tokens[i].length() , tokens[i].substr(2, token.length() - 3) , i , closing_tag_with_missing_opening_tag);
                } else {
                    index_in_stack = stackIdx.top();
                    stackIdx.pop();
                    openingtag = stackDetect.top();
                    stackDetect.pop();
                    closingtag = token.substr(2, token.length() - 3);

                    if (openingtag != closingtag) {
                        errors.emplace_back(-1, -1, openingtag.length(), openingtag, index_in_stack, opening_tag_with_missing_closing_tag);
                    }
                }
            } else {
                stackIdx.push(i);
                stackDetect.push(token.substr(1, token.length() - 2));
            }
        }
    }

    while (!stackDetect.empty()) {

        int index_in_stack = stackIdx.top();
        stackIdx.pop();
        openingtag = stackDetect.top();
        stackDetect.pop();
        if (openingtag != closingtag) {
          errors.emplace_back(-1, -1, openingtag.length(), openingtag,index_in_stack, opening_tag_with_missing_closing_tag);
        }

    }

    return errors;
}

void getErrorInfo(error_detect& error, const string& input) {
    int idx = 0;
    error.line_number = 0;
    error.offset = 0;

    for (size_t i = 0; i < input.size(); ++i) {
        char c = input[i];
        error.offset++;

        if (c == '\r') {
            continue;  // Skip carriage return
        }

        if (c == '\n') {
            error.line_number++;
            error.offset = 0;
        }
        if (c == '<'){
            if (idx == error.tagIdx){
                break;
            }
            idx++;
        }

    }
}




int main() {
   // string input = "This</k><mamamia> <b>is some<tag>text</tag><anotherTag><n>tag</anotherTag> inside.";

    vector<string> tok = tokenizeFileFromFileLoc("file.txt");
    for (string &t : tok) {
        cout << t << endl;
    }
    string input = FileToString("file.txt");
    if (!bool_errorDetection(tok)) {
        cout << "There is an error in the tags." << endl;
    } else {
        cout << "No tag errors found." << endl;
    }

    vector<error_detect> errors = int_errorDetection(tok);

    for ( auto &error : errors) {
    getErrorInfo(error, input);
    cout << "Error type: " << error.error << ", Line: " << error.line_number << ", Offset: " << error.offset
         << ", Tag Length: " << error.tagLength << ", Tag Info: " << error.tagInfo << ", Tag Index: " << error.tagIdx << endl;
}


    return 0;
}
