using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace AsynProg
{
    class Program
    {
        static void Main(string[] args)
        {
            ////Task.Factory.StartNew(() => Speak("Hello World")).Wait();
            //Console.WriteLine("Calling Function");
            //Task<int> t = Task.Factory.StartNew(() => Add(5000, 10000));
            //Console.WriteLine("waiting for result");
            //Console.WriteLine(t.Result);
        }
        private static void WhatTypeThread()
        {
            Console.WriteLine("I am a {0} thread", Thread.CurrentThread.IsThreadPoolThread ? "Thread Pool" : "Custom");
        }
        private static void Speak(string words)
        {
            Console.WriteLine(words);
        }
        public static int Add(int x, int y)
        {
            return x + y;
        }
    }
}