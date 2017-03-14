#ifndef _SimModelSolverBase_H_
#define _SimModelSolverBase_H_

#include <vector>
#include <string>
#include "SolverCallerInterface/SolverCaller.h"
#include "SimModelSolverBase/SimModelSolverErrorData.h"
#include "SimModelSolverBase/OptionInfo.h"

class SimModelSolverBase
{	
	protected:

		//Pointer to the caller instance of the solver.
		//Used to call RHS/Jacobian/DDE-functions of the current problem (diff. eq. system)
		ISolverCaller * _solverCaller;

		bool _initialized;

		//No. of variables (= No. of equation) of the system
		int _problemSize;

		//Number of sensitivity parameters of the system
		int _numberOfSensitivityParameters;

		double _initialTime;
		std::vector < double > _initialValues;
		std::vector < double > _sensitivityParametersInitialValues;

		//Relative tolerance of ODE/DDE system
		double _relTol;

		//Absolute tolerance of ODE/DDE system
		std::vector < double > _absTol;

		//Max number of internal steps
		long _mxStep;

		//Initial solver step
		double _h0;

		//Minimal solver step
		double _hMin;

		//Maximal solver step
		double _hMax;

		//Delays size (Number of delays) for DDE system
		int _delaysSize;
	
	public:
		SIMMODELSOLVER_EXPORT SimModelSolverBase (ISolverCaller * pSolverCaller, int problemSize, int numberOfSensitivityParameters);
		SIMMODELSOLVER_EXPORT virtual ~SimModelSolverBase ();
		SIMMODELSOLVER_EXPORT ISolverCaller * GetSolverCaller ();

		//Get vector with information of "Non-Standard" solver options
		virtual std::vector < OptionInfo > GetSolverOptionsInfo () = 0;
		
		//-----------------------------------------------------------------------------------------------------
		//Solver dependent initialization routine
		//MUST be called before first call to PerformSolverStep after all solver properties are set
		//
		//Inherited class Init routine:
		// - MUST call SimModelSolverInterface::Init() first
		// - MUST set initialized status = true at the end (in case of success)
		//-----------------------------------------------------------------------------------------------------
		SIMMODELSOLVER_EXPORT virtual void Init ();
		
		//-----------------------------------------------------------------------------------------------------
		//Get solution of ODE/DDE system at the "next" timepoint.
		// - [IN] tout: next time at which a solution is required
		// - [OUT] tret: time point reached by solver:
		//                        - returns tout, if no error occured
		//                        - returns value < tout otherwise (e.g. max. no. of internal solver steps reached; 
		//                                                                                     no convergence etc.)
		// - [OUT] y: Solution vector at time tret
		// - [OUT] yS: Parameter sensitivities at time tret. yS[i][j]=dy_i/dp_j
		//Returns:
		// - 0 if successful
		// - positive value if a recoverable error occurred (e.g. max. no. of internal solver steps reached)
		// - negative value if an unrecoverable error occurred (e.g. illegal input)
		//-----------------------------------------------------------------------------------------------------
		SIMMODELSOLVER_EXPORT virtual int PerformSolverStep (double tout, double * y, double ** yS, double & tret) = 0;
		
		//-----------------------------------------------------------------------------------------------------
		//Reinitialize DE system (e.g. in case of bigger discontinuities). New relative / absolute tolerance should be set by caller prior to ReInit (if required)
		// - [IN] t0: continue integration from this time point
		// - [IN] y0: new initial value at t0
		//Returns:
		// - 0 if successful
		// - positive value if a recoverable error occurred 
		// - negative value if an unrecoverable error occurred 
		//
		//Inherited class:
		// - MUST call SimModelSolverInterface::ReInit first
		// - MUST perform solver-dependent checks (if applies)
		//-----------------------------------------------------------------------------------------------------
		SIMMODELSOLVER_EXPORT virtual int ReInit (double t0, const std::vector < double > & y0);
		
		//Solver dependent clean up routine (clear memory etc.)
		SIMMODELSOLVER_EXPORT virtual void Terminate () = 0;

		//Retrieve solver error message from any error code returned by PerformSolverStep or ReInit
		SIMMODELSOLVER_EXPORT virtual std::string GetSolverErrMsg (int solverRetVal) = 0;

		SIMMODELSOLVER_EXPORT virtual void SetOption (const std::string & name, double value) = 0;
		SIMMODELSOLVER_EXPORT int GetProblemSize ();
		SIMMODELSOLVER_EXPORT void SetProblemSize (int problemSize);

		SIMMODELSOLVER_EXPORT int GetNumberOfSensitivityParameters();
		SIMMODELSOLVER_EXPORT void SetNumberOfSensitivityParameters(int numberOfSensitivityParameters);

		SIMMODELSOLVER_EXPORT int GetDelaysSize ();
		SIMMODELSOLVER_EXPORT void SetDelaysSize (int delaysSize);
		SIMMODELSOLVER_EXPORT double GetInitialTime ();
		SIMMODELSOLVER_EXPORT void SetInitialTime (double initialTime);
		SIMMODELSOLVER_EXPORT std::vector < double > GetInitialValues ();
		SIMMODELSOLVER_EXPORT void SetInitialValues (const std::vector < double > & initialValues);

		SIMMODELSOLVER_EXPORT std::vector < double > GetSensitivityParametersInitialValues();
		SIMMODELSOLVER_EXPORT void SetSensitivityParametersInitialValues(const std::vector < double > & initialValues);

		SIMMODELSOLVER_EXPORT double GetRelTol ();
		SIMMODELSOLVER_EXPORT void SetRelTol (double relTol);
		SIMMODELSOLVER_EXPORT std::vector < double > GetAbsTol ();
		SIMMODELSOLVER_EXPORT void SetAbsTol (const std::vector < double > & absTol);
		SIMMODELSOLVER_EXPORT void SetAbsTol (double absTol);
		SIMMODELSOLVER_EXPORT long GetMxStep ();
		SIMMODELSOLVER_EXPORT void SetMxStep (long mxStep);
		SIMMODELSOLVER_EXPORT double GetH0 ();
		SIMMODELSOLVER_EXPORT void SetH0 (double h0);
		SIMMODELSOLVER_EXPORT double GetHMin ();
		SIMMODELSOLVER_EXPORT void SetHMin (double hMin);
		SIMMODELSOLVER_EXPORT double GetHMax ();
		SIMMODELSOLVER_EXPORT void SetHMax (double hMax);

		SIMMODELSOLVER_EXPORT virtual SimModelSolverErrorData::errNumber GetErrorNumberFromSolverReturnValue(int solverRetVal)=0;
};

#endif //_SimModelSolverBase_H_
