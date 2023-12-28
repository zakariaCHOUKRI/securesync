function Get-TreeStructure {
    param (
        [string]$Path = ".",
        [int]$IndentLevel = 0
    )

    $indentation = '    ' * $IndentLevel
    $items = Get-ChildItem -Path $Path

    foreach ($item in $items) {
        $relativePath = $item.FullName -replace [regex]::Escape((Get-Location).Path + "\"), ""
        Write-Host "$indentation$relativePath"

        if ($item.PSIsContainer) {
            Get-TreeStructure -Path $item.FullName -IndentLevel ($IndentLevel + 1)
        }
    }
}

# Display the tree structure of the current directory
Get-TreeStructure
