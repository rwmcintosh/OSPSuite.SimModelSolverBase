#include "SimModelSolverBase/SimModelSolverErrorData.h"

SimModelSolverErrorData::SimModelSolverErrorData ()
{
	m_Number = err_OK;
	m_Source = "";
	m_Description = "";
}

SimModelSolverErrorData::SimModelSolverErrorData (errNumber Number, const std::string & Source, const std::string & Description)
{
	m_Number = Number;
	m_Source = Source;
	m_Description = Description;
}

const SimModelSolverErrorData::errNumber SimModelSolverErrorData::GetNumber () const
{
    return m_Number;
}

void SimModelSolverErrorData::SetNumber (errNumber p_Number)
{
    m_Number=p_Number;
}

const std::string SimModelSolverErrorData::GetSource () const
{
    return m_Source;
}

void SimModelSolverErrorData::SetSource (const std::string & p_Source)
{
    m_Source=p_Source;
}

const std::string SimModelSolverErrorData::GetDescription () const
{
    return m_Description;
}

void SimModelSolverErrorData::SetDescription (const std::string & p_Description)
{
    m_Description=p_Description;
}

void SimModelSolverErrorData::operator = (const SimModelSolverErrorData & ED)
{
	m_Number = ED.GetNumber();
	m_Description = ED.GetDescription();
	m_Source = ED.GetSource();
}

void SimModelSolverErrorData::SetError (errNumber Number, const std::string & Source, const std::string & Description)
{
	m_Number = Number;
	m_Description = Description;
	m_Source = Source;
}

void SimModelSolverErrorData::Clear ()
{
	m_Number = err_OK;
	m_Description = "";
	m_Source = "";
}

