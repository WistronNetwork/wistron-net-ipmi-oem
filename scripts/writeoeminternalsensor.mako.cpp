## This file is a template.  The comment below is emitted
## into the rendered file; feel free to edit this file.
// !!! WARNING: This is a GENERATED Code..Please do NOT Edit !!!
<%
interfaceDict = {}
sensorNameMaxLength = 16
%>\
%for key in sensorDict.keys():
<%
    sensor = sensorDict[key]
    serviceInterface = sensor["serviceInterface"]
%>\
% endfor

#include "oem_types.hpp"

IdInfoMap_oem oem_internalsensors = {
<%
  count = 0
%>
% for key in sensorDict.keys():
  % if key:
<%
        sensor = sensorDict[key]
        path = sensor["path"]
%>
    % if 'PSU' not in path:
        <%
            count = count + 1
        %>
{${count},{
        .sensorPath = "${path}",
    }
},
    % endif
  % endif
% endfor
};
