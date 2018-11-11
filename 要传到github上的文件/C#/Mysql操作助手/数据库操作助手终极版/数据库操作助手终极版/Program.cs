using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MySql.Data.MySqlClient;
using System.Data;

namespace 数据库操作助手终极版
{
    class Program
    {
        static void Main(string[] args)
        {
            MysqlAssistant assistant = new MysqlAssistant("root", "12356", "user");

            #region 测试MysqlDataReader
            string sql_1 = @"SELECT * FROM alcuser";
            MySqlDataReader reader = assistant.GetDataReader(CommandType.Text,sql_1,null);
            //判断MysqlDataReader是否有记录，没有是false
            //每次使用DataReader前务必使用该判断；否则无数据时，仍旧操作数据如，reader.GetInt16(0)
            //会发生异常
            if (reader.HasRows) 
            {
                while (reader.Read()) //reader刚开始在第一行记录的前面，每执行一次Read(),就前进到下一行记录，无记录时返回false
                {
                    Console.WriteLine(reader.GetInt16(0));
                    Console.WriteLine(reader.GetString(1));
                    Console.WriteLine(reader.GetString(2));
                    Console.WriteLine(reader.GetInt16(3));
                    Console.WriteLine("-------------------");
                }
            }
            reader.Close();  //关闭reader，很重要，否则会浪费数据库连接资源
            #endregion

            string sql_2 = @"SELECT * FROM alcuser";
            DataSet ds = assistant.GetDataSet(CommandType.Text, sql_2, null);
            DataTable tb1 = ds.Tables[0];
            foreach (DataColumn co1 in tb1.Columns)
                Console.WriteLine(co1.ColumnName);

            #region 测试ExecuteScalar函数
            string sql_3 = @"SELECT * FROM alcuser WHERE uname = 'Bruc'";
            object obj = assistant.ExecuteScalar(CommandType.Text,sql_3,null);
            if (obj == null)
                Console.WriteLine("数据表中无此记录");
            else
            Console.WriteLine(obj.ToString());
            #endregion

            Console.Read();
        }
    }
}
