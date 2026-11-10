
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	axis_X.dt = 0.002f;
	
	Axis_X_HW.EncIf1_Typ = ncSDC_ENC16;
	Axis_X_HW.DiDoIf_Typ = ncSDC_DIDO;
	Axis_X_HW.DrvIf_Typ = ncSDC_DRVSERVO16;
	
	strcpy(Axis_X_HW.EncIf1_Name, "Axis_X_EncIf");
	strcpy(Axis_X_HW.DrvIf_Name, "Axis_X_DrvIf");
	strcpy(Axis_X_HW.DiDoIf_Name, "Axis_X_DiDoIf");
	Axis_X_EncIf.iEncOK = 1;
	Axis_X_DrvIf.iDrvOK = 1;
	Axis_X_DrvIf.iStatusEnable = 1;
	Axis_X_DiDoIf.iDriveReady = 1;
	
	fb_regulator.dt = 0.002f;
	//fb_motor.dt = 0.01f;
	//fb_motor.ke = 0.016f;
	//fb_motor.Tm = 0.1f;
	fb_regulator.max_abs_value = 24;
	fb_regulator.k_i = 0.16f;
	fb_regulator.k_p = 0.0f;
	fb_regulator.iyOld = 0.0f;
	
	axis_X.reset_error = 1;
	
	pwm_period = 200;
}

void _CYCLIC ProgramCyclic(void)
{
	BOOL ctrl_on;
	BOOL hand_pos;
	BOOL hand_neg;
	
	Axis_X_EncIf.iLifeCnt++;
	Axis_X_DiDoIf.iLifeCntDriveEnable++;
	Axis_X_DiDoIf.iLifeCntDriveReady++;
	Axis_X_DiDoIf.iLifeCntNegHwEnd++;
	Axis_X_DiDoIf.iLifeCntPosHwEnd++;
	Axis_X_DiDoIf.iLifeCntReference++;
	Axis_X_DrvIf.iLifeCnt++;
	Axis_X_EncIf.iActTime = (INT)AsIOTimeCyclicStart();
	
	Axis_X_EncIf.iActPos = axis_X.counter;
	Axis_X_DiDoIf.iPosHwEnd = axis_X.endswitch_a_reached;
	Axis_X_DiDoIf.iNegHwEnd = axis_X.endswitch_b_reached;
	Axis_X_DiDoIf.iDriveReady = coil_powered;
	
	coil_pwm_value = coil_powered ? 32767 : 0;
	
	ctrl_on = (Axis_X.controller.status == ncON);
	hand_pos = pos_hand_btn && !ctrl_on;
	hand_neg = neg_hand_btn && !ctrl_on;
	
	if (Axis_X.move.mode == ncHOMING)
		homing_active = 1;
	else if (homing_active && Axis_X.move.mode == ncOFF)
	{
		homing_active = 0;
		if (Axis_X.move.homing.status.ok && ctrl_on)
			ncaction((UDINT)&Axis_X, ncCONTROLLER, ncSWITCH_OFF);
	}
	
	fb_regulator.e = Axis_X_DrvIf.oSetPos * 6500.0f / 32767.0f - axis_X.speed;
	FB_Regulator(&fb_regulator);
	axis_X.u = fb_regulator.u;
	
	if (!coil_powered)
		axis_X.u = 0.0f;
	else if (hand_pos && !axis_X.endswitch_a_reached)
		axis_X.u = 12.0f;
	else if (hand_neg && !axis_X.endswitch_b_reached)
		axis_X.u = -12.0f;
	FB_Axis(&axis_X);
	if(axis_X.u > -4.0f && axis_X.u < 4.0f) // Слишком маленькое напряжение не позволяет провернуть двигатель, но пищит
		axis_X.pwm_value = 0;
	
	if (hand_pos || hand_neg || !coil_powered){
		axis_X.speed = 0.0f;
		fb_regulator.integrator.out = 0.0f;
		fb_regulator.iyOld = 0.0f;
	}
}

void _EXIT ProgramExit(void)
{

}

