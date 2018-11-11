using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace 刷新窗体的控制台类
{
    public partial class Form1 : Form
    {
        private UpgradeUI upgrade;
        public Form1()
        {
            InitializeComponent();
            upgrade = new UpgradeUI(this);
        }


        public void UpgradeTextBox(string msg)
        {
            Random ran = new Random();
            int digit = ran.Next();

            if (this.mainTextBox.InvokeRequired)
            {
                this.mainTextBox.BeginInvoke(new Action<string>((str) => { this.mainTextBox.Text = str; }), msg+digit.ToString());
            }
            else
            {
                this.mainTextBox.Text = msg + digit.ToString();
            }

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            new Thread(() => {
                for(int i = 0; i < 10; ++i)
                {
                    Thread.Sleep(1000);
                    this.upgrade.fffff();
               }


            }).Start();
        }
    }
}
