#include "error_detect.h"

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
                        errors.emplace_back(-1, -1, openingtag.length()+2, openingtag, index_in_stack, opening_tag_with_missing_closing_tag);
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
          errors.emplace_back(-1, -1, openingtag.length()+2, openingtag,index_in_stack, opening_tag_with_missing_closing_tag);
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

//function to correct all errors in XML file
//takes vector of error_detect and a const string
//returns modified string
string errorCorrect(error_detect& CurError, const string& input, vector<error_detect> &errors) {
    string correctedInput;
    int offset = 1;
    int line = 0;
    int flag1 = 0;  //flag to indicate if we corrected 1st type error or not
    int flag2 = 0;  //flag to indicate if we corrected 2nd type error or not
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '\n') {
            line++;
        }

        if (line == CurError.line_number) {
            if (offset == CurError.offset+1) {
                if (CurError.error == closing_tag_with_missing_opening_tag) {
                    // insert an opening tag right before the existing closing tag
                    correctedInput += "<" + CurError.tagInfo + ">";
                    flag1 =1;
                }

                if (CurError.error == opening_tag_with_missing_closing_tag) {
                    for(int j =-1; j< CurError.tagLength; j++ ) {
                        correctedInput += input[i];
                        i++;
                    }
                    //i--;    //to counteract the extra loop d
                    // insert a closing tag right after the existing opening tag
                    correctedInput = correctedInput + "</" + CurError.tagInfo + ">";
                    flag2 =1;
                }

            }
            offset++;
        }
        correctedInput += input[i];
    }
    if (flag1 == 1){
        //update all the error offsets for new corrected string
            for ( auto &error : errors) {
                if(CurError.offset < error.offset && CurError.line_number == error.line_number)
                error.offset += (CurError.tagLength)-1;
            }
        }
    if (flag2 == 1){
        //update all the error offsets for new corrected string (except our current error)
            for ( auto &error : errors) {
                if(CurError.offset < error.offset && CurError.line_number == error.line_number)
                error.offset += (CurError.tagLength)+1;
            }
    }
    return correctedInput;
}