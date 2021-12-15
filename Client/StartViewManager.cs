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

        public StartViewManager(TextBox name1) {
            LabelChallenge = new Label()
            {
                Text = "Enter name player: ",
                Location = new Point(0, 0)
            };
            NamePlayer = new List<TextBox>()
            {
                name1,
                new TextBox() { Location = new Point(0, LabelChallenge.Location.Y + LabelChallenge.Height) }
            };
            
        }

        public void showListPlayer(ListView listPlayer) {
            listPlayer.Items.Add("123");
            listPlayer.Items.Add("345");
        }

        public void showPanelChallenge(Panel panelchallenge) {
            Button buttonEnter = new Button()
            {
                Text = "Challenge",
                Location = new Point(0, NamePlayer[1].Location.Y + 2 * NamePlayer[1].Height)
            };

            panelchallenge.Controls.Add(LabelChallenge);
            panelchallenge.Controls.Add(NamePlayer[1]);
            panelchallenge.Controls.Add(buttonEnter);

            buttonEnter.Click += ButtonEnter_Click;
        }

        private void ButtonEnter_Click(object sender, EventArgs e) {
            MessageBox.Show("Challenge accepted");

            string name1 = NamePlayer[0].Text;
            string name2 = NamePlayer[1].Text;

            FormPlay formPlay = new FormPlay(name1, name2);
            formPlay.ShowDialog();
        }
    }
}
