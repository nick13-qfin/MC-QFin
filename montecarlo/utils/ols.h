#pragma once
#include "ols_report.h"
#include "statistics_utils.h"
#include "vectors_utils.h"

namespace utils
{
    template<class vector_t>
    void ols(const vector_t& X, const vector_t& Y, ols_report& out_report)
    {
        double rho, std_x, std_y, mu_x, mu_y;
        calculate_first_second_moments(X, Y, mu_x, mu_y, std_x, std_y, rho);
        
        const double b = rho * std_y / std_x;
        const double a = mu_y - b * mu_x;
        
        auto y_hat = vector_map(X, [](double x){return a + b * x;});
        
        double rsqr = pearson_correlation(y_hat, y);
        rqsr *= rsqr;
        
        out_report.set_a(a);
        out_report.set_b(b);
        out_report.set_r_sqr(rsqr);
        out_report.set_y_hat(y_hat);
        
    }
}
