namespace MemImage
{
    partial class Form1
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
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.imageBox1 = new System.Windows.Forms.PictureBox();
            this.GetImage = new System.Windows.Forms.Button();
            this.StopImage = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.imageBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // imageBox1
            // 
            this.imageBox1.Location = new System.Drawing.Point(42, 12);
            this.imageBox1.Name = "imageBox1";
            this.imageBox1.Size = new System.Drawing.Size(270, 240);
            this.imageBox1.TabIndex = 0;
            this.imageBox1.TabStop = false;
            // 
            // GetImage
            // 
            this.GetImage.Location = new System.Drawing.Point(42, 269);
            this.GetImage.Name = "GetImage";
            this.GetImage.Size = new System.Drawing.Size(75, 23);
            this.GetImage.TabIndex = 1;
            this.GetImage.Text = "获取图像";
            this.GetImage.UseVisualStyleBackColor = true;
            this.GetImage.Click += new System.EventHandler(this.GetImage_Click);
            // 
            // StopImage
            // 
            this.StopImage.Location = new System.Drawing.Point(237, 269);
            this.StopImage.Name = "StopImage";
            this.StopImage.Size = new System.Drawing.Size(75, 23);
            this.StopImage.TabIndex = 2;
            this.StopImage.Text = "停止";
            this.StopImage.UseVisualStyleBackColor = true;
            this.StopImage.Click += new System.EventHandler(this.StopImage_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(360, 304);
            this.Controls.Add(this.StopImage);
            this.Controls.Add(this.GetImage);
            this.Controls.Add(this.imageBox1);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "c#实时显示图像";
            ((System.ComponentModel.ISupportInitialize)(this.imageBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox imageBox1;
        private System.Windows.Forms.Button GetImage;
        private System.Windows.Forms.Button StopImage;
    }
}

