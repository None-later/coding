namespace Rulez.Engine
{
	public interface IRule
	{
		string Name { get; }

		void Invoke();
		void Invoke(object sender, RuleEventArgs e);

		event RuleDelegate RulePassed;
		void OnRulePassed(object sender);

		event RuleDelegate RuleFailed;
		void OnRuleFailed(object sender);

		event RuleDelegate BeginRuleEvaluation;
		void OnBeginRuleEvaluation(object sender);

		event RuleDelegate EndRuleEvaluation;
		void OnEndRuleEvaluation(object sender);

		void RegisterRules();
		void RegisterRules(IRule rulePassed, IRule ruleFailed);
		void RegisterRules(params IRule[] rules);
	}
}