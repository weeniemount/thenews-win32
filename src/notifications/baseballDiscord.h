#ifndef BASEBALLDISCORD_H
#define BASEBALLDISCORD_H

#include <wchar.h>
const wchar_t baseballDiscord[] =
L"<toast launch=\"action=viewPhoto&amp;photoId=92187\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text>&#9918;&#65039; Baseball on Discord?! &#129327;</text>\r\n"
L"      <text>Fr fr, a baseball emoji just dropped on Discord. Icl, ts kinda mogging ngl. &#129315;</text>\r\n"
L"      <image src=\"file:///%TEMP%/thenews/whateverthisis.png\"/>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <action content=\"Read More\" arguments=\"likePhoto&amp;photoId=92187\" activationType=\"background\" />\r\n"
L"    <action content=\"discard\" arguments=\"action=commentPhoto&amp;photoId=92187\" activationType=\"foreground\" />\r\n"
L"  </actions>\r\n"
L"</toast>\r\n";

#endif // BASEBALLDISCORD_H
