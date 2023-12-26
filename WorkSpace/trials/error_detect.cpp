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
                        stackDetect.push(openingtag);
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

vector<error_detect> int_errorDetection(const vector<string> &tokens, const string& input) {
    vector<error_detect> errors;
    stack<string> stackDetect;
    stack<int> stackIdx;
    stack<string> temp_stackDetect;
    stack<int> temp_stackIdx;
    string openingtag;
    string closingtag;
    int index_in_stack;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const string &token = tokens[i];
        if (token.front() == '<' && token.back() == '>') {
            if (token[1] == '/') {
                if (stackDetect.empty()) {
                    errors.emplace_back(-1, -1, tokens[i].length() , tokens[i].substr(2, token.length() - 3) , i , closing_tag_with_missing_opening_tag);
                    getErrorInfo(errors.back(),input);
                } else {
                    index_in_stack = stackIdx.top();
                    stackIdx.pop();
                    openingtag = stackDetect.top();

                    stackDetect.pop();
                    temp_stackDetect.push(openingtag);
                    //                  cout<<"temp_stackDetect "<<temp_stackDetect.top()<<endl<<endl;
                    temp_stackIdx.push(index_in_stack);
                    closingtag = token.substr(2, token.length() - 3);
                    //cout<<"openingtag "<<openingtag<<" closingtag "<<closingtag<<endl<<endl;

                    //cout << "before ";printStringStack(stackDetect);
                    //cout<<endl;
                    int flag = 1;
                    if (openingtag != closingtag) {

                        while(!stackDetect.empty()){
                            index_in_stack = stackIdx.top();
                            stackIdx.pop();
                            openingtag = stackDetect.top();
                            stackDetect.pop();
                            temp_stackDetect.push(openingtag);
                            temp_stackIdx.push(index_in_stack);
                            if (openingtag != closingtag) {
                                flag = 1;
                            }
                            else{
                                flag = 0;
                                temp_stackDetect.pop();
                                temp_stackIdx.pop();
                                break;
                            }
                        }
                        while(!temp_stackDetect.empty()){
                            stackDetect.push(temp_stackDetect.top());
                            temp_stackDetect.pop();
                            stackIdx.push(temp_stackIdx.top());
                            temp_stackIdx.pop();
                        }

                        if (flag == 1){errors.emplace_back(-1, -1, closingtag.length()+3, closingtag, i, closing_tag_with_missing_opening_tag);
                            //cout << "after ";printStringStack(stackDetect);
                            getErrorInfo(errors.back(),input);
                            continue;
                        }
                        /* stackIdx.push(index_in_stack);
                        stackDetect.push(openingtag);

                        errors.emplace_back(-1, -1, closingtag.length()+3, closingtag, i, closing_tag_with_missing_opening_tag);
                        getErrorInfo(errors.back(),input);
                        stackIdx.push(index_in_stack);
                        stackDetect.push(openingtag);
                        cout<< " error "<<errors.back().tagIdx <<" "<<index_in_stack<<" "<<errors.back().tagInfo<<" "<<errors.back().line_number<<endl;
                        */


                    }
                    else{
                        //stackIdx.pop();
                        //stackDetect.pop();
                        temp_stackDetect.pop();
                        temp_stackIdx.pop();
                    }
                }
            }

            else {
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
            getErrorInfo(errors.back(),input);
        }

    }
    /*while (!stackDetect.empty()) {

        int index_in_stack = stackIdx.top();
        stackIdx.pop();
       openingtag = stackDetect.top();
        stackDetect.pop();
       // if (openingtag != closingtag) {
          errors.emplace_back(-1, -1, openingtag.length()+2, openingtag,index_in_stack, opening_tag_with_missing_closing_tag);
         // getErrorInfo(errors.back(),input);
       // }

        else{
            for (size_t i = 0; i < errors.size(); ++i) {
                 for (size_t j = 0; j < errors.size(); ++j) {
                    if(errors[i].line_number== errors[j].line_number){errors.erase(errors.begin()+j);
                    cout<< "erase error "<<errors[j].tagIdx <<" "<<index_in_stack<<" "<<errors[j].tagInfo<<" "<<errors[j].line_number<<endl;
                    }
                 }
            }
        }
        */

    //}
    return errors;
}


void printStringStack(const stack<string>& s) {
    stack<string> tempStack = s; // Create a copy of the stack to avoid modifying the original
    while (!tempStack.empty()) {
        cout << tempStack.top() << " ";
        tempStack.pop();
    }
    cout << std::endl;
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
