using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace IAsyncResult01
{
    class Program
    {
        delegate void methodDelegate(string name, int delayTime, out string info);

        static void Main(string[] args)
        {
            string info = null;
            Thread thread1 = new Thread(new ThreadStart(() => { Method("使用Thread开启新线程",2, out info); }));
            thread1.Start();
            Console.WriteLine("使用Thread开启的新线程开始运行");
            Console.WriteLine("主线程执行其它任务");
            Console.WriteLine("等待线程结束");
            thread1.Join();
            Console.WriteLine("线程结束");
            Console.WriteLine(info);

            methodDelegate method = new methodDelegate(Method);
            IAsyncResult iar = method.BeginInvoke("无返回值的方法异步执行",2,out info,null,null);
            Console.WriteLine("主线程执行其它任务");
            Console.WriteLine("等待线程结束");
            //while(iar.IsCompleted)
            //{
            //    ;
            //}
            method.EndInvoke(out info, iar);
            Console.WriteLine("线程结束");
            Console.WriteLine(info);

            Console.Read();
        }

        static void Method(string name,int delayTime,out string info)
        {
            Thread.Sleep(TimeSpan.FromSeconds(delayTime));
            info = string.Format("Thread name:{0},Thread id:{1}, Is Thread pool thread: {2},sleep {3} seconds", 
                name,Thread.CurrentThread.ManagedThreadId,Thread.CurrentThread.IsThreadPoolThread,delayTime);
        }
    }
}
