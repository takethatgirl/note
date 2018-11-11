using System;
using System.Threading;

namespace IAsyncResult03
{
    class Program
    {
        public delegate string MethodDelete(string threadName, out int threadId);
        static void Main(string[] args)
        {
            string info = null;
            MethodDelete method = Method;
            int threadId = 0;
            IAsyncResult iar = method.BeginInvoke("异步线程001", out threadId, null, null);
            
            //方法1
            //info = method.EndInvoke(out threadId, iar);
            //Console.WriteLine(info);
            //方法2
            //iar.AsyncWaitHandle.WaitOne(10);
            //info = method.EndInvoke(out threadId, iar);
            //Console.WriteLine(info);
            while (!iar.IsCompleted)
            {
                Console.WriteLine("异步线程还未结束");
            }
            info = method.EndInvoke(out threadId, iar);
            Console.WriteLine(info);
            Console.Read();
        }

        static string Method(string threadName,out int threadId)
        {
            Thread.Sleep(TimeSpan.FromSeconds(1));
            threadId = Thread.CurrentThread.ManagedThreadId;
            return string.Format("【thread id】:{0},【thread name】:{1},completed...",threadId,threadName);
        }
    }
}
