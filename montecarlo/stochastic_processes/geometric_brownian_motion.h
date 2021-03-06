#pragma once
#include "stochastic_process.h"
#include "../parameters/parameters_utils.h"


namespace mc
{
	template<param_type mu_t, param_type vol_t>
	class geometric_brownian_motion 
		: public stoch_process<geometric_brownian_motion<mu_t, vol_t>>
	{
		std::unique_ptr<mu_t> mu_;
		std::unique_ptr<vol_t> vol_;
		double x0_;
		using base = stoch_process<geometric_brownian_motion<mu_t, vol_t>>;
	public:
		geometric_brownian_motion(std::unique_ptr<mu_t>&& mu, std::unique_ptr<vol_t>&& vol, double x0)
			:
			mu_(std::move(mu)), vol_(std::move(vol)) , x0_(x0)
		{ };
        
        geometric_brownian_motion(double mu, double vol, double x0)
        : geometric_brownian_motion(
            std::make_unique<constant_param>(mu),
            std::make_unique<constant_param>(vol), x0) {};

		double drift(const markovian_state& state) const
		{
			if constexpr (std::is_same_v <null_param, mu_t>)
			{
				return 0.0;
			}
			else
			{
				const double x_t = state[base::get_index()];
				return x_t * mu_->value(state);
			}
		}

		double diffusion(const markovian_state& state) const
		{
			const double x_t = state[base::get_index()];
			return x_t * vol_->value(state);
		}
		
		double get_x0() const
		{
			return x0_;
		}

		size_t get_n_diffusions() const
		{
			return 1;
		}
		
		void set_parameters_index(size_t i)
		{
            if constexpr (is_state_dep_par<mu_t>::value)
            {
                //
            }
            if constexpr (is_state_dep_par<vol_t>::value)
            {
                //
            }
		}

	};
}
