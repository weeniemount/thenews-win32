#ifndef PLZDONATE_H
#define PLZDONATE_H

#include <wchar.h>
const wchar_t plzDonate[] =
L"<toast launch=\"action=viewEvent&amp;eventId=63851\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text><![CDATA[we need your money]]></text>\r\n"
L"      <text><![CDATA[donate to \"the news\"]]></text>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <input id=\"status\" type=\"selection\" defaultInput=\"yes\">\r\n"
L"      <selection id=\"yes\" content=\"100k dollars\"/>\r\n"
L"      <selection id=\"maybe\" content=\"1k dollars\"/>\r\n"
L"      <selection id=\"no\" content=\"1 dollar\"/>\r\n"
L"    </input>\r\n"
L"    <action content=\"gladly\" arguments=\"action=rsvpEvent&amp;eventId=63851\" activationType=\"background\"/>\r\n"
L"    <action content=\"no please\" arguments=\"\" activationType=\"system\"/>\r\n"
L"  </actions>\r\n"
L"</toast>\r\n";

#endif // PLZDONATE_H 