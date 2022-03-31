#pragma once
#include <vector>

namespace mc
{
    class mc_report
    {
        std::vector<double> results_;
        
    public:
        void add_result(double value) 
        {
            results_.push_back(value);
        }
        
    }
}
