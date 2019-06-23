#include "String.h"
#include <cstdlib>
#include <ctime>
#include <sstream>

using std::vector;
using std::string;

vector<string> splitString(const string& value, char seperator)
{
    vector<string> splitedStrings;

    size_t currentPos = 0;
    while(true)
    {
        size_t nextPos = value.find(seperator, currentPos);
        if (nextPos == string::npos)
        {
            string currentString = value.substr(currentPos);
            if(currentString != "")
            {
                splitedStrings.push_back(currentString);
            }

            break;
        
        }
        string currentString = value.substr(currentPos,nextPos-currentPos);
        splitedStrings.push_back(currentString);
        currentPos = nextPos + 1;    
    }

    return splitedStrings;
}

std::string  randomString(const std::string& candidate, int32_t length)
{
    srand48(static_cast<uint32_t>(time(0)));

    std::string result;
    for( int32_t index=0; index != length; ++ index)
    {
        int32_t charIndex = rand() % candidate.size();
        result.push_back(candidate[charIndex]);
    }

    return result;
}

std::string itos(int32_t number)
{
    std::ostringstream numberConverter;
    numberConverter << number;

    return numberConverter.str();
}