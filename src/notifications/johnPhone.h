#ifndef JOHNPHONE_H
#define JOHNPHONE_H

#include <wchar.h>
const wchar_t johnPhone[] =
L"<toast launch=\"action=openThread&amp;threadId=92187\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text hint-maxLines=\"1\"><![CDATA[John Phone]]></text>\r\n"
L"      <text><![CDATA[Find me online]]></text>\r\n"
L"      <image placement=\"hero\" src=\"file:///%TEMP%/thenews/itsme...johnphone.jpg\"/>\r\n"
L"      <image placement=\"appLogoOverride\" hint-crop=\"circle\" src=\"file:///%TEMP%/thenews/johnphone.jpg\"/>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <input id=\"textBox\" type=\"text\" placeHolderContent=\"reply\" />\r\n"
L"    <action content=\"Send\" arguments=\"action=reply&amp;threadId=92187\" activationType=\"background\" imageUri=\"file:///%TEMP%/thenews/send.png\" />\r\n"
L"  </actions>\r\n"
L"</toast>\r\n";

#endif // JOHNPHONE_H
