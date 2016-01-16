using System;
using System.Collections.Generic;
using System.Text;
using StopWatch;

namespace Rulez.RandomRules
{
    class Program
    {
        static void Main(string[] args)
        {
            SimpleLogger log = new SimpleLogger("RandomRuleBuilder");
            log.StartTimer("Building Rules");

            RandomRule baseRule = RandomRule.BuildRuleTree(0, 10, log, "BaseRule");
            log.StopTimer("Rules Built");

            Console.WriteLine(log.ToString());


            log.StartTimer("Begin Processing Rules");
            baseRule.Invoke();
            log.StopTimer("All Rules Processed");

            Console.WriteLine(log.ToString());

            Console.Read();
        }
    }
}
