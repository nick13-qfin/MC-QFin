#pragma once
#include <vector>

namespace utils
{
    template<class vector_t, class operator_t>
    vector_t vector_map(vector_t&& vec, operator_t f)
    {
        const size_t n = vec.size();
        for (size_t i = 0; i < n; ++i)
            vec[i] = f(vec[i]);
        vector_t result(std::move(vec));
        return result;
    }
    
    template<class vector_t, class operator_t>
    vector_t vector_map(const vector_t& vec, operator_t f)
    {
        const size_t n = vec.size();
        vector_t result(vec);
        for (size_t i = 0; i < n; ++i)
            result[i] = f(vec[i]);
        return result;
    }
}
