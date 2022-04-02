#pragma once
#include "../mc_representation/state.h"

namespace mc
{
	template<class derived_proc>
	class stoch_process
	{
	protected:
		size_t index_ = 0;

	public:
		const derived_proc& true_this() const
		{
			return static_cast<const derived_proc&>(*this);
		}

		derived_proc& true_this()
		{
			return static_cast<derived_proc&>(*this);
		}

		double get_x0() const
		{
			return true_this().get_x0();
		}

		double drift(const markovian_state& state) const
		{
			return true_this().drift(state);
		}

		double diffusion(const markovian_state& state) const
		{
			return true_this().diffusion(state);
		}

		// this is needed by the scheme
		size_t get_index() const
		{
			return index_;
		}

		void set_index(size_t i)
		{
			index_ = i;
            true_this().set_parameters_index(i);
		}

		size_t get_n_diffusions() const
		{
			return true_this().get_n_diffusions();
		}
	};
    
    template<class T>
    concept stochprocess_type = std::is_base_of_v<stoch_process<T>,T>;

}
