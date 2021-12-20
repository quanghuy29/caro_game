using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client
{
    public class EventManager
    {
        private event EventHandler<SuperEventArgs> _login;
        private event EventHandler<SuperEventArgs> _accept;
        private event EventHandler<SuperEventArgs> _move;

        public event EventHandler<SuperEventArgs> Login {
            add {
                _login += value;
            }
            remove {
                _login -= value;
            }
        }

        public event EventHandler<SuperEventArgs> Accept {
            add {
                _accept += value;
            }
            remove {
                _accept -= value;
            }
        }

        public event EventHandler<SuperEventArgs> Move {
            add {
                _move += value;
            }
            remove {
                _move -= value;
            }
        }

        public void notifLogin(int result) {
            if (_login != null)
                _login(this, new SuperEventArgs(result));
        }

        public void notifChallenge(string name) {
            if (_accept != null)
                _accept(this, new SuperEventArgs(name));
        }

        public void notifMove(string move) {
            if (_move != null)
                _move(this, new SuperEventArgs(move));
        }
    }

    public class SuperEventArgs : EventArgs
    {
        private int returnCode;
        private string returnName;

        public SuperEventArgs(int returnCode) {
            this.ReturnCode = returnCode;
        }

        public SuperEventArgs(string returnName) {
            this.ReturnName = returnName;
        }

        public int ReturnCode {
            get {
                return returnCode;
            }

            set {
                returnCode = value;
            }
        }

        public string ReturnName {
            get {
                return returnName;
            }

            set {
                returnName = value;
            }
        }
    }
}
