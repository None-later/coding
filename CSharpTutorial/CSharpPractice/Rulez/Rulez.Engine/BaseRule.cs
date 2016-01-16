using System;

namespace Rulez.Engine
{
	/// <summary>
	/// Summary description for BaseRule.
	/// </summary>
	public class BaseRule : IRule
	{
		#region Constructors

		public BaseRule(string Name)
		{
			_name = Name;
		}

		#endregion

		#region Property - Name

		private readonly string _name;

		public string Name
		{
			get { return _name; }
		}

		#endregion

		#region Method - Invoke

		public virtual void Invoke()
		{
			throw new NotImplementedException();
		}

		public virtual void Invoke(object sender, RuleEventArgs e)
		{
			throw new NotImplementedException();
		}

		#endregion

		#region Rule Passed

		public event RuleDelegate RulePassed;

		public void OnRulePassed(object sender)
		{
			Events.FireEvent(RulePassed, sender);
		}

		#endregion

		#region Rule Failed

		public event RuleDelegate RuleFailed;

		public void OnRuleFailed(object sender)
		{
			Events.FireEvent(RuleFailed, sender);
		}

		#endregion

		#region Begin Rule Evaluation

		public event RuleDelegate BeginRuleEvaluation;

		public void OnBeginRuleEvaluation(object sender)
		{
			Events.FireEvent(BeginRuleEvaluation, sender);
		}

		#endregion

		#region End Rule Evaluation

		public event RuleDelegate EndRuleEvaluation;

		public void OnEndRuleEvaluation(object sender)
		{
			Events.FireEvent(EndRuleEvaluation, sender);
		}

		#endregion

		#region Method - RegisterRules()

		public void RegisterRules()
		{
			throw new NotImplementedException();
		}
		
		public void RegisterRules(IRule rulePassed, IRule ruleFailed)
		{
			if (rulePassed == null) throw new ArgumentNullException("rulePassed");
			if (ruleFailed == null) throw new ArgumentNullException("ruleFailed");

			this.RulePassed += new RuleDelegate(rulePassed.Invoke);
			this.RuleFailed += new RuleDelegate(ruleFailed.Invoke);
		}

		public void RegisterRules(params IRule[] rules)
		{
			throw new NotImplementedException();
		}
		#endregion
	}
}