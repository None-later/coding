using System;
using System.Security.Cryptography;

namespace Rulez.RandomRules
{
	public class GenerateRandomNumbers
	{
		public GenerateRandomNumbers()
		{
		}

		public int GetRandomNumber(bool noZeros)
		{
			byte[] random = new Byte[1];
			RNGCryptoServiceProvider rng = new RNGCryptoServiceProvider();
			if (noZeros)
			{
				rng.GetNonZeroBytes(random);
			}
			else
			{
				rng.GetBytes(random);
			}
			return (int)random[0];
		}

		public static int GetRandomNumber(int high)
		{
			byte[] random = new Byte[4];
			new RNGCryptoServiceProvider().GetBytes(random);
			int randomNumber = BitConverter.ToInt32(random, 0);

			return Math.Abs(randomNumber % high);
		}

		public int GetRandomNumber(int low, int high)
		{
			return new Random().Next(low, high);
		}

		public double GetRandomNumber()
		{
			return new Random().NextDouble();
		}
	}
}
