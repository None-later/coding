using System;
using Rulez.Engine;

namespace Rulez.OverTime
{
	/// <summary>
	/// Summary description for BaseBizRule.
	/// </summary>
	public class BaseBizRule : BaseRule
	{
		protected readonly Employee employee;

		public BaseBizRule(string Name, Employee employee) : base(Name)
		{
			this.employee = employee;
		}

		public override void Invoke()
		{
			Invoke(this, EventArgs.Empty as RuleEventArgs);
		}

	}
}
