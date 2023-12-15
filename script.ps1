# Define the project name
$projectName = "SecureSync"

# Define the directories
$directories = @(
    "src",
    "src\gui",
    "include",
    "resources",
    "docs",
    "presentations"
)

# Define the source files
$sourceFiles = @(
    "src\main.cpp",
    "src\file_manager.cpp",
    "src\authentication.cpp",
    "src\network_manager.cpp",
    "src\gui\mainwindow.ui",
    "src\gui\mainwindow.cpp",
    "include\file_manager.h",
    "include\authentication.h",
    "include\network_manager.h",
    "docs\user_guide.md",
    "docs\technical_guide.md",
    "presentations\presentation.pdf",
    ".gitignore"
)

# Create directories
foreach ($directory in $directories) {
    New-Item -ItemType Directory -Force -Path (Join-Path $projectName $directory)
}

# Create source files, excluding README.md and LICENSE.md if they already exist
foreach ($file in $sourceFiles) {
    $filePath = Join-Path $projectName $file
    if (!(Test-Path $filePath) -or ($file -notin @("README.md", "LICENSE.md"))) {
        New-Item -ItemType File -Force -Path $filePath
    }
}

# Display a message
Write-Host "Project structure created for $projectName"
