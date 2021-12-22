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
            this.logoutButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // loginText
            // 
            this.loginText.AutoSize = true;
            this.loginText.Location = new System.Drawing.Point(60, 46);
            this.loginText.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.loginText.Name = "loginText";
            this.loginText.Size = new System.Drawing.Size(73, 17);
            this.loginText.TabIndex = 0;
            this.loginText.Text = "Username";
            // 
            // loginButton
            // 
            this.loginButton.Location = new System.Drawing.Point(44, 133);
            this.loginButton.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.loginButton.Name = "loginButton";
            this.loginButton.Size = new System.Drawing.Size(100, 28);
            this.loginButton.TabIndex = 1;
            this.loginButton.Text = "Login";
            this.loginButton.UseVisualStyleBackColor = true;
            this.loginButton.Click += new System.EventHandler(this.loginButton_Click);
            // 
            // userNameBox
            // 
            this.userNameBox.Location = new System.Drawing.Point(31, 87);
            this.userNameBox.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.userNameBox.Name = "userNameBox";
            this.userNameBox.Size = new System.Drawing.Size(132, 22);
            this.userNameBox.TabIndex = 2;
            // 
            // exitButton
            // 
            this.exitButton.Location = new System.Drawing.Point(44, 180);
            this.exitButton.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.exitButton.Name = "exitButton";
            this.exitButton.Size = new System.Drawing.Size(100, 28);
            this.exitButton.TabIndex = 3;
            this.exitButton.Text = "Exit";
            this.exitButton.UseVisualStyleBackColor = true;
            this.exitButton.Click += new System.EventHandler(this.exitButton_Click);
            // 
            // listPlayer
            // 
            this.listPlayer.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.listPlayer.Location = new System.Drawing.Point(248, 37);
            this.listPlayer.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.listPlayer.Name = "listPlayer";
            this.listPlayer.Size = new System.Drawing.Size(247, 328);
            this.listPlayer.TabIndex = 4;
            this.listPlayer.UseCompatibleStateImageBehavior = false;
            // 
            // panelChallenge
            // 
            this.panelChallenge.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.panelChallenge.BackColor = System.Drawing.SystemColors.GradientActiveCaption;
            this.panelChallenge.Location = new System.Drawing.Point(31, 233);
            this.panelChallenge.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.panelChallenge.Name = "panelChallenge";
            this.panelChallenge.Size = new System.Drawing.Size(171, 177);
            this.panelChallenge.TabIndex = 5;
            // 
            // logoutButton
            // 
            this.logoutButton.Location = new System.Drawing.Point(44, 133);
            this.logoutButton.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.logoutButton.Name = "logoutButton";
            this.logoutButton.Size = new System.Drawing.Size(100, 28);
            this.logoutButton.TabIndex = 6;
            this.logoutButton.Text = "Log Out";
            this.logoutButton.UseVisualStyleBackColor = true;
            this.logoutButton.Click += new System.EventHandler(this.logoutButton_Click);
            // 
            // FormStart
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(564, 448);
            this.Controls.Add(this.logoutButton);
            this.Controls.Add(this.panelChallenge);
            this.Controls.Add(this.listPlayer);
            this.Controls.Add(this.exitButton);
            this.Controls.Add(this.userNameBox);
            this.Controls.Add(this.loginButton);
            this.Controls.Add(this.loginText);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
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
        private System.Windows.Forms.Button logoutButton;
    }
}