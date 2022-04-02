#pragma once
#include <random>
#include "rng_base.h"
#include "acklam_norm_inversion.h"

namespace rng
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


	template<class unif_rng_t, norm_inv_type N>
	class normal_inv_rng : public rng_base<normal_inv_rng<unif_rng_t, N>>
	{
		unif_rng_t mt_;
		N inv_;

	public:
		normal_inv_rng(unsigned seed)
			:mt_(seed), inv_() {}

		double next()
		{
			auto p = mt_.next();
			auto x = inv_.invert(p);
			return x;
		}
	};

}