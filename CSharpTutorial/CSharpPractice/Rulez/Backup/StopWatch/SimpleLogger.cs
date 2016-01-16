using System;
using System.Text;

namespace StopWatch
{
	/// <summary>
	/// Summary description for SimpleLogger.
	/// </summary>
	public class SimpleLogger
	{
		private readonly StringBuilder _log;
		private readonly HiPerfTimer _timer;

		public SimpleLogger(string Name)
		{
			_timer = new HiPerfTimer();

			_log = new StringBuilder(100);
			Log(string.Format("Logger Name: {0}", Name));
			Log(DateTime.Now.ToString());
		}

		#region Method - StartTimer()

		public void StartTimer(string Message)
		{
			Log(string.Format("Starting Timer: {0}", DateTime.Now.ToString()));
			Log(Message);

			_timer.Start();
		}

		#endregion

		#region Method - MarkTime()

		public void MarkTime()
		{
			Log(string.Format("Time +{0} seconds", _timer.Duration));
		}

		public void MarkTime(string Message)
		{
			Log(Message);
			MarkTime();
		}

		#endregion

		#region Method - StopTimer()

		public void StopTimer(string Message)
		{
			_timer.Stop();
			Log(string.Format("Timer Stopped: {0}\r\n", DateTime.Now));
			Log(string.Format("Duration: {0} Seconds\r\n", _timer.Duration.ToString()));
			Log(Message);
		}

		#endregion

		#region Method - Log Message

		public void Log(string Message)
		{
			_log.Append(Message).Append("\r\n");
		}

		#endregion

		#region Override - ToString()

		public override string ToString()
		{
			return _log.ToString();
		}

		#endregion
	}
}