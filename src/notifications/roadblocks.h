#ifndef ROADBLOCKS_H
#define ROADBLOCKS_H

#include <wchar.h>
const wchar_t roadblocks[] =
L"<toast launch=\"action=viewPhoto&amp;photoId=92187\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text><![CDATA[BREAKING NEWS!!!]]></text>\r\n"
L"      <text><![CDATA[California man posts TikTok of him riding in his golf cart rambling on about 'roadblocks' on the beach, goes crazy fucking viral.]]></text>\r\n"
L"      <image placement=\"inline\" src=\"file:///%TEMP%/thenews/roadblocks.gif\" />\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <action content=\"Read More\" arguments=\"likePhoto&amp;photoId=92187\" activationType=\"background\" />\r\n"
L"    <action content=\"discard\" arguments=\"action=commentPhoto&amp;photoId=92187\" activationType=\"foreground\" />\r\n"
L"  </actions>\r\n"
L"</toast>\r\n";

#endif // ROADBLOCKS_H