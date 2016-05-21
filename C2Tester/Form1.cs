using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace C2Tester
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private List<Point> _points = new List<Point>(); 

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            RenderOnPanel(e.X, e.Y);
        }

        private void buttonReset_Click(object sender, EventArgs e)
        {
            ClearPanel();
        }

        private void ClearPanel()
        {
            _points.Clear();
            using (var g = panel1.CreateGraphics())
            {
                g.Clear(Color.White);
            }
        }

        private void buttonSave_Click(object sender, EventArgs e)
        {
            File.WriteAllLines("points.txt", _points.Select(p=> $"{{{p.X},{p.Y}}}"));
        }

        private void buttonLoad_Click(object sender, EventArgs e)
        {
            ClearPanel();
            var lines = File.ReadAllLines("points.txt");
            var points = lines
                .Select(l =>
                {
                    var split = l.Split(new char[] {'{', '}', ','}, StringSplitOptions.RemoveEmptyEntries);
                    return new Point(int.Parse(split[0]), int.Parse(split[1]));
                });

            foreach (Point p in points)
            {
                RenderOnPanel(p.X, p.Y);
            }
        }

        private void RenderOnPanel(int x, int y)
        {
            using (var g = panel1.CreateGraphics())
            {
                var pen = new Pen(Color.Blue, 1);
                g.DrawRectangle(pen, x, y, 2, 2);
                _points.Add(new Point(x, y ));
            }
        }

        void FillPoint(Point p)
        {
            using (var g = panel1.CreateGraphics())
            {
                g.FillRectangle(new SolidBrush(Color.Red), p.X, p.Y, 2, 2 );
            }
        }

        void DrawLine(Point p1, Point p2)
        {
            using (var g = panel1.CreateGraphics())
            {
                g.DrawLine(new Pen(Color.Red, 1), p1, p2);
            }
        }

        private void buttonTest_Click(object sender, EventArgs e)
        {
            var p1 = new Point(int.Parse(textP1x.Text), int.Parse(textP1y.Text));
            var p2 = new Point(int.Parse(textP2x.Text), int.Parse(textP2y.Text));

            FillPoint(p1);
            FillPoint(p2);

            DrawLine(p1, p2);
        }
    }
}
