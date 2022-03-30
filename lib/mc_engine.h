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
        std::shared_ptr<timeline> timeline_;
        Eigen::MatrixXd single_path_;
        

	public:
		mc_engine(std::unique_ptr<E>&&... schemes)
            : schemes_(std::make_tuple(std::move(schemes)...)) {}
            
            
        void calculate(/*function repr , n_simulation*/)
        {
            mc::mc_path path(single_path_);
            //wieners <-
            std::vector<double> wieners;
            std::apply([&](auto&... ts){(ts->evolve(path, wieners), ...);}, schemes_);
        }
	};
    
    template<ev_scheme_type... E>
    auto make_mcengine(std::unique_ptr<E>&&... schemes)
    {
        return mc_engine<E...>(std::move(schemes)...);
    }
}
