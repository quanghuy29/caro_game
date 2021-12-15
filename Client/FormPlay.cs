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
        public FormPlay(string name1, string name2)
        {
            InitializeComponent();
            chessBoard = new ChessBoardManager(panelBoard, namePlayer1, namePlayer2, name1, name2);
            chessBoard.drawBoard(panelBoard);            
        }

        private void surrondButton_Click(object sender, EventArgs e) {
            this.Close();
        }
    }
}
