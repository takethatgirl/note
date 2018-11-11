using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 刷新窗体的控制台类
{
    
    class UpgradeUI
    {
        public Form1 f1;

        public UpgradeUI(Form1 f1)
        {
            this.f1 = f1; 
        }


        public void fffff()
        {
            Action<string>  aaaa = new Action<string>(f1.UpgradeTextBox);
            aaaa("1234.toString()");
        }
    }
}
