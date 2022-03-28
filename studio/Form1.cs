using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TextEditor
{
    public partial class Form1 : Form
    {

        string filePath = null;

        public Form1()
        {
            InitializeComponent();

            //расширения открываемых файлов
            saveFileDialog1.Filter = "RTF Files|*.rtf|Text File(*.txt)|*.txt|All Files|*.*";
        }

        private void сохранитьКакToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.Cancel)
                return;

            string fileName = saveFileDialog1.FileName;
            File.WriteAllText(fileName, richTextBox1.Text);
            MessageBox.Show("Сохранение прошло успешно");
        }

        private void открытьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.Cancel)
                return;

            string fileName = openFileDialog1.FileName;
            filePath = fileName;

            //try
            //{
            //    richTextBox1.LoadFile(fileName, RichTextBoxStreamType.RichText);
            //}
            //catch (ArgumentException ex)
            //{
            //    richTextBox1.LoadFile(fileName, RichTextBoxStreamType.PlainText);
            //}

            this.Text = fileName;
            
            string fileText = File.ReadAllText(fileName);
            richTextBox1.Text = fileText;
        }

        private void новыйФайлToolStripMenuItem_Click(object sender, EventArgs e)
        {
           DialogResult dialogResult =  MessageBox.Show(
                "Сохранять текущий файл?",
                "Сообщение",
                MessageBoxButtons.YesNoCancel,
                MessageBoxIcon.Information,
                MessageBoxDefaultButton.Button1,
                MessageBoxOptions.DefaultDesktopOnly);

            if (dialogResult == DialogResult.Cancel)
            {
                return;
            }
            else if (dialogResult == DialogResult.Yes)
            {
                if (saveFileDialog1.ShowDialog() == DialogResult.Cancel)
                    return;

                string fileName = saveFileDialog1.FileName;
                filePath = fileName;
                File.WriteAllText(fileName, richTextBox1.Text);
                richTextBox1.Text = "";
                this.Text = "Calc";
                MessageBox.Show("Сохранение прошло успешно");
            }
            else
            {
                richTextBox1.Text = "";
                this.Text = "Calc";
            }
                
        }

        private void сохранитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == null)
            {
                if (saveFileDialog1.ShowDialog() == DialogResult.Cancel)
                    return;

                string fileName = saveFileDialog1.FileName;
                File.WriteAllText(fileName, richTextBox1.Text);
                MessageBox.Show("Сохранение прошло успешно");
                this.Text = fileName;
            }
            else
                File.WriteAllText(filePath, richTextBox1.Text);
        }

        private void выходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void richTextBox1_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Control && e.KeyCode == Keys.V)
            {
                if (Clipboard.ContainsText())
                    richTextBox1.Paste(DataFormats.GetFormat(DataFormats.Text));
                e.Handled = true;
            }
        }

        private void отменитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.Undo();
        }

        private void настройкаШрифтаToolStripMenuItem_Click(object sender, EventArgs e)
        {
            fontDialog1.ShowDialog();
            richTextBox1.Font = fontDialog1.Font;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void запускПрограммыToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Process myProcess = new Process();
            myProcess.StartInfo.FileName = @"C:\Application.exe";
            myProcess.Start();
        }
    }
}
