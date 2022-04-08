#pragma once
#include <vector>
#include "../utils/statistics_utils.h"

namespace mc
{
    class mc_report
    {
        std::vector<double> results_;

    public:
        void add_result(double value)
        {
            results_.push_back(value);
        }

        double operator[](size_t i) const
        {
            return results_[i];
        }

        size_t get_n() const
        {
            return results_.size();
        }

        double get_estimate() const
        {
            double result = 0.0;
            for (const auto d : results_)
                result += d;
            return result / results_.size();
        }

        double mc_err() const
        {
            const size_t n = results_.size();
            const double var = utils::variance(results_, n);
            return var / sqrt(n);
        }

    };
}
