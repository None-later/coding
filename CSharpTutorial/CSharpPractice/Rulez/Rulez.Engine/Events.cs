using System;

namespace Rulez.Engine
{
	public delegate void RuleDelegate(object sender, RuleEventArgs e);

	public class RuleEventArgs : EventArgs
	{
		public RuleEventArgs() : base()
		{}
	}

	/// <summary>
	/// Fires the RuleDelegate Events
	/// </summary>
	public class Events
	{
		#region Public Static Method - FireEvent

		public static void FireEvent(RuleDelegate ruleEvent, object sender)
		{
			FireEvent(ruleEvent, sender, new RuleEventArgs());
		}

		public static void FireEvent(RuleDelegate ruleEvent, object sender, RuleEventArgs args)
		{
			if (ruleEvent != null)
			{
				ruleEvent(sender, args);
			}
		}

		#endregion
	}
}