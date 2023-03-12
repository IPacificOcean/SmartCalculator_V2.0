//
// Created by Qyburn Bongo on 3/11/23.
//

#ifndef GOOGLE_TESTS_VALIDATION_H
#define GOOGLE_TESTS_VALIDATION_H

#include <string>


namespace s21 {

    class Validation {

    public:

        explicit Validation(const std::string &expression) : expression_(expression) {}

        ~Validation() = default;


        bool IsValid() const;
       bool CheckNumber(size_t &index) const ;

    private:

        std::string expression_;

    };
}

#endif //GOOGLE_TESTS_VALIDATION_H
