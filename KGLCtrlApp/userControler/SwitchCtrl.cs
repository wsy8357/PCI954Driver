using KGLCtrlApp.utils;
using LibKGL3U24;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace KGLCtrlApp.userControler
{
    public partial class SwitchCtrl : UserControl
    {
        private int channelNo;
        private readonly KGL3U24 kGL3U24;

        public SwitchCtrl()
        {
            InitializeComponent();
        }

        public SwitchCtrl(int channelNo, string channelName, KGL3U24 kGL3U24):this()
        {
            this.channelNo = channelNo;
            this.kGL3U24 = kGL3U24;
            channleNameLabel.Text = channelName;
        }

        public void setSwitchStatus(bool isEnable)
        {
            this.statusSwitch.Checked = isEnable;
        }

        private void statusSwitch_Click(object sender, EventArgs e)
        {
            StringBuilder stringBuilder = new StringBuilder();
            if(statusSwitch.Checked)
            {
                stringBuilder.Append("打开");
            }
            else
            {
                stringBuilder.Append("关闭");
            }
            stringBuilder.Append(channleNameLabel.Text);
            LoggerService.logger.Info(stringBuilder.ToString());
        }
    }
}
