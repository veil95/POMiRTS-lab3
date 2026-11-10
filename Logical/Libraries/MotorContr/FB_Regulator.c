#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "MotorContr.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_Regulator(struct FB_Regulator* inst)
{
	/*TODO: Add your code here*/
	float proportial = inst->e * inst->k_p;
	if (proportial > inst->max_abs_value)
	{
		proportial = inst->max_abs_value;
	}
	else if ( proportial < -inst->max_abs_value)
	{
		proportial = -inst->max_abs_value;
	}
	float integral_part_in = inst->e * inst->k_i - inst->iyOld / inst->dt;
	inst->integrator.in = integral_part_in;
	inst->integrator.dt = inst->dt;
	FB_Integrator(&inst->integrator);
	float sum = proportial + inst->integrator.out;
	
	if (sum > inst->max_abs_value)
	{
		inst->u = inst->max_abs_value;
	}
	else if (sum < -inst->max_abs_value)
	{
		inst->u = -inst->max_abs_value;
	}
	else inst->u = sum;
	
	inst->iyOld = sum - inst->u;
}
