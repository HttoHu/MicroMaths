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

namespace Micx.Pages.Settings
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class Settings : Page
    {
        void process()
        {
            string x = Micx.Class.SettingContainer.GetValue("togswitch_hide_keyboard");
            if (x == "on")
            {
                togswitch_hide_keyboard.IsOn = true;
            }
            else if (x == "off")
            {
                togswitch_hide_keyboard.IsOn = false;
            }
            else
            {
                Micx.Class.SettingContainer.Add("togswitch_hide_keyboard", "off");
            }
        }
        public Settings()
        {
            this.InitializeComponent();
            process();
        }

        private void btn_about_click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(About));
        }

        private void togswitch_hide_keyboard_Toggled(object sender, RoutedEventArgs e)
        {
            if(togswitch_hide_keyboard.IsOn)
            {
                Micx.Class.SettingContainer.Add("togswitch_hide_keyboard", "on");
            }
            else
            {
                Micx.Class.SettingContainer.Add("togswitch_hide_keyboard", "off");
            }
        }
    }
}
