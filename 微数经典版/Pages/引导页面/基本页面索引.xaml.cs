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

// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace 微数.Pages.引导页
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class 基本页面索引: Page
    {
        public 基本页面索引()
        {
            this.InitializeComponent();
            Window.Current.SizeChanged += Current_SizeChanged; ;
            First_SizeChanged();

            if (Data.localSettings.Values["BlackMode"].ToString() == "on")
            {
                MainPane.Background = new SolidColorBrush(Windows.UI.Colors.Black);
            }
        }

        private void First_SizeChanged()
        {
            if (Window.Current.Bounds.Width < 550)
            {
                Grid.SetRow(简单多元方程, 0);
                Grid.SetColumn(简单多元方程, 1);
                Grid.SetRow(化简, 1);
                Grid.SetColumn(化简, 0);
            }
            else if (Window.Current.Bounds.Width > 550)
            {
                Grid.SetRow(简单多元方程, 0);
                Grid.SetColumn(简单多元方程, 1);
                Grid.SetRow(化简, 1);
                Grid.SetColumn(化简, 0);
            }
        }

        private void Current_SizeChanged(object sender, Windows.UI.Core.WindowSizeChangedEventArgs e)
        {
            this.Width = e.Size.Width;
            this.Height = e.Size.Height;
            if (e.Size.Width < 550)
            {
                Grid.SetRow(简单多元方程, 0);
                Grid.SetColumn(简单多元方程, 1);
                Grid.SetRow(化简, 1);
                Grid.SetColumn(化简, 0);
            }
            else if (e.Size.Width > 550)
            {
                Grid.SetRow(简单多元方程, 0);
                Grid.SetColumn(简单多元方程, 1);
                Grid.SetRow(化简, 1);
                Grid.SetColumn(化简, 0);
            }
        }

        private void 化简_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(微数2.Pages.基本.化简.化简多项式));
        }

        private void 简单多元方程_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(微数2.Pages.基本.简单二元方程));
        }
        private void 简单一元方程_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(微数2.Pages.基本.简单一元方程));
        }

    }
}