using System;
using System.Collections.Generic;
using System.Linq;
using Windows.UI.Xaml.Documents;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using System.Collections;
using System.Threading;
using Windows.UI.Xaml.Controls;
using Windows.UI.Popups;
using Windows.Storage;

namespace Micx.Class
{
    public class ResultData
    {
        public struct Pair
        {
            public Pair(string f, string s)
            {
                first = s;
                second = s;
            }

            public string first;
            public string second;
        }

        public void SetValue(string key, string value)
        {
            Pair p;
            p.first = key;
            p.second = value;
            ResultDataContainer.Add(p);
        }
        public List<Pair> ResultDataContainer = new List<Pair>();
        static public ResultData Histroy=new ResultData();
    }
}
