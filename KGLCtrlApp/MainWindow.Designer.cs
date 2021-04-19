
namespace KGLCtrlApp
{
    partial class MainWindow
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

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.文件ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.WorkSpaceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.LoadWorkSpaceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SaveWorkSpaceToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.帮助ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.SwitchtableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.LogShowWindow = new System.Windows.Forms.RichTextBox();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.menuStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.GripMargin = new System.Windows.Forms.Padding(2, 2, 0, 2);
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件ToolStripMenuItem,
            this.WorkSpaceToolStripMenuItem,
            this.帮助ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(1200, 32);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 文件ToolStripMenuItem
            // 
            this.文件ToolStripMenuItem.Name = "文件ToolStripMenuItem";
            this.文件ToolStripMenuItem.Size = new System.Drawing.Size(62, 28);
            this.文件ToolStripMenuItem.Text = "文件";
            // 
            // WorkSpaceToolStripMenuItem
            // 
            this.WorkSpaceToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.LoadWorkSpaceToolStripMenuItem,
            this.SaveWorkSpaceToolStripMenuItem});
            this.WorkSpaceToolStripMenuItem.Name = "WorkSpaceToolStripMenuItem";
            this.WorkSpaceToolStripMenuItem.Size = new System.Drawing.Size(80, 28);
            this.WorkSpaceToolStripMenuItem.Text = "工作区";
            // 
            // LoadWorkSpaceToolStripMenuItem
            // 
            this.LoadWorkSpaceToolStripMenuItem.Name = "LoadWorkSpaceToolStripMenuItem";
            this.LoadWorkSpaceToolStripMenuItem.Size = new System.Drawing.Size(200, 34);
            this.LoadWorkSpaceToolStripMenuItem.Text = "加载工作区";
            this.LoadWorkSpaceToolStripMenuItem.Click += new System.EventHandler(this.LoadWorkSpaceToolStripMenuItem_Click);
            // 
            // SaveWorkSpaceToolStripMenuItem
            // 
            this.SaveWorkSpaceToolStripMenuItem.Name = "SaveWorkSpaceToolStripMenuItem";
            this.SaveWorkSpaceToolStripMenuItem.Size = new System.Drawing.Size(200, 34);
            this.SaveWorkSpaceToolStripMenuItem.Text = "新建工作区";
            this.SaveWorkSpaceToolStripMenuItem.Click += new System.EventHandler(this.SaveWorkSpaceToolStripMenuItem_Click);
            // 
            // 帮助ToolStripMenuItem
            // 
            this.帮助ToolStripMenuItem.Name = "帮助ToolStripMenuItem";
            this.帮助ToolStripMenuItem.Size = new System.Drawing.Size(62, 28);
            this.帮助ToolStripMenuItem.Text = "帮助";
            // 
            // SwitchtableLayoutPanel
            // 
            this.SwitchtableLayoutPanel.ColumnCount = 4;
            this.SwitchtableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.SwitchtableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.SwitchtableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.SwitchtableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.SwitchtableLayoutPanel.Location = new System.Drawing.Point(18, 69);
            this.SwitchtableLayoutPanel.Margin = new System.Windows.Forms.Padding(4);
            this.SwitchtableLayoutPanel.Name = "SwitchtableLayoutPanel";
            this.SwitchtableLayoutPanel.RowCount = 4;
            this.SwitchtableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.SwitchtableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.SwitchtableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.SwitchtableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 25F));
            this.SwitchtableLayoutPanel.Size = new System.Drawing.Size(1164, 352);
            this.SwitchtableLayoutPanel.TabIndex = 1;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.LogShowWindow);
            this.groupBox1.Location = new System.Drawing.Point(18, 432);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(1164, 206);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "操作日志";
            // 
            // LogShowWindow
            // 
            this.LogShowWindow.Dock = System.Windows.Forms.DockStyle.Fill;
            this.LogShowWindow.Enabled = false;
            this.LogShowWindow.Location = new System.Drawing.Point(4, 25);
            this.LogShowWindow.Name = "LogShowWindow";
            this.LogShowWindow.Size = new System.Drawing.Size(1156, 177);
            this.LogShowWindow.TabIndex = 0;
            this.LogShowWindow.Text = "";
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 18F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1200, 675);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.SwitchtableLayoutPanel);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximizeBox = false;
            this.Name = "MainWindow";
            this.Text = "开关量控制台";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainWindow_FormClosing);
            this.Shown += new System.EventHandler(this.MainWindow_Shown);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 文件ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem WorkSpaceToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem LoadWorkSpaceToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem SaveWorkSpaceToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 帮助ToolStripMenuItem;
        private System.Windows.Forms.TableLayoutPanel SwitchtableLayoutPanel;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RichTextBox LogShowWindow;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
    }
}

