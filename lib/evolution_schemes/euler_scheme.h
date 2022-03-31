#pragma once
#include <memory>
#include "evol_scheme_base.h"
#include "../mc_representation/time_line.h"

namespace mc
{
    template<stochprocess_type S>
    class euler_scheme : public evolution_scheme<euler_scheme<S>, S>
    {
        mc::timeline time_;
        std::unique_ptr<S> process_; // TODO: maybe shared e.g. stoch param?
        size_t nth_row_;
        size_t n_times_;

    public:

        euler_scheme(double t0, double tN, double dt, std::unique_ptr<S>&& process)
            : time_(t0, tN, dt), process_(std::move(process)),
            nth_row_{ process_->get_index() }, n_times_{ time_.get_n() } {};

        template<class vector_t> // TODO: it depends on RNG choice
        void evolve(mc_path& out_path, const vector_t& wieners) const
        {
            out_path.set_path_value(process_->get_x0(), nth_row_, 0);
            for (size_t i = 1; i < n_times_; i++)
            {
                const auto sqrt_dt = time_.get_sqrtdt(i - 1);
                const auto dt = time_.get_dt(i - 1);
                const auto x_old = out_path.get_state(i - 1);
                double xt = x_old[nth_row_] + process_->drift(x_old) * dt
                    + process_->diffusion(x_old) * sqrt_dt * wieners[i - 1];
                out_path.set_path_value(xt, nth_row_, i);
            }
        }

        const S& get_process() const
        {
            return *process_;
        }

        size_t get_n_times() const
        {
            return n_times_;
        }
    };
}