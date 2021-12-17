using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Client
{
    public class Cons
    {
        public static int BUTTON_WIDTH = 110;
        public static int BUTTON_HEIGHT = 110;
        public static int BOARD_SIZE = 3;

        public static int OPCODE_SIZE = 1;
        public static int LENGTH_SIZE = 2;
        public static int LOCATION_SIZE = 2;
        public static string SAMPLE = "00";

        public static string IP = "127.0.0.1";
        public static int port = 5500;
        public static int BUFFER_SIZE = 1024;
    }
}
