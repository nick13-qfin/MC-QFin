#pragma once
#include <Eigen/Dense>
#include "state.h"

namespace mc
{
    /*
     * mutable object - to be owned by the mc engine
     */
    
    class mc_path
    {
        Eigen::Index n_processes_;
        Eigen::Index n_times_;
        Eigen::Map<Eigen::MatrixXd> m_; // there is going to be only one matrix
        markovian_state state_;


    public:
        mc_path(Eigen::MatrixXd& m)
            : n_processes_{ m.rows()}, n_times_{m.cols()}, m_(m.data(), n_processes_, n_times_),
            state_(n_processes_)
        {}

        const markovian_state& get_state(size_t i) 
        {
            state_.set_state(m_, i);
            return state_;
        }

        void set_path_value(double value, size_t row, size_t col)
        {
            m_(row, col) = value;
        }

        size_t get_n_times() const
        {
            return n_times_;
        }

        double get_element(size_t i, size_t j) const
        {
            return m_(i, j);
        }
    };
}

