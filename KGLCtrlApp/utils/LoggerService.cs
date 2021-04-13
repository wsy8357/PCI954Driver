using NLog;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace KGLCtrlApp.utils
{
    public static class LoggerService
    {
        public static Logger logger = null;

        public static void IniterLogService()
        {
            if (logger == null)
            {
                logger = LogManager.GetCurrentClassLogger();
            }
        }
    }
}
