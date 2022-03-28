#pragma once
#include <algorithm>
#include <vector>
#include "extrapolation_policies.h"

namespace utils
{
	size_t index_first_elem_above(const std::vector<double>& x, double x0)
	{
		const size_t n = x.size();
		for (size_t i = n - 2; i >= 0; --i)
		{
			if (x[i] <= x0)
				return i;
		}
		return n - 2;
	}


	template<template<class> class derived_interp, extrapolation_type E>
	class base_interp1d
	{
		const derived_interp<E>& true_this() const
		{
			return static_cast<const derived_interp<E>&>(*this);
		}

		derived_interp<E>& true_this() 
		{
			return static_cast<derived_interp<E>&>(*this);
		}

	public:
		double interpolate(double t) const
		{
			if constexpr (std::is_same_v<unchecked_boundaries, E>)
				return true_this().interpolate(t);
			else
			{
				//TODO check boundaries
				return true_this().interpolate(t);
			}
		}

	};

        
	template<class full_interp_t>
	concept interp_type = requires (full_interp_t f, double a)
	{
		f.interpolate(a);
	};

    
    template <template<class> class concrete, extrapolation_type T>
    std::true_type is_interp_func(base_interp1d<concrete,T>*);
    
    std::false_type is_interp_func(...);
    
    template<class T>
    struct is_interp2 : decltype(is_interp_func(std::declval<T*>())) {};
    
    template<class T>
    concept interp_type2 = is_interp2<T>::value;
    
    
	template<extrapolation_type E>
	class dummy_interp : public base_interp1d<dummy_interp, E>
	{
	public:
		double interpolate(double t) const
		{
			return 1.0;
		}
	};

	template<extrapolation_type E>
	class pwc_interp : public base_interp1d<pwc_interp, E>
	{
		
		std::vector<double> x_;
		std::vector<double> f_;
		

	public:
		pwc_interp(const std::vector<double>& x, const std::vector<double>& f)
			: x_{x}, f_{f} {}

		pwc_interp(std::vector<double>&& x, std::vector<double>&& f)
			: x_(std::move(x)), f_(std::move(f)) {}

		double interpolate(double p) const
		{
			const auto i0 = index_first_elem_above(x_, p);
			return f_[i0];
		}

	};



}
