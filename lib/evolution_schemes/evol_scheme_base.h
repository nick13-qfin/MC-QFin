#pragma once

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
        
//         template<class vector_t>
//         void evolve(
        
    }
}
