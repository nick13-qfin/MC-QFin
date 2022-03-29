#pragma once
#include "parameter.h"

namespace mc
{
	template<class T>
	concept param_type = requires (T p, const markovian_state & state)
	{
		p.value(state);
	};

	template<class T>
	concept param_type2 = std::is_base_of_v<base_param<T>, T>;
}