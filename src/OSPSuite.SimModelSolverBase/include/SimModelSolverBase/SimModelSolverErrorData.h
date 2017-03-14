#ifndef _SimModelSolverErrorData_H_
#define _SimModelSolverErrorData_H_

#include <string>

#ifdef WIN32
#define SIMMODELSOLVER_EXPORT __declspec(dllexport)
#endif
#ifdef linux
#define SIMMODELSOLVER_EXPORT 
#endif

class SimModelSolverErrorData
{	
	public:
		enum errNumber
		{
			err_OK = 0,
			err_FAILURE,
			err_ILL_INPUT,
			err_TOO_MUCH_WORK,
			err_TOO_MUCH_ACC,
			err_TEST_FAILURE,
			err_CONV_FAILURE
		};
	
	private:
		errNumber m_Number;
		std::string m_Source;
		std::string m_Description;
	
	public:
		SIMMODELSOLVER_EXPORT SimModelSolverErrorData ();
		SIMMODELSOLVER_EXPORT SimModelSolverErrorData (errNumber Number, const std::string & Source, const std::string & Description);
		SIMMODELSOLVER_EXPORT const errNumber GetNumber () const;
		SIMMODELSOLVER_EXPORT void SetNumber (errNumber p_Number);
		SIMMODELSOLVER_EXPORT const std::string GetSource () const;
		SIMMODELSOLVER_EXPORT void SetSource (const std::string & p_Source);
		SIMMODELSOLVER_EXPORT const std::string GetDescription () const;
		SIMMODELSOLVER_EXPORT void SetDescription (const std::string & p_Description);
		SIMMODELSOLVER_EXPORT void operator = (const SimModelSolverErrorData & ED);
		SIMMODELSOLVER_EXPORT void SetError (errNumber Number, const std::string & Source, const std::string & Description);
		SIMMODELSOLVER_EXPORT void Clear ();
};

#endif //_SimModelSolverErrorData_H_

