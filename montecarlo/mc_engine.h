#pragma once
#include "evolution_schemes/evol_scheme_base.h"
#include "mc_representation/time_line.h"
#include "mc_representation/mc_path.h"
#include "mc_representation/payoff.h"
#include "mc_representation/output_report.h"
#include <../random_numbers/include/norm_rng.h>
#include <../random_numbers/include/unif_rng.h>
#include <../random_numbers/include/acklam_norm_inversion.h>
#include <tuple>
#include <memory>

namespace mc
{
    //TODO: tmply here
    using normal_rng2 = rng::normal_inv_rng < rng::mersenne_twister, rng::acklam_inversion>;

	template<ev_scheme_type... E>
	class mc_engine
	{
		std::tuple<std::unique_ptr<E>...> schemes_;
        size_t n_diffusions_ = 0;
        size_t n_steps_ = 0;
        size_t n_sims_ = 2;
        std::shared_ptr<timeline> timeline_; // probably not needed
        mc_report output_;
        unsigned int seed_ = 1;

        void init(std::tuple<std::unique_ptr<E>...>& schemes)
        {
            std::apply([&](auto&... args) {((
                n_diffusions_ += args->get_process().get_n_diffusions()), ...); }, schemes);

            const size_t n_schemes = sizeof...(E);
            std::vector<size_t> tmp(n_schemes, 0);
            size_t i = 0;
            std::apply([&](auto&... args) {((
                tmp[i++] = args->get_n_times()), ...); }, schemes);
            n_steps_ = tmp[0];
            //check timeline in schemes is the same?
            i = 0;
            std::apply([&](auto&... args) {((
                args->set_process_index(i++)), ...); }, schemes);
        }

	public:
        mc_engine(size_t n_sims, unsigned int seed, std::tuple<std::unique_ptr<E>...>& schemes)
            : n_sims_{ n_sims }, seed_{seed}
            //, schemes_(std::make_tuple(std::make_unique<E>(schemes)...))
        {
            init(schemes);
        }

		mc_engine(size_t n_sims, unsigned int seed, std::unique_ptr<E>&&... schemes)
            : schemes_(std::make_tuple(std::move(schemes)...)),
            n_sims_{ n_sims }, seed_{seed}
        {
            init(schemes_);
        }
            
        template<class payoff_t>
        void calculate(const payoff_t& payoff, mc_report& output, std::tuple<std::unique_ptr<E...>>& schemes)
        {
            Eigen::MatrixXd master_path(n_diffusions_, n_steps_);
            Eigen::MatrixXd wieners(n_diffusions_, n_steps_ - 1);
            mc_path path(master_path);
            output.reset();
            normal_rng2 rand{ seed_ };

            for (size_t n = 0; n < n_sims_; n++)
            {
                rand.fill_matrix(wieners, n_diffusions_, n_steps_ - 1);
                size_t i = 0;
                std::apply([&](auto&... ts) {(ts->evolve(path, wieners.row(i++)), ...); }, schemes);
                auto result = payoff(path);
                output.add_result(result);
            }
        }

        template<class payoff_t>
        void calculate(const payoff_t& payoff, mc_report& output)
        {
            calculate(payoff, output, schemes_);
        }

        template<class payoff_t>
        void calculate(const payoff_t& payoff)
        {
            calculate(payoff, output_);
        }

        const mc_report& get_results() const
        {
            return output_;
        }
	};
    
    template<ev_scheme_type... E>
    auto make_mcengine(size_t n_sims, unsigned int seed, std::unique_ptr<E>&&... schemes)
    {
        return mc_engine<E...>(n_sims, seed, std::move(schemes)...);
    };
    
    template<ev_scheme_type... E>
    auto make_mcengine(size_t n_sims, unsigned int seed, std::tuple<std::unique_ptr<E>...>& schemes)
    {
        return mc_engine<E...>(n_sims, seed, schemes);
    };


    template<class payoff_t, ev_scheme_type... E>
    void run_single_thread(const payoff_t& p, size_t n_sims, unsigned int seed, 
        mc_report& output, std::tuple<std::unique_ptr<E>...>& schemes)
    {
        auto mcengine = make_mcengine(n_sims, seed, schemes);
        mcengine.calculate(p, output, schemes);
    };
}
