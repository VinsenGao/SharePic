using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
namespace MemImage
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        public  static bool videoS=false;
        static byte[] PadLines(byte[] bytes, int rows, int columns)
        {

            try
            {
                var currentStride = 4 * columns; // 3
                var newStride = 4 * columns;  // 4
                var newBytes = new byte[newStride * rows];
                for (var i = 0; i < rows; i++)
                    Buffer.BlockCopy(bytes, currentStride * i, newBytes, newStride * i, currentStride);
                return newBytes;
            }
            catch (AccessViolationException)
            {
                Console.WriteLine("eror");
            }
            return bytes;

        }
        private void GetImage_Click(object sender, EventArgs e)
        {
            videoS = true;
            Thread RecoThread = new Thread(RecoMethod);


            RecoThread.Start();
        }

        public void RecoMethod()
        {
            byte[] varB = new byte[270 * 240 * 4];
            ShareMemLib MemDB = new ShareMemLib(); // 为公共的变量
            while(videoS)
            {

                
                try
                {

                    varB = MemDB.ReadFromMemory(270 * 240 * 4, typeof(byte), "Local\\RecoResultMap");
                  
                  //  byte[] varB = new byte[270 * 240 * 4];
                    //GetBGRMaps(varB);
                    var columns = 270;
                    var rows = 240;
                    var stride = 4 * columns;
                    try
                    {
                        var newbytes = PadLines(varB, rows, columns);


                 
                        var im = new Bitmap(columns, rows, stride,
                                                    PixelFormat.Format32bppRgb,
                                                    Marshal.UnsafeAddrOfPinnedArrayElement(newbytes, 0));
                        try
                        {
                            imageBox1.Image = im;
                        }catch(AccessViolationException e)
                        {
                            Console.WriteLine("test");
                            continue;
                        }

                        Thread.Sleep(60);

                    }catch(Exception e)
                    {
                        Console.WriteLine("tewt"+e.ToString());
                        //continue;
                        break;
                    }


                   // DateTime afterDT = System.DateTime.Now;
                   // TimeSpan ts = afterDT.Subtract(beforDT);
                   // Console.WriteLine("DateTime总共花费{0}ms.", ts.TotalMilliseconds);
                   


                }
                catch 
                {
                    Console.WriteLine("voliation s");
                    continue;
                }


            }
            


        }

        private void StopImage_Click(object sender, EventArgs e)
        {
            videoS = false;
        }
    }
}
