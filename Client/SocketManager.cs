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

        //@funtion connectServer: connect to server
        //@return true if success, false if false
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

        //@funtion closeSocket: close the socket
        public void closeSocket() {
            if (client == null) return;
            client.Close();
        }

        //@funtion sendData: send data to server
        //@param data
        //@return ret: length of data 
        public int sendData(string data) {
            var sendBuffer = Encoding.ASCII.GetBytes(data);
            int ret = client.Send(sendBuffer);
            return ret;
        }

        //@funtion receiveData: receive data from server
        //@return revBuff: buffer containing the data
        private string receiveData() {
            string rcvBuff;
            int size;
            byte[] receiveBuffer = new byte[Cons.BUFFER_SIZE];
            int lengthRcv = client.Receive(receiveBuffer);
            rcvBuff = Encoding.ASCII.GetString(receiveBuffer, 0, lengthRcv);

            string length = rcvBuff.Substring(Cons.OPCODE_SIZE, Cons.LENGTH_SIZE);
            size = Convert.ToInt32(length);
            size -= lengthRcv - Cons.OPCODE_SIZE - Cons.LENGTH_SIZE;

            while (size != 0)
            {
                receiveBuffer = new byte[Cons.BUFFER_SIZE];
                lengthRcv = client.Receive(receiveBuffer);
                rcvBuff = Encoding.ASCII.GetString(receiveBuffer, 0, lengthRcv);

                length = rcvBuff.Substring(Cons.OPCODE_SIZE, Cons.LENGTH_SIZE);
                size -= lengthRcv;
            }
            return rcvBuff;
        }

        //@funtion Listen: listen message from data
        //@param eventManager: event object that will notify to system when received a message
        private void Listen(EventManager eventManager) {
            try
            {
                string rcvBuff;
                rcvBuff = receiveData();
                processData(rcvBuff, eventManager);
             }
             catch { }    
        }

        //@funtion ListenThread: create a thread to listen from server
        //@param eventManager: event object that will notify to system when received a message
        public void ListenThread(EventManager eventManager) {
            Thread listenThread = new Thread(() =>
            {
                Listen(eventManager);
            });
            listenThread.IsBackground = true;
            listenThread.Start();
        }

        //@funtion processData: process data received
        //@param mess: message received
        //@param eventManager: event object that will notify to system when received a message
        private void processData(string mess, EventManager eventManager) {
            Message rcvMess = new Message(mess);

            int opcode = Convert.ToInt32(rcvMess.Opcode);
            string payload = rcvMess.Payload;
            MessageBox.Show(mess);
            switch (opcode)
            {
                case (int)Cons.command.LOGIN:
                    if (String.Compare(payload, "1") == 0) eventManager.notifLogin(1);
                    else eventManager.notifLogin(0);
                    break;
                case (int)Cons.command.LIST:
                    eventManager.notifList(payload);
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
