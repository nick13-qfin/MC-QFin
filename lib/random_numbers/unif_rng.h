#pragma once
#include "rng_base.h"
#include <random>

namespace mc
{
	class mersenne_twister : public rng_base<mersenne_twister>
	{
		std::mt19937_64 mt_;
		double norm_factor_;
		std::mt19937_64::result_type max_;
		std::mt19937_64::result_type min_;


	public:
		mersenne_twister(unsigned seed)
			: mt_(seed), norm_factor_(1.0/ (mt_.max()-mt_.min())), max_(mt_.max()), min_(mt_.min()) {}

		double next()
		{
			return mt_() * norm_factor_;
		}
	};
}