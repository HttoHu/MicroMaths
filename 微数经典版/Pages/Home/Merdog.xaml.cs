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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace 微数经典版.Pages.Home
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class Merdog : Page
    {
        public Merdog()
        {
            this.InitializeComponent();
            this.NavigationCacheMode = Windows.UI.Xaml.Navigation.NavigationCacheMode.Enabled;
        }
        private void SetLineNo(string str)
        {
            int count = 0;
            LineNo.Text = "1";
            foreach (var t in str)
            {
                if (t == '\n'||t=='\r')
                {
                    count++;
                }
            }
            for (int i=2; i<=count+1;i++)
            {
                LineNo.Text += "\n" + i.ToString();
            }
        }
        private Windows.Storage.StorageFile current_file;
        private async void Open_Click(object sender, RoutedEventArgs e)
        {
            var picker = new Windows.Storage.Pickers.FileOpenPicker();
            picker.ViewMode = Windows.Storage.Pickers.PickerViewMode.Thumbnail;
            picker.SuggestedStartLocation = Windows.Storage.Pickers.PickerLocationId.PicturesLibrary;
            picker.FileTypeFilter.Add(".txt");
            picker.FileTypeFilter.Add(".mer");
            picker.FileTypeFilter.Add(".cc");
            picker.FileTypeFilter.Add(".cpp");
            picker.FileTypeFilter.Add(".c");
            current_file = await picker.PickSingleFileAsync();
            if (current_file != null)
            {
                this.Editor.Text = await Windows.Storage.FileIO.ReadTextAsync(current_file);
                SetLineNo(Editor.Text);
            }
            else
            {
                Htto.Tools.showInformation("Error", "open filed failed");
            }
            if (current_file != null)
            {
                SFileName.Text = current_file.Name;
            }
        }

        private void Run_Click(object sender, RoutedEventArgs e)
        {
            string tmp = "";
            tmp = GuassRT.Equation.Merdog(Editor.Text);
            Htto.Tools.showInformation("output", tmp);
        }

        private async void Save_Click(object sender, RoutedEventArgs e)
        {
            if (current_file != null)
            {
                await Windows.Storage.FileIO.WriteTextAsync(current_file, Editor.Text);
                Htto.Tools.showInformation(current_file.Name, "保存成功");
            }
            else if (current_file == null)
            {
                var savePicker = new Windows.Storage.Pickers.FileSavePicker();
                savePicker.SuggestedStartLocation =
                    Windows.Storage.Pickers.PickerLocationId.DocumentsLibrary;
                // Dropdown of file types the user can save the file as
                savePicker.FileTypeChoices.Add("merdog program", new List<string>() { ".mer" });
                // Default file name if the user does not type one in or select a file to replace
                savePicker.SuggestedFileName = "new";

                current_file = await savePicker.PickSaveFileAsync();
                if (current_file != null)
                {
                    // Prevent updates to the remote version of the file until
                    // we finish making changes and call CompleteUpdatesAsync.
                    Windows.Storage.CachedFileManager.DeferUpdates(current_file);
                    // write to file
                    await Windows.Storage.FileIO.WriteTextAsync(current_file, Editor.Text);
                    // Let Windows know that we're finished changing the file so
                    // the other app can update the remote version of the file.
                    // Completing updates may require Windows to ask for user input.
                    Windows.Storage.Provider.FileUpdateStatus status =
                        await Windows.Storage.CachedFileManager.CompleteUpdatesAsync(current_file);
                    if (status == Windows.Storage.Provider.FileUpdateStatus.Complete)
                    {
                        Htto.Tools.showInformation(current_file.Name, "保存文件成功");
                    }
                    else
                    {
                        Htto.Tools.showInformation(current_file.Name, "保存文件失败");
                    }
                }
                else
                {
                    Htto.Tools.showInformation("信息", "保存文件取消");
                }
            }
            if (current_file != null)
            {
                SFileName.Text = current_file.Name;
            }
        }

        private async void SaveAs_Click(object sender, RoutedEventArgs e)
        {
            var savePicker = new Windows.Storage.Pickers.FileSavePicker();
            savePicker.SuggestedStartLocation =
                Windows.Storage.Pickers.PickerLocationId.DocumentsLibrary;
            // Dropdown of file types the user can save the file as
            savePicker.FileTypeChoices.Add("merdog program", new List<string>() { ".mer" });
            // Default file name if the user does not type one in or select a file to replace
            savePicker.SuggestedFileName = "new";

            current_file = await savePicker.PickSaveFileAsync();
            if (current_file != null)
            {
                // Prevent updates to the remote version of the file until
                // we finish making changes and call CompleteUpdatesAsync.
                Windows.Storage.CachedFileManager.DeferUpdates(current_file);
                // write to file
                await Windows.Storage.FileIO.WriteTextAsync(current_file, Editor.Text);
                // Let Windows know that we're finished changing the file so
                // the other app can update the remote version of the file.
                // Completing updates may require Windows to ask for user input.
                Windows.Storage.Provider.FileUpdateStatus status =
                    await Windows.Storage.CachedFileManager.CompleteUpdatesAsync(current_file);
                if (status == Windows.Storage.Provider.FileUpdateStatus.Complete)
                {
                    Htto.Tools.showInformation(current_file.Name, "保存文件成功");
                }
                else
                {
                    Htto.Tools.showInformation(current_file.Name, "保存文件失败");
                }
            }
            else
            {
                Htto.Tools.showInformation("信息", "保存文件取消");
            }
            if (current_file != null)
            {
                SFileName.Text = current_file.Name;
            }
        }

        private async void Reference_Click(object sender, RoutedEventArgs e)
        {
            Windows.Storage.StorageFolder storageFolder =
            Windows.Storage.ApplicationData.Current.LocalFolder;
            Windows.Storage.StorageFile sampleFile= await Windows.Storage.StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///Resources/merdog_grammar.txt"));
            this.Editor.Text = await Windows.Storage.FileIO.ReadTextAsync(sampleFile);
            SetLineNo(Editor.Text);
            SFileName.Text = "参考手册";
        }

        private void Editor_KeyDown(object sender, KeyRoutedEventArgs e)
        {
            
        }

        private void Refresh_Click(object sender, RoutedEventArgs e)
        {
            SetLineNo(Editor.Text);
        }
    }

}
