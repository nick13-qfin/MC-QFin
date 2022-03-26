#pragma once

#include "../lib/state.h"
#include "../lib/interpolator_base.h"
#include <memory>
namespace mc
{
	double ret(double x)
	{
		return x * 2;
	}
	
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

    template<class interpolator_t>
    class time_dep_param : public base_param<time_dep_param<interpolator_t>>
    {
        std::unique_ptr<interpolator_t> par_;
    public:

        time_dep_param(std::vector<double>&& x, std::vector<double>&& f)
        {
            par_ = std::make_unique<interpolator_t>(std::move(x), std::move(f));
        }

        double value(const dummy_state& state) const
        {
            const double t = state.get_t();
            return par_->value(t);
        }
    };
	
    template<class par_t>
	double consume_parameter(const base_param<par_t>& par)
    {
        const dummy_state state(0.0);
        return par.value(state);
    }
    
}
