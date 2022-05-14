#pragma once
#include <algorithm>
#include <vector>
#include "extrapolation_policies.h"

namespace interp
{



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

	protected:
		size_t index_first_elem_above(const std::vector<double>& x, double x0) const
		{
			const size_t n = x.size();
			for (size_t i = n - 2; i >= 0; --i)
			{
				if (x[i] <= x0)
					return i;
			}
			return n - 2;
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
    
    template <template<class> class concrete, extrapolation_type T>
    std::true_type is_interp_func(base_interp1d<concrete,T>*);
    
    std::false_type is_interp_func(...);
    
    template<class T>
    struct is_interp : decltype(is_interp_func(std::declval<T*>())) {};
    
    template<class T>
    concept interp_type = is_interp<T>::value;
    
	//alternative concept defintion - duck typing-esque?
	template<class full_interp_t>
	concept interp_type2 = requires (full_interp_t f, double a)
	{
		{f.interpolate(a)} -> std::convertible_to<double>;
	};





}
