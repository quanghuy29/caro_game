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
        EventManager eventManager;

        public FormStart() {
            InitializeComponent();

            client = new SocketManager();
            eventManager = new EventManager();
            startView = new StartViewManager(userNameBox, this.client, this.eventManager);

            eventManager.Login += Notif_Login;
            eventManager.Respone += EventManager_Respone;

            logoutButton.Visible = false;
            panelChallenge.Visible = false;

        }

        private void exitButton_Click(object sender, EventArgs e) {
            client.closeSocket();
            Application.Exit();
        }

        private void loginButton_Click(object sender, EventArgs e) {
            if (!String.IsNullOrEmpty(userNameBox.Text))
            {
                userNameBox.ReadOnly = true;
                loginButton.Enabled = false;
                if (client.connectServer())
                {
                    Message mess = new Message(Cons.LOGIN, userNameBox.Text.Length.ToString(Cons.SAMPLE), userNameBox.Text);
                    client.sendData(mess.convertToString());
                    client.ListenThread(eventManager);
                }
                else
                {
                    MessageBox.Show("Connected failed!");
                    userNameBox.ReadOnly = false;
                    loginButton.Enabled = true;
                }               
            }
            else
            {
                MessageBox.Show("Please enter name!!!");
            }
        }        

        private void logoutButton_Click(object sender, EventArgs e) {
            DialogResult dialogResult = MessageBox.Show("Do you want to log out?", "Question", MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                logoutButton.Enabled = false;
                Message mess = new Message(Cons.LOGOUT, Cons.SAMPLE, "");
                client.sendData(mess.convertToString());
                client.ListenThread(eventManager);
            }            
        }

        private void Notif_Login(object sender, SuperEventArgs e) {
            this.Invoke((MethodInvoker)(() => {
                if (e.ReturnCode == 1)
                {
                    MessageBox.Show("Login successful!");

                    startView.showListPlayer(listPlayer);
                    startView.showPanelChallenge(panelChallenge);

                    loginButton.Visible = false;
                    logoutButton.Enabled = true;
                    logoutButton.Visible = true;

                    client.ListenThread(eventManager);
                }
                else
                {
                    MessageBox.Show("Login failed!");
                    userNameBox.ReadOnly = false;
                    loginButton.Enabled = true;
                    client.closeSocket();
                }
            }));
        }

        private void EventManager_Respone(object sender, SuperEventArgs e) {
            this.Invoke((MethodInvoker)(() => {
                if (e.ReturnCode == (int)Cons.command.ACCEPT)
                {
                    MessageBox.Show("Challenge accepted!");
                    string name1 = userNameBox.Text;
                    string name2 = e.ReturnName;

                    FormPlay formPlay = new FormPlay(name1, name2, this.client, eventManager);
                    formPlay.ShowDialog();
                }
                else if (e.ReturnCode == (int)Cons.command.REFUSE) MessageBox.Show("Challenge refuse!");
                else if (e.ReturnCode == (int)Cons.command.LOGOUT)
                {
                    MessageBox.Show("Log out successful");
                    loginButton.Visible = true;
                    loginButton.Enabled = true;
                    logoutButton.Visible = false;
                    userNameBox.ReadOnly = false;

                    client.closeSocket();

                    startView.hideListPlayer(listPlayer);
                    startView.hidePanelChallenge(panelChallenge);
                }
            }));
        }
    }
}
