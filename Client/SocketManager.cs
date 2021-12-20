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

        public void Listen(EventManager eventManager) {
            try
            {
                string rcvBuff;
                rcvBuff = this.receiveData();
                processData(rcvBuff, eventManager);
             }
             catch { }    
        }

        public void ListenThread(EventManager eventManager) {
            Thread listenThread = new Thread(() =>
            {
                Listen(eventManager);
            });
            listenThread.IsBackground = true;
            listenThread.Start();
        }

        private void processData(string mess, EventManager eventManager) {
            Message rcvMess = new Message(mess);

            string opcode = rcvMess.Opcode;
            string payload = rcvMess.Payload;

            if(String.Compare(opcode, Cons.LOGIN) == 0)
            {
                if (String.Compare(payload, "1") == 0) eventManager.notifLogin(1);
                else eventManager.notifLogin(0);
            }
            else if (String.Compare(opcode, Cons.LIST) == 0)
            {

            }
            else if (String.Compare(opcode, Cons.CHALLENGE) == 0)
            {

            }
            else if (String.Compare(opcode, Cons.ACCEPT) == 0)
            {
                eventManager.notifChallenge(payload);
            }
            else if (String.Compare(opcode, Cons.REFUSE) == 0)
            {

            }
            else if (String.Compare(opcode, Cons.MOVE) == 0)
            {
                eventManager.notifMove(payload);
            }
            else if (String.Compare(opcode, Cons.RESULT) == 0)
            {

            }
            else if (String.Compare(opcode, Cons.ERROR) == 0)
            {

            }
            else if (String.Compare(opcode, Cons.LOGOUT) == 0)
            {

            }
            else
            {
                Message messError = new Message(Cons.ERROR, Cons.SAMPLE, "");
                sendData(messError.convertToString());
                Listen(eventManager);
            }
        }       
    }
}
