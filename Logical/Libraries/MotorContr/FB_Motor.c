
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
void FB_Motor(struct FB_Motor* inst)
{
	/*TODO: Add your code here*/
	inst->w = (inst->u / inst->ke - inst->w) * (inst->dt / inst->Tm) + inst->w;
	inst->integrator.in = inst->w * 3.1415f / 30.0f; // С переводом в [рад/с]
	inst->integrator.dt = inst->dt;
	FB_Integrator(&inst->integrator);
	inst->phi = inst->integrator.out;
}
