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
using 微数;
// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace 微数2.Pages.基本
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class 简单二元方程 : Page
    {
        public 简单二元方程()
        {
            this.InitializeComponent();
            SystemNavigationManager.GetForCurrentView().BackRequested += Back_Button_Click;
            if (Data.localSettings.Values["BlackMode"].ToString() == "on")
            {
                MainPane.Background = new SolidColorBrush(Windows.UI.Color.FromArgb(1, 169, 169, 169));
            }
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
        public bool IsNumber(char ch)
        {
            if (ch >= 48 && ch <= 57)
                return true;
            else
                return false;
        }
        public float StrTofloat(string s)
        {
            for (int i = 0; i < s.Length; i++)
            {
                if (s[i] != '.' && !IsNumber(s[i]))
                {
                    ErrorTextBlock.Text = "Enter a number!";
                    return 0.0f;
                }
            }
            return float.Parse(s);
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            ErrorTextBlock.Text = "";
            float Rx, Ry;//x,y 的结果
            if (string.IsNullOrEmpty(ia.Text) || string.IsNullOrEmpty(ib.Text) || string.IsNullOrEmpty(ic.Text) ||
                string.IsNullOrEmpty(id.Text) || string.IsNullOrEmpty(ie.Text) || string.IsNullOrEmpty(iff.Text))
            {
                ErrorTextBlock.Text = "输入系数!";
                return;
            }
            float aa, ba, ca, da, ea, fa;
            aa = StrTofloat(ia.Text);
            ba = StrTofloat(ib.Text);
            ca = StrTofloat(ic.Text);
            da = StrTofloat(id.Text);
            ea = StrTofloat(ie.Text);
            fa = StrTofloat(iff.Text);
            if (ErrorTextBlock.Text == "Enter a number!")
            {
                return;
            }
            Rx = (ca * ea - ba * fa) / (aa * ea - ba * da);
            Ry = (aa * fa - ca * da) / (aa * ea - ba * da);
            ResultTextBlock.Text = "x=" + Rx + "  y=" + Ry;
        }
        private void IButton_Click(object sender, RoutedEventArgs e)
        {
        }
        private void ClearButton_Click(object sender, RoutedEventArgs e)
        {
            ia.Text = "";
            ib.Text = "";
            ic.Text = "";
            id.Text = "";
            ie.Text = "";
            iff.Text = "";
        }
    }
}
