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
using Windows.Storage;
using Windows.UI.Xaml.Navigation;
namespace Micx.Class
{
    public class SettingContainer
    {
        static SettingContainer()
        {
            settings = ApplicationData.Current.LocalSettings;
        }
        public static void Add(string key, string value)
        {
            settings.Values[key] = value;
        }
        public static void Remove(string key)
        {
            settings.Values.Remove(key);
        }
        public static string GetValue(string key)
        {
            return (string)settings.Values[key];
        }

        static bool isLoad = false;
        private static ApplicationDataContainer settings;
    }
}
