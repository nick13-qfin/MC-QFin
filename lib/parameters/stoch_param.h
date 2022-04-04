#pragma once
#include "parameter.h"
#include "../stochastic_processes/stochastic_process.h"
#include <memory>
namespace mc
{
	// is-a param? yes
	// is-a process? yes I think -> it needs to hold an additional mapping for the param
	template<stochprocess_type S>
	class stoch_parameter : public base_param<stoch_parameter<S>>, public stoch_process<stoch_parameter<S>>
	{
		std::unique_ptr<S> und_process_;

	public:
		stoch_parameter(const S& proc)
			: und_process_(std::make_unique<S>(proc)) {}
	};
}