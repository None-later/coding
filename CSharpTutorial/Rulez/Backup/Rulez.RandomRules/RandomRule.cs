using System;
using Rulez.Engine;
using StopWatch;

namespace Rulez.RandomRules
{
	/// <summary>
	/// RandomRule - The rule randomly passes or fails.
	/// </summary>
	public class RandomRule : BaseRule
	{
		#region Constructor

		private readonly SimpleLogger _logger;

		public RandomRule(SimpleLogger logger, string Name) : base(Name)
		{
			_logger = logger;
		}

		#endregion

		#region Invoke() Overrides

		public override void Invoke()
		{
			Invoke(this, EventArgs.Empty as RuleEventArgs);
		}

		public override void Invoke(object sender, RuleEventArgs e)
		{
			bool pass = (GenerateRandomNumbers.GetRandomNumber(999))%2 == 0;

            _logger.Log(string.Format("Results: {1} :: Rule Name: {0}, ", Name, pass ? "PASSED" : "FAILED"));
			if (pass)
				OnRulePassed(this);
			else
				OnRuleFailed(this);
		}

		#endregion

		#region Build RandomRule Tree

		public static RandomRule BuildRuleTree(int CurrentDepth, int MaxDepth
		                                       , SimpleLogger logger, string Name)
		{
			RandomRule rr = new RandomRule(logger, Name);
			CurrentDepth += 1;

			if (CurrentDepth <= MaxDepth)
				rr.RegisterRules(
					BuildRuleTree(CurrentDepth, MaxDepth, logger, Name + ".Passed")
					, BuildRuleTree(CurrentDepth, MaxDepth, logger, Name + ".Failed"));

			return rr;
		}

		#endregion
	}
}