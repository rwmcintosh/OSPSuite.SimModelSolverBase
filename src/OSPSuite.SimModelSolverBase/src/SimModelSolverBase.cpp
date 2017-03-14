#include "SimModelSolverBase/SimModelSolverBase.h"

SimModelSolverBase::SimModelSolverBase(ISolverCaller * pSolverCaller, int problemSize, int numberOfSensitivityParameters)
{
	//Save pointer to the solver caller instance
	//Use dynamic_cast to assure that the right pointer is passed
	_solverCaller = dynamic_cast <ISolverCaller *> (pSolverCaller);

	_problemSize = 0;
	this->SetProblemSize(problemSize);
	
	_numberOfSensitivityParameters = 0;
	this->SetNumberOfSensitivityParameters(numberOfSensitivityParameters);

	_initialTime = 0.0;
	_relTol = 1e-9;
	
	//default properties for ODE/DDE solver: 
	//  - min/max/initial internal step
	//  - max. no. of internal steps for the solver to reach the next output time point
	_mxStep = 100000;
	_h0 = 1e-10;
	_hMin = 0.;
	_hMax = 60;
	
	//Init-routine eas not called yet
	_initialized = false;
	
	_delaysSize = 0;
}

SimModelSolverBase::~SimModelSolverBase ()
{
}

ISolverCaller * SimModelSolverBase::GetSolverCaller ()
{
	return _solverCaller;
}

void SimModelSolverBase::Init ()
{
	const char * ERROR_SOURCE = "SimModelSolverInterface::Init";

	//general checks
	if (!_solverCaller) //should never happen
		throw SimModelSolverErrorData(SimModelSolverErrorData::err_FAILURE, ERROR_SOURCE,"Invalid pointer to the solver caller instance passed!");
	
	if (_problemSize == 0)
		throw SimModelSolverErrorData(SimModelSolverErrorData::err_FAILURE, ERROR_SOURCE,"Invalid number of absolute tolerances passed");

	if ((long)_absTol.size() != _problemSize)
		throw SimModelSolverErrorData(SimModelSolverErrorData::err_FAILURE, ERROR_SOURCE,"Number of absolute tolerances differs from problem size");

	if ((long)_initialValues.size() != _problemSize)
		throw SimModelSolverErrorData(SimModelSolverErrorData::err_FAILURE, ERROR_SOURCE,"Number of initial value components differs from problem size");	

	if ((long)_sensitivityParametersInitialValues.size() != _numberOfSensitivityParameters)
		throw SimModelSolverErrorData(SimModelSolverErrorData::err_FAILURE, ERROR_SOURCE, "Number of sensitivity parameters initial values differs from the number of sensitivity parameters");

	//solver dependent checks MUST be called by the routine of inherited class,
	//which also MUST set _initialized = true in case of success
}

int SimModelSolverBase::ReInit (double t0, const std::vector < double > & y0)
{
	const char * ERROR_SOURCE = "SimModelSolverInterface::ReInit";
	
	//check Initialized status
	if (!_initialized)
		throw SimModelSolverErrorData(SimModelSolverErrorData::err_FAILURE, ERROR_SOURCE,"Solver was not initialized");
	
	//set new initial value
	if ((long)y0.size() != _problemSize)
		throw SimModelSolverErrorData(SimModelSolverErrorData::err_FAILURE, ERROR_SOURCE,"Initial value has invalid number of components");	
	_initialValues = y0;
	
	//set new start time
	_initialTime = t0;
	
	return SimModelSolverErrorData::err_OK;
	
	//Solver-dependent reinit will be performed by inherited class
	//(which must call SimModelSolverInterface::ReInit first!)
}

int SimModelSolverBase::GetProblemSize ()
{
	return _problemSize;
}

void SimModelSolverBase::SetProblemSize (int problemSize)
{
	if (_problemSize == problemSize)
    	return; //nothing to do
    
	_problemSize = problemSize;
	if (_problemSize < 0)
		_problemSize = 0;

	//clear initial value
	_initialValues.clear();
	
	//clear absolute tolerances
	//(DO NOT reset to default - user must set new AbsTol explicitely)
	_absTol.clear();

	//reset initialized status
	_initialized = false;
}

int SimModelSolverBase::GetNumberOfSensitivityParameters()
{
	return _numberOfSensitivityParameters;
}

void SimModelSolverBase::SetNumberOfSensitivityParameters(int numberOfSensitivityParameters)
{
	if (_numberOfSensitivityParameters == numberOfSensitivityParameters)
		return; //nothing to do

	_numberOfSensitivityParameters = numberOfSensitivityParameters;

	_sensitivityParametersInitialValues.clear();

	//reset initialized status
	_initialized = false;
}

int SimModelSolverBase::GetDelaysSize ()
{
    return _delaysSize;
}

void SimModelSolverBase::SetDelaysSize (int delaysSize)
{
    _delaysSize=delaysSize;
}

double SimModelSolverBase::GetInitialTime ()
{
	return _initialTime;
}

void SimModelSolverBase::SetInitialTime (double initialTime)
{
	_initialTime = initialTime;
}

std::vector < double > SimModelSolverBase::GetInitialValues ()
{
	return _initialValues;
}

void SimModelSolverBase::SetInitialValues (const std::vector < double > & initialValues)
{
	_initialValues = initialValues;
}

std::vector < double > SimModelSolverBase::GetSensitivityParametersInitialValues()
{
	return _sensitivityParametersInitialValues;
}

void SimModelSolverBase::SetSensitivityParametersInitialValues(const std::vector < double > & initialValues)
{
	_sensitivityParametersInitialValues = initialValues;
}

double SimModelSolverBase::GetRelTol ()
{
	return _relTol;
}

void SimModelSolverBase::SetRelTol (double relTol)
{
	const char * ERROR_SOURCE = "SimModelSolverBase::SetRelTol";

	if (relTol <= 0.0)
		throw SimModelSolverErrorData(SimModelSolverErrorData::err_FAILURE, ERROR_SOURCE,"Relative tolerance must be > 0");

	_relTol = relTol;
}

std::vector < double > SimModelSolverBase::GetAbsTol ()
{
    return _absTol;
}

void SimModelSolverBase::SetAbsTol (const std::vector < double > & absTol)
{
	const char * ERROR_SOURCE = "SimModelSolverInterface::SetAbsTol";
	
	if (_problemSize == 0)
		throw SimModelSolverErrorData(SimModelSolverErrorData::err_FAILURE, ERROR_SOURCE,"Cannot set absolute tolerance: problem size not set!");

    _absTol=absTol;
}

void SimModelSolverBase::SetAbsTol (double absTol)
{
	const char * ERROR_SOURCE = "SimModelSolverInterface::SetAbsTol";
	
	if (_problemSize == 0)
		throw SimModelSolverErrorData(SimModelSolverErrorData::err_FAILURE, ERROR_SOURCE,"Cannot set absolute tolerance: problem size not set!");

	if (absTol <= 0.0)
		throw SimModelSolverErrorData(SimModelSolverErrorData::err_FAILURE, ERROR_SOURCE,"Absolute tolerance must be > 0");

	_absTol.clear();
	
	for (int i = 0; i< _problemSize; i++)
		_absTol.push_back(absTol);
}

long SimModelSolverBase::GetMxStep ()
{
    return _mxStep;
}

void SimModelSolverBase::SetMxStep (long mxStep)
{
    _mxStep=mxStep;
}

double SimModelSolverBase::GetH0 ()
{
    return _h0;
}

void SimModelSolverBase::SetH0 (double h0)
{
    _h0=h0;
}

double SimModelSolverBase::GetHMin ()
{
    return _hMin;
}

void SimModelSolverBase::SetHMin (double hMin)
{
    _hMin=hMin;
}

double SimModelSolverBase::GetHMax ()
{
    return _hMax;
}

void SimModelSolverBase::SetHMax (double hMax)
{
    _hMax=hMax;
}

