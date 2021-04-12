using KGLCtrlApp.entity;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.Xml.Serialization;

namespace KGLCtrlApp.utils
{
    public class ConfigWorkSpaceUtils
    {
        public WorkSpace LoadWorkSpaceFromFile(string fileName)
        {
            WorkSpace willUseWorkSpace = null;
            XmlSerializer formatter = new XmlSerializer(typeof(WorkSpace));
            
            using(FileStream stream = new FileStream(fileName, FileMode.Open))
            {
                willUseWorkSpace = formatter.Deserialize(stream) as WorkSpace;
            }

            return willUseWorkSpace;
        }

        public bool SaveWorkSpaceFile(WorkSpace workSpace, string fileName)
        {
            try
            {
                XmlSerializer formatter = new XmlSerializer(typeof(WorkSpace));
                using (FileStream stream = new FileStream(fileName, FileMode.OpenOrCreate))
                {
                    formatter.Serialize(stream, workSpace);
                }

                return true;
            }
            catch (Exception)
            {

                return false;
            }

        }


    }
}
