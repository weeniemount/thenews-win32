#ifndef FEMBOYLABS_H
#define FEMBOYLABS_H

#include <wchar.h>
const wchar_t femboyLabs[] =
L"<toast launch=\"action=viewPhoto&amp;photoId=92187\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text><![CDATA[BREAKING NEWS!!!]]></text>\r\n"
L"      <text><![CDATA[femboyLabs has rebranded again!]]></text>\r\n"
L"      <image src=\"file:///%TEMP%/thenews/astolfo.jpg\"/>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <action content=\"Read More\" arguments=\"likePhoto&amp;photoId=92187\" activationType=\"background\" />\r\n"
L"    <action content=\"discard\" arguments=\"action=commentPhoto&amp;photoId=92187\" activationType=\"foreground\" />\r\n"
L"  </actions>\r\n"
L"</toast>\r\n";

#endif // FEMBOYLABS_H
