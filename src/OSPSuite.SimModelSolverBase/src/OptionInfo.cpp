#include "SimModelSolverBase/OptionInfo.h"

OptionInfo::OptionInfo ()
{
	m_DataType = SODT_Double;
	m_DefaultValue = 0.0;
	m_MaxValue = 1.0e300;
	m_MinValue = -1.0e300;
}

std::string OptionInfo::GetName ()
{
    return m_Name;
}

void OptionInfo::SetName (std::string p_Name)
{
    m_Name=p_Name;
}

std::string OptionInfo::GetDescription ()
{
    return m_Description;
}

void OptionInfo::SetDescription (std::string p_Description)
{
    m_Description=p_Description;
}

double OptionInfo::GetDefaultValue ()
{
    return m_DefaultValue;
}

void OptionInfo::SetDefaultValue (double p_DefaultValue)
{
    m_DefaultValue=p_DefaultValue;
}

OptionInfo::SolverOptionDataType OptionInfo::GetDataType ()
{
    return m_DataType;
}

void OptionInfo::SetDataType (SolverOptionDataType p_DataType)
{
    m_DataType=p_DataType;
}

const std::vector < OptionValueInfo > & OptionInfo::GetListOfValues () const
{
    return m_ListOfValues;
}

void OptionInfo::AddOptionValue (OptionValueInfo pValueInfo)
{
	m_ListOfValues.push_back(pValueInfo);
}

double OptionInfo::GetMinValue ()
{
    return m_MinValue;
}

void OptionInfo::SetMinValue (double p_MinValue)
{
    m_MinValue=p_MinValue;
}

double OptionInfo::GetMaxValue ()
{
    return m_MaxValue;
}

void OptionInfo::SetMaxValue (double p_MaxValue)
{
    m_MaxValue=p_MaxValue;
}

