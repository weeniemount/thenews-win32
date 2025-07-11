#ifndef MCAFEE_H
#define MCAFEE_H

#include <wchar.h>
const wchar_t mcafee[] =
L"<toast launch=\"action=viewStory&amp;storyId=92187\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <image placement=\"appLogoOverride\" src=\"file:///%TEMP%/thenews/mcafee.png\"/>\r\n"
L"      <image placement=\"hero\" src=\"file:///%TEMP%/thenews/mcafeehero.png\"/>\r\n"
L"      <text><![CDATA[BREAKING NEWS!!!]]></text>\r\n"
L"      <text>Your McAfee&#8482; subscription plan has expired. Please select a new one below.></text>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <input id=\"answer\" type=\"selection\" defaultInput=\"wrongDefault\">\r\n"
L"      <selection id=\"wrongDefault\" content=\"Essential - $119.99\"/>\r\n"
L"      <selection id=\"wrong\" content=\"McAfee+&#8482; Premium Individual - $149.99\"/>\r\n"
L"      <selection id=\"right\" content=\"McAfee+&#8482; Advanced Individual - $199.99\"/>\r\n"
L"    </input>\r\n"
L"    <action\r\n"
L"      activationType=\"system\"\r\n"
L"      arguments=\"snooze\"\r\n"
L"      content=\"yeah this gud!\"/>\r\n"
L"    <action\r\n"
L"      activationType=\"background\"\r\n"
L"      arguments=\"dismiss\"\r\n"
L"      content=\"no never cancel it rn\"/>\r\n"
L"  </actions>\r\n"
L"</toast>\r\n";

#endif // MCAFEE_H
