#pragma once

#include "../mc_representation/state.h"
#include "../interpolation/interpolator_base.h"
#include "../template_utils.h"
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
        
        double value(const markovian_state& state) const
        {
            return true_this().value(state);
        }
    };
    
    class constant_param : public base_param<constant_param>
    {
        double par_ = 0; //default, but it can be set in constructor
        
    public:
        constant_param(double par) : par_(par) {};
        double value(const markovian_state& state) const
        {
            return par_;
        }
        
    };

    class null_param : public constant_param
    {
        double par_ = 0.0; // no user-defined constructor to change it
    };

 	
    //dummy test function
    template<class par_t>
	double consume_parameter(const base_param<par_t>& par)
    {
        const markovian_state state(0.0, std::vector<double>(1));
        return par.value(state);
    }
    
}
