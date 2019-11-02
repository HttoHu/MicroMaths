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
    public sealed partial class 高级索引页 : Page
    {
        public 高级索引页()
        {
            this.InitializeComponent();
            First_SizeChanged();
            if (Data.localSettings.Values["BlackMode"].ToString() == "on")
            {
                MainPane.Background = new SolidColorBrush(Windows.UI.Colors.Black);
            }
        }

        private void First_SizeChanged()
        {
            if (Window.Current.Bounds.Width > 481)
            {
                Grid.SetRow(解三角形, 0);
                Grid.SetColumn(解三角形, 1);
            }
        }

        private void Current_SizeChanged(object sender, Windows.UI.Core.WindowSizeChangedEventArgs e)
        {
            this.Width = e.Size.Width;
            this.Height = e.Size.Height;
            if (e.Size.Width > 481)
            {
                Grid.SetRow(解三角形, 0);
                Grid.SetColumn(解三角形, 1);
            }
        }

        private void 一元不等式_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(微数2.高级.不等式1));
        }

        private void 解三角形_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(微数2.Pages.高级.解三角.SolveTriangle));
        }
    }
}
