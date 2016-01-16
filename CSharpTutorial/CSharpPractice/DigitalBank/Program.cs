using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DigitalBank
{
    class Program
    {
        static void Main(string[] args)
        {
            string action;

            DBPublisher myAccount = new DBPublisher();
            myAccount.objBalChanged += OnBalanceSubscriber;
            myAccount.objGoalChanged += OnGoalSubscriber;
            do {
                action = Console.ReadLine();
                if (action != "exit")
                {
                    myAccount.Action = Int32.Parse(action);
                }
            } 
            while(action != "exit");
        }
        static void OnBalanceSubscriber(object source, objBalChangedArg args)
        {
            Console.WriteLine("The new bal is : " + args.money);
        }
        static void OnGoalSubscriber(object source, objBalChangedArg args)
        {
            Console.WriteLine("The goal {0} has been reached", args.money);
        }
    }

}
