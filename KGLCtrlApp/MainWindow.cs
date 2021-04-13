using KGLCtrlApp.userControler;
using KGLCtrlApp.utils;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace KGLCtrlApp
{
    public partial class MainWindow : Form
    {
        private List<SwitchCtrl> switchCtrls;
        public MainWindow()
        {
            InitializeComponent();
            switchCtrls = new List<SwitchCtrl>();
            drawSwitchCtrlUI();
        }

        private void LoadWorkSpaceToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void SaveWorkSpaceToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void drawSwitchCtrlUI()
        {
            for (int i = 0; i < 16; i++)
            {
                SwitchCtrl tempSwitchCtrl = new SwitchCtrl(i + 1, $"通道{i + 1}");
                SwitchtableLayoutPanel.Controls.Add(tempSwitchCtrl, i % 4, i / 4);

                tempSwitchCtrl.Dock = DockStyle.Fill;
                tempSwitchCtrl.Name = $"switchCtrl{i}";

                switchCtrls.Add(tempSwitchCtrl);
            }
        }

        private void MainWindow_Shown(object sender, EventArgs e)
        {
            LoggerService.IniterLogService();
            LoggerService.logger.Info("启动开关量控制软件");
        }
    }
}
