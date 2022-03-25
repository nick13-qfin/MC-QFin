#pragma once

// #include <eigen3/Eigen/Dense>
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
        
        double value() const
        {
            return true_this().value();
        }
    };
    
    class constant_param : public base_param<constant_param>
    {
        double par_ = 0;
        
    public:
        double value2() const
        {
            return par_;
        }
        
    };
	
    template<class par_t>
	double consume_parameter(const base_param<par_t>& par)
    {
        return par.value();
    }
    
}
