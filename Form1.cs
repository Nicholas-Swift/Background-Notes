using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Diagnostics;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            //Read from notes and add it to text box
            int counter = 0;
            string line;
            System.IO.StreamReader file = new System.IO.StreamReader("data/notes.txt");
            while ((line = file.ReadLine()) != null)
            {
                richTextBox1.AppendText(line);
                richTextBox1.AppendText("\n");
                counter++;
            }
            file.Close();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //when hits save button, save the text to the file!
            richTextBox1.SaveFile("data/notes.txt", RichTextBoxStreamType.PlainText);

            //and update background
            ProcessStartInfo start = new ProcessStartInfo();
            start.Arguments = null;
            start.FileName = "background.exe";
            int exitCode;

            using (Process proc = Process.Start(start))
            {
                proc.WaitForExit();
                exitCode = proc.ExitCode;
            }
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //when hits exit button, exit the application!
            Application.Exit();
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
