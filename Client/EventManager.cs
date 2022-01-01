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
        private event EventHandler<SuperEventArgs> _respone;
        private event EventHandler<SuperEventArgs> _move;
        private event EventHandler<SuperEventArgs> _result;
        private event EventHandler<SuperEventArgs> _invite;
        private event EventHandler<SuperEventArgs> _list;

        public event EventHandler<SuperEventArgs> Login {
            add {
                _login += value;
            }
            remove {
                _login -= value;
            }
        }

        public event EventHandler<SuperEventArgs> Respone {
            add {
                _respone += value;
            }
            remove {
                _respone -= value;
            }
        }

        public event EventHandler<SuperEventArgs> Result {
            add {
                _result += value;
            }
            remove {
                _result -= value;
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

        public event EventHandler<SuperEventArgs> Invite {
            add {
                _invite += value;
            }
            remove {
                _invite -= value;
            }
        }

        public event EventHandler<SuperEventArgs> List {
            add {
                _list += value;
            }
            remove {
                _list -= value;
            }
        }

        public void notifLogin(int result) {
            if (_login != null)
                _login(this, new SuperEventArgs(result));
        }

        public void notifRespone(int code, string name) {
            if (_respone != null)
                _respone(this, new SuperEventArgs(code, name));
        }

        public void notifMove(string move) {
            if (_move != null)
            {
                _move(this, new SuperEventArgs(move));
            }
               
        }

        public void notifResult(string name) {
            if (_result != null)
                _result(this, new SuperEventArgs(name));
        }

        public void notifInvite(string name) {
            if (_invite != null)
                _invite(this, new SuperEventArgs(name));
        }

        public void notifList(string listname) {
            if (_list != null)
                _list(this, new SuperEventArgs(listname));
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

        public SuperEventArgs(int returnCode, string returnName) {
            this.returnCode = returnCode;
            this.returnName = returnName;
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
