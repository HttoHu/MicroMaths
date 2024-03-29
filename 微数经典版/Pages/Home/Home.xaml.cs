﻿using System;
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

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace Micx.Pages.Home
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class Home : Page
    {
        public Home()
        {
            this.InitializeComponent();
        }

        private void 简单一元方程_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Pages.Home.OneDollarEquation));
        }

        private void n元1次方程_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Pages.Home.LinnnerEquation));
        }

        private void 计算器_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Calculate));
        }
        private void Program_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(微数经典版.Pages.Home.Merdog));
        }
    }
}
