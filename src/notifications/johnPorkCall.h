#ifndef JOHNPORKCALL_H
#define JOHNPORKCALL_H

#include <wchar.h>
const wchar_t johnPorkCall[] =
L"<toast scenario=\"incomingCall\" launch=\"action=answer&amp;callId=938163\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text>John Pork</text>\r\n"
L"      <text>Incoming Call - Sattelite</text>\r\n"
L"      <image src=\"file:///%TEMP%/thenews/johnpork.jpg\" hint-crop=\"circle\"/>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <action content=\"Answer\" \r\n"
L"            imageUri=\"file:///%TEMP%/thenews/answer.png\" \r\n"
L"            arguments=\"action=answer&amp;callId=938163\" \r\n"
L"            activationType=\"foreground\"/>\r\n"
L"  </actions>\r\n"
L"  <audio src=\"ms-winsoundevent:Notification.Looping.Call\" loop=\"true\" />\r\n"
L"</toast>\r\n";

#endif // JOHNPORKCALL_H
