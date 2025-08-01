#ifndef MAZENOTIFICATION_H
#define MAZENOTIFICATION_H

#include <wchar.h>
const wchar_t mazeNotification[] =
L"<toast launch=\"action=viewPhoto&amp;photoId=92187\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text><![CDATA[BREAKING NEWS!!!!!!!!!!!!!!!!!!!!!!]]></text>\r\n"
L"      <text><![CDATA[MAZE CONCENTRATED ON GAMBLING SO HARD THEY GOT $-1 IN RETURN???]]></text>\r\n"
L"      <image src=\"file:///%TEMP%/thenews/maze.png\"/>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <action content=\"Read More\" arguments=\"likePhoto&amp;photoId=92187\" activationType=\"background\" />\r\n"
L"    <action content=\"discard\" arguments=\"action=commentPhoto&amp;photoId=92187\" activationType=\"foreground\" />\r\n"
L"  </actions>\r\n"
L"</toast>\r\n";

#endif // MAZENOTIFICATION_H
