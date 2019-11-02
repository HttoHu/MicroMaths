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
    public sealed partial class Calculate : Page
    {
        public void KeyBoardTest()
        {
            if(Class.SettingContainer.GetValue("togswitch_hide_keyboard")=="off")
            {
                MMKeyBoard.Visibility = Visibility.Visible;
            }
            else
            {
                MMKeyBoard.Visibility = Visibility.Collapsed;
            }
        }
        public Calculate()
        {
            this.InitializeComponent();
            this.NavigationCacheMode = Windows.UI.Xaml.Navigation.NavigationCacheMode.Enabled;
        }
   

        private void KeyBoardClick(object sender, RoutedEventArgs e)
        {
            Button xi = new Button();
            xi = (Button)sender;
            inputBox.Text += xi.Content.ToString();
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
            txt_AnswerTextBlock.Text = GuassRT.Equation.Calculate(inputBox.Text);
            Micx.Class.ResultData.Histroy.SetValue(inputBox.Text+'\n', txt_AnswerTextBlock.Text+'\n');
        }

        private void btn_Clear_Click(object sender, RoutedEventArgs e)
        {
            inputBox.Text = "";
            txt_AnswerTextBlock.Text = "";
        }

        private void btn_Del_Click(object sender, RoutedEventArgs e)
        {
            if (inputBox.Text.Count() != 0)
            {
                inputBox.Text
                    = inputBox.Text.Substring(0, inputBox.Text.Count() - 1);
            }
        }

        private void Histroy_Click(object sender, RoutedEventArgs e)
        {
            Frame.Navigate(typeof(Pages.Home.Histroy));
        }
    }
}

