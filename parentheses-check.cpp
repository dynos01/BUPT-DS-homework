/*
 * License: GPLv3
 * BUPT DS homework: Parentheses Check
 * Tested under G++ 9.2.0, with minimal parameters
 * Author: Yinuo Deng <i@dyn.im>
*/

#include <iostream>
#include <string>
#ifdef _WIN32
#include "windows.h"
#endif

std::string mark(std::string exp) {
    size_t j = 0;
    std::string pSet = "()[]", ret = std::string(exp.length(), ' ');
    char *myStack = new char[exp.length()];
    size_t *indexStack = new size_t[exp.length()];
    for (size_t i = 0; i < exp.length() && exp.length() > 0; i++) {
        if (pSet.find(exp[i]) == std::string::npos) continue;
        myStack[j] = exp[i], indexStack[j] = i;
        if (j != 0 && myStack[j - 1] == '(' && myStack[j] == ')') j--;
        else if (j != 0 && myStack[j - 1] == '[' && myStack[j] == ']') j--;
        else j++;
    }
    while (j-- > 0) ret[indexStack[j]] = '^';
    delete [] myStack;
    delete [] indexStack;
    return ret;
}

int main(void) {
    std::string exp;
    std::getline(std::cin, exp);
    #ifdef __unix__
    std::cout << "\033[31m" << mark(exp) << "\033[0m\n";
	#elif _WIN32
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	std::cout << mark(exp) << std::endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	#else
	std::cout << mark(exp) << std::endl;
	#endif
    return 0;
}
