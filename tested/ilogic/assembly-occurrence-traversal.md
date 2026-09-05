# Assembly Occurrence Traversal in iLogic

## Purpose

Verified pattern for recursively traversing ComponentOccurrences in an AssemblyComponentDefinition, safely handling suppressed components and nested subassemblies.

## Context

- Inventor version: 2026
- Environment: iLogic internal rule
- Document type: Assembly document (`.iam`)
- Object/context: `AssemblyComponentDefinition.Occurrences`, `ComponentOccurrence.SubOccurrences`

## Verified API Members

| Member | Type | Description |
|--------|------|-------------|
| `AssemblyComponentDefinition.Occurrences` | `ComponentOccurrences` | Top-level occurrences in the assembly |
| `ComponentOccurrence.Name` | `String` (read) | Occurrence name (not the file name) |
| `ComponentOccurrence.Suppressed` | `Boolean` (read) | Returns `True` if the occurrence is suppressed |
| `ComponentOccurrence.SubOccurrences` | `ComponentOccurrences` | Nested occurrences within a subassembly |
| `ComponentOccurrences.Count` | `Integer` (read) | Number of occurrences |

## Implementation Pattern

### Recursive Traversal with Safe Suppression Handling

```vb
Private Sub TraverseOccurrences( _
    ByVal occurrences As ComponentOccurrences, _
    ByRef validationErrors As List(Of String), _
    ByVal path As String)

    For Each occ As ComponentOccurrence In occurrences
        Dim occName As String = ""
        Dim occPath As String = path & "/" & occ.Name

        Try
            occName = occ.Name
        Catch
            validationErrors.Add("Cannot read occurrence name at path: " & occPath)
            GoTo NextOccurrence
        End Try

        ' Check suppression state
        Dim isSuppressed As Boolean = False
        Try
            isSuppressed = occ.Suppressed
        Catch
            ' Cannot read suppression state - treat as suppressed
            isSuppressed = True
            validationErrors.Add("Cannot read suppression state for: " & occPath)
        End Try

        ' Skip sub-occurrence traversal for suppressed components
        ' Inventor throws an exception when accessing SubOccurrences on suppressed occurrences
        If Not isSuppressed Then
            Try
                If occ.SubOccurrences.Count > 0 Then
                    TraverseOccurrences(occ.SubOccurrences, validationErrors, occPath)
                End If
            Catch
                validationErrors.Add("Cannot traverse sub-occurrences at path: " & occPath)
            End Try
        End If

NextOccurrence:
    Next
End Sub
```

## Key Points

1. **Use `GoTo` labels instead of `Continue For`**: VB.NET in iLogic does not support `Continue` statements. Use `GoTo NextItem` with a labeled line instead.

2. **Check `Suppressed` before accessing `SubOccurrences`**: Inventor throws an exception when `SubOccurrences` is accessed on a suppressed `ComponentOccurrence`. Always check `occ.Suppressed` first.

3. **Handle suppression read failures conservatively**: If `occ.Suppressed` throws an exception, assume the component might be suppressed and skip traversal.

4. **Track path for debugging**: Build a path string during traversal to identify where errors occur.

## Validation

Verified during development of `ValidateAssemblyStructure` (2026-09-05):

- Successfully traversed top-level occurrences in a test assembly
- Successfully traversed nested subassemblies at multiple depth levels
- Correctly detected suppressed components
- Gracefully handled `SubOccurrences` access on suppressed components (no crash)
- Recorded meaningful errors when properties could not be read

## Result

VERIFIED

## Important Limitations

- `ComponentOccurrence.Name` is the occurrence name in the browser, not the referenced document file name. These can differ.
- Recursive traversal can be slow on very large assemblies with deep nesting. Consider adding a maximum depth limit if needed.
- Occurrence names are not unique — use the full path to distinguish between duplicate names in different branches.
- The `Suppressed` property returns `True` only for manually suppressed occurrences, not for occurrences suppressed due to unresolved constraints.

## Related

- `addins/ValidateAssemblyStructure/` — Production function using this pattern
- `knowledge/inventor/2026/assemblies.md` — General assembly API knowledge
