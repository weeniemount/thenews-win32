#ifndef WEBSITEREDESIGN_H
#define WEBSITEREDESIGN_H

#include <wchar.h>
const wchar_t websiteRedesign[] =
L"<toast launch=\"action=viewPhoto&amp;photoId=92187\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text>we redesigned our website</text>\r\n"
L"      <text>enjoy it and leave feed back</text>\r\n"
L"      <image src=\"file:///%TEMP%/thenews/redesign.png\" />\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <action content=\"good\" arguments=\"likePhoto&amp;photoId=92187\" activationType=\"background\" />\r\n"
L"    <action content=\"horrid\" arguments=\"action=commentPhoto&amp;photoId=92187\" activationType=\"foreground\" />\r\n"
L"  </actions>\r\n"
L"</toast>\r\n";

#endif // WEBSITEREDESIGN_H