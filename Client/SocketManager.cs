using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client
{
    public class SocketManager
    {
        Socket client;

        public bool connectServer() {
            IPEndPoint iep = new IPEndPoint(IPAddress.Parse(Cons.IP), Cons.port);
            client = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            try
            {
                client.Connect(iep);
                return true;
            }
            catch
            {
                return false;
            }
        }

        public void closeSocket() {
            if (client == null) return;
            client.Close();
        }

        public int sendData(string data) {
            var sendBuffer = Encoding.ASCII.GetBytes(data);
            int ret = client.Send(sendBuffer);
            //client.Shutdown(SocketShutdown.Send);
            return ret;
        }

        public string receiveData() {
            byte[] receiveBuffer = new byte[Cons.BUFFER_SIZE];
            int length = client.Receive(receiveBuffer);
            string rcvBuff = Encoding.ASCII.GetString(receiveBuffer, 0, length);
            return rcvBuff;
        }

        public void Listen(EventManager eventManager, string debug) {
            try
            {
                string rcvBuff;
                rcvBuff = this.receiveData();
                processData(rcvBuff, eventManager, debug);
             }
             catch { }    
        }

        public void ListenThread(EventManager eventManager, string debug) {
            Thread listenThread = new Thread(() =>
            {
                Listen(eventManager, debug);
            });
            listenThread.IsBackground = true;
            listenThread.Start();
        }

        private void processData(string mess, EventManager eventManager, string debug) {
            Message rcvMess = new Message(mess);

            int opcode = Convert.ToInt32(rcvMess.Opcode);
            string payload = rcvMess.Payload;
            //MessageBox.Show(debug);
            switch (opcode)
            {
                case (int)Cons.command.LOGIN:
                    if (String.Compare(payload, "1") == 0) eventManager.notifLogin(1);
                    else eventManager.notifLogin(0);
                    break;
                case (int)Cons.command.LIST:
                    break;
                case (int)Cons.command.CHALLENGE:
                    eventManager.notifInvite(payload);
                    break;
                case (int)Cons.command.ACCEPT:                   
                    eventManager.notifRespone(opcode, payload);
                    break;
                case (int)Cons.command.REFUSE:
                    eventManager.notifRespone(opcode, payload);
                    break;
                case (int)Cons.command.MOVE:                    
                    eventManager.notifMove(payload);
                    break;
                case (int)Cons.command.RESULT:
                    
                    eventManager.notifResult(payload);
                    break;
                case (int)Cons.command.ERROR:
                    eventManager.notifRespone(opcode, payload);
                    break;
                case (int)Cons.command.LOGOUT:
                    eventManager.notifRespone(opcode, payload);
                    break;
                default:
                    break;
            }
        }
    }
}
