# Demo Farm Game
This is a terminal based farm game for Windows machines written in C90.

The main gameplay loop features choosing crops.

Possible additions may be purchasing/selling of farms or random encounters

Ideally all gameplay should be do-able and user friendly within the terminal, however graphics.h Borland Graphics interface could also be used

# Design Notes

### Most of this is bad for big projects, but is fun to do here

- Linked lists are a cool way to store data. Unlike an array, no data in the list is inheritly linked to it's indice and the list more easily has data inserted or popped in the middle.

- C90 is cool. I like newing variables at the top of functions.

- Pointers are cool. Passing pointers to a function avoids copying large amounts of data and let's me easily modify lots of values without returning tons of variables in the function output

- Write code so if your logic is slightly off there will be a stack overflow, infinite loop, or you'll write into another variables memory. Debugging those problems is cool and memory is neat.

- Use .C files and not .h files for new code. .h files are often used like an interface to re-state what's in the .C file and be accessed by other files. This
makes things more complicated and duplicative than just putting all of my code in .C files and not having function interfaces at all.

- Use Codeblocks as the IDE

- Don't use libraries, including the C standard library. Instead of using someone else's code, we could be cool and rewrite it ourselves.
We can interface with Windows System Binaries ourselves.

# Playing

The releases on github should contain pre-compiled .exe files that work on modern 64bit Windows machines. You should simply be able to download the exe and run it,
without requiring any other dependent files that do not come with Windows.

If you don't know how to download the file from the releases page, you can also run this in PowerShell on your computer to get+run the latest version

```powershell
$repo = "Larckson/FarmGame"

$release = Invoke-RestMethod "https://api.github.com/repos/$repo/releases/latest"
$asset = $release.assets | Where-Object { $_.name -like "*.exe" } | Select-Object -First 1
$outPath = Join-Path [Environment]::GetFolderPath("Desktop") $asset.name

Invoke-WebRequest $asset.browser_download_url -OutFile $outPath

Start-Process "cmd.exe" -ArgumentList "/c `"$outPath`""
```

# Contributing

Please make issues and pull requests. That'd be neat.
