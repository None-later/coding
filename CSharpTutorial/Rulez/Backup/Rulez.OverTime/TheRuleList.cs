using Rulez.Engine;

namespace Rulez.OverTime
{
	/// <summary>
	/// Summary description for TheRuleList.
	/// </summary>
	public class TheRuleList : BaseBizRule
	{
		#region The Rulez

		private Rule1 r1;
		private Rule2 r2;
		private Rule3 r3;

		private Rule2_1 r2_1;
		private Rule2_2 r2_2;
		private Rule2_2_1 r2_2_1;
		private Rule2_2_2 r2_2_2;

		private Rule3_1 r3_1;
		private Rule3_2 r3_2;

		private RuleIsSalary r_isSalary1;
		private RuleIsSalary r_isSalary2;

		private RuleTerminator rt;

		#endregion

		#region Constructor

		public TheRuleList(Employee employee) : base("TheRuleList", employee)
		{
			r1 = new Rule1(employee);
			r2 = new Rule2(employee);
			r3 = new Rule3(employee);

			r2_1 = new Rule2_1(employee);
			r2_2 = new Rule2_2(employee);
			r2_2_1 = new Rule2_2_1(employee);
			r2_2_2 = new Rule2_2_2(employee);

			r3_1 = new Rule3_1(employee);
			r3_2 = new Rule3_2(employee);

			r_isSalary1 = new RuleIsSalary(employee);
			r_isSalary2 = new RuleIsSalary(employee);

			rt = new RuleTerminator(employee);

			r1.RegisterRules(rt, r2);
			r2.RegisterRules(r_isSalary1, r3);
			r3.RegisterRules(r_isSalary2, rt);

			r_isSalary1.RegisterRules(r2_2, r2_1);
			r_isSalary2.RegisterRules(r3_2, r3_1);

			r2_2.RegisterRules(r2_2_1, r2_2_2);

			r2_1.RegisterRules(rt, rt);
			r2_2_1.RegisterRules(rt, rt);
			r2_2_2.RegisterRules(rt, rt);

			r3_1.RegisterRules(rt, rt);
			r3_2.RegisterRules(rt, rt);
		}

		#endregion

		#region Invoke()

		public override void Invoke()
		{
			OnBeginRuleEvaluation(this);

			r1.Invoke();

			OnEndRuleEvaluation(this);
		}

		#endregion
	}

	#region RuleTerminator

	public class RuleTerminator : BaseBizRule
	{
		public RuleTerminator(Employee employee) : base("RuleTerminator", employee)
		{}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			OnBeginRuleEvaluation(this);

			OnEndRuleEvaluation(this);
		}

	}

	#endregion

	#region Rule 1 If the Employee worked 40 hours or less

	public class Rule1 : BaseBizRule
	{
		public Rule1(Employee employee) : base("Rule1", employee)
		{}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			OnBeginRuleEvaluation(this);

			if (employee.HoursWorked <= 40)
			{
				employee.OverTimeHours = 0;
				OnRulePassed(this);
			}
			else
			{
				OnRuleFailed(this);
			}

			OnEndRuleEvaluation(this);
		}
	}

	#endregion

	#region Rule 2 Employee worked over 40 and less than 60 hrs

	public class Rule2 : BaseBizRule
	{
		public Rule2(Employee employee) : base("Rule2", employee)
		{}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			OnBeginRuleEvaluation(this);

			if (employee.HoursWorked > 40 && employee.HoursWorked <= 60)
			{
				OnRulePassed(this);
			}
			else
			{
				OnRuleFailed(this);
			}

			OnEndRuleEvaluation(this);
		}

	}

	#endregion

	#region Rule 3 Employee worked over 60 hrs

	public class Rule3 : BaseBizRule
	{
		public Rule3(Employee employee) : base("Rule3", employee)
		{}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			OnBeginRuleEvaluation(this);

			if (employee.HoursWorked > 60)
			{
				OnRulePassed(this);
			}
			else
			{
				OnRuleFailed(this);
			}

			OnEndRuleEvaluation(this);
		}

	}

	#endregion

	#region IsSalary - Is EmployeeType == Salary

	public class RuleIsSalary : BaseBizRule
	{
		public RuleIsSalary(Employee employee) : base("IsSalary", employee)
		{}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			OnBeginRuleEvaluation(this);

			if (employee.EmployeeType == EmployeeType.Salary)
			{
				OnRulePassed(this);
			}
			else
			{
				OnRuleFailed(this);
			}

			OnEndRuleEvaluation(this);
		}

	}

	#endregion

	#region Rule 2.1 Hourly Employee worked over 40 and less than 60 hrs

	public class Rule2_1 : BaseBizRule
	{
		public Rule2_1(Employee employee) : base("Rule2_1", employee)
		{}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			OnBeginRuleEvaluation(this);

			employee.OverTimeHours = 1.5*(employee.HoursWorked - 40.0);

			OnRulePassed(this);

			OnEndRuleEvaluation(this);
		}
	}

	#endregion

	#region Rule 2.2 Salary Employee worked over 40 and less than 45 hrs

	public class Rule2_2 : BaseBizRule
	{
		public Rule2_2(Employee employee) : base("Rule2_2", employee)
		{}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			OnBeginRuleEvaluation(this);

			if (employee.HoursWorked > 40 && employee.HoursWorked <= 45)
			{
				OnRulePassed(this);
			}
			else
			{
				OnRuleFailed(this);
			}

			OnEndRuleEvaluation(this);
		}
	}

	#endregion

	#region Rule 2.2.1 Salary Employee worked over 40 and less than 45 hrs

	public class Rule2_2_1 : BaseBizRule
	{
		public Rule2_2_1(Employee employee) : base("Rule2_2_1", employee)
		{}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			OnBeginRuleEvaluation(this);

			employee.OverTimeHours = 0;

			OnRulePassed(this);

			OnEndRuleEvaluation(this);
		}
	}

	#endregion

	#region Rule 2.2.2 Salary Employee worked over 45 and less than 60 hrs

	public class Rule2_2_2 : BaseBizRule
	{
		public Rule2_2_2(Employee employee) : base("Rule2_2_2", employee)
		{}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			OnBeginRuleEvaluation(this);

			employee.OverTimeHours = 1.5*(employee.HoursWorked - 45);

			OnRulePassed(this);

			OnEndRuleEvaluation(this);
		}
	}

	#endregion

	#region Rule 3.1 Hourly Employee worked over 60 hrs

	public class Rule3_1 : BaseBizRule
	{
		public Rule3_1(Employee employee) : base("Rule3_1", employee)
		{}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			OnBeginRuleEvaluation(this);

			employee.OverTimeHours = 1.5*20 + 2*(employee.HoursWorked - 60);

			OnRulePassed(this);

			OnEndRuleEvaluation(this);
		}
	}

	#endregion

	#region Rule 3.2 Salary Employee worked over 60 hrs

	public class Rule3_2 : BaseBizRule
	{
		public Rule3_2(Employee employee) : base("Rule3_2", employee)
		{}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			OnBeginRuleEvaluation(this);

			employee.OverTimeHours = 1.5*15 + 2*(employee.HoursWorked - 60);

			OnRulePassed(this);

			OnEndRuleEvaluation(this);
		}
	}

	#endregion
}