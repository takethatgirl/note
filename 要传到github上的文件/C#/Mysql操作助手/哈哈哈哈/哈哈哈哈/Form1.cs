using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data;
using MySql.Data.MySqlClient;

namespace 哈哈哈哈
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            MysqlAssistant ass = new MysqlAssistant("root", "12356", "user");
            this.dataGridView1.DataSource = ass.GetDataSet(CommandType.Text, "SELECT * FROM alcuser", null).Tables[0].DefaultView;
        }
    }
}
