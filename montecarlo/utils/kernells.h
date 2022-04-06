#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace utils
{
    template<class derived_kernell>
    class kernell_base
    {
    protected:
        double norm_constant_;
        kernell_base(double norm_constant) : norm_constant_(norm_constant){}
        
        const derived_kernell& true_this() const
        {
            return static_cast<const derived_kernell&>(*this);
        }
        
    public:
        double operator()(double x) const
        {
            return true_this()(x);
        }
    };
    
    
    class exponential_kernell : public kernell_base<exponential_kernell>
    {
        double one_over_sqrt_pi_;  
      
    public:
        exponential_kernell(double norm_constant)
        : 
        kernell_base(norm_constant),
        one_over_sqrt_pi_(1 / sqrt(2 * M_PI)) {}
        
        
        double operator()(double x) const
        {
            const double y = x * norm_constant_;
            return norm_constant_ * one_over_sqrt_pi_ * exp(0.5 * y * y);
        }
        
    };
    
    class quartic_kernell : public kernell_base<quartic_kernell>
    {
        double fifteen_sixteenth_;
        
    public:
        quartic_kernell(double norm_constant)
        : kernell_base(norm_constant), fifteen_sixteenth_(15.0/16.0) {}
        
        double operator()(double x) const
        {
            const double y =  x* norm_constant_;
            const double result = (x < 1 && x > -1) ? 
                norm_constant_ * fifteen_sixteenth_ * (1 - x*x) * (1- x*x) : 0.0;
            return result;
            
        }
        
    };
}
