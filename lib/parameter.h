#pragma once

#include "../lib/state.h"
#include "../lib/interpolator_base.h"
#include "../lib/template_utils.h"
#include <memory>

namespace mc
{


    template <class derived_param_t>
    class base_param
    {
    public:
        const derived_param_t& true_this() const
        {
            return static_cast<const derived_param_t&>(*this);
        }
        
        double value(const dummy_state& state) const
        {
            return true_this().value(state);
        }
    };
    
    class constant_param : public base_param<constant_param>
    {
        double par_ = 0;
        
    public:
        double value(const dummy_state& state) const
        {
            return par_;
        }
        
    };

    template<utils::interp_type I>
    class time_dep_param : public base_param<time_dep_param<I>>
    {
        std::unique_ptr<I> par_;
    public:

        time_dep_param(std::vector<double>&& x, std::vector<double>&& f)
        {
            //static_assert(utils::is_interp<I, E>::value,
            //    "interpolator_t is expected to be a specialization of base_interp_1d");
            par_ = std::make_unique<I>(std::move(x), std::move(f));
        }

        time_dep_param(const std::vector<double>& x, const std::vector<double>& f)
        {
            //static_assert(utils::is_interp<I, E>::value,
            //    "interpolator_t is expected to be a specialization of base_interp_1d");
            par_ = std::make_unique<I>(x, f);
        }

        time_dep_param(std::unique_ptr<I>&& par) : par_(std::move(par)) {};

        double value(const dummy_state& state) const
        {
            const double t = state.get_t();
            return par_->interpolate(t);
        }
    };
	
    template<class par_t>
	double consume_parameter(const base_param<par_t>& par)
    {
        const dummy_state state(0.0);
        return par.value(state);
    }
    
}
