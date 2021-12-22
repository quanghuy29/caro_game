using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client
{
    public class StartViewManager
    {
        private List<TextBox> namePlayer;
        private Label labelChallenge;
        SocketManager client;
        EventManager eventManager;

        public List<TextBox> NamePlayer {
            get {
                return namePlayer;
            }

            set {
                namePlayer = value;
            }
        }

        public Label LabelChallenge {
            get {
                return labelChallenge;
            }

            set {
                labelChallenge = value;
            }
        }

        public StartViewManager(TextBox name1, SocketManager client) {
            LabelChallenge = new Label()
            {
                Text = "Enter name player: ",
                Location = new Point(10, 10),
            };
            NamePlayer = new List<TextBox>()
            {
                name1,
                new TextBox() { Location = new Point(10, LabelChallenge.Location.Y + 2 * LabelChallenge.Height) }
            };
            this.client = client;
            eventManager = new EventManager();

            eventManager.Respone += EventManager_Respone;
        }

        private void EventManager_Respone(object sender, SuperEventArgs e) {
            if (e.ReturnCode == (int)Cons.command.ACCEPT)
            {
                MessageBox.Show("Challenge accepted!");
                string name1 = NamePlayer[0].Text;
                string name2 = e.ReturnName;

                FormPlay formPlay = new FormPlay(name1, name2, this.client);
                formPlay.ShowDialog();
            }
            else MessageBox.Show("Challenge refuse!");
        }

        public void showListPlayer(ListView listPlayer) {
            listPlayer.Items.Add("123");
            listPlayer.Items.Add("345");
        }

        public void showPanelChallenge(Panel panelchallenge) {
            Button buttonEnter = new Button()
            {
                Text = "Challenge",
                Location = new Point(20, NamePlayer[1].Location.Y + 2 * NamePlayer[1].Height)
            };

            panelchallenge.Controls.Add(LabelChallenge);
            panelchallenge.Controls.Add(NamePlayer[1]);
            panelchallenge.Controls.Add(buttonEnter);
            panelchallenge.Visible = true;

            buttonEnter.Click += ButtonEnter_Click;
        }

        public void hideListPlayer(ListView listPlayer) {
            listPlayer.Items.Clear();
        }

        public void hidePanelChallenge(Panel panelchallenge) {
            panelchallenge.Visible = false;
        }

        private void ButtonEnter_Click(object sender, EventArgs e) {                      
            string name = NamePlayer[1].Text;

            Message mess = new Message(Cons.CHALLENGE, name.Length.ToString(Cons.SAMPLE), name);
            client.sendData(mess.convertToString());
            client.Listen(eventManager);           
        }
    }
}
