using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace DeadLock
{
    class Account
    {
        int _id;
        double _balance;

        public Account(int id, double bal)
        {
            _id = id;
            _balance = bal;
        }
        public int ID
        {
            get { return _id; }
        }
        public void Withdraw(double amount)
        {
            _balance -= amount;
        }
        public void Deposit(double amount)
        {
            _balance += amount;
        }
    }
    class AccountManager
    {
        Account _fromAccount;
        Account _toAccount;
        double _amountToTransfer;

        public AccountManager(Account fromAccount, Account toAccount, double amountTransfer)
        {
            this._fromAccount = fromAccount;
            this._toAccount = toAccount;
            this._amountToTransfer = amountTransfer;
        }
        public void Transfer()
        {
            lock (_fromAccount)
            {
                Thread.Sleep(1000);
                lock (_toAccount)
                {
                    _fromAccount.Withdraw(_amountToTransfer);
                    _toAccount.Deposit(_amountToTransfer);
                }
            }
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Main Start");
            Account accountA = new Account(101, 5000);
            Account accountB = new Account(102, 3000);

            AccountManager accMgrA = new AccountManager(accountA, accountB, 1000);
            Thread T1 = new Thread(accMgrA.Transfer);
            T1.Name = "T1";
            
            AccountManager accMgrB = new AccountManager(accountB, accountA, 2000);
            Thread T2 = new Thread(accMgrB.Transfer);
            T2.Name = "T2";

            T1.Start();
            T2.Start();

            T1.Join();
            T2.Join();

            

            Console.WriteLine("Main Completed");
        }
    }
}
