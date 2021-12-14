using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client
{
    public partial class FormStart : Form
    {
        public FormStart() {
            InitializeComponent();
        }

        private void exitButton_Click(object sender, EventArgs e) {
            Application.Exit();
        }

        private void loginButton_Click(object sender, EventArgs e) {
            if (!String.IsNullOrEmpty(userNameBox.Text))
            {
                string name = userNameBox.Text;
                FormPlay formPlay = new FormPlay(name);
                formPlay.ShowDialog();
            }
            else
            {
                MessageBox.Show("Please enter name!!!");
            }
        }
    }
}
