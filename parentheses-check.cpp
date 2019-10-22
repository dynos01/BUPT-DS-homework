/*
 * License: GPLv3
 * BUPT DS homework: Parentheses Check
 * Tested under G++ 9.2.0, with minimal parameters
 * Author: Yinuo Deng <i@dyn.im>
*/

#include <iostream>
#include <string>

bool match(std::string exp) {
    int j = 0;
    std::string pSet = "()[]";
    char *myStack = new char[exp.length()];
    for (size_t i = 0; i < exp.length() && exp.length() > 0; i++) {
        if (pSet.find(exp[i]) == std::string::npos) continue;
        myStack[j] = exp[i];
        if (j == 0) j++;
        else if (myStack[j - 1] == '(' && myStack[j] == ')') j--;
        else if (myStack[j - 1] == '[' && myStack[j] == ']') j--;
        else j++;
    }
    delete [] myStack;
    return j == 0;
}

int main(void) {
    std::string exp;
    std::getline(std::cin, exp);
    std::cout << (match(exp) ? "Yes" : "No") << std::endl;
    return 0;
}
