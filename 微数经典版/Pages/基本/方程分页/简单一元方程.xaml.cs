using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using AlgorithmRT;
using 微数.Pages;
using 微数算法.Core;
using 微数;
using 微数算法;
// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace 微数2.Pages.基本
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    ///  
    public class thisdata
    {
        public SolidColorBrush Mod { get; set; }
        public string name { get; set; }
        public SolidColorBrush forg { get; set; }
    }
    public sealed partial class 简单一元方程 : Page
    {
        thisdata Head = new thisdata { forg = new SolidColorBrush(Windows.UI.Colors.Black), Mod = new SolidColorBrush(Windows.UI.Colors.White), name = "简单方程" };
        public 简单一元方程()
        {
            this.InitializeComponent();
            if (Data.localSettings.Values["BlackMode"].ToString() == "on")
            {
                Head.Mod = new SolidColorBrush(Windows.UI.Colors.Black);
                Head.forg = new SolidColorBrush(Windows.UI.Colors.White);
            }
            this.DataContext = Head;
        }
        private void ShowAnswerPage()
        {
            List<RealNum> exp = new List<RealNum>();
            BaseEquation equ = new BaseEquation();
            exp = equ.MakeEasyH1(inputBox.Text);
            exp = equ.MakeEasyM1(exp);
            exp = equ.MakeEasyM2(exp);
            int a = (int)EquationTools.GetFrontByTimes(exp, 2);
            int b = (int)EquationTools.GetFrontByTimes(exp, 1);
            int c = (int)EquationTools.GetFrontByTimes(exp, 0);
            int XDown = 2 * (int)a;
            if (b * b - 4 * a * c < 0)
            {
                showInformation("Error", "b*b-4*a*c<0");
                return;
            }
            //¡Ì
            string answer = new Trans().GetX(a, b, c);
            answer=answer.Replace("¡Ì", "√");
            txt_AnswerTextBlock.Text = answer;
            /*     fraction fa = new fraction(a);
            fraction fb = new fraction(b);
            fraction fc = new fraction(c);
            fraction diat = new fraction(b * b - 4 * a * c);
            diat.numsqrt();
            fraction x1 = (-fb + diat) / (new fraction("2") * fa);
            fraction x2 = (-fb - diat) / (new fraction("2") * fa);
            txt_AnswerTextBlock.Text = "x1:" + x1.ToString() + "\n";
            txt_AnswerTextBlock.Text += "x2:" + x2.ToString();*/
        }
        private void KeyBoardClick(object sender, RoutedEventArgs e)
        {
            Button xi = new Button();
            xi = (Button)sender;
            switch (xi.Content.ToString())
            {
                case "*": inputBox.Text += "*"; break;
                case "^": inputBox.Text += "^"; break;
                case "x": inputBox.Text += "x"; break;
                case "+": inputBox.Text += "+"; break;
                case "-": inputBox.Text += "-"; break;
                case "=": inputBox.Text += "="; break;
                case "(": inputBox.Text += "("; break;
                case ")": inputBox.Text += ")"; break;
                case "0": inputBox.Text += "0"; break;
                case "1": inputBox.Text += "1"; break;
                case "2": inputBox.Text += "2"; break;
                case "3": inputBox.Text += "3"; break;
                case "4": inputBox.Text += "4"; break;
                case "5": inputBox.Text += "5"; break;
                case "6": inputBox.Text += "6"; break;
                case "7": inputBox.Text += "7"; break;
                case "8": inputBox.Text += "8"; break;
                case "9": inputBox.Text += "9"; break;
                case "＜": inputBox.Text += "<"; break;
                case "＞": inputBox.Text += ">"; break;
            }
        }
        public static async void showInformation(string title, string row)
        {
            ContentDialog textDia = new ContentDialog()
            {
                Title = title,
                Content = row,
                PrimaryButtonText = "Ok",
            };
            ContentDialogResult result = await textDia.ShowAsync();
        }
        public string CutString_front(string exp)
        {
            int index = 0;
            bool haveChar = false; ;
            foreach (var ch in exp)
            {
                if (ch == '<' || ch == '>')
                {
                    haveChar = true; ;
                    break;
                }
                index++;
            }
            if (haveChar == false)
            {
                showInformation("Bad Exp", "检查输入");
                return "";
            }
            return exp.Substring(0, index);
        }
        public string CutString_back(string exp)
        {
            int index = 0;
            bool haveChar = false; ;
            foreach (var ch in exp)
            {
                if (ch == '<' || ch == '>' || ch == '=')
                {
                    haveChar = true;
                    index++;
                    break;
                }
                index++;
            }
            if (exp[index] == '=')
            {
                showInformation("E", exp[index].ToString());
                index++;
            }
            if (haveChar == false)
            {
                showInformation("Bad Exp", "检查输入");
                return "";
            }
            return exp.Substring(index);
        }
        private void btn_Count_Click(object sender, RoutedEventArgs e)
        {
            txt_AnswerTextBlock.Text = "";
            BaseEquation equ = new BaseEquation();
            if (!equ.Checker(inputBox.Text))
            {
                return;
            }
            if (inputBox.Text.Length == 0)
            {
                return;
            }
            List<RealNum> Exp = new List<RealNum>(equ.MakeEasyH1(inputBox.Text));
            if (Exp[Exp.Count - 1].times == 2 && Data.localSettings.Values["RealMode"].ToString() == "on")
            {
                ShowAnswerPage();
                return;
            }
            List<float> xValue = new List<float>();
            xValue = equ.Getxvalue(inputBox.Text);
            for (int i = 0; i < xValue.Count; i++)
            {
                txt_AnswerTextBlock.Text += " x" + i + "=" + xValue[i] + " ";
            }
        }
        private void btn_Clear_Click(object sender, RoutedEventArgs e)
        {
            inputBox.Text = "";
        }
        private void btn_Del_Click(object sender, RoutedEventArgs e)
        {
            if (inputBox.Text == "")
            {
                showInformation("ERROR", "数据为空");
                return;
            }
            inputBox.Text = inputBox.Text.Substring(0, inputBox.Text.Length - 1);
        }
    }
}
