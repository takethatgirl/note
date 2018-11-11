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
using System.Net;
using System.Net.Sockets;

namespace 服务器
{
    public partial class myServer : Form
    {
        public myServer()
        {
            InitializeComponent();
        }

        private Dictionary<string, Socket> Clientstore = new Dictionary<string, Socket>();

        private Socket socketWatch;
         
        private void startBtn_Click(object sender, EventArgs e)
        {
            socketWatch = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            IPAddress ip = IPAddress.Parse(ipText.Text.Trim());
            IPEndPoint point = new IPEndPoint(ip, Convert.ToInt32(portText.Text.Trim()));
            socketWatch.Bind(point);
            socketWatch.Listen(5);
            this.logRichText.AppendText("监听成功" + "\r\n");
        }

        
    }
}
