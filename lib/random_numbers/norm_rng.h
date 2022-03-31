#pragma once
#include <random>
#include "rng_base.h"

namespace mc
{
	class normal_rng : public rng_base<normal_rng>
	{
		std::mt19937_64 mt_;
		std::normal_distribution<double> norm_;

	public:
		normal_rng(unsigned seed)
			:mt_(seed), norm_(0.0, 1.0) {}

		double next()
		{
			return norm_(mt_);
		}
	};
}