# Win32 TestBed-Local Sample App

**This app is primarily for the convenience of repo maintainers, in order to
build against local SDK source instead of the installed MSI.

## Prerequisites

- Windows 10 (version 1809 or greater)
- Visual Studio 2019 with C++ and UWP workflows (the latter may be necessary for MSIX)
- [Branch SDK MSI generated by WIX](../../../BranchSDK/Windows/BranchInstaller) (required for Poco and other dependencies)

## Build and install

1. Install the Branch SDK using the MSI.
2. Open `TestBed-Local.sln` with Visual Studio.
3. Deploy the solution to the Start menu: `Build > Deploy Solution`

Note that this app is installed alongside the usual TestBed in the Start menu
as TestBed (Local).

## Run the app

You can run the app in the debugger in Visual Studio. You can also launch it from
the Start menu or via a link on the rzc2g.app.link domain, e.g. https://rzc2g.app.link/KHxB9RHGldb.
You can generate links via the Get Short URL option in the app that will open
the app.

## Logs

SDK logs appear in `%LocalAppData%\Branch\TestBed\branch-sdk.log`. The `LocalAppData` environment variable usually expands to `%HomeDrive%%HomePath%\AppData\Local`. Note that `AppData` is a hidden folder. In Git Bash, the easiest way to view the log is:

`$ tail -f ~/AppData/Local/Branch/TestBed/branch-sdk.log`

Note that the logs may roll over when they exceed a certain size.

## Uninstall

You can uninstall the app via the "Add or remove programs" option
in Windows settings.