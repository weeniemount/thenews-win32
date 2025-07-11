#ifndef PLZDONATE2_H
#define PLZDONATE2_H

#include <wchar.h>
const wchar_t plzDonate2[] =
L"<toast launch=\"action=viewAlarm&amp;alarmId=1\" scenario=\"alarm\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text><![CDATA[please donate us money]]></text>\r\n"
L"      <text><![CDATA[our in house servers ae dying of money :(]]></text>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <input id=\"answer\" type=\"selection\" defaultInput=\"wrongDefault\">\r\n"
L"      <selection id=\"wrongDefault\" content=\"100k dollars\"/>\r\n"
L"      <selection id=\"wrong\" content=\"1k dollars\"/>\r\n"
L"      <selection id=\"wrong\" content=\"1 dollar\"/>\r\n"
L"    </input>\r\n"
L"    <action content=\"gladly\" arguments=\"snooze\" activationType=\"system\"/>\r\n"
L"    <action content=\"never disturb me again\" arguments=\"dismiss\" activationType=\"background\"/>\r\n"
L"  </actions>\r\n"
L"</toast>\r\n";

#endif // PLZDONATE2_H 