using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace Client
{
    public class ChessBoardManager
    {
        private Panel chessBoard;        
        private List<Player> player;      
        private int currentPlayer;
        private List<TextBox> namePlayer;
        SocketManager client;
        private Message message;

        public Panel ChessBoard {
            get {
                return chessBoard;
            }
            set {
                chessBoard = value;
            }
        }

        public List<Player> Player {
            get {
                return player;
            }
            set {
                player = value;
            }
        }

        public int CurrentPlayer {
            get {
                return currentPlayer;
            }
            set {
                currentPlayer = value;
            }
        }

        public List<TextBox> NamePlayer {
            get {
                return namePlayer;
            }
            set {
                namePlayer = value;
            }
        }

        public Message Message {
            get {
                return message;
            }

            set {
                message = value;
            }
        }

        public ChessBoardManager(Panel chessBoard, TextBox namePlayer1, TextBox namePlayer2, string name1, string name2, SocketManager client)
        {
            this.client = client;
            this.ChessBoard = chessBoard;
            this.NamePlayer = new List<TextBox>()
            {
                namePlayer1,
                namePlayer2
            };

            NamePlayer[0].Text = name1;
            NamePlayer[1].Text = name2;
            
            this.Player = new List<Player>() {
                new Player(this.NamePlayer[0].Text, Image.FromFile(Application.StartupPath + "\\imagine\\x.png")),
                new Player(this.NamePlayer[1].Text, Image.FromFile(Application.StartupPath + "\\imagine\\o.png"))
            };
            
            
            CurrentPlayer = 0;
            NamePlayer[CurrentPlayer].BackColor = Color.FromArgb(100, 214, 179);
        }
     
        public void drawBoard(Panel boardChess)
        {
            Button oldButton = new Button() { Width = 0, Location = new Point(0, 0) };
            for (int i = 0; i < Cons.BOARD_SIZE; i++)
            {
                for (int j = 0; j < Cons.BOARD_SIZE + 1; j++)
                {
                    Button btn = new Button()
                    {
                        Width = Cons.BUTTON_WIDTH,
                        Height = Cons.BUTTON_HEIGHT,
                        Location = new Point(oldButton.Location.X + oldButton.Width, oldButton.Location.Y),
                        BackgroundImageLayout = ImageLayout.Stretch,
                        Tag = i.ToString(Cons.SAMPLE) + j.ToString(Cons.SAMPLE)
                    };
                    btn.Click += Btn_Click;
                    boardChess.Controls.Add(btn);
                    oldButton = btn;
                }
                oldButton.Location = new Point(0, oldButton.Location.Y + Cons.BUTTON_HEIGHT);
                oldButton.Width = 0;
                oldButton.Height = 0;
            }
        }

        private void Btn_Click(object sender, EventArgs e)
        {
            Button btn = sender as Button;
            if (btn.BackgroundImage != null)
                return;

            Point point = getChessPoint(btn);
            Message = new Message("1", "02", point.X, point.Y);
            client.sendData(Message.convertToString());

            
            btn.BackgroundImage = Player[CurrentPlayer].Mark;

            NamePlayer[CurrentPlayer].BackColor = Color.White;
            CurrentPlayer = CurrentPlayer == 1 ? 0 : 1;

            NamePlayer[CurrentPlayer].BackColor = Color.FromArgb(100, 214, 179);

        }

        public Point getChessPoint(Button btn) {
            int x = Convert.ToInt32(btn.Tag.ToString().Substring(0, Cons.LOCATION_SIZE));
            int y = Convert.ToInt32(btn.Tag.ToString().Substring(Cons.LOCATION_SIZE, Cons.LOCATION_SIZE));
            Point point = new Point(x, y);
            return point;
        }
    }
}
