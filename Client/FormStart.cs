using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client
{
    public partial class FormStart : Form
    {
        public StartViewManager startView;
        SocketManager client;
        EventManager eventManager;

        public FormStart() {
            InitializeComponent();

            client = new SocketManager();
            eventManager = new EventManager();
            startView = new StartViewManager(userNameBox, client, eventManager);

            eventManager.Login += EventManager_Login;
            eventManager.Respone += EventManager_Respone;
            eventManager.Invite += EventManager_Invite;

            logoutButton.Visible = false;
            panelChallenge.Visible = false;
           
        }

        private void exitButton_Click(object sender, EventArgs e) {
            try
            {
                client.closeSocket();
                Application.Exit();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
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
                    client.ListenThread(eventManager, "login");
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
                client.ListenThread(eventManager, "logout");
            }
        }

        private void EventManager_Login(object sender, SuperEventArgs e) {
            this.Invoke((MethodInvoker)(() =>
            {
                if (e.ReturnCode == 1)
                {
                    MessageBox.Show("Login successful!");

                    startView.showListPlayer(listPlayer);
                    startView.showPanelChallenge(panelChallenge);

                    loginButton.Visible = false;
                    logoutButton.Enabled = true;
                    logoutButton.Visible = true;

                    client.ListenThread(eventManager, "start");
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
            this.Invoke((MethodInvoker)(() =>
            {
                if (e.ReturnCode == (int)Cons.command.ACCEPT)
                {
                    if(String.Compare(e.ReturnName,"1") == 0)
                    {
                        MessageBox.Show("Game started!");
                        string yourName = userNameBox.Text;
                        string otherName = e.ReturnName;

                        FormPlay formPlay = new FormPlay(otherName, yourName, client, eventManager, 2);
                        formPlay.ShowDialog();

                        startView.ButtonEnter.Visible = true;
                        startView.ButtonCancel.Visible = false;
                    }
                    else
                    {
                        MessageBox.Show("Challenge accepted!");
                        string yourName = userNameBox.Text;
                        string otherName = e.ReturnName;

                        FormPlay formPlay = new FormPlay(yourName, otherName, client, eventManager, 1);
                        formPlay.ShowDialog();

                        startView.ButtonEnter.Visible = true;
                        startView.ButtonCancel.Visible = false;
                    }                    
                }
                else if (e.ReturnCode == (int)Cons.command.REFUSE)
                {
                    MessageBox.Show("Challenge refuse!");
                    startView.ButtonEnter.Visible = true;
                    startView.ButtonCancel.Visible = false;
                }
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
                else if (e.ReturnCode == (int)Cons.command.ERROR)
                {
                    if (String.Compare(e.ReturnName, "1") == 0) MessageBox.Show("Player is playing!");
                    else MessageBox.Show("Can't play with player has too high or too low rank!");
                }
            }));
        }

        private void EventManager_Invite(object sender, SuperEventArgs e) {
            this.Invoke((MethodInvoker)(() =>
            {
                DialogResult dialogResult = MessageBox.Show(e.ReturnName + " want to challenge you. Do you accept?", "Invite", MessageBoxButtons.YesNo);
                if (dialogResult == DialogResult.Yes)
                {
                    Message mess = new Message(Cons.ACCEPT, e.ReturnName.Length.ToString(Cons.SAMPLE), e.ReturnName);
                    client.sendData(mess.convertToString());

                    client.ListenThread(eventManager, "");
                }
                else if (dialogResult == DialogResult.No)
                {
                    Message mess = new Message(Cons.REFUSE, e.ReturnName.Length.ToString(Cons.SAMPLE), e.ReturnName);
                    client.sendData(mess.convertToString());
                }
            }));
        }
    }
}
