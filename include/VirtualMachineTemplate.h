/* -------------------------------------------------------------------------- */
/* Copyright 2002-2018, OpenNebula Project, OpenNebula Systems                */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License"); you may    */
/* not use this file except in compliance with the License. You may obtain    */
/* a copy of the License at                                                   */
/*                                                                            */
/* http://www.apache.org/licenses/LICENSE-2.0                                 */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/* -------------------------------------------------------------------------- */

#ifndef VIRTUAL_MACHINE_TEMPLATE_H_
#define VIRTUAL_MACHINE_TEMPLATE_H_

#include "Template.h"

#include <string.h>

using namespace std;

/**
 *  Virtual Machine Template class, it represents a VM configuration file.
 */
class VirtualMachineTemplate : public Template
{
public:
    VirtualMachineTemplate():Template(false,'=',"TEMPLATE"){};

    VirtualMachineTemplate(
            bool _replace_mode,
            const char   _separator,
            const char * _xml_root):
        Template(_replace_mode, _separator, _xml_root){};

    ~VirtualMachineTemplate(){};

    VirtualMachineTemplate(VirtualMachineTemplate& vmt):Template(vmt){};

    void set_xml_root(const char * _xml_root)
    {
        Template::set_xml_root(_xml_root);
    };

    /**
     * Replaces the given image from the DISK attribute with a new one
     *   @param target_id IMAGE_ID the image to be replaced
     *   @param target_name IMAGE the image to be replaced
     *   @param target_uname IMAGE_UNAME the image to be replaced
     *   @param new_name of the new image
     *   @param new_uname of the owner of the new image
     */
    int replace_disk_image(int target_id, const string&
        target_name, const string& target_uname, const string& new_name,
        const string& new_uname);

    // -------------------------------------------------------------------------
    // Restricted attributes interface implementation
    // -------------------------------------------------------------------------
    virtual bool check_restricted(string& rs_attr, const Template* base)
    {
        return Template::check_restricted(rs_attr, base, restricted);
    }

    virtual bool check_restricted(string& rs_attr)
    {
        return Template::check_restricted(rs_attr, restricted);
    }

    static void parse_restricted(vector<const SingleAttribute *>& ra)
    {
        Template::parse_restricted(ra, restricted);
    }

    string& to_xml_short(string& xml) const
    {
        ostringstream oss;
        string labels;
        string schd_rank, rank,schd_ds_rank;
        string public_cloud, ec2;
        string schd_req, schd_ds_req, schd_messg;

        if (attributes.empty())
        {
            oss << "<USER_TEMPLATE/>";
        }
        else
        {
             oss << "<USER_TEMPLATE>";

            if (get("LABELS", labels))
            {
                oss << "<LABELS>" << labels << "</LABELS>";
            }
            if (get("SCHED_RANK", schd_rank))
            {
                oss << "<SCHED_RANK>" << schd_rank << "</SCHED_RANK>";
            }
            if (get("RANK", rank))
            {
                oss << "<RANK>" << rank << "</RANK>";
            }
            if (get("SCHED_DS_RANK", schd_ds_rank))
            {
                oss << "<SCHED_DS_RANK>" << schd_ds_rank << "</SCHED_DS_RANK>";
            }
            if (get("PUBLIC_CLOUD", public_cloud))
            {
                oss << "<PUBLIC_CLOUD>" << public_cloud << "</PUBLIC_CLOUD>";
            }
            if (get("EC2", ec2))
            {
                oss << "<EC2>" << ec2 << "</EC2>";
            }
            if (get("SCHED_REQUIREMENTS", schd_req))
            {
                oss << "<SCHED_REQUIREMENTS>" << schd_req << "</SCHED_REQUIREMENTS>";
            }
            if (get("SCHED_DS_REQUIREMENTS", schd_ds_req))
            {
                oss << "<SCHED_DS_REQUIREMENTS>" << schd_ds_req << "</SCHED_DS_REQUIREMENTS>";
            }
            if (get("SCHED_MESSAGE", schd_messg))
            {
                oss << "<SCHED_MESSAGE>" << schd_messg << "</SCHED_MESSAGE>";
            }

            oss << "</USER_TEMPLATE>";
        }

        xml = oss.str();
        return xml;
    }

private:
    /**
     *  Restricted attribute list for VirtualMachineTemplates
     */
    static std::map<std::string, std::set<std::string> > restricted;
};

/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */

#endif /*VIRTUAL_MACHINE_TEMPLATE_H_*/
