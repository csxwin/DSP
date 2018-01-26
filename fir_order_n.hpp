#include <cstdlib>
#include <cstdint>
#include <array>
#include <algorithm>
#include <iostream>

#ifndef __FIR_ORDER_N_H_
#define __FIR_ORDER_N_H_

/**
 * @brief scalable template FIR fllter
 */
template<const std::size_t resol = 64,
			typename sample_t = std::uint16_t,
			typename value_t = sample_t,
			typename result_t = sample_t>
class Fir_order_n//<5U, resol, sample_t, value_t, result_t>
{
public:
	typedef sample_t sample_type;
	typedef value_t value_type;
	typedef result_t result_type;
	typedef std::int_fast16_t weight_type;
	
	Fir_order_n()
		: result(0U)
	{
		std::fill(values.begin(), values.end(), result);
	}
	
	Fir_order_n(const sample_type& x)
		: result(static_cast<value_type>(x) * resol)
	{
		std::fill(values.begin(), values.end(), result);
	}
	
	template<const weight_type B0,
				const weight_type B1,
				const weight_type B2,
				const weight_type B3,
				const weight_type B4,
				const weight_type B5>
	void NewSample(const sample_type& val)
	{
		std::copy(values.begin() + 1, values.end(), values.begin());
		
		*(values.end() - 1) = resol * static_cast<value_type>(val);
				
		result = (B0 * values[0]
		          + B1 * values[1]
		          + B2 * values[2]
		          + B3 * values[3]
		          + B4 * values[4]
		          + B5 * values[5]
		          + ((B0 + B1 + B2 + B3 + B4 + B5) / 2)) 
		          / (B0 + B1 + B2 + B3 + B4 + B5);
	}
	
	result_type GetResult() const
	{
		return (result + (resol / 2U)) / resol;
	}

private:
	result_type result;
	std::array<value_type, 6U> values;

};

#endif

