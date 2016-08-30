# RFID_Band
A simple C# / .NET library code to connect with Chafon RFID writer / reader - LHF and retrieving TK4100 tag values

Chafon reference code is available for free download here
http://www.chafon.com/DownLoad.aspx?page=1

TK4100 specs are available here
http://www.smartcardchn.com/uploadfile/single/TK4100.pdf

1. Download Chafon RFID application for your corresponding LHF Device.
2. Install the prolific driver
3. Follow the steps given by Chafon to update old driver in device manager
4. Now use their given application to read and write into the tag
5. you may want to make some changes to their code like I did - by adding a few decorators for the managed dll we are going to use
6. Copy that dll into your executing code folder so that code can find it.

You may want to download and install Microsoft Visual C++ 2005 Redistributable Package (x86)
https://www.microsoft.com/en-in/download/details.aspx?id=3387
to ensure that you are able to develop in a Win 10 x64 machine.

Good to go I suppose.


