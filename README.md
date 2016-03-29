# Background-Notes
Notes directly on your desktop background! A work in progress. A program requested by a friend.

# The Code
Form1.cs is a simple C# form that I quickly wrote up to provide an interface to type in without having it be a command prompt program. There isn't much to it.

First we initialize the text box to have the correct information in it at startup.
<code> public Form1()
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
        } </code>
