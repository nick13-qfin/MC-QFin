#pragma once
#include <stdexcept>
#include <vector>

namespace utils
{

    struct ols_report
    {
        double rsqr_;
        double a_;
        std::vector<double> b_;
        std::vector<double> y_hat_;
        std::vector<double> y_;
        std::vector<double> x_;
        
    public:
        void set_rsqr(double value)
        {
            rsqr_ = value;
        }
        
        double get_rsqr() const
        {
         return rsqr_;   
        }
        
        void set_a(double value)
        {
            a_ = value;
        }
        
        double get_a() const
        {
            return a_;
        }
        
        void set_b(double value)
        {
            if (b_.size() == 1)
                b_[0] = value;
            else
                throw std::out_of_range("OLSREPORT:::: An attempt has been made to set a b vector with a double");
        }
        
        void set_b(std::vector<double>&& value)
        {
            b_ = std::move(value);
        }
        
        const std::vector<double>& get_b() const
        {
            return b_;
        }

        void set_y_hat(std::vector<double>&& value)
        {
            y_hat_ = std::move(value);
        }
        
        const std::vector<double>& get_y_hat() const
        {
            return y_hat_;
        }
        
        template<class vector_t>
        void set_y(const vector& value)
        {
            y_.clear();
            y_.reserve(value.size());
            for (const auto v: value)
                y_.push_back(v);
        }
        
        const std::vector<double>& get_y() const
        {
            return y_;
        }

        template<class vector_t>
        void set_x(const vector& value)
        {
            x_.clear();
            x_.reserve(value.size());
            for (const auto v: value)
                x_.push_back(v);
        }
        
        const std::vector<double>& get_x() const
        {
            return x_;
        }
        
    };
    
}
