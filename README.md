# Background-Notes
Notes directly on your desktop background! A work in progress. A program requested by a friend.

# The Code
Form1.cs is a simple C# form that I quickly wrote up to provide an interface to type in without having it be a command prompt program. There isn't much to it.

====================================================================

First we initialize the text box to have the correct information in it at startup. We read the current notes.txt and append that to the richTextBox.
```
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
```

====================================================================

Other than that, the user just can type away in the notes section. When saving, this code is run. We simply save all the new text to the notes.txt and then run background.exe (the c++ code!).

```
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
```

====================================================================
