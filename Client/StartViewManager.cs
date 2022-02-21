using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
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
        Button buttonEnter;
        Button buttonCancel;

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

        public Button ButtonEnter {
            get {
                return buttonEnter;
            }

            set {
                buttonEnter = value;
            }
        }

        public Button ButtonCancel {
            get {
                return buttonCancel;
            }

            set {
                buttonCancel = value;
            }
        }

        public StartViewManager(TextBox name1, SocketManager client, EventManager eventManager) {
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
            this.eventManager = eventManager;
            
        }

        //@funtion initPanelChallenge: init the panel challenge
        //@param panelchallenge
        public void initPanelChallenge(Panel panelchallenge) {
            ButtonEnter = new Button()
            {
                Text = "Invite",
                Location = new Point(20, NamePlayer[1].Location.Y + 2 * NamePlayer[1].Height)
            };
            ButtonCancel = new Button()
            {
                Text = "Cancel",
                Location = new Point(20, NamePlayer[1].Location.Y + 2 * NamePlayer[1].Height)
            };
            panelchallenge.Controls.Add(LabelChallenge);
            panelchallenge.Controls.Add(NamePlayer[1]);
            panelchallenge.Controls.Add(ButtonEnter);
            panelchallenge.Controls.Add(ButtonCancel);
            panelchallenge.Visible = true;

            ButtonEnter.Click += ButtonEnter_Click;
            ButtonCancel.Click += ButtonCancel_Click;
        }

        //@funtion showPanelChallenge: show the panel challenge
        //@param panelchallenge
        public void showPanelChallenge(Panel panelchallenge) {
            panelchallenge.Visible = true;
        }

        //@funtion hidePanelChallenge: hide the panel challenger
        //@param panelchallenge
        public void hidePanelChallenge(Panel panelchallenge) {
            panelchallenge.Visible = false;
        }

        //@funtion clearOtherName: clear the name in the text box challenger
        public void clearOtherName() {
            NamePlayer[1].Text = "";
        }

        public void hideCancelButton() {
            ButtonEnter.Visible = true;
            ButtonCancel.Visible = false;
        }
        
        //@funtion ButtonEnter_Click: send challenger message to server
        private void ButtonEnter_Click(object sender, EventArgs e) {                      
            string name = NamePlayer[1].Text;

            Message mess = new Message(Cons.CHALLENGE, name.Length.ToString(Cons.SAMPLE_0000), name);
            client.sendData(mess.convertToString());

            ButtonEnter.Visible = false;
            ButtonCancel.Visible = true;   
        }

        //@funtion ButtonCancel_Click: cancel the invitation
        private void ButtonCancel_Click(object sender, EventArgs e) {
            string name = NamePlayer[1].Text;

            Message mess = new Message(Cons.CANCEL, name.Length.ToString(Cons.SAMPLE_0000), name);
            client.sendData(mess.convertToString());

            hideCancelButton();
        }
    }
}
