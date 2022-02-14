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
        public static int LENGTH_SIZE = 4;
        public static int LOCATION_SIZE = 2;
        public static string SAMPLE_0000 = "0000";
        public static string SAMPLE_00 = "00";
        public static string SPACE = " ";

        public static string IP = "127.0.0.1";
        public static int port = 5500;
        public static int BUFFER_SIZE = 1024;

        public static string LOGIN = "1";
        public static string LIST = "2";
        public static string CHALLENGE = "3";
        public static string ACCEPT = "4";
        public static string REFUSE = "5";
        public static string MOVE = "6";
        public static string RESULT = "7";
        public static string ERROR = "8";
        public static string LOGOUT = "9";
        public static string CANCEL = "0";

        public static int PL_SUCCESS = 0;
        public static int PL_FAIL = 1;
        public static int PL_NOT_SUITABLE = 1;
        public static int PL_BUSY = 2;
        public static int PL_NOT_FOUND = 3;

        public enum command
        {
            LOGIN = 1,
            LIST = 2,
            CHALLENGE = 3,
            ACCEPT = 4,
            REFUSE = 5,
            MOVE = 6,
            RESULT = 7,
            ERROR = 8,
            LOGOUT = 9,
            CANCAL = 0
        }
    }
}
