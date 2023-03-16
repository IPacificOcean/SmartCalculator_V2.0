//
// Created by Qyburn Bongo on 3/16/23.
//

#ifndef GOOGLE_TESTS_DATA_PLOT_H
#define GOOGLE_TESTS_DATA_PLOT_H

#include <string>

namespace s21 {

    struct DataPlot {
        DataPlot(const std::string& expression, const double& x_begin,
                 const double& x_end)
                : expression_(expression), x_begin_(x_begin), x_end_(x_end) {}

        std::string expression_{};
        double x_begin_{}, x_end_{};
    };

}  // namespace s21

#endif //GOOGLE_TESTS_DATA_PLOT_H
