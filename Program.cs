using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace RFID_USBCode
{
    class Program
    {
        
        public static void Main()
        {

            if (LFReader.gOpenReader("com4", 38400, 0))
            {
                Console.WriteLine("1->Open Reader");
                LFReader.gSetBeep(50, 0);//beep 50 millisecond

                StringBuilder str_out = new StringBuilder(50);
                int len = 0;
                LFReader.gGetModel(str_out, ref len, 0);//get reader model
                str_out.Insert(0, "2->Reader Model:");
                Console.WriteLine(str_out);
                byte[] array = new byte[8];

                LFReader.gReadIDCard(array, 0);//get reader model
                str_out.Insert(0, "2.1->Reader Data:");
                Console.WriteLine(str_out);

                Console.WriteLine("3->Close Reader");
                LFReader.gCloseReader(0);//disconnect reader, 

            }
            else
            {
                Console.WriteLine("Not open reader");
            }
            Console.ReadLine();
        }

        class LFReader
        {
            [DllImport("LFReaderAPI.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool gOpenReader(string port, uint baud, int addr);//connect reader 

            [DllImport("LFReaderAPI.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern bool gCloseReader(int addr);//disconnect reader

            [DllImport("LFReaderAPI.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern int gSetBeep(Byte time, int addr);//set beep

            [DllImport("LFReaderAPI.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern int gGetModel(StringBuilder model, ref int len, int addr);//Get Reader Model

            [DllImport("LFReaderAPI.dll", CallingConvention = CallingConvention.Cdecl)]
            public static extern int gReadIDCard(Byte[] ID, int addr); //read TK4100

        }
    }
}
