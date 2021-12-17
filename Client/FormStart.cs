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
        StartViewManager startView;
        SocketManager client;

        public FormStart() {
            InitializeComponent();

            client = new SocketManager();
        }    

        private void exitButton_Click(object sender, EventArgs e) {
            client.closeSocket();
            Application.Exit();
        }

        private void loginButton_Click(object sender, EventArgs e) {
            if (!String.IsNullOrEmpty(userNameBox.Text))
            {
                if (client.connectServer())
                {
                    MessageBox.Show("Connected!");

                    Message mess = new Message("1", "02", userNameBox.Text);

                    client.sendData(mess.convertToString());

                    startView = new StartViewManager(userNameBox, this.client);
                    startView.showListPlayer(listPlayer);
                    startView.showPanelChallenge(panelChallenge);

                    Button loginButt = sender as Button;
                    loginButt.Visible = false;
                }
                else MessageBox.Show("Login failed!");
                
            }
            else
            {
                MessageBox.Show("Please enter name!!!");
            }
        }
    }
}
