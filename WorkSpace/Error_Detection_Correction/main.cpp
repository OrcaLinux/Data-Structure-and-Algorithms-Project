#include <iostream>
#include "error_detect.h"
using namespace std;

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
      string corrected = input;
for ( auto &error : errors) {
    corrected = errorCorrect(error,corrected,errors);
}
cout<<corrected <<endl<<endl;


    return 0;
}
