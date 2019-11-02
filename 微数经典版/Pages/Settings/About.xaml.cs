using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel.DataTransfer;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using System.Collections;
// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace Micx.Pages.Settings
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class About : Page
    {
        public About()
        {
            this.InitializeComponent();
        }
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (Frame.CanGoBack)
            {
                Frame.GoBack();
            }
        }

        private void TextBlock_Tapped(object sender, TappedRoutedEventArgs e)
        {
            DataPackage dp = new DataPackage();
            dp.SetText("215685374");
            Clipboard.SetContent(dp);
            ShowInformation();
        }

        private async void ShowInformation()
        {
            
            ContentDialog textDia = new ContentDialog()
            {
                Title = "复制成功",
                Content = "哈哈，QQ群号码已经复制到了您的剪切板上，还不赶快加入我们的大家族？",
                PrimaryButtonText = "来吧",
            };
            ContentDialogResult result = await textDia.ShowAsync();
        }
    }
}
