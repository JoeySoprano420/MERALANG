@echo off
mkdir dist
copy build\Release\meralang.exe dist\
copy tools\repl_ui.exe dist\
echo Creating installer...
"%ProgramFiles(x86)%\Inno Setup 6\ISCC.exe" installer\meralang_installer.iss

# installer/meralang_installer.iss
[Setup]
AppName=MeraLang
AppVersion=1.0
DefaultDirName={pf}\MeraLang
DefaultGroupName=MeraLang
OutputBaseFilename=meralang-setup
Compression=lzma
SolidCompression=yes

[Files]
Source: "dist\meralang.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "dist\repl_ui.exe"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\MeraLang REPL"; Filename: "{app}\repl_ui.exe"
