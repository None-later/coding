using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace CSharpPractice
{
    //delegate void CarSpeedChangedHandler(object sender, CarExceedSpeedEventArgs e);
    class Car
    {
        //public event CarSpeedChangedHandler CarSpeedChanged;
        public EventHandler<CarExceedSpeedEventArgs> CarSpeedChanged;
        private int speed;

        public int Speed
        {
            get { return this.speed; }
            set
            {
                this.speed = value;
                if (value > 60)
                {
                    if (this.CarSpeedChanged != null)
                    {
                        CarSpeedChanged(this, new CarExceedSpeedEventArgs());
                    }
                }
            }
        }
    }

    class CarExceedSpeedEventArgs : EventArgs
    {
        private DateTime whenVoilate;

        public CarExceedSpeedEventArgs()
        {
            this.whenVoilate = DateTime.Now;
        }
        public DateTime WhenVoilate
        {
            get { return whenVoilate; }
        }
    }

    class HighWayPatrol
    {
        // Event handler
        public void HandleWhenExceedSpeed(object sender, CarExceedSpeedEventArgs e)
        {
            Console.WriteLine("slow down ! Your speed is " + ((Car)sender).Speed + "Time : " + e.WhenVoilate);
        }
    }



    //interface I1
    //{
    //    void InterfaceMethod();
    //}
    //interface I2
    //{
    //    void InterfaceMethod();
    //}

    //public abstract class Customer : I1, I2
    //{
    //    public void Print()
    //    {
    //        Console.WriteLine("hello");
    //    }
    //}


    //class A : Customer, I1, I2
    //{
    //    public void InterfaceMethod()  // default implemtation 
    //    {
    //        Console.WriteLine("I1 interface method");
    //    }
    //    void I2.InterfaceMethod()
    //    {
    //        Console.WriteLine("I2 interface method");
    //    }
    //    public override void Print()
    //    {
    //        Console.WriteLine("Abstract Hello");
    //    }
    //};
    //class B : A
    //{
    //    public void Method()
    //    {
    //        Console.WriteLine("method B is used");
    //    }
    //};

    //class C : A
    //{
    //    public override void Method()
    //    {
    //        Console.WriteLine("method C is used");
    //    }
    //};

    //class D : B,C
    //{
    //    public override void Method()
    //    {
    //        Console.WriteLine("method C is used");
    //    }
    //};


    delegate bool IsPromotable(Employee empl);

    class Employee
    {
        public int ID { get; set; }
        public string Name { get; set; }
        public int Salary { get; set; }
        public int Experience { get; set; }

        public static void PromoteEmployee(List<Employee> employeeList
                                            , IsPromotable IsEligibleToPromote)
        {
            foreach (Employee employee in employeeList)
            {
                if (IsEligibleToPromote(employee))
                    Console.WriteLine(employee.Name + " promoted");
            }
        }
    }

    public delegate void SumOfNumbersCallback(int SumOfNumber);

    class Number
    {
        private int _target;
        SumOfNumbersCallback _callback;

        public Number(int target, SumOfNumbersCallback callback)
        {
            this._target = target;
            this._callback = callback;
        }
        public void ComputeSumOfNumber()
        {
            int sum = 0;
            for (int i = 1; i <= _target; ++i)
                sum += i;
            if (_callback != null)
                _callback(sum);
        }
    }


    interface IA
    {
        void AMethod();
    }
    interface IB
    {
        void BMethod();
    }
    class A : IA
    {
        public void AMethod()
        {
            Console.WriteLine("A Method");
        }
    }
    class B : IB
    {
        public void BMethod()
        {
            Console.WriteLine("B Method");
        }
    }


    class AB : IA, IB
    {
        A a = new A();
        B b = new B();

        public void AMethod()
        {
            a.AMethod();
        }
        public void BMethod()
        {
            b.BMethod();
        }
    }


    class Z
    {
        private int _x;

        Z(int x)
        {
            _x = x;
        }
        //public abstract void Print();
    }

    class Program
    {
        public static void PrintSum(int result)
        {
            Console.WriteLine(result);
        }

        static void Main(string[] args)
        {
            SumOfNumbersCallback resCallback = new SumOfNumbersCallback(PrintSum);

            Number number = new Number(10, resCallback);

            //ParameterizedThreadStart paraThreadStart = new ParameterizedThreadStart(ComputeSum);
            Thread T1 = new Thread(number.ComputeSumOfNumber);
            T1.Start();
            //List<Employee> empList = new List<Employee>();

            //empList.Add(new Employee() { ID = 101, Name = "Mary", Salary = 5000, Experience = 5 });
            //empList.Add(new Employee() { ID = 101, Name = "Mike", Salary = 4000, Experience = 4 });
            //empList.Add(new Employee() { ID = 101, Name = "John", Salary = 6000, Experience = 6 });
            //empList.Add(new Employee() { ID = 101, Name = "Todd", Salary = 3000, Experience = 3 });

            ////IsPromotable isPromotable = new IsPromotable(Promote);
            //Employee.PromoteEmployee(empList, emp => emp.Experience >= 5);

            AB ab = new AB();

            Random r = new Random();

            Console.WriteLine(r);

        }
        public static void AddNumbers(int first, int second, params object[] rest)
        {
            int res = first + second;
            if (rest != null)
            {
                foreach (int i in rest)
                    res += i;
            }
            Console.WriteLine(res);
        }
    }
}