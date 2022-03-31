#pragma once
#include "mc_path.h"

namespace mc
{
    template<class derived_payoff>
    class payoff_base
    {
    public:
        
        const derived_payoff& true_this() const
        {
            return static_cast<const derived_payoff&>(*this);
        }
        
        const double operator()(const mc_path& path) const
        {
            return true_this()(path);
        }
    };
    
    class dummy_payoff : public payoff_base<dummy_payoff>
    {
    public:
        double operator()(const mc_path& path) const
        {
            return 1.0;
        }
    };
}
