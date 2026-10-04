param(
    [Parameter(Mandatory = $true)]
    [ValidatePattern('^[A-Za-z][A-Za-z0-9_]*$')]
    [string]$Name
)

Set-StrictMode -Version Latest
$ErrorActionPreference = 'Stop'

$repoRoot = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path
$gitMarker = Join-Path $repoRoot '.git'
$cmakeFile = Join-Path $repoRoot 'CMakeLists.txt'
$submodulePath = Join-Path $repoRoot 'seconds/wxlib'
$placeholder = 'project(StarterApp LANGUAGES CXX)'

if (-not (Test-Path -LiteralPath $gitMarker)) {
    throw 'Run this script only in a Git repository created from the template.'
}

$cmakeText = [System.IO.File]::ReadAllText($cmakeFile)
if (-not $cmakeText.Contains($placeholder)) {
    throw 'This project has already been initialized or its CMake project name was changed.'
}
if (Test-Path -LiteralPath $submodulePath) {
    throw 'seconds/wxlib already exists. Check the submodule before continuing.'
}

[System.IO.Directory]::CreateDirectory((Join-Path $repoRoot 'seconds')) | Out-Null
& git -C $repoRoot submodule add git@github.com:andrelorenzo/wxlib.git seconds/wxlib
if ($LASTEXITCODE -ne 0) {
    throw 'Could not add wxlib. Check SSH access to GitHub and try again.'
}

$cmakeText = $cmakeText.Replace($placeholder, "project($Name LANGUAGES CXX)")
$utf8NoBom = New-Object System.Text.UTF8Encoding($false)
[System.IO.File]::WriteAllText($cmakeFile, $cmakeText, $utf8NoBom)

Write-Host "Initialized $Name. Commit CMakeLists.txt, .gitmodules and seconds/wxlib."

