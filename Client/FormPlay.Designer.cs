namespace Client
{
    partial class FormPlay
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.Label label1;
            this.panelBoard = new System.Windows.Forms.Panel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.surrenderButton = new System.Windows.Forms.Button();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.namePlayer2 = new System.Windows.Forms.TextBox();
            this.namePlayer1 = new System.Windows.Forms.TextBox();
            label1 = new System.Windows.Forms.Label();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            label1.Location = new System.Drawing.Point(89, 176);
            label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            label1.Name = "label1";
            label1.Size = new System.Drawing.Size(32, 25);
            label1.TabIndex = 2;
            label1.Text = "vs";
            // 
            // panelBoard
            // 
            this.panelBoard.BackColor = System.Drawing.SystemColors.Control;
            this.panelBoard.Location = new System.Drawing.Point(17, 16);
            this.panelBoard.Margin = new System.Windows.Forms.Padding(4);
            this.panelBoard.Name = "panelBoard";
            this.panelBoard.Size = new System.Drawing.Size(463, 431);
            this.panelBoard.TabIndex = 0;
            // 
            // panel2
            // 
            this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.panel2.BackColor = System.Drawing.SystemColors.ControlLightLight;
            this.panel2.Controls.Add(this.surrenderButton);
            this.panel2.Controls.Add(this.pictureBox2);
            this.panel2.Controls.Add(this.pictureBox1);
            this.panel2.Controls.Add(label1);
            this.panel2.Controls.Add(this.namePlayer2);
            this.panel2.Controls.Add(this.namePlayer1);
            this.panel2.Location = new System.Drawing.Point(488, 20);
            this.panel2.Margin = new System.Windows.Forms.Padding(4);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(213, 417);
            this.panel2.TabIndex = 1;
            // 
            // surrenderButton
            // 
            this.surrenderButton.Location = new System.Drawing.Point(56, 332);
            this.surrenderButton.Margin = new System.Windows.Forms.Padding(4);
            this.surrenderButton.Name = "surrenderButton";
            this.surrenderButton.Size = new System.Drawing.Size(100, 28);
            this.surrenderButton.TabIndex = 5;
            this.surrenderButton.Text = "Surrender";
            this.surrenderButton.UseVisualStyleBackColor = true;
            this.surrenderButton.Click += new System.EventHandler(this.surrenderButton_Click);
            // 
            // pictureBox2
            // 
            this.pictureBox2.BackgroundImage = global::Client.Properties.Resources.o;
            this.pictureBox2.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox2.Location = new System.Drawing.Point(143, 247);
            this.pictureBox2.Margin = new System.Windows.Forms.Padding(4);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(67, 62);
            this.pictureBox2.TabIndex = 4;
            this.pictureBox2.TabStop = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImage = global::Client.Properties.Resources.x;
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pictureBox1.Location = new System.Drawing.Point(7, 79);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(4);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(67, 62);
            this.pictureBox1.TabIndex = 3;
            this.pictureBox1.TabStop = false;
            // 
            // namePlayer2
            // 
            this.namePlayer2.Location = new System.Drawing.Point(7, 215);
            this.namePlayer2.Margin = new System.Windows.Forms.Padding(4);
            this.namePlayer2.Name = "namePlayer2";
            this.namePlayer2.ReadOnly = true;
            this.namePlayer2.Size = new System.Drawing.Size(203, 22);
            this.namePlayer2.TabIndex = 1;
            // 
            // namePlayer1
            // 
            this.namePlayer1.Location = new System.Drawing.Point(5, 148);
            this.namePlayer1.Margin = new System.Windows.Forms.Padding(4);
            this.namePlayer1.Name = "namePlayer1";
            this.namePlayer1.ReadOnly = true;
            this.namePlayer1.Size = new System.Drawing.Size(204, 22);
            this.namePlayer1.TabIndex = 0;
            // 
            // FormPlay
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(739, 462);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panelBoard);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "FormPlay";
            this.Text = "Caro";
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panelBoard;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TextBox namePlayer2;
        private System.Windows.Forms.TextBox namePlayer1;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button surrenderButton;
    }
}

