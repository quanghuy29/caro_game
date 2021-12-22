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

        public FormPlay(string name1, string name2, SocketManager client)
        {
            InitializeComponent();
            this.client = client;
            chessBoard = new ChessBoardManager(panelBoard, namePlayer1, namePlayer2, name1, name2, client);
            chessBoard.drawBoard(panelBoard);

            eventManager = new EventManager();
            eventManager.Result += EventManager_Result;

            client.ListenThread(eventManager);
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

        private void surrondButton_Click(object sender, EventArgs e) {
            Message mess = new Message(Cons.MOVE, Cons.SAMPLE, "");
            client.sendData(mess.convertToString());

        }
    }
}
