function Get-DirectoryTree {
    param (
        [string]$path = (Get-Location),
        [int]$indentLevel = 0
    )

    # Get the current directory
    $currentDir = Get-Item -LiteralPath $path

    # Display the current directory with appropriate indentation
    Write-Host (" " * $indentLevel) -NoNewline
    Write-Host "-- " -NoNewline
    Write-Host $currentDir.Name

    # Get subdirectories
    $subDirs = Get-ChildItem -LiteralPath $currentDir.FullName -Directory

    # Recursively call the function for each subdirectory
    foreach ($subDir in $subDirs) {
        Get-DirectoryTree -path $subDir.FullName -indentLevel ($indentLevel + 3)
    }
}

# Call the function with the current directory
Get-DirectoryTree
