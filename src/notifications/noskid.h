#ifndef NOSKID_H
#define NOSKID_H

#include <wchar.h>
const wchar_t noskid[] =
L"<toast launch=\"action=viewStory&amp;storyId=92187\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text><![CDATA[BREAKING NEWS!!!]]></text>\r\n"
L"      <image placement=\"appLogoOverride\" src=\"file:///%TEMP%/thenews/noskid.png\"/>\r\n"
L"      <text><![CDATA[To view this notification, upload a NoSkid certificate.]]></text>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"</toast>\r\n";

#endif // NOSKID_H
