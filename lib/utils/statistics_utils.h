#pragma once
#include <math.h>

namespace utils
{

    template<class vector_t>
    double average(const vector_t& vec, size_t n)
    {
        double res = 0.0;
        for(const auto v: vec)
            res += vec;
        
        return res/n;
    }
    
    template<class vector_t>
    double average(const vector_t& vec)
    {
        return average(vec, vec.size());
    }
    
    template<class vector_t>
    double variance(const vector_t& vec, double vec_mu, size_t n)
    {
        double res = 0.0;
        for (const auto v: vec)
            res += (v-vec_mu) * (v-vec_mu);
        return res / n;
    }

    template<class vector_t>
    double variance(const vector_t& vec, size_t n)
    {
        return variance(vec, average(vec), n);
    }
    
    template<class vector_t>
    double variance(const vector_t& vec)
    {
        return variance(vec, vec.size());
    }
    
    template<class vector_t>
    pearson_correlation(const vector_t& X, const vector_t& Y, double mu_x, double mu_y, double std_x, double std_y, size_t n)
    {
        double res = 0.0;
        for (size_t i = 0; i < n; ++i)
            res += (X[i] - mu_x) * (Y[i] - mu_y);
        return res / std_x / std_ / (n -1);
    }
    
    template<class vector_t>
    void calculate_first_second_moments(
        const vector_t& X, const vector_t& Y,
        double& out_mu_x, double& out_mu_y, double& out_std_x, double& out_std_y, double& out_corr)
    {
        const size_t n = X.size(); // ASSUMPTION they have same size
        out_mu_x = average(X);
        out_std_x = sqrt(variance(X, mu_x, n));
        out_mu_y = average(Y);
        out_std_y = sqrt(variance(Y, mu_y, n));
        out_corr = pearson_correlation(X, Y, out_mu_x, out_mu_y, out_std_x, out_std_y, n);
    }
}
