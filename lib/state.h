#pragma once
#include <Eigen/Dense>

namespace mc
{
 
    /*
    Mutable class
    The state can be changed. This is needed to be able to point to a given column in the 
    realization of a mc simulation

    It is expected to be consumed const by parameters and owned (non-const) by a mc_path (also, non-const)
    */

    class markovian_state 
    {
        double t_;
        std::vector<double> dummy_state_;
        Eigen::Map<Eigen::VectorXd> x_;

    public:
        markovian_state(double t, Eigen::VectorXd& x) : t_(t), dummy_state_(), x_(x.data(), x.size()) {}
        markovian_state(double t, std::vector<double>& x) : t_(t), dummy_state_(x), 
            x_(dummy_state_.data(), dummy_state_.size()) {}
        markovian_state(double t, std::vector<double>&& x) : t_(t), dummy_state_(std::move(x)),
            x_(dummy_state_.data(), dummy_state_.size()) {}
        markovian_state(size_t n_states) : markovian_state(0.0, std::vector<double>(n_states, 0.0)) {}

        double get_t() const
        {
            return t_;
        }

        double operator[](size_t index) const
        {
            return x_[index];

        }

        void set_state(Eigen::Map<Eigen::MatrixXd>& matrix, size_t col)
        {
            new (&x_) Eigen::Map<Eigen::VectorXd>(matrix.data() + matrix.rows() * (col), matrix.cols());
        }

        size_t n_states() const
        {
            return x_.size();
        }
        

    };


    
    
    
    
}
