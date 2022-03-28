#pragma once
#include <Eigen/Dense>

namespace mc
{
    /*
     * Maybe it doesn't need any hyerarchy
     * This might just be the markovian state + time 
     */
    
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

        double get_t() const
        {
            return true_this().time();
        }

        double operator[](size_t index) const
        {
            return true_this().operator[](index);

        }
    };

    class dummy_state : public base_state<dummy_state>
    {
        double t_;
        std::vector<double> x_;

    public:
        dummy_state(double t, const std::vector<double>& x) : t_(t), x_(x) {}
        dummy_state(double t, std::vector<double>&& x) : t_(t), x_(std::move(x)) {}
        double get_t() const
        {
            return t_;
        }

        double operator[](size_t index) const
        {
            return x_[index];

        }
        

    };


    
    
    
    
}
