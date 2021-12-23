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
    public partial class FormPlay : Form
    {
        ChessBoardManager chessBoard;
        SocketManager client;
        EventManager eventManager;

        public FormPlay(string name1, string name2, SocketManager client, EventManager eventManager)
        {
            InitializeComponent();

            namePlayer1.Text = name1;
            namePlayer2.Text = name2;

            this.client = client;
            chessBoard = new ChessBoardManager(panelBoard, namePlayer1, namePlayer2, client, eventManager);
            chessBoard.drawBoard(panelBoard);

            this.eventManager = eventManager;
            this.eventManager.Result += EventManager_Result;

            client.ListenThread(eventManager);

            this.ControlBox = false;
        }

        private void EventManager_Result(object sender, SuperEventArgs e) {
            this.Invoke((MethodInvoker)(()=>{
                if (String.Compare(e.ReturnName, namePlayer1.Text) == 0)
                {
                    MessageBox.Show("You win!");
                }
                else if (String.Compare(e.ReturnName, namePlayer2.Text) == 0)
                {
                    MessageBox.Show("You lose!");
                }
                else MessageBox.Show("Draw!");
            }));            
            this.Close();
        }

        private void surrenderButton_Click(object sender, EventArgs e) {
            DialogResult dialogResult = MessageBox.Show("Do you want surrender?", "Question", MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                Message mess = new Message(Cons.MOVE, Cons.SAMPLE, "");
                client.sendData(mess.convertToString());
            }         
        }
    }
}
