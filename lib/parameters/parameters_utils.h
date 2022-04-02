#pragma once
#include "parameter.h"
#include "time_dep_param.h"
#include "state_dep_param.h"

namespace mc
{
	template<class T>
	concept param_type = std::is_base_of_v<base_param<T>, T>;

	template<class T>
	concept param_type2 = requires (T p, const markovian_state & state)
	{
		p.value(state);
	};
}
