# Copyright (c) 2025 The Crimson Zamboni
#
# This Software is licensed for non-commercial use only, subject to the following
# conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# The Software may not be monetized. This means that you cannot use it on a
# server with access limited only to paying players, or a server with extra
# privileges, such as priority queue slots, granted to paying players.
#
# The Software is not authorized for posting on Steam, except under the Steam
# account https://steamcommunity.com/id/DirtySanchez/

$ModName = "CHFSleep"
$VersionFile = "scripts\3_game\version.c"
$ModCppFile = "mod.cpp"

$ErrorActionPreference = "Stop"

$version = $(git describe --tags --dirty)
$rawVersion = $version -replace "^v",""

$originalVersion = (Get-Content -path "$VersionFile" -raw)
$originalModCpp = (Get-Content -path "$ModCppFile" -raw)

if (Test-Path "P:\@${ModName}") { Remove-Item -Recurse "P:\@${ModName}" }

New-Item -Type Directory "P:\@${ModName}" | Out-Null
New-Item -Type Directory "P:\@${ModName}\addons" | Out-Null
New-Item -Type Directory "P:\@${ModName}\keys" | Out-Null

$originalVersion -replace "\bdev\b","$version" | Set-Content -path "$VersionFile" -NoNewLine
$originalModCpp -replace "\bdev\b","$rawVersion" | Set-Content -path "$ModCppFile" -NoNewLine

pbo "--sign=$env:BIPRIVATEKEY_PATH" "--header=prefix=${ModName}".ToLower() "--header=version=${version}" "--pattern=**/config.cpp" "--pattern=scripts/**/*.c" "--pattern=**/*.paa" "--pattern=**/*.csv" "--pattern=**/*.edds" "--pattern=**/*.layout" "--pattern=**/*.ogg" "--pattern=data/**/*.xml" "P:\@${ModName}\addons\chfsleep.pbo"
$buildcode = $lastexitcode
$builderror = $errorMessage

Copy-Item "mod.cpp" -Destination "P:\@${ModName}\mod.cpp"

Set-Content -Path "$VersionFile" -Value "$originalVersion" -NoNewLine
Set-Content -Path "$ModCppFile" -Value "$originalModCpp" -NoNewLine

if ($buildcode -ne 0) { throw ("Exec: " + $builderror) }

Copy-Item $env:BIKEY_PATH -Destination "P:\@${ModName}\keys"
