#pragma once
#include "evolution_schemes/evol_scheme_base.h"
#include "mc_representation/time_line.h"
#include "mc_representation/mc_path.h"
#include "mc_representation/payoff.h"
#include "mc_representation/output_report.h"
#include "random_numbers/norm_rng.h"
#include <tuple>
#include <memory>

namespace mc
{
	template<ev_scheme_type... E>
	class mc_engine
	{
		std::tuple<std::unique_ptr<E>...> schemes_;
        size_t n_diffusions_ = 0;
        size_t n_steps_ = 0;
        size_t n_sims_ = 2;
        std::shared_ptr<timeline> timeline_; // probably not needed



	public:
		mc_engine(size_t n_sims, std::unique_ptr<E>&&... schemes)
            : n_sims_{ n_sims }, schemes_(std::make_tuple(std::move(schemes)...))
        {
            std::apply([&](auto&... args) {((
                n_diffusions_+=args->get_process().get_n_diffusions()), ...); }, schemes_);

            auto n_schemes = sizeof...(E);
            std::vector<size_t> tmp(n_schemes, 0.0);
            size_t i = 0;
            std::apply([&](auto&... args) {((
                tmp[i++] = args->get_n_times()), ...); }, schemes_);
            n_steps_ = tmp[0];
            //check timeline in schemes is the same?
            i = 0;
            std::apply([&](auto&... args) {((
                args->set_process_index(i++)), ...); }, schemes_);
        }
            
        template<class payoff_t>
        mc_report calculate(const payoff_t& payoff/*function repr , n_simulation*/)
        {
            Eigen::MatrixXd master_path(n_diffusions_, n_steps_);
            Eigen::MatrixXd wieners(n_diffusions_, n_steps_ - 1);
            mc_path path(master_path);
            mc_report output{};
            normal_rng rand{ 1 };

            for (size_t n = 0; n < n_sims_; n++)
            {
                rand.fill_matrix(wieners, n_diffusions_, n_steps_ - 1);
                size_t i = 0;
                std::apply([&](auto&... ts) {(ts->evolve(path, wieners.row(i++)), ...); }, schemes_);
                auto result = payoff(path);
                output.add_result(result);
            }
            return output;
        }
	};
    
    template<ev_scheme_type... E>
    auto make_mcengine(size_t n_sims, std::unique_ptr<E>&&... schemes)
    {
        return mc_engine<E...>(n_sims, std::move(schemes)...);
    }
}
