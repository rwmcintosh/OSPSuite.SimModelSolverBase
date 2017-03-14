#include "SimModelSolverBase/OptionValueInfo.h"

OptionValueInfo::OptionValueInfo ()
{
	m_Value = 0.0;
}

OptionValueInfo::OptionValueInfo (double pValue, std::string pValueDescription)
{
	m_Value = pValue;
	m_ValueDescription = pValueDescription;
}

double OptionValueInfo::GetValue ()
{
    return m_Value;
}

void OptionValueInfo::SetValue (double p_Value)
{
    m_Value=p_Value;
}

std::string OptionValueInfo::GetValueDescription ()
{
    return m_ValueDescription;
}

void OptionValueInfo::SetValueDescription (std::string p_ValueDescription)
{
    m_ValueDescription=p_ValueDescription;
}

