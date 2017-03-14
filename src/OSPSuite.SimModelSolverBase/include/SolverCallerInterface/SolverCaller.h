#ifndef _SolverCaller_H_
#define _SolverCaller_H_

enum Rhs_Return_Value
{
	RHS_FAILED=-1,
	RHS_OK=0,
	RHS_RECOVERABLE_ERROR=1
};

enum Jacobian_Return_Value
{
	JACOBIAN_FAILED=-1,
	JACOBIAN_OK=0,
	JACOBIAN_RECOVERABLE_ERROR=1
};

enum Sensitivity_Rhs_Return_Value
{
	SENSITIVITY_RHS_FAILED = -1,
	SENSITIVITY_RHS_OK = 0,
	SENSITIVITY_RHS_RECOVERABLE_ERROR = 1
};

//-------------------------------------------------------------------------
//Common ODE/DDE Solver Caller Interface.
//Will be passed to every Solver instance to  provide function calls to 
//RHS/Jacobian/DDE-functions of the current diff. equations system.
//-------------------------------------------------------------------------

class ISolverCaller
{		
	public:
		//-----------------------------------------------------------------------------------------------------
		//RHS Function of the ODE system dy/dt = f(t, y(t))
		// - [IN] t: current time
		// - [IN] y: Solution vector at time t
		// - [IN] p: parameter values for sensitivity parameters
		// - [OUT] ydot: RHS function value of ODE System
		// - [IN, OPTIONAL] f_data: data passed to the RHS function
		//-----------------------------------------------------------------------------------------------------
		virtual Rhs_Return_Value ODERhsFunction(double t, const double * y, const double * p, double * ydot, void * f_data) = 0;

		//-----------------------------------------------------------------------------------------------------
		//Jacobian function of the ODE system dy/dt = f(t, y(t))
		// - [IN] t: current time
		// - [IN] y: Solution vector at time t
		// - [IN] p: parameter values for sensitivity parameters
		// - [IN] fy: RHS function value at (t, y) 
		// - [OUT] Jacobian: Jacobian Matrix of the ODE system at (t, y)
		// - [IN, OPTIONAL] Jac_data: data passed to the function
		//-----------------------------------------------------------------------------------------------------
		virtual Jacobian_Return_Value ODEJacFunction(double t, const double * y, const double * p, const double * fy, double * * Jacobian, void * Jac_data) = 0;
		
		//-----------------------------------------------------------------------------------------------------
		//RHS Function of the DDE system dy/dt = f(t, y(t), yd)
		// - [IN] t: current time
		// - [IN] y: Solution vector at time t
		// - [IN] yd: yd(i, j) = y_i(delay(j)), where delay(j) is j-th component of the delays(t, y(t))
		// - [OUT] ydot: RHS function value of DDE System
		// - [IN, OPTIONAL] f_data: data passed to the RHS function
		//-----------------------------------------------------------------------------------------------------
		virtual Rhs_Return_Value DDERhsFunction (double t, const double * y, const double * * yd, double * ydot, void * f_data) = 0;
		
		//-----------------------------------------------------------------------------------------------------
		//Delays function of the DDE system dy/dt = f(t, y(t), yd)
		//  - [IN] t: current time
		//  - [IN] y: Solution vector at time t
		//  - [OUT] delays: Delays vector
		//  - [IN, OPTIONAL] delays_data: data passed to the RHS function
		//-----------------------------------------------------------------------------------------------------
		virtual void DDEDelayFunction (double t, const double * y, double * delays, void * delays_data) = 0;
		
		//-----------------------------------------------------------------------------------------------------
		//Sensitivity RHS Function for the ODE system dy/dt = f(t, y(t), p)
		//
		//This function computes the sensitivity right-hand side for ONE sensitivity equation at a time.
		//It must compute the vector(df/dy)s_i(t) + (df/dp_i) for i = iS and store it in ySdot (where s_i(t)= dy(t)/dp_i)
		//
		// - [IN] t: current time
		// - [IN] y: Solution vector at time t
		// - [OUT] ydot: RHS function value of ODE System
		// - [IN]  iS: index of parameter, whose sensitivity should be returned 
		//             (iS: [0..NS-1], where NS is no of sensitivity paramsters)
		// - [OUT] ySdot: stores the iS-th sensitivity RHS vector
		// - [IN, OPTIONAL] f_data: data passed to the RHS function
		//-----------------------------------------------------------------------------------------------------
		virtual Sensitivity_Rhs_Return_Value ODESensitivityRhsFunction(double t, const double * y, double * ydot,
			                                                           int iS, const double * yS, double * ySdot, void * f_data) = 0;

		//Returns true, if ODE RHS function is set (we have an ODE system)
		virtual bool IsSet_ODERhsFunction () = 0;

		//Returns true, if ODE Jacobian function is set (we have an ODE system AND Jacobian function of the ODE system is available)
		virtual bool IsSet_ODEJacFunction () = 0;

		//Returns true, if ODE Sensitivity RHS function is set (we have an ODE system and SENSITIVITY RHS calculation is available)
		virtual bool IsSet_ODESensitivityRhsFunction() = 0;

		//Returns true, if DDE RHS function is set (we have a DDE system)
		virtual bool IsSet_DDERhsFunction () = 0;

		//Returns true if band linear solver should be used
		virtual bool UseBandLinearSolver() = 0;
		
		//Returns lower halfband width of the DE system.
		//(only relevant if UseBandLinearSolver is set to true)
		virtual int GetLowerHalfBandWidth() = 0;
		
		//Returns upper halfband width of the DE system.
		//(only relevant if UseBandLinearSolver is set to true)
		virtual int GetUpperHalfBandWidth() = 0;
};


#endif //_SolverCaller_H_

