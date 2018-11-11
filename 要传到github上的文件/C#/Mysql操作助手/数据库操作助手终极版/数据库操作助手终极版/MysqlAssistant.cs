using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Data;
using MySql.Data;
using MySql.Data.MySqlClient;

namespace 数据库操作助手终极版
{
    public class MysqlAssistant
    {
        #region 成员变量
        private string userid;
        private string password;
        private string server = "127.0.0.1";
        private string port = "3306";
        private string database;
        private string charset = "utf8";
        #endregion

        #region 构造函数
        public MysqlAssistant(string userid,string password,string database)
        {
            this.userid = userid;
            this.password = password;
            this.database = database;
        }
        public MysqlAssistant(string userid, string password, string database,string server):this(userid,password,database)
        {
            this.server = server;
        }
        public MysqlAssistant(string userid, string password, string database, string server,string port) : this(userid, password, database, server)
        {
            this.port = port;
        }
        public MysqlAssistant(string userid, string password, string database, string server, string port,string charset) : this(userid, password, database, server,port)
        {
            this.charset = charset;
        }

        public string GetConnectionString()
        {
            string connectString = String.Format("userid={0};password={1};server={2};port={3};database={4};charset={5}", userid, password, server, port, database, charset);
            return connectString;
        }
        #endregion

        #region 执行insert，delete，upgrade三种sql语句
        /// <summary>
        /// 返回执行命令影响的行数（仅适用于insert，delete，upgrade；select和其他命令都是返回-1，不能使用该函数）
        /// </summary>
        /// <param name="cmdType">命令类型</param>  可不需要，但是如果指明，可加快命令的执行速度
        /// <param name="cmdText">sql语句</param>
        /// <param name="cmdParams">sql语句参数</param>
        /// <returns></returns>
        public int ExecuteNonQuery(CommandType cmdType, string cmdText, params MySqlParameter[] cmdParams)
        {
            using(MySqlConnection con = new MySqlConnection(this.GetConnectionString()))
            {
                using(MySqlCommand cmd = new MySqlCommand()) //自动释放该命令所有资源，包括cmd.Parameters.Clear();
                {
                    this.PrepareCommand(con, cmd, cmdType, cmdText, cmdParams);
                    return cmd.ExecuteNonQuery(); //返回影响的行数，无影响返回0，其他指令返回-1
                }
            }
        }
        #endregion

        #region 返回数据集MysqlDataReader，用于快速读取数据库
        /// <summary>
        /// 返回数据集MysqlDataReader，用于快速读取数据库
        /// </summary>
        /// <param name="cmdType"></param>
        /// <param name="cmdText"></param>
        /// <param name="cmdParams"></param>
        /// <returns></returns>
        public MySqlDataReader GetDataReader(CommandType cmdType, string cmdText, params MySqlParameter[] cmdParams)
        {
            MySqlConnection con = null;
            MySqlCommand cmd = null;
            MySqlDataReader reader = null;
            try
            {
                con = new MySqlConnection(this.GetConnectionString());
                cmd = new MySqlCommand();
                this.PrepareCommand(con, cmd, cmdType, cmdText, cmdParams);
                reader = cmd.ExecuteReader();
                return reader;
            }
            catch(Exception e)  //之所以捕获异常，是因为如果出现异常，既没有获得
            {                   //DataReader读取器来间接关闭连接，代码又没主动关闭
                Debug.WriteLine(e.Data);//关闭连接，会浪费资源；应当及时让系统关闭不用的
                con.Close();            //数据库连接
                return null;
            }
        }
        /*【MysqlDataReader讲解】
         * 与DataSet不同，DataSet是离线的，而MysqlDataReader是在线读取器；
         * MysqlDataReader读取速度比DataSet快，原因是：Dataset相当于是个
         * 存在于内存的小型数据库，所有的数据全部被取出放到DataSet；这样DataSet
         * 就于被读取的数据库无关了，MysqlConnection连接是否中断，MysqlCommand
         * 命令参数是否被修改，都不会影响从DataSet读取数据。但是DataReader是只读到
         * 第一个数据时就返回，相当于获取了头，然后用户可以直接从头慢慢往后读；所以，
         * 比DataSet快，正因为不是把数据全部获取另存到自身，所以DataReader要保证
         * MysqlConnnection对象一直存在，且处于open状态；MysqlCommand对象一直存在
         * 且命令参数在DataReader关闭之前不得变化。
         * 只要DataReader存在，你不去主动关闭改变连接或命令，二者就会一直存在；
         * 只要DataReader存在，连接对象一直被占用，除了close掉它，不得对它进行任何操作；
         * 当DataReader读取完毕，应该手动Close掉DataReader，这样也就同时释放掉了
         * 连接对象和命令对象。
         */
        #endregion

        #region 返回DataSet
        /// <summary>
        /// 返回DataSet
        /// </summary>
        /// <param name="cmdType"></param>
        /// <param name="cmdText"></param>
        /// <param name="cmdParams"></param>
        /// <returns></returns>
        public DataSet GetDataSet(CommandType cmdType,string cmdText,params MySqlParameter[] cmdParams)
        {
            using(MySqlConnection con = new MySqlConnection(this.GetConnectionString()))
            {
                using(MySqlCommand cmd = new MySqlCommand())
                {
                    this.PrepareCommand(con, cmd, cmdType, cmdText, cmdParams);
                    DataSet ds = new DataSet();
                    MySqlDataAdapter ad = new MySqlDataAdapter(cmd);
                    ad.Fill(ds);
                    return ds;
                }
            }
        }
        #endregion

        #region 执行一条命令前的准备工作
        /// <summary>
        /// 执行一条命令前的准备工作
        /// </summary>
        /// <param name="con">连接对象</param>
        /// <param name="cmd">命令</param>
        /// <param name="cmdType">sql语句类型</param>
        /// <param name="cmdText">sql语句</param>
        /// <param name="cmdParams">sql语句参数</param>
        public void PrepareCommand(MySqlConnection con,MySqlCommand cmd,CommandType cmdType,string cmdText,params MySqlParameter[] cmdParams)
        {
            if(con.State != ConnectionState.Open) //连接对象有三种状态：closed，connecting（正在与数据源连接），open
            {
                con.Open();
            }
            //填补命令的四个参数：连接对象，sql语句类型，sql语句，sql语句参数
            cmd.Connection = con;      
            cmd.CommandType = cmdType;
            cmd.CommandText = cmdText;
            if(cmdParams != null)  //为空时，表示无参数，不再添加
            {
                cmd.Parameters.Clear();//AddRange()是在命令的参数集合中追加参数，所以要先释放掉可能潜在的遗留参数
                cmd.Parameters.AddRange(cmdParams); 
            }
        }
        #endregion

        #region 快速查询数据库中有无某条记录
        public object ExecuteScalar(CommandType cmdType, string cmdText, params MySqlParameter[] cmdParams)
        {
            using(MySqlConnection con = new MySqlConnection(this.GetConnectionString()))
            {
                using (MySqlCommand cmd = new MySqlCommand())
                {
                    this.PrepareCommand(con, cmd, cmdType, cmdText, cmdParams);
                    object obj = cmd.ExecuteScalar();//如果执行的是SELECT语句，如果SELECT查询的不为空，返回第一行第一列对象的引用，
                    return obj;//使用返回值时，记得向下转型；如果SELECT查询为空，返回null；可通过判断是不是null来判断存在不存在记录；
                }//如果是其他类型的sql，仅仅是执行该语句，返回值没有什么用
            }
        }
        #endregion

        #region 判断DataSet中无任何记录
        /// <summary>
        /// 判断DataSet中无任何记录
        /// </summary>
        /// <param name="ds"></param>
        /// <returns></returns>
        public static bool DatasetIsEmpty(DataSet ds)
        {
            MySqlParameter p = new MySqlParameter();
            return true;
        }
        #endregion
    }
}


