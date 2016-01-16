using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using System.Text;

namespace StopWatch
{
	public class Logging
	{
		public double StartTicks;
		public double EndTicks;
		public double cumTime;
		public string ActiveGUID = String.Empty;
		public string strLogFileName = String.Empty;
		private HiPerfTimer hpt;

		public Logging(string strFileName)
		{
			if (strFileName != "")
			{
				strLogFileName = strFileName;
			}
			else
			{
				strLogFileName = "DefaultAppLog";
			}
			hpt = new HiPerfTimer();
		}

		public string StartLogEntry(string strLogEntryName, string strComment)
		{
			string lf = String.Empty;
			if (strLogFileName != "")
			{
				lf = @"\" + strLogFileName + ".csv";
			}
			else
			{
				lf = @"\DefaultAppLog.csv";
			}
			string strFullLogPathName = AppDomain.CurrentDomain.BaseDirectory.ToString() + lf;
			string strLogEntryGUID = Guid.NewGuid().ToString();
			ActiveGUID = strLogEntryGUID;
			string strtime = DateTime.Now.ToShortDateString() + ": " + DateTime.Now.ToShortTimeString();


			hpt.Start();
			StartTicks = 0; // set to zero
			cumTime = 0;
			Debug.WriteLine(StartTicks.ToString());
			StringBuilder sbLog = new StringBuilder();
			sbLog.Append("New Entry: ");
			sbLog.Append(",");
			sbLog.Append(strLogEntryGUID);
			sbLog.Append(",");
			sbLog.Append(strtime);
			sbLog.Append(",");
			sbLog.Append(strLogEntryName);
			sbLog.Append(",");
			sbLog.Append(strComment);
			sbLog.Append("| Caller: ");
			string strCallAssy = Assembly.GetCallingAssembly().ToString();
			strCallAssy = strCallAssy.Substring(0, strCallAssy.IndexOf(","));
			sbLog.Append(strCallAssy);

			sbLog.Append(",");
			sbLog.Append("0");
			sbLog.Append(",");
			sbLog.Append("0");
			sbLog.Append("\r\n");
			try
			{
				FileInfo fi = new FileInfo(strFullLogPathName);
				FileStream sWriterAppend = fi.Open(FileMode.Append, FileAccess.Write, FileShare.ReadWrite);
				sWriterAppend.Write(Encoding.ASCII.GetBytes(sbLog.ToString()), 0, sbLog.Length);
				sWriterAppend.Flush();
				sWriterAppend.Close();
				sbLog = null;
				fi = null;
				sWriterAppend = null;
			}
			catch (Exception ex)
			{
				sbLog = null;
				return ex.Message;
			}
			return strLogEntryGUID;
		}

		public string AddLogEntry(string strLogEntryGUID, string strLogEntryName, string strComment)
		{
			if (strLogEntryGUID != ActiveGUID) throw new Exception("Log Entry GUID Mismatch.");

			string lf = String.Empty;

			if (strLogFileName.Length > 0)
			{
				lf = @"\" + strLogFileName + ".csv";
			}
			else
			{
				lf = @"\DefaultAppLog.csv";
			}

			string strFullLogPathName = AppDomain.CurrentDomain.BaseDirectory.ToString() + lf;
			string strtime = DateTime.Now.ToShortDateString() + ": " + DateTime.Now.ToShortTimeString();

			hpt.Stop();
			EndTicks = hpt.Duration;
			cumTime += EndTicks; // add to cum time elapsed

			StringBuilder sbLog = new StringBuilder();
			sbLog.Append("Add Entry: ");
			sbLog.Append(",");
			sbLog.Append(strLogEntryGUID);
			sbLog.Append(",");
			sbLog.Append(strtime);
			sbLog.Append(",");
			sbLog.Append(strLogEntryName);
			sbLog.Append(",");
			sbLog.Append(strComment);
			sbLog.Append(",");
			string strIntElapsed = String.Empty;


			sbLog.Append(EndTicks.ToString()); // this event duration in sec
			sbLog.Append(",");
			strIntElapsed = cumTime.ToString();
			hpt.Start();
			sbLog.Append(strIntElapsed);
			sbLog.Append("\r\n");
			try
			{
				FileInfo fi = new FileInfo(strFullLogPathName);
				FileStream sWriterAppend = fi.Open(FileMode.Append, FileAccess.Write, FileShare.ReadWrite);
				sWriterAppend.Write(Encoding.ASCII.GetBytes(sbLog.ToString()), 0, sbLog.Length);
				sWriterAppend.Flush();
				sWriterAppend.Close();
				sbLog = null;
				fi = null;
				sWriterAppend = null;
			}
			catch (Exception ex)
			{
				sbLog = null;
				return ex.Message;
			}
			return strLogEntryGUID;
		}

		public string CloseLogEntry(string strLogEntryGUID, string strLogEntryName, string strComment)
		{
			if (strLogEntryGUID != ActiveGUID)
			{
				throw new Exception("Log Entry GUID Mismatch.");
			}
			string lf = String.Empty;

			if (strLogFileName != "")
			{
				lf = @"\" + strLogFileName + ".csv";
			}
			else
			{
				lf = @"\DefaultAppLog.csv";
			}

			string strFullLogPathName = AppDomain.CurrentDomain.BaseDirectory.ToString() + lf;
			string strtime = DateTime.Now.ToShortDateString() + ": " + DateTime.Now.ToShortTimeString();
			hpt.Stop();
			EndTicks = hpt.Duration;
			cumTime += EndTicks; // add to cum time elapsed
			StringBuilder sbLog = new StringBuilder();
			sbLog.Append("Close Entry: ");
			sbLog.Append(",");
			sbLog.Append(strLogEntryGUID);
			sbLog.Append(",");
			sbLog.Append(strtime);
			sbLog.Append(",");
			sbLog.Append(strLogEntryName);
			sbLog.Append(",");
			sbLog.Append(strComment);
			sbLog.Append(",");
			sbLog.Append(EndTicks.ToString());
			sbLog.Append(",");
			sbLog.Append(cumTime.ToString());
			sbLog.Append("\r\n");
			try
			{
				FileInfo fi = new FileInfo(strFullLogPathName);
				FileStream sWriterAppend = fi.Open(FileMode.Append, FileAccess.Write, FileShare.ReadWrite);
				sWriterAppend.Write(Encoding.ASCII.GetBytes(sbLog.ToString()), 0, sbLog.Length);
				sWriterAppend.Flush();
				sWriterAppend.Close();
				sbLog = null;
				fi = null;
				sWriterAppend = null;
				StartTicks = 0;

				EndTicks = 0;
				cumTime = 0;
			}
			catch (Exception ex)
			{
				sbLog = null;
				return ex.Message;
			}
			return strLogEntryGUID;
		}
	}


}