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

        bool IsNotValid(const std::string &expression) const;

    private:

        bool CheckNumber(size_t &index, const std::string &expression) const;
    };
}  // namespace s21
#endif //GOOGLE_TESTS_VALIDATION_H
