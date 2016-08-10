using System;
using System.Collections.Generic;
using System.IO.Ports;
using System.Runtime.InteropServices;
using System.Text;
using System.Management;


namespace RFID_USBCode
{
    class Program
    {
        
        public static void Main()
        {
            // Get a list of serial port names.
            string[] ports = SerialPort.GetPortNames();


            Console.WriteLine("The following serial ports were found:");

            string portName = string.Empty;

            foreach (COMPortInfo comPort in COMPortInfo.GetCOMPortsInfo())
            {
                Console.WriteLine(string.Format("{0} – {1}", comPort.Name, comPort.Description));
                if (IsProlificPort(comPort, "Prolific"))
                {
                    portName = comPort.Name;
                    break;
                }
            }

            Console.ReadLine();

            if (LFReader.gOpenReader(portName, 38400, 0))
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
        private static bool IsProlificPort(COMPortInfo comPort, string driverName)
        {
            return comPort.Description.Contains(driverName);
        }

        internal class ProcessConnection
        {

            public static ConnectionOptions ProcessConnectionOptions()
            {
                ConnectionOptions options = new ConnectionOptions();
                options.Impersonation = ImpersonationLevel.Impersonate;
                options.Authentication = AuthenticationLevel.Default;
                options.EnablePrivileges = true;
                return options;
            }

            public static ManagementScope ConnectionScope(string machineName, ConnectionOptions options, string path)
            {
                ManagementScope connectScope = new ManagementScope();
                connectScope.Path = new ManagementPath(@"\\" + machineName + path);
                connectScope.Options = options;
                connectScope.Connect();
                return connectScope;
            }
        }

        public class COMPortInfo
        {
            public string Name { get; set; }
            public string Description { get; set; }

            public COMPortInfo() { }

            public static List<COMPortInfo> GetCOMPortsInfo()
            {
                List<COMPortInfo> comPortInfoList = new List<COMPortInfo>();

                ConnectionOptions options = ProcessConnection.ProcessConnectionOptions();
                ManagementScope connectionScope = ProcessConnection.ConnectionScope(Environment.MachineName, options, @"\root\CIMV2");

                ObjectQuery objectQuery = new ObjectQuery("SELECT * FROM Win32_PnPEntity WHERE ConfigManagerErrorCode = 0");
                ManagementObjectSearcher comPortSearcher = new ManagementObjectSearcher(connectionScope, objectQuery);

                using (comPortSearcher)
                {
                    string caption = null;
                    foreach (ManagementObject obj in comPortSearcher.Get())
                    {
                        if (obj != null)
                        {
                            object captionObj = obj["Caption"];
                            if (captionObj != null)
                            {
                                caption = captionObj.ToString();
                                if (caption.Contains("(COM"))
                                {
                                    COMPortInfo comPortInfo = new COMPortInfo();
                                    comPortInfo.Name = caption.Substring(caption.LastIndexOf("(COM")).Replace("(", string.Empty).Replace(")",
                                                                         string.Empty);
                                    comPortInfo.Description = caption;
                                    comPortInfoList.Add(comPortInfo);
                                }
                            }
                        }
                    }
                }
                return comPortInfoList;
            }
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
