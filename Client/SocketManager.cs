using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

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

        public int receiveData(string rcvBuff) {
            byte[] receiveBuffer = new byte[Cons.BUFFER_SIZE];
            int length = client.Receive(receiveBuffer);
            rcvBuff = Encoding.ASCII.GetString(receiveBuffer, 0, length);
            return length;
        }
    }
}
