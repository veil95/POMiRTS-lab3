
{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_Integrator (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		in : {REDUND_UNREPLICABLE} REAL;
	END_VAR
	VAR_OUTPUT
		out : {REDUND_UNREPLICABLE} REAL;
	END_VAR
	VAR
		dt : {REDUND_UNREPLICABLE} REAL;
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_Motor (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		u : {REDUND_UNREPLICABLE} REAL; (*Напряжение на двигателе*)
	END_VAR
	VAR_OUTPUT
		w : {REDUND_UNREPLICABLE} REAL; (*Угловая скорость вала*)
		phi : {REDUND_UNREPLICABLE} REAL; (*Угол поворота вала*)
	END_VAR
	VAR
		integrator : {REDUND_UNREPLICABLE} FB_Integrator; (*Интегратор*)
		Tm : {REDUND_UNREPLICABLE} REAL; (*Механическая постоянная времени*)
		ke : {REDUND_UNREPLICABLE} REAL; (*коэф двигателя по напряжению*)
		dt : {REDUND_UNREPLICABLE} REAL; (*шаг дискретизации*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_Regulator (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		e : {REDUND_UNREPLICABLE} REAL; (*ошибка регулирования*)
	END_VAR
	VAR_OUTPUT
		u : {REDUND_UNREPLICABLE} REAL; (*выходное напряжение*)
	END_VAR
	VAR
		k_p : {REDUND_UNREPLICABLE} REAL; (*кэф П-регулятора*)
		k_i : {REDUND_UNREPLICABLE} REAL; (*кэф И-регулятора*)
		integrator : {REDUND_UNREPLICABLE} FB_Integrator; (*интегратор*)
		iyOld : {REDUND_UNREPLICABLE} REAL; (*превышение выхода над ограничением*)
		max_abs_value : {REDUND_UNREPLICABLE} REAL; (*ограничение выхода*)
		dt : {REDUND_UNREPLICABLE} REAL; (*шаг дискретизации*)
	END_VAR
END_FUNCTION_BLOCK

{REDUND_ERROR} {REDUND_UNREPLICABLE} FUNCTION_BLOCK FB_Axis (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		reset_error : {REDUND_UNREPLICABLE} BOOL; (*Сброс ошибок мотора*)
		endswitch_a_reached : {REDUND_UNREPLICABLE} BOOL; (*Состояние начального концевого датчика*)
		endswitch_b_reached : {REDUND_UNREPLICABLE} BOOL; (*Состояние конечного концевого датчика*)
	END_VAR
	VAR_OUTPUT
		reset_counter : {REDUND_UNREPLICABLE} BOOL; (*Сброс счётчика*)
		pwm_value : {REDUND_UNREPLICABLE} INT; (*Время Импулься ШИМ*)
		counter : {REDUND_UNREPLICABLE} INT; (*Счётчик импульсов*)
		speed : {REDUND_UNREPLICABLE} REAL; (*Скорость вращения оси двигателя*)
	END_VAR
	VAR
		last_counter : {REDUND_UNREPLICABLE} INT; (*Хранение предыдущего значения counter в процессе расчёта*)
		dt : {REDUND_UNREPLICABLE} REAL; (*Шаг дискретизации*)
	END_VAR
	VAR_INPUT
		u : {REDUND_UNREPLICABLE} REAL; (*Напряжение с выхода регулятора*)
	END_VAR
END_FUNCTION_BLOCK
