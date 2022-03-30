#pragma once
#include "evolution_schemes/evol_scheme_base.h"
#include <tuple>
#include <memory>

namespace mc
{
	template<ev_scheme_type ... E>
	class mc_engine
	{
		std::tuple<std::unique_ptr<E>...> schemes_;

	public:
		mc_engine(std::unique_ptr<E>&&... schemes)
			: schemes_(std::make_tuple(std::move(schemes)...)) {}
	};
}