using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Core;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using 微数算法.Core;
using 微数;
// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace 微数2.Pages.基本.化简
{
    public class thisdata
    {
        public SolidColorBrush Mod { get; set; }
        public string name { get; set; }
        public SolidColorBrush forg { get; set; }
    }
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class 化简多项式 : Page
    {
        thisdata Head=new thisdata { forg= new SolidColorBrush(Windows.UI.Colors.Black),Mod = new SolidColorBrush(Windows.UI.Colors.White),name="化简表达式"};
        public 化简多项式()
        {
            this.InitializeComponent();
            if (Data.localSettings.Values["BlackMode"].ToString() == "on")
            {
                Head.Mod = new SolidColorBrush(Windows.UI.Colors.Black);
                Head.forg = new SolidColorBrush(Windows.UI.Colors.White);
            }
            this.DataContext = Head;
            SystemNavigationManager.GetForCurrentView().BackRequested += Back_Button_Click;
        }
        public string GetResult(List<RealNum> ListExp)
        {
            string ret = "";
            for (int i = ListExp.Count - 1; i >= 0; i--)
            {
                if (i == ListExp.Count - 1)
                {
                    if (ListExp[i].front == 1 && ListExp[i].times == 1)
                    {
                        ret += "x";
                    }
                    else if (ListExp[i].front == 1 && ListExp[i].times != 0)
                    {
                        ret += "x" + "^" + ListExp[i].times.ToString();
                    }
                    else if (ListExp[i].times == 0)
                    {
                        ret += ListExp[i].front.ToString();
                    }
                    else
                        ret += ListExp[i].front + "x" + "^" + ListExp[i].times.ToString();
                }
                else
                {
                    if (ListExp[i].front > 0)
                    {
                        if (ListExp[i].front == 1 && ListExp[i].times == 1)
                        {
                            ret += "+" + "x";
                        }
                        else if (ListExp[i].front == 1 && ListExp[i].times != 0)
                        {
                            ret += "+" + "x" + "^" + ListExp[i].times.ToString();
                        }
                        else if (ListExp[i].times == 0)
                        {
                            ret += "+" + ListExp[i].front.ToString();
                        }
                        else
                            ret += "+" + ListExp[i].front.ToString() + "x" + "^" + ListExp[i].times.ToString();
                    }
                    else
                    {
                        if (ListExp[i].front == 1 && ListExp[i].times == 1)
                        {
                            ret += "x";
                        }
                        else if (ListExp[i].front == 1 && ListExp[i].times != 0)
                        {
                            ret += "x" + "^" + ListExp[i].times.ToString();
                        }
                        else if (ListExp[i].times == 0)
                        {
                            ret += ListExp[i].front.ToString();
                        }
                        else
                            ret += ListExp[i].front.ToString() + "x" + "^" + ListExp[i].times.ToString();
                    }
                }
            }

            return ret;
        }
        private void Back_Button_Click(object sender, BackRequestedEventArgs e)
        {
            if (Frame.CanGoBack)
            {
                Frame.GoBack();
            }
            else
                return;
        }
        private void KeyBoardClick(object sender, RoutedEventArgs e)
        {
            Button xi = new Button();
            xi = (Button)sender;
            xi.Foreground = new SolidColorBrush(Windows.UI.Colors.Yellow);
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
            xi.Foreground = Head.forg;
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
        private void btn_Count_Click(object sender, RoutedEventArgs e)
        {
            txt_AnswerTextBlock.Text = "";
            ExpressionHandle hl = new ExpressionHandle();
            List<RealNum> ListExp = new List<RealNum>();
            BaseEquation eqtools = new BaseEquation();
            if(!eqtools.BalanceChecker(inputBox.Text))
            {
                showInformation("ERROR", "表达式括号不平衡");
                return;
            }
            ListExp = hl.MakeEasy(inputBox.Text);
            string result = GetResult(ListExp);
            txt_AnswerTextBlock.Text = result;
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

