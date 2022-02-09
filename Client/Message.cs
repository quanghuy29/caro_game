using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public class Message
    {
        private string opcode;
        private string length;
        private string payload;

        public string Opcode {
            get {
                return opcode;
            }

            set {
                opcode = value;
            }
        }

        public string Length {
            get {
                return length;
            }

            set {
                length = value;
            }
        }

        public string Payload {
            get {
                return payload;
            }

            set {
                payload = value;
            }
        }

        public Message(string opcode, string length, string payload) {
            this.Opcode = opcode;
            this.Length = length;
            this.Payload = payload;
        }

        public Message(string opcode, string length, int locationX, int locationY) {
            this.Opcode = opcode;
            this.Length = length;
            this.Payload = locationX.ToString(Cons.SAMPLE_00) + locationY.ToString(Cons.SAMPLE_00);
        }

        public Message(string message) {
            this.Opcode = message.Substring(0, Cons.OPCODE_SIZE);
            this.Length = message.Substring(Cons.OPCODE_SIZE, Cons.LENGTH_SIZE);
            this.Payload = message.Remove(0, Cons.OPCODE_SIZE + Cons.LENGTH_SIZE);
        }

        public string convertToString() {
            string result = this.Opcode + this.Length + this.Payload;
            return result;
        }
    }
}
