#ifndef TEXTMESSAGEVALVE_H
#define TEXTMESSAGEVALVE_H

#include <wchar.h>
const wchar_t textMessageValve[] =
L"<toast launch=\"action=viewStory&amp;storyId=92187\">"
L"  <visual>"
L"    <binding template=\"ToastGeneric\">"
L"      <text>Text message from +1 248-434-5508</text>"
L"      <text>We've successfully assassinated the attacker. Thank you for contacting Valve Support.</text>"
L"      <text placement=\"attribution\">Linker's Samsung Galaxy</text>"
L"    </binding>"
L"  </visual>"
L"  <actions>"
L"    <action content=\"Gamble it all away\" "
L"            arguments=\"action=pauseDownload&amp;downloadId=9438108\" "
L"            activationType=\"background\"/>"
L"  </actions>"
L"</toast>";

#endif // TEXTMESSAGEVALVE_H
