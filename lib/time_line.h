#pragma once
#include <chrono>
#include <algorithm>

namespace mc
{
 class timeline
 {
     std::vector<double> times_;
     std::vector<std::year_month_day> dates_;
     
 public:
     
     size_t get_date_index(const std::year_month_day& date) const
     {
         return -1;
     }
     
     size_t get_time_indes(double time) const
     {
         return -1;
     }
 }
}
