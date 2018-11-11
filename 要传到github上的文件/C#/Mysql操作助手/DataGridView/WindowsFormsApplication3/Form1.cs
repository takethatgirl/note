using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            InitDataGridView();
        }

        /// <summary>
        /// 刷新产品信息
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="e"></param>
        private void AddProductInfoToUI(object obj, Class1 e)
        {
            foreach (Control ctrl in this.panel1.Controls)
            {
                if(ctrl is DataGridView)
                {
                    DataGridView dgv = (DataGridView)ctrl;
                    if(dgv.RowCount < 10)
                    {
                        if (dgv.InvokeRequired)
                        {
                            dgv.BeginInvoke(new Action(() => {
                                int index = dgv.Rows.Add();
                                dgv.Rows[index].Cells[0].Value = e.product_sn;
                                dgv.Rows[index].Cells[1].Value = e.test_result;
                                dgv.FirstDisplayedScrollingRowIndex = dgv.Rows[dgv.Rows.Count - 1].Index;//定位到最后一行
                            }));
                        }
                        else
                        {
                            int index = dgv.Rows.Add();
                            dgv.Rows[index].Cells[0].Value = e.product_sn;
                            dgv.Rows[index].Cells[1].Value = e.test_result;
                            dgv.FirstDisplayedScrollingRowIndex = dgv.Rows[dgv.Rows.Count - 1].Index;//定位到最后一行
                        }
                    }
                    else
                    {
                        if (dgv.InvokeRequired)
                        {
                            dgv.BeginInvoke(new Action(() => {
                                int index = dgv.Rows.Add();
                                dgv.Rows[index].Cells[0].Value = e.product_sn;
                                dgv.Rows[index].Cells[1].Value = e.test_result;
                                dgv.FirstDisplayedScrollingRowIndex = dgv.Rows[dgv.Rows.Count - 1].Index;//定位到最后一行
                            }));
                        }
                        else
                        {
                            int index = dgv.Rows.Add();
                            dgv.Rows[index].Cells[0].Value = e.product_sn;
                            dgv.Rows[index].Cells[1].Value = e.test_result;
                            dgv.FirstDisplayedScrollingRowIndex = dgv.Rows[dgv.Rows.Count - 1].Index;//定位到最后一行
                        }
                    }
                    
                }
            }
               
        }

        /// <summary>
        /// 初始化DataGridView
        /// </summary>
        private void InitDataGridView()
        {
            // 1，创建一个DataGridView
            DataGridView dataGridView1 = new DataGridView();
            //2，设置列数（不包括空白的RowHeader）
            dataGridView1.ColumnCount = 4;
            //3.设置列头可见
            dataGridView1.ColumnHeadersVisible = true;
            // 4，设置列头的样式
            DataGridViewCellStyle columnHeaderStyle = new DataGridViewCellStyle();
            columnHeaderStyle.BackColor = Color.Beige;
            columnHeaderStyle.Font = new Font("Verdana", 10, FontStyle.Bold);
            dataGridView1.ColumnHeadersDefaultCellStyle = columnHeaderStyle;
            //5，设置列头的各个列名
            dataGridView1.Columns[0].Name = "Product SN";
            dataGridView1.Columns[1].Name = "Test Result";
            dataGridView1.Columns[2].Name = "User";
            dataGridView1.Columns[3].Name = "Machine SN";
            //6,添加若干空白行以待赋值显示
            for (int i = 0; i < 10; i++)
            {
                dataGridView1.Rows.Add();
            }




            //行头的空白列不再显示
            dataGridView1.RowHeadersVisible = false;
            // 禁止用户改变 DataGridView1 的所有列的列宽
            dataGridView1.AllowUserToResizeColumns = false;
            // 禁止用户改变 DataGridView1 所有行的行高
            dataGridView1.AllowUserToResizeRows = false;
            //指定列高
            dataGridView1.RowTemplate.Height = 20;
            //不留最后的空白行
            dataGridView1.AllowUserToAddRows = false;
            //表格不可修改
            dataGridView1.ReadOnly = false;

            //位置待设置dataGridView.Location
            //this.dataGridView1.Location = new Point(this.panel1.Location.X, this.panel1.Location.Y + this.panel1.Size.Height + 15);
            this.panel1.Controls.Add(dataGridView1);
            //设置相对于机器面板的初始位置


        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}
