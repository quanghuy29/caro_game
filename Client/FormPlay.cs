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

        public FormPlay(string name1, string name2, SocketManager client)
        {
            InitializeComponent();
            this.client = client;
            chessBoard = new ChessBoardManager(panelBoard, namePlayer1, namePlayer2, name1, name2, client);
            chessBoard.drawBoard(panelBoard);                
        }

        private void surrondButton_Click(object sender, EventArgs e) {
            client.sendData("Bye");
            this.Close();
        }
    }
}
