#pragma once
#include "../mc_representation/state.h"
#include "../mc_representation/mc_path.h"
#include "../stochastic_processes/stochastic_process.h"

namespace mc
{
    template<class derived_scheme, stochprocess_type S>
    class evolution_scheme
    {
    public:
        
        const derived_scheme& true_this() const
        {
            return static_cast<const derived_scheme&>(*this);
        }
        
        template<class vector_t> // TODO: it depends on RNG choice
        void evolve(mc_path& out_path, const vector_t& wieners) const
        {
            true_this().evolve(out_path, wieners);
        }

        const S& get_process() const
        {
            return true_this().get_process();
        }
        
        size_t get_n_times() const
        {
            return true_this().get_n_times();
        }
    };
    
    template<template<class> class S, stochprocess_type P>
    std::true_type is_scheme_func(evolution_scheme<S<P>, P>*);

    std::false_type is_scheme_func(...);

    template<class S>
    struct is_scheme : decltype(is_scheme_func(std::declval<S*>())) {};


    template<class T>
    concept ev_scheme_type = is_scheme<T>::value;
        //std::is_base_of_v<evolution_scheme<T>, T>;
    
    
}
