#include "johnCall.h"

const wchar_t johnCall[] =
L"<toast scenario=\"incomingCall\" launch=\"action=answer&amp;callId=938163\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text>John Phone</text>\r\n"
L"      <text>Incoming Call - Sattelite</text>\r\n"
L"      <image src=\"file:///%TEMP%/thenews/johnphone.jpg\" hint-crop=\"circle\"/>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <action content=\"Answer\" \r\n"
L"            imageUri=\"file:///%TEMP%/thenews/answer.png\" \r\n"
L"            arguments=\"action=answer&amp;callId=938163\" \r\n"
L"            activationType=\"foreground\"/>\r\n"
L"  </actions>\r\n"
L"</toast>\r\n"; 