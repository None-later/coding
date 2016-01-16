using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Collections.Specialized;


namespace MyEventBasedPattern
{
    delegate void CarSpeedChangedHandler(object sender, CarSpeedChangedEventArgs e);

    // pub
    class Car
    {
        public event CarSpeedChangedHandler CarSpeedChanged;

        private int speed;

        public int Speed 
        {
            get { return speed; }
            set
            {
                this.speed = value;
                if (value >= 60)
                {
                    if (this.CarSpeedChanged != null)
                        CarSpeedChanged(this, new CarSpeedChangedEventArgs());
                }
            }
        }
    };

    class CarSpeedChangedEventArgs : EventArgs
    {
        private DateTime whenToVoilate;

        public CarSpeedChangedEventArgs()
        {
            this.whenToVoilate = DateTime.Now;
        }
        public DateTime WhenToVoilate
        {
            get { return whenToVoilate; }
        }
    };

    // sub
    class HighwayPolice 
    { 
        // event handler    
        public void HandleWhenExceedSpeed(object sender, CarSpeedChangedEventArgs e)
        {
            Console.WriteLine("Slow down");
        }
    };

    class Program
    {
        static void Main(string[] args)
        {
            





        }
    }
}
