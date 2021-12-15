namespace Client
{
    partial class FormStart
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
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
        private void InitializeComponent() {
            this.loginText = new System.Windows.Forms.Label();
            this.loginButton = new System.Windows.Forms.Button();
            this.userNameBox = new System.Windows.Forms.TextBox();
            this.exitButton = new System.Windows.Forms.Button();
            this.listPlayer = new System.Windows.Forms.ListView();
            this.panelChallenge = new System.Windows.Forms.Panel();
            this.SuspendLayout();
            // 
            // loginText
            // 
            this.loginText.AutoSize = true;
            this.loginText.Location = new System.Drawing.Point(53, 39);
            this.loginText.Name = "loginText";
            this.loginText.Size = new System.Drawing.Size(55, 13);
            this.loginText.TabIndex = 0;
            this.loginText.Text = "Username";
            // 
            // loginButton
            // 
            this.loginButton.Location = new System.Drawing.Point(33, 117);
            this.loginButton.Name = "loginButton";
            this.loginButton.Size = new System.Drawing.Size(75, 23);
            this.loginButton.TabIndex = 1;
            this.loginButton.Text = "Login";
            this.loginButton.UseVisualStyleBackColor = true;
            this.loginButton.Click += new System.EventHandler(this.loginButton_Click);
            // 
            // userNameBox
            // 
            this.userNameBox.Location = new System.Drawing.Point(23, 71);
            this.userNameBox.Name = "userNameBox";
            this.userNameBox.Size = new System.Drawing.Size(100, 20);
            this.userNameBox.TabIndex = 2;
            // 
            // exitButton
            // 
            this.exitButton.Location = new System.Drawing.Point(33, 156);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(75, 23);
            this.exitButton.TabIndex = 3;
            this.exitButton.Text = "Exit";
            this.exitButton.UseVisualStyleBackColor = true;
            this.exitButton.Click += new System.EventHandler(this.exitButton_Click);
            // 
            // listPlayer
            // 
            this.listPlayer.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.listPlayer.Location = new System.Drawing.Point(186, 30);
            this.listPlayer.Name = "listPlayer";
            this.listPlayer.Size = new System.Drawing.Size(186, 267);
            this.listPlayer.TabIndex = 4;
            this.listPlayer.UseCompatibleStateImageBehavior = false;
            // 
            // panelChallenge
            // 
            this.panelChallenge.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.panelChallenge.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.panelChallenge.Location = new System.Drawing.Point(23, 210);
            this.panelChallenge.Name = "panelChallenge";
            this.panelChallenge.Size = new System.Drawing.Size(130, 100);
            this.panelChallenge.TabIndex = 5;
            // 
            // FormStart
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(423, 364);
            this.Controls.Add(this.panelChallenge);
            this.Controls.Add(this.listPlayer);
            this.Controls.Add(this.exitButton);
            this.Controls.Add(this.userNameBox);
            this.Controls.Add(this.loginButton);
            this.Controls.Add(this.loginText);
            this.Name = "FormStart";
            this.Text = "Login";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label loginText;
        private System.Windows.Forms.Button loginButton;
        private System.Windows.Forms.TextBox userNameBox;
        private System.Windows.Forms.Button exitButton;
        private System.Windows.Forms.ListView listPlayer;
        private System.Windows.Forms.Panel panelChallenge;
    }
}