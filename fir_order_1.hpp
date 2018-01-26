#include <cstdlib>
#include <cstdint>
#include <array>

#ifndef __FIR_ORDER_1_H_
#define __FIR_ORDER_1_H_

/**
 * @brief scalable template FIR fllter
 */
template<const std::size_t resol = 4U,
			typename sample_t = std::uint16_t,
			typename value_t = sample_t,
			typename result_t = sample_t>
class Fir_order_1
{
public:
	typedef sample_t sample_type;
	typedef value_t value_type;
	typedef result_t result_type;
	typedef std::int_fast16_t weight_type;
	
	Fir_order_1(const sample_type& val = 0U)
		: result(val * resol)
	{
		std::fill(values.begin(), values.end(), result);
	}
	
	template<const weight_type B0,
				const weight_type B1>
	void NewSample(const sample_type& val)
	{
		values[0] = values[1];
		values[1] = val * static_cast<value_type>(resol);
		result = (B0 * values[0] + B1 * values[1] 
						+ (B0 + B1) / 2) / (B0 + B1);
	}

	result_type GetResult() const
	{
		return (result + (resol / 2U)) / resol;
	}


private:
	result_type result;
	std::array<value_type, 2U> values;

};




#endif
