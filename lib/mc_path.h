#pragma once
#include <Eigen/Dense>

namespace mc
{
    /*
     * mutable object - to be held by the mc engine
     */
    
    class mc_path
    {
        size_t n_processes_;
        size_t n_times_;
        Eigen::MatrixXd m_;
    public:
        mc_path(size_t n_processes, size_t n_times)
        : n_processes_{n_processes}, n_times_{n_times}, m_{Eigen::MatrixXd(n_processes_, n_times_)}
        {}
    };
}

