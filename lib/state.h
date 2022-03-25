#pragma once
#include <Eigen/Dense>

namespace mc
{

    template <class derived_state_t>
    class base_state
    {
        Eigen::MatrixXd state_;
    public:
        const derived_state_t& true_this() const
        {
            return static_cast<const derived_state_t&>(*this);
        }
        
        derived_state_t& true_this() 
        {
            return static_cast<derived_state_t&>(*this);
        }
        
        double time() const
        {
            return true_this().time();
        }
        
        double operator[](int index) const
        {
            return true_this().operator[](index);
            
        }
    };
    
    class  
    
    
    
    
}
