#ifndef _OptionInfo_H_
#define _OptionInfo_H_

#include <vector>
#include <string>
#include "SimModelSolverBase/OptionValueInfo.h"
#include "SimModelSolverBase/SimModelSolverErrorData.h"

class OptionInfo
{	
	public:
		enum SolverOptionDataType
		{
			SODT_Double,
			SODT_Integer,
			SODT_ListOfValues
		};
	
	private:
		std::string m_Name;
		std::string m_Description;
		double m_DefaultValue;
		SolverOptionDataType m_DataType;
		std::vector < OptionValueInfo > m_ListOfValues;
		double m_MinValue;
		double m_MaxValue;
	
	public:
		SIMMODELSOLVER_EXPORT OptionInfo ();
		SIMMODELSOLVER_EXPORT std::string GetName ();
		SIMMODELSOLVER_EXPORT void SetName (std::string p_Name);
		SIMMODELSOLVER_EXPORT std::string GetDescription ();
		SIMMODELSOLVER_EXPORT void SetDescription (std::string p_Description);
		SIMMODELSOLVER_EXPORT double GetDefaultValue ();
		SIMMODELSOLVER_EXPORT void SetDefaultValue (double p_DefaultValue);
		SIMMODELSOLVER_EXPORT SolverOptionDataType GetDataType ();
		SIMMODELSOLVER_EXPORT void SetDataType (SolverOptionDataType p_DataType);
		SIMMODELSOLVER_EXPORT const std::vector < OptionValueInfo > & GetListOfValues () const;
		SIMMODELSOLVER_EXPORT void AddOptionValue (OptionValueInfo pValueInfo);
		SIMMODELSOLVER_EXPORT double GetMinValue ();
		SIMMODELSOLVER_EXPORT void SetMinValue (double p_MinValue);
		SIMMODELSOLVER_EXPORT double GetMaxValue ();
		SIMMODELSOLVER_EXPORT void SetMaxValue (double p_MaxValue);
};

#endif //_OptionInfo_H_

