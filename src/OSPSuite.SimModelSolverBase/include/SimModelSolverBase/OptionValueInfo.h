#ifndef _OptionValueInfo_H_
#define _OptionValueInfo_H_

#include <string>
#include "SimModelSolverBase/SimModelSolverErrorData.h"

class OptionValueInfo
{		
	private:
		double m_Value;
		std::string m_ValueDescription;
	
	public:
		SIMMODELSOLVER_EXPORT OptionValueInfo ();
		SIMMODELSOLVER_EXPORT OptionValueInfo (double pValue, std::string pValueDescription);
		SIMMODELSOLVER_EXPORT double GetValue ();
		SIMMODELSOLVER_EXPORT void SetValue (double p_Value);
		SIMMODELSOLVER_EXPORT std::string GetValueDescription ();
		SIMMODELSOLVER_EXPORT void SetValueDescription (std::string p_ValueDescription);
};

#endif //_OptionValueInfo_H_
