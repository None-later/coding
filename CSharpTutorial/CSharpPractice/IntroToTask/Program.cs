using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

using System.Net;
using System.Net;
using System.Runtime.InteropServices;
//using System.Numerics; 
/*
 * CPU bound tasks : the tasks that should be using the CPU the whole time while it's executing, by default it's background thread
 * I/O bound tasks : the tasks that can be sitting there waiting something to happen, allows the waiting

*/

namespace IntroToTask
{
    struct A
    {
        public int x;
    };

    class Program
    {
        static void Main(string[] args)
        {
            //Task t = new Task(Speak);
            //t.Start();

            //Task.Factory.StartNew(WhatTypeOfThreadAmI, TaskCreationOptions.LongRunning).Wait();

            //Task.Factory.StartNew(() => Speak("Hello")).Wait();  // using lambda expression

            //Task<int> t= Task.Factory.StartNew(()=>Add(5000, 10000));  // have to declare Task<int> for the return type
            //Console.WriteLine(t.Result);    // call Result to make the main wait for the result come out


        }
        //private static void Speak()
        //{
        //    Console.WriteLine("Hello");
        //}

        //private static void WhatTypeOfThreadAmI()
        //{
        //    Console.WriteLine("I'm a {0} thread", Thread.CurrentThread.IsThreadPoolThread ? "Thread Pool" : "Custom");
        //}

        //private static void Speak(string words)
        //{
        //    Console.WriteLine(words);
        //}

        //public static int Add(int x, int y)
        //{
        //    return x + y;
        //}

        private static string DownloadWebPage(string url)
        {
            WebRequest request = WebRequest.Create(url);

        
        }
    }
}
