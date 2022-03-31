#pragma once
#include <Eigen/Dense>

namespace mc
{
	template<class derived>
	class rng_base
	{
	public:
		const derived& true_this() const
		{
			return static_cast<const derived&>(*this);
		}

		double next() const
		{
			return true_this().next();
		}

		void fill_matrix(Eigen::MatrixXd& out_matrix, size_t n_rows, size_t n_cols) const
		{
			for (size_t i = 0; i < n_rows; i++)
			{
				for (size_t j = 0; j < n_cols; j++)
					out_matrix(i, j) = next();
			}
		}
	};
}