using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace IAsyncResult02
{
    class Program
    {
        delegate string methodDelete(string name, int times, out string info);
        static void Main(string[] args)
        {
            methodDelete method = Method;
            string info = null;
            IAsyncResult iar = method.BeginInvoke("有参数有返回值的方法",2,out info,null,null);
            while(iar.IsCompleted == false)
            {
                Console.WriteLine("线程还未结束");
            }
            
            Console.Read();

        }

        static string Method(string name,int times,out string info)
        {
            Thread.Sleep(TimeSpan.FromSeconds(times));
            return info = string.Format("Thread name: {0},Thread id: {1},Is thread pool thread: {2},thread sleep time: {3}",
                name, Thread.CurrentThread.ManagedThreadId, Thread.CurrentThread.IsThreadPoolThread, times);
        }
    }
}
