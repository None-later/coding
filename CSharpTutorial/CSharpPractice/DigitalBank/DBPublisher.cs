using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DigitalBank
{
    class objBalChangedArg : EventArgs
    {
        public Int32 money { get; set; }
    }

    class DBPublisher
    {
        //private Int32 theGoal = 500;
        public Int32 theAction;
        public Int32 theBalance = 0;
        public Int32 Action
        {
            set 
            {
                this.theAction = value;
                theBalance += theAction;
                if (theBalance >= 500)
                {
                    this.objGoalChanged(this, new objBalChangedArg() { money = 500 });
                }
                else
                {
                    this.objBalChanged(this, new objBalChangedArg() { money = theBalance });
                }
            }
        }
      
        // 1: Define a delegate 
        // 2: Define an event based on the delegate
        // 3: Publish the event
        public event EventHandler<objBalChangedArg> objBalChanged;
        public event EventHandler<objBalChangedArg> objGoalChanged;

        //protected virtual void OnBalanceChange(int amount)
        //{
        //    if (balChanged != null)
        //        balChanged(this, new objBalChangedArg() { money = amount }); 
        //}
        //protected virtual void OnGoalReach(int amount)
        //{ 
            
        //}
    }
}
