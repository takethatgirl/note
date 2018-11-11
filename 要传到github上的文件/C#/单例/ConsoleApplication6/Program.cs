using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;

namespace ConsoleApplication6
{

    /// <summary>
    /// 单例类（饿汉模式）
    /// </summary>
    class GlobalAccess
    {
        /// <summary>
        /// 采用饿汉模式实现单例类的代码
        /// </summary>
        private static readonly GlobalAccess instance = new GlobalAccess();

        private GlobalAccess()
        {
            this.TheSystemStatus = SystemStatus.RUNNING;
        }

        public static GlobalAccess GetInstance()
        {
            return instance;
        }

        /// <summary>
        /// 系统状态（所可能的取值受枚举限制）
        /// </summary>
        private SystemStatus theSystemStatus;

        /// <summary>
        /// 这是一个锁，用来互斥访问系统状态。
        /// </summary>
        private object lockFortheSystemStatus = new object();
        /// <summary>
        /// 利用属性来访问系统状态（实现互斥和赋值的逻辑性审查）
        /// </summary>
        public SystemStatus TheSystemStatus
        {
            get
            {
                lock (lockFortheSystemStatus)
                {
                    return theSystemStatus;
                }
                
            }
            set
            {
                lock (lockFortheSystemStatus)
                {
                    theSystemStatus = value;
                }
                
            }
        }

        /// <summary>
        /// 系统状态的枚举
        /// </summary>
        public enum SystemStatus
        {
            IDEL,
            STARTING,
            RUNNING,
            ABORT,
            //TO DO
            //其他状态，麻烦你添加一下，我记不清了，忘拿笔记本了
        } 

        /// <summary>
        /// 用户角色的枚举
        /// </summary>
        public enum UserRole
        {
            Admin = 1,
            Engineer = 2,
            Operator = 3
        }
    }

    /// <summary>
    /// 主函数测试是否达到互斥访问
    /// </summary>
    class Program
    {
        static void Main(string[] args)
        {
            Thread t1 = new Thread(() =>
            {
                Console.WriteLine(GlobalAccess.GetInstance().TheSystemStatus);
                GlobalAccess.GetInstance().TheSystemStatus = GlobalAccess.SystemStatus.IDEL;
            });

            Thread t2 = new Thread(() =>
            {
                t1.Join();
                Console.WriteLine(GlobalAccess.GetInstance().TheSystemStatus);
                GlobalAccess.GetInstance().TheSystemStatus = GlobalAccess.SystemStatus.STARTING;
            });

            Thread t3 = new Thread(() =>
            {
                
                t2.Join();
                Console.WriteLine(GlobalAccess.GetInstance().TheSystemStatus);
                GlobalAccess.GetInstance().TheSystemStatus = GlobalAccess.SystemStatus.ABORT;
                Console.WriteLine(GlobalAccess.GetInstance().TheSystemStatus);
            });

            t1.Start();
            t2.Start();
            t3.Start();

            Console.WriteLine(GlobalAccess.UserRole.Engineer);
        }
    }
}
