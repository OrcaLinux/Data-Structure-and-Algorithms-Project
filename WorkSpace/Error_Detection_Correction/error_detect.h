#ifndef XML_ERROR_DETECTION_CORRECTION_H
#define XML_ERROR_DETECTION_CORRECTION_H

#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

enum error_type {
    incorrect_tag,
    empty_field,
    no_error,
    closing_tag_with_missing_opening_tag,
    opening_tag_with_missing_closing_tag
};

using namespace std;

class error_detect {
public:
    int offset;
    int line_number;
    int tagLength;
    string tagInfo;
    int tagIdx;
    error_type error;

    error_detect(int offset, int line_number, int tagLength, const string &tagInfo, int tagIdx, error_type error)
        : offset(offset), line_number(line_number), tagLength(tagLength), tagInfo(tagInfo), tagIdx(tagIdx), error(error) {}
};

vector<string> tokenizeFileFromTextInput(const string &textInput);
vector<string> tokenizeFileFromFileLoc(const string &fileLocation);
string FileToString(const string &fileLocation);
bool bool_errorDetection(const vector<string> &tokens);
vector<error_detect> int_errorDetection(const vector<string> &tokens);
void getErrorInfo(error_detect &error, const string &input);
string errorCorrect(error_detect &CurError, const string &input, vector<error_detect> &errors);

#endif // XML_ERROR_DETECTION_CORRECTION_H
