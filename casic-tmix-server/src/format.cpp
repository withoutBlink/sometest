#include "format.h"

Format::Format(){}

void Format::RemoveSpace(std::string *inputstr){
    inputstr->erase(std::remove(inputstr->begin(),inputstr->end(),' '), inputstr->end());
}
