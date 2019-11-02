using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows;
using Windows.UI;
using Windows.ApplicationModel;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.ViewManagement;
using Windows.Foundation.Metadata;
using Windows.Storage;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

namespace Micx
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        SolidColorBrush accentColor = (SolidColorBrush)Application.Current.Resources["SystemControlBackgroundAccentBrush"];
        SolidColorBrush pointerOver = (SolidColorBrush)Application.Current.Resources["ButtonBackgroundPressed"];
        public MainPage()
        {
            this.InitializeComponent();
            ShowStatusBar();
        }
        private async void ShowStatusBar()
        {
            if (ApiInformation.IsTypePresent("Windows.UI.ViewManagement.StatusBar"))
            {
                var statusbar = StatusBar.GetForCurrentView();
                await statusbar.ShowAsync();
                statusbar.BackgroundColor = accentColor.Color;
                statusbar.BackgroundOpacity = 1;
                statusbar.ForegroundColor = Windows.UI.Colors.White;
            }
        }
        private void btn_BootBasePages_Click(object sender, RoutedEventArgs e)
        {
            //方程按钮.Background = new SolidColorBrush(Windows.UI.Color.FromArgb(255, 255, 255, 0));
            btn_BootSettingPages.Background = accentColor;
            btn_BootSeniorPages.Background = accentColor;
            btn_BootBasePages.Background = pointerOver;
            MyFrame.Navigate(typeof(Pages.Home.Home));
        }

        private void btn_BootSeniorPages_Click(object sender, RoutedEventArgs e)
        {
            btn_BootSettingPages.Background = accentColor;
            btn_BootBasePages.Background = accentColor;
            btn_BootSeniorPages.Background = pointerOver;
            MyFrame.Navigate(typeof(Pages.Advance.Changelog));
        }

        private void btn_BootSettingPages_Click(object sender, RoutedEventArgs e)
        {
            btn_BootSettingPages.Background = pointerOver;
            btn_BootBasePages.Background = accentColor;
            btn_BootSeniorPages.Background = accentColor;
             MyFrame.Navigate(typeof(Pages.Settings.About));
        }

        private async void ShowInformation(string title, string row)
        {
            ContentDialog textDia = new ContentDialog()
            {
                Title = title,
                Content = row,
                PrimaryButtonText = "Ok",
            };
            ContentDialogResult result = await textDia.ShowAsync();
        }
    }
}
