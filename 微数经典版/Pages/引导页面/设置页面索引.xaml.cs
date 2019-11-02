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
using 微数;
using Windows.Storage;
// “空白页”项模板在 http://go.microsoft.com/fwlink/?LinkId=234238 上有介绍

namespace 微数.Pages.引导页
{
    public class Settings
    {
        public SolidColorBrush background;
        public SolidColorBrush txt_foreground;
    }
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class 设置 : Page
    {
        Settings newS = new Settings { background=new SolidColorBrush(Windows.UI.Colors.LightGray),txt_foreground=new SolidColorBrush(Windows.UI.Colors.Black)};
        public static Windows.UI.Color Good;
        public 设置()
        {
            this.InitializeComponent();
          //  this.DataContext = newS;
            if (Data.localSettings.Values["BlackMode"].ToString() == "on")
            {
                NightTogSwitch.IsOn = true;
                newS.background = new SolidColorBrush(Windows.UI.Colors.Black);
                newS.txt_foreground = new SolidColorBrush(Windows.UI.Colors.LightGray);
            }
            this.DataContext = newS;
            if (Data.localSettings.Values["RealMode"].ToString() == "on")
            {
                根号TogSwitch.IsOn = true;
            }
        }

        private void About_Tapped(object sender, TappedRoutedEventArgs e)
        {
            Frame.Navigate(typeof(微数2.Pages.设置.关于));
        }

        private void Count_Tapped(object sender, TappedRoutedEventArgs e)
        {
            //Frame.Navigate(typeof(算法开源));
        }


        private void BackPage_Button_Click(object sender, RoutedEventArgs e)
        {
            if (Frame.CanGoBack)
            {
                Frame.GoBack();
            }
        }


        private void NightTogSwitch_Toggled(object sender, RoutedEventArgs e)
        {
            if (NightTogSwitch.IsOn)
            {
                Data.localSettings.Values["BlackMode"] = "on";
            }
            else
                Data.localSettings.Values["BlackMode"] = "off";
        }


        private void 根号TogSwitch_Toggled(object sender, RoutedEventArgs e)
        {
            if (根号TogSwitch.IsOn)
            {
                Data.localSettings.Values["RealMode"] = "on";
            }
            else
                Data.localSettings.Values["RealMode"] = "off";
        }
    }
}
