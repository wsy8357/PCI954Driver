
namespace KGLCtrlApp.userControler
{
    partial class SwitchCtrl
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.statusSwitch = new IndustrialPCUIControls.StatusSwitch.StatusSwitch();
            this.channleNameLabel = new System.Windows.Forms.Label();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Controls.Add(this.statusSwitch, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.channleNameLabel, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(150, 150);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // statusSwitch
            // 
            this.statusSwitch.Checked = false;
            this.statusSwitch.Dock = System.Windows.Forms.DockStyle.Fill;
            this.statusSwitch.FalseColor = System.Drawing.Color.FromArgb(((int)(((byte)(111)))), ((int)(((byte)(122)))), ((int)(((byte)(126)))));
            this.statusSwitch.Location = new System.Drawing.Point(3, 3);
            this.statusSwitch.Name = "statusSwitch";
            this.statusSwitch.Size = new System.Drawing.Size(144, 69);
            this.statusSwitch.SwitchType = IndustrialPCUIControls.StatusSwitch.SwitchType.Quadrilateral;
            this.statusSwitch.TabIndex = 0;
            this.statusSwitch.Tests = null;
            this.statusSwitch.TrueColor = System.Drawing.Color.FromArgb(((int)(((byte)(34)))), ((int)(((byte)(163)))), ((int)(((byte)(169)))));
            this.statusSwitch.Click += new System.EventHandler(this.statusSwitch_Click);
            // 
            // channleNameLabel
            // 
            this.channleNameLabel.AutoSize = true;
            this.channleNameLabel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.channleNameLabel.Location = new System.Drawing.Point(3, 75);
            this.channleNameLabel.Name = "channleNameLabel";
            this.channleNameLabel.Size = new System.Drawing.Size(144, 75);
            this.channleNameLabel.TabIndex = 1;
            this.channleNameLabel.Text = "label1";
            this.channleNameLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // SwitchCtrl
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "SwitchCtrl";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private IndustrialPCUIControls.StatusSwitch.StatusSwitch statusSwitch;
        private System.Windows.Forms.Label channleNameLabel;
    }
}
