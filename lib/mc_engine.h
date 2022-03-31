#pragma once
#include "evolution_schemes/evol_scheme_base.h"
#include "mc_representation/time_line.h"
#include "mc_representation/mc_path.h"
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
        std::shared_ptr<timeline> timeline_; // probably not needed


	public:
		mc_engine(std::unique_ptr<E>&&... schemes)
            : schemes_(std::make_tuple(std::move(schemes)...)) 
        {
            std::apply([&](auto&... args) {((
                n_diffusions_+=args->get_process().get_n_diffusions()), ...); }, schemes_);

            auto n_schemes = sizeof...(E);
            std::vector<size_t> tmp(n_schemes, 0.0);
            size_t i = 0;
            std::apply([&](auto&... args) {((
                tmp[i++] = args->get_n_times()), ...); }, schemes_);

            //check timeline in schemes is the same?
        }
            
            
        void calculate(/*function repr , n_simulation*/)
        {
            Eigen::MatrixXd master_path(n_diffusions_, n_steps_);
            Eigen::MatrixXd wieners(n_diffusions_, n_steps_ - 1);
            mc::mc_path path(master_path);
            //wieners <-
            std::apply([&](auto&... ts){(ts->evolve(path, wieners), ...);}, schemes_);
        }
	};
    
    template<ev_scheme_type... E>
    auto make_mcengine(std::unique_ptr<E>&&... schemes)
    {
        return mc_engine<E...>(std::move(schemes)...);
    }
}
