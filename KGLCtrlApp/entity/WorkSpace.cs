using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KGLCtrlApp.entity
{
    [Serializable]
    public class WorkSpace
    {
        public string Device { set; get; }
        public string SpaceName { set; get; }

        public List<Channel> Channels { get; set; }
    }

    [Serializable]
    public class Channel
    {
        int Id { get; set; }
        string Name { get; set; }
        bool Enable { get; set; }
    }
}
