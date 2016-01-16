namespace Rulez.OverTime
{
	public enum EmployeeType
	{
		Hourly,
		Salary
	}
	/// <summary>
	/// Summary description for Employee.
	/// </summary>
	public class Employee
	{
		public Employee(string Name, EmployeeType employeeType, double HoursWorked)
		{
			_hoursWorked = HoursWorked;
			_name = Name;
			_employeeType = employeeType;
			_overTimeHours = 0;
		}

		private readonly EmployeeType _employeeType;
		public EmployeeType EmployeeType
		{
			get { return _employeeType;}
		}

		private readonly string _name;
		public string Name
		{
			get { return _name; }
		}

		private readonly double _hoursWorked;

		public double HoursWorked
		{
			get { return _hoursWorked; }
		}

		private double _overTimeHours;

		public double OverTimeHours
		{
			get { return _overTimeHours; }
			set { _overTimeHours = value; }
		}
	}
}