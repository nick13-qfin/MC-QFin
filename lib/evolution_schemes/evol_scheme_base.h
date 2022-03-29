#pragma once
#include "../mc_representation/state.h"
#include "../mc_representation/mc_path.h"
#include "../stochastic_processes/stochastic_process.h"

namespace mc
{
    template<class derived_scheme>
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
        
    };
    
   
    
    
}
