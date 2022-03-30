#pragma once
#include <chrono>
#include <algorithm>
#include <vector>
#include <cmath>
namespace mc
{
    class timeline
    {
        std::vector<double> times_;
//         std::vector<std::chrono::year_month_day> dates_;
        size_t n_elems_;
        std::vector<double> dt_;
        std::vector<double> sqrt_dt_;

    public:
        //TODO: this needs a constructor based on dates
        timeline(double t0, double tN, double dt)
            //: times_(), dates_()
        {
            times_.push_back(t0);
            while (times_.back() < tN)
            {
                double new_t = times_.back() + dt;
                times_.push_back(new_t);
            }
            if (times_.back() > tN)
                times_.back() = tN;
            if (times_.back() < tN)
                times_.push_back(tN);

            n_elems_ = times_.size();
            dt_.reserve(n_elems_);
            sqrt_dt_.reserve(n_elems_);

            for (size_t i = 0; i < n_elems_-1; i++)
            {
                auto dt = times_[i + 1] - times_[i];
                dt_.push_back(dt);
                sqrt_dt_.push_back(sqrt(dt));
            }
        }

//         size_t get_date_index(const std::chrono::year_month_day& date) const
//         {
//             return -1;
//         }

        size_t get_time_indes(double time) const
        {
            return -1;
        }

        double get_time(size_t index) const
        {
            return times_[index];
        }

        double get_dt(size_t index) const
        {
            return dt_[index];
        }

        double get_sqrtdt(size_t index) const
        {
            return sqrt_dt_[index];
        }

        size_t get_n() const
        {
            return n_elems_;
        }
    };
}
