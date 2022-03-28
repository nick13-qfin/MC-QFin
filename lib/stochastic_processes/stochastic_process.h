#pragma once
#include "../state.h"

namespace mc
{
	template<class derived_proc>
	class stoch_process
	{
	protected:
		inline static size_t counter_ = 0;

		void update_count()
		{
			counter_++;
		}

		size_t get_counter() const
		{
			return counter_;
		}
		
		stoch_process(bool reset = false)
        {
            if (reset)
                counter_ = 0;
        }

	public:
		const derived_proc& true_this() const
		{
			return static_cast<const derived_proc&>(*this);
		}

		double get_x0() const
		{
			return true_this().get_x0();
		}

		double drift(const dummy_state& state) const
		{
			return true_this().drift(state);
		}

		double diffusion(const dummy_state& state) const
		{
			return true_this().diffusion(state);
		}
	};
    
    template<class T>
    concept stochprocess_type = std::is_base_of_v<stoch_process<T>,T>;

}
