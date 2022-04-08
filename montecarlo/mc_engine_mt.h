#pragma once
#include "mc_engine.h"
#include <thread>

namespace mc
{
	template<ev_scheme_type... E>
	class mc_engine_mt
	{
		size_t n_sims_;
		size_t seed_;
		size_t n_threads_;
		std::vector<mc_report> outputs_;
		std::tuple<std::unique_ptr<E>...> schemes_;

	public:
		mc_engine_mt(size_t n_sims, unsigned int seed, size_t n_threads, std::unique_ptr<E>&&... schemes)
			: n_sims_{ n_sims }, seed_{ seed }, n_threads_{ n_threads }, outputs_(n_threads),
			schemes_(std::make_tuple(std::move(schemes)...)) {}


		template<class payoff_t>
		void calculate(const payoff_t& p)
		{
			std::vector<std::thread> threads;
			for (size_t i = 0; i < n_threads_; ++i)
			{
				threads.push_back(std::thread(
					run_single_thread<payoff_t, E...>,
					p,
					(int)(n_sims_/n_threads_),
					seed_ + i,
					std::ref(outputs_[i]),
					std::ref(schemes_)
				));
			}

			std::for_each(threads.begin(), threads.end(),
				std::mem_fn(&std::thread::join));
		}

		double get_result() const
		{
			//TODO to review if outputs have different sizes
			double result = 0.0;
			for (const auto& res : outputs_)
				result += res.get_estimate();
			return result / outputs_.size();
		}

		double mc_err() const
		{
			double result = 0.0;
			for (const auto& res : outputs_)
				result += res.mc_err() * res.mc_err();
			return sqrt(result);
		}
	};

	template<ev_scheme_type... E>
	auto make_mcengine_mt(size_t n_sims, unsigned int seed, size_t n_threads, std::unique_ptr<E>&&... schemes)
	{
		return mc_engine_mt<E...>(n_sims, seed, n_threads, std::move(schemes)...);
	}
}