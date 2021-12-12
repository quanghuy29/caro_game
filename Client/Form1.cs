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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            drawBoard(panelBoard);
        }

        void drawBoard(Panel boardChess)
        {
            Button oldButton = new Button() { Width = 0, Location = new Point(0, 0) };
            for(int i = 0; i < Cons.BOARD; i++)
            {
                for (int j = 0; j < Cons.BOARD + 1; j++)
                {
                    Button btn = new Button()
                    {
                        Width = Cons.BUTTON_WIDTH,
                        Height = Cons.BUTTON_HEIGHT,
                        Location = new Point(oldButton.Location.X + oldButton.Width, oldButton.Location.Y)
                    };
                    boardChess.Controls.Add(btn);
                    oldButton = btn;
                }
                oldButton.Location = new Point(0, oldButton.Location.Y + Cons.BUTTON_HEIGHT);
                oldButton.Width = 0;
                oldButton.Height = 0;
            }
        }
    }
}
