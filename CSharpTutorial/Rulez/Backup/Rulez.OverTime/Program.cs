using System;
using Rulez.Engine;

namespace Rulez.OverTime
{
    class Program
    {
        static void Main(string[] args)
        {
            Program p = new Program();
            p._calcOT("Darren", EmployeeType.Hourly, 40, 0);
            p._calcOT("Darren", EmployeeType.Hourly, 45, 7.5);
            p._calcOT("Darren", EmployeeType.Hourly, 60, 30);
            p._calcOT("Darren", EmployeeType.Hourly, 65, 40);
            p._calcOT("Darren", EmployeeType.Salary, 40, 0);
            p._calcOT("Darren", EmployeeType.Salary, 45, 0);
            p._calcOT("Darren", EmployeeType.Salary, 60, 22.5);
            p._calcOT("Darren", EmployeeType.Salary, 65, 32.5);

            Console.Read();
        }

        public void _calcOT(string Name, EmployeeType empType, double HoursWorked, double ExpectedOT)
        {
            Employee emp = new Employee(Name, empType, HoursWorked);
            TheRuleList trl = new TheRuleList(emp);
            trl.Invoke();

            Console.WriteLine("Name: {0}\tEmployeeType: {1}\tHoursWorked: {2}\tOverTime: {3}\tExpected OverTime: {4}"
            , Name, empType.ToString(), HoursWorked.ToString(), emp.OverTimeHours.ToString(), ExpectedOT.ToString());

        }

    }
}
