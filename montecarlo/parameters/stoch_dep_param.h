#pragma once
#include "parameter.h"
#include "../stochastic_processes/stochastic_process.h"
#include <memory>
namespace mc
{
	template<class T>
	concept transf_policy = requires(T op, double x) { op(x); };
	// is-a param? yes
	// is-a process? yes I think -> it needs to hold an additional mapping for the param
	template<stochprocess_type S, class F>
	class stoch_parameter : public base_param<stoch_parameter<S, F>>, public stoch_process<stoch_parameter<S,F>>
	{
		std::unique_ptr<S> process_;
		F f_;

	public:
		stoch_parameter(S& proc)
			: process_(std::make_unique<S>(proc)), f_() {}

		stoch_parameter(std::unique_ptr<S>&& proc)
			: process_(std::move(proc)), f_() {}

		stoch_parameter(S& proc, F& f)
			: process_(std::make_unique<S>(proc)), f_(f) {}

		stoch_parameter(std::unique_ptr<S>&& proc, F& f)
			: process_(std::move(proc)), f_(f) {}

		//parameter interface
		double value(const markovian_state& state) const
		{
			const double v = state[process_->get_index()];
			return f_(v);
		}

		//process interface
		double get_x0() const
		{
			return process_->get_x0();
		}

		double drift(const markovian_state& state) const
		{
			return process_->drift(state);
		}

		double diffusion(const markovian_state& state) const
		{
			return process_->diffusion(state);
		}

		void set_index(size_t i)
		{
			process_->set_index(i); 
		}

		size_t get_n_diffusions() const
		{
			return process_->get_n_diffusions();
		}
	};

	//TODO: it doesn't work - why?
	template<stochprocess_type S, class F>
	std::unique_ptr<stoch_parameter<S, F>> make_stoch_param(S& process, F& f)
	{
		return std::make_unique<stoch_parameter<S, F>>(process, f);
	};

	template<stochprocess_type S, class F>
	std::unique_ptr<stoch_parameter<S, F>> make_stoch_param(std::unique_ptr<S>&& process, F& f)
	{
		return std::make_unique<stoch_parameter<S, F>>(std::move(process), f);
	};

	class dummy_lambda
	{
	public:
		double operator()(double x)
		{
			return x * x;
		}
	};

}