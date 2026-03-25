# Background

Because CodeBlocks is an uncommon IDE, and because the way I have my files linked together is pretty uncommon and saved in the CodeBlocks file.
I thought I'd make an easy guide on how to get a working dev setup.

# Requirements

- Running a 64 bit version of Windows. Windows versions from Windows 95 to Windows 11 should be supported. Internet connection to download dependent software

# Setup

### Step 0. Set up Chocolatey

The steps here can be done without a package manager.
But having a package manager makes install easier since you can just repeatedly paste commands into a PowerShell prompt rather than navigating GUIs that change with new releases.
To install Chocolatey run this in an admin PowerShell window:

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; `
[System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; `
iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))
```

You can test Chocolatey is installed by running the following. It should return back the version of chocolatey you are running

```powershell
choco
```

### Step 1. Download CodeBlocks

We want to download the MinGW version to the have it come with GCC for compiling and debugging.
Codeblocks is the IDE that is configured with this project and has the compiler instructions and file linking stored in the .cpb file for this project.

##### Method 1 (Chocolatey)

Run the following in an Admin PowerShell prompt

```powershell
choco install codeblocks-mingw
```

##### Method 2 (Website)

Go to the [CodeBlocks website](https://www.codeblocks.org/). Then navigate to the Downloads and Download the binary release.
Then choose a mingw setup version for Windows 64 bit.
Then run the downloaded exe and go through the setup steps.

### Step 2. Download the Netwide Assembler

The netwide assembler is used to compile the assembly for this project.

##### Method 1 (Chocolatey)

Run the following in an Admin PowerShell prompt

```powershell
choco install nasm
```

##### Method 2 (Website)

Go to the [Netwide Assembler website](https://www.nasm.us/). Then go to the downloads tab.
Then click on the folder for the latest install version (i.e. the one that is just a number and does not end in rc). 
Inside of that open the /win64/ folder. Then download the -installer-x64.exe file. Run that file.

### Step 3. Add NASM to the System Path

Test if NASM is automatically in your system path by closing and re-openning admin PowerShell.
Having this in our system path will allow us to run NASM compilation steps easily regardless of what directory you put the project files in.
In the admin powershell try running, if this errors you must continue with this step.

```powershell
nasm -v.
``` 

##### Method 1 PowerShell

Run the following in an admin PowerShell prompt

```powershell
[Environment]::SetEnvironmentVariable("Path", $env:Path + ";C:\Program Files\NASM", [EnvironmentVariableTarget]::Machine)
```

##### Method 2 Environment Variables Snap-In

Open the start menu of Windows and go to Environment Variables.
Under System Variables find Path and click Edit.
Then add C:\Program Files\NASM.
Click OK.

### Step 4. Download Git Bash

CodeBlocks does not come with a terminal to integrate with GIT unlike modern IDEs (e.g. VSCode, VisualStudio). Instead, I use Git Bash to interact with Git.
This is just a plain terminal without a GUI or other overhead that takes a long time to startup or tries to mask the actual git calls that buttons do.

Once this is downloaded, you should also set up GIT to both have your (username and email)[https://docs.github.com/en/get-started/git-basics/setting-your-username-in-git]
and to have an access token to push to (github remotely with)[https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens] 

##### Method 1 (Chocolatey)

```powershell
choco install git
```

##### Method 2 (Website)

Go to the (official GIT website)[https://git-scm.com]. Hit the Install for Windows Button. Run the exe and go through the setup wizard.

### Step 5. Clone the Repo

In GitBash run the following commands. This will download the current version of the project.

```bash
git clone https://github.com/LarzP123/FarmGame.git
```

### Step 6. Test

Double Click on the .cbp file that was downloaded. It should open the project in CodeBlocks.
Inside of CodeBlocks either click the gear and green arrow button to run or press F9 for the shortcut.
This should open the video game.

