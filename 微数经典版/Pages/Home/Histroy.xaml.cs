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

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace Micx.Pages.Home
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class Histroy : Page
    {
        public Histroy()
        {
            this.InitializeComponent();
            foreach (var a in Micx.Class.ResultData.Histroy.ResultDataContainer)
            {
                TextBlock txt_block1 = new TextBlock();
                txt_block1.Text = a.first;
                txt_block1.FontSize = 25;
                txt_block1.TextWrapping = TextWrapping.Wrap;
                txt_block1.FontWeight = Windows.UI.Text.FontWeights.ExtraBold;
                TextBlock txt_block2 = new TextBlock();
                txt_block2.Text = a.second;
                txt_block2.Foreground = new SolidColorBrush(Windows.UI.Colors.Red);
                txt_block2.FontSize = 20;
                txt_block2.TextWrapping = TextWrapping.Wrap;
                DataShow.Children.Add(txt_block1);
                DataShow.Children.Add(txt_block2);
            }
        }
    }
}
