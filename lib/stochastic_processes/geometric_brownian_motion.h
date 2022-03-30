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
		size_t this_index_;
		using base = stoch_process<geometric_brownian_motion<mu_t, vol_t>>;
	public:
		geometric_brownian_motion(std::unique_ptr<mu_t>&& mu, std::unique_ptr<vol_t>&& vol, double x0, bool reset = false)
			:
			base(reset), mu_(std::move(mu)), vol_(std::move(vol)) , x0_(x0)
		{
			this_index_ = base::get_counter();
			base::update_count();
		};
        
        geometric_brownian_motion(double mu, double vol, double x0, bool reset = false)
        : geometric_brownian_motion(
            std::make_unique<constant_param>(mu),
            std::make_unique<constant_param>(vol), x0, reset) {};

		double drift(const markovian_state& state) const
		{
			if constexpr (std::is_same_v <null_param, mu_t>)
			{
				return 0.0;
			}
			else
			{
				const double x_t = state[this_index_]; 
				return x_t * mu_->value(state);
			}
		}

		double diffusion(const markovian_state& state) const
		{
			const double x_t = state[this_index_];
			return x_t * vol_->value(state);
		}

		size_t get_index() const
		{
			// needed by the scheme
			return this_index_;
		}

	};
}
