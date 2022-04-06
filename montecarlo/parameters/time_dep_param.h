#pragma once

#include "parameter.h"

namespace mc
{
    template<interp::interp_type I>
    class time_dep_param : public base_param<time_dep_param<I>>
    {
        std::unique_ptr<I> par_;
    public:

        time_dep_param(std::vector<double>&& x, std::vector<double>&& f)
        {
            par_ = std::make_unique<I>(std::move(x), std::move(f));
        }

        time_dep_param(const std::vector<double>& x, const std::vector<double>& f)
        {
            par_ = std::make_unique<I>(x, f);
        }

        time_dep_param(std::unique_ptr<I>&& par) : par_(std::move(par)) {};

        double value(const markovian_state& state) const
        {
            const double t = state.get_t();
            return par_->interpolate(t);
        }
    };

}
