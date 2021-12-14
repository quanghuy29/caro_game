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
        public FormPlay(string name)
        {
            InitializeComponent();
            chessBoard = new ChessBoardManager(panelBoard, namePlayer1, namePlayer2, name);
            chessBoard.drawBoard(panelBoard);
            
        }

    }
}
