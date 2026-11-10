
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
void FB_Axis(struct FB_Axis* inst)
{
	inst->pwm_value = (INT)(inst->u / 24.0f * 32767.0f);
	inst->speed = inst->u / 24.0f * 6500.0f;
}
