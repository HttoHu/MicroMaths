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
using 微数算法.Core;
using 微数;
//“空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409 上有介绍
namespace 微数2.高级
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
    public sealed partial class 不等式1 : Page
    {
        thisdata Head = new thisdata { forg = new SolidColorBrush(Windows.UI.Colors.Black), Mod = new SolidColorBrush(Windows.UI.Colors.White), name = "不等式" };
        public 不等式1()
        {
            this.InitializeComponent();
            if(Data.localSettings.Values["BlackMode"].ToString() == "on")
            {
                Head.Mod = new SolidColorBrush(Windows.UI.Colors.Black);
                Head.forg = new SolidColorBrush(Windows.UI.Colors.White);
            }
            this.DataContext = Head;
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
        public static async void showInformation(string title = "Message", string row = "NONE")
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
                index++;
            }
            if (haveChar == false)
            {
                showInformation("Bad Exp", "检查输入");
                return "";
            }
            return exp.Substring(index);
        }
        public string GetOPPChar(string op)
        {
            switch (op)
            {
                case "<": return ">";
                case ">": return "<";
                case "<=": return ">=";
                case ">=": return "<=";
                default: return "EROR";
            }
        }
        public string ExchangeOp(object op1, object op2)
        {

            return "SUCCED";
        }
        public string WorkOut(string exp)
        {
            List<float> ret = new List<float>();
            BaseEquation et = new BaseEquation();
            string frontPart = CutString_front(exp);
            string backPart = CutString_back(exp);
            string IChar = GetOPC(exp);
            string oppChar;
            oppChar = GetOPPChar(IChar);
            if (oppChar == "ERROR")
            {
                showInformation("ERROR", "不支持此类不等式");
                return oppChar;
            }
            List<RealNum> frontList = et.MakeEasy(frontPart);
            List<RealNum> lastList = et.MakeEasy(backPart);
            List<RealNum> endList;
            endList = et.EquationExpHandle(frontList, lastList);
            int MaxTimes = et.MaxTimes(endList);
            if (MaxTimes == 1)
            {
                if (endList[1].front == 0)
                {
                    ret.Add(0);
                    return "NO FOUND";
                }
                ret.Add(-endList[0].front / endList[1].front);
                if (endList[endList.Count - 1].front < 0)
                {
                    return "x" + oppChar + ret[0].ToString();
                }
                else
                    return "x" + IChar + ret[0].ToString();
            }
            else if (MaxTimes > 2 || MaxTimes < 1)
            {
                showInformation("抱歉", "由于能力问题。我们只设计了二次不等式和一次不等式.");
            }
            else if (MaxTimes == 2)
            {
                bool haveEq = false;
                float[] frontNumContainer = new float[3];
                #region 预处理
                if (IChar[IChar.Length - 1] == '=')
                    haveEq = true;
                for (int i = 0; i < 3; i++)
                {
                    frontNumContainer[i] = 0;
                }
                foreach (var ele in endList)
                {
                    frontNumContainer[ele.times] = ele.front;
                }
                float x1, x2;
                float a, b, c;
                a = frontNumContainer[2];
                b = frontNumContainer[1];
                c = frontNumContainer[0];
                float Diat = (float)Math.Sqrt(b * b - 4 * a * c);
                x1 = ((-b) + Diat) / (2 * a);
                x2 = ((-b) - Diat) / (2 * a);
                if (a < 0)
                {
                    string op3 = IChar;
                    IChar = oppChar;
                    oppChar = op3;
                    a = -a;
                    b = -b;
                    c = -c;
                }

                if (x1 > x2)
                {
                    float x = x1;
                    x1 = x2;
                    x2 = x;
                }
                #endregion
                if ((b * b - 4 * a * c) < 0)
                {
                    return "x∈∅";
                }
                else if ((b * b - 4 * a * c) == 0)
                {
                    if (IChar == ">" || IChar == ">=")
                        return "x≠" + (-(b) / 2 * a).ToString();
                    else
                        return "x∈∅";
                }
                else
                {
                    string BOp;
                    string SOp;
                    string Lk;
                    string Rk;
                    if (haveEq)
                    {
                        BOp = ">=";
                        SOp = "<=";
                        Lk = "[";
                        Rk = "]";
                    }
                    else
                    {
                        BOp = "＞";
                        SOp = "＜";
                        Lk = "(";
                        Rk = ")";
                    }

                    if (IChar == ">" || IChar == ">=")
                        return string.Format("{{x {0} {1} or x {2} {3}}}", SOp, x1.ToString(), BOp, x2.ToString());
                    if (IChar == "<" || IChar == "<=")
                        return string.Format("x∈{0} {1},{2} {3}", Lk, x1.ToString(), x2.ToString(), Rk);
                }
            }
            else
            {
                showInformation("抱歉", "由于能力问题。我们只设计了二次不等式和一次不等式.");
            }
            return "";
        }
        public string GetOPC(string exp)
        {
            string ret;
            int STindex = 0;
            int index = 0;
            bool haveChar = false; ;
            foreach (var ch in exp)
            {
                if (ch == '<' || ch == '>' || ch == '=')
                {
                    haveChar = true;
                    STindex++;
                    index++;
                    break;
                }
                STindex++;
                index++;
            }
            if (exp[index] == '=')
            {
                index++;
            }
            if (haveChar == false)
            {
                showInformation("Bad Exp", "检查输入");
                return "";
            }
            ret = exp.Substring(STindex - 1, index - STindex + 1);
            return ret;
        }
        private void btn_Count_Click(object sender, RoutedEventArgs e)
        {
            txt_AnswerTextBlock.Text = WorkOut(inputBox.Text);
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
