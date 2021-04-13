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
        public int Id { get; set; }
        public string Name { get; set; }
        public bool Enable { get; set; }
    }
}
