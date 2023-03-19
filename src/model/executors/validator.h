//
// Created by Qyburn Bongo on 3/11/23.
//

#ifndef GOOGLE_TESTS_VALIDATION_H
#define GOOGLE_TESTS_VALIDATION_H

#include <string>


#include <string>

namespace s21 {

    class Validator {
    public:
        /***
        * @brif main method for calculation expression
        * @param expression -  a mathematical expression
        * @return true if the expression is not valid
        */
        bool IsNotValid(const std::string &expression) const;

    private:
        /***
        * @brif checks to see if the number is correct and shifts the index by the length of the number
        * @param expression -  a mathematical expression
        * @param index - index a string of expressions
        * @return true if the number is not valid
        */
        bool CheckNumber(size_t &index, const std::string &expression) const;
    };
}  // namespace s21
#endif //GOOGLE_TESTS_VALIDATION_H
