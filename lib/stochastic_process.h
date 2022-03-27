#pragma once
#include "../lib/state.h"

namespace mc
{
	template<class derived_proc>
	class stoch_process
	{
	protected:
		double x0_ = 0.0;
	public:
		const derived_interp<derived_proc>& true_this() const
		{
			return static_cast<const derived_interp<derived_proc>&>(*this);
		}

		double get_x0() const
		{
			return x0_;
		}

		double drift(const dummy_state& state) const
		{
			return true_this.drift(state);
		}

		double diffusion(const dummy_state& state) const
		{
			return true_this.diffusion(state);
		}
	};

}