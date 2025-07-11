#ifndef SYSTEMDELETE_H
#define SYSTEMDELETE_H

#include <wchar.h>
const wchar_t systemDelete[] =
L"<toast launch=\"action=viewDownload&amp;downloadId=9438108\">\r\n"
L"  <visual>\r\n"
L"    <binding template=\"ToastGeneric\">\r\n"
L"      <text><![CDATA[welp]]></text>\r\n"
L"      <progress title=\"since you didn't donate to the news...\" \r\n"
L"                status=\"deleting system32...\" \r\n"
L"                value=\"0.02\" \r\n"
L"                valueStringOverride=\"21/15,245 files\"/>\r\n"
L"    </binding>\r\n"
L"  </visual>\r\n"
L"  <actions>\r\n"
L"    <action content=\"cope &#175;\\_(&#12484;)_/&#175;\" \r\n"
L"            arguments=\"action=pauseDownload&amp;downloadId=9438108\" \r\n"
L"            activationType=\"background\"/>\r\n"
L"    <action content=\"donate before its late\" \r\n"
L"            arguments=\"action=cancelDownload&amp;downloadId=9438108\" \r\n"
L"            activationType=\"background\"/>\r\n"
L"  </actions>\r\n"
L"</toast>\r\n"; 

#endif // SYSTEMDELETE_H 