#pragma once
#include "parameter.h"
#include <Eigen/Dense>
#include <memory>

namespace mc
{
    template<class interp2d_t>
    class state_dep_param : public base_param<state_dep_param<interp2d_t>>
    {
        std::unique_ptr<interp2d_t> interp_;
        size_t index_ = 0; // to be set by the process that owns this
    public:
        state_dep_param(std::vector<double>&& t, std::vector<double>&& x, Eigen::MatrixXd&& value)
        : interp_(std::move(t), std::move(x), std::move(value)) {}
        
        
        double value(const markovian_state& state) const
        {
            const double t = state.get_t();
            const double x = state[index_];
            return interp_->interpolate(t, x);
        }
        
        void set_index(size_t i)
        {
            index_ = i;
        }
    };
    
    template<template<class> class B, class T>
    std::true_type is_statdep_impl(B<T>*);
    
    std::false_type is_statdep_impl(...);
    
    template<class T>
    struct is_state_dep_par : decltype(is_statdep_impl(std::declval<T*>())){};
    
}
