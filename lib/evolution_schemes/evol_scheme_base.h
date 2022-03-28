#pragma once
#include "../state.h"
#include "../mc_path.h"
#include "../stochastic_processes/stochastic_process"

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
        
        template<class vector_t>
        void evolve(mc_path& out_path, const vector_t& wieners) const
        {
            true_this().evolve(out_path, wieners);
        }
        
    };
    
    
    template<stochprocess_type S>
    class euler_scheme : public evolution_scheme<euler_scheme<S>>
    {
        std::unique_ptr<S> process_;
        
    public:
        
    }
    
    
}
