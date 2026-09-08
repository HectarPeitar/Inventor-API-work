Imports System
Module DstvProfileWrapper
%%FUNC%%
End Module
Module ProfileCodeTest
    Sub Main()
        Dim failures As Integer = 0
        Dim inputs As String() = New String() { _
            "HEB400", "HEA220", "IPE 300", _
            "L 80*80*8", "HOEKPROFIEL 100", _
            "UNP 160", "UPN180", "UPE 200", _
            "PLATE 10", "PL 200*10", "SHEET 5", _
            "ROHR 50x3", "ROUND TUBE 48.3", "CHS 88.9", _
            "RND 20", "RUND 25", _
            "RHS 100x50x3", "SHS 40x40x4", "KOK 80x80x5", _
            "C 100", "T 80", "CustomProfile 123", "" }
        Dim expects As String() = New String() { _
            "I", "I", "I", _
            "L", "L", _
            "U", "U", "U", _
            "B", "B", "B", _
            "RO", "RO", "RO", _
            "RU", "RU", _
            "M", "M", "M", _
            "C", "T", "SO", "SO" }
        If expects.GetLength(0) <> inputs.GetLength(0) Then
            Console.WriteLine("INTERNAL: array mismatch")
            Environment.Exit(2)
        End If
        For i As Integer = 0 To inputs.GetLength(0) - 1
            Dim r As String = GetDstvProfileCode(inputs(i))
            If r <> expects(i) Then
                Console.WriteLine("FAIL: " & inputs(i) & " => " & r & " (expected " & expects(i) & ")")
                failures += 1
            Else
                Console.WriteLine("PASS: " & inputs(i) & " => " & r)
            End If
        Next
        Console.WriteLine("failures=" & failures)
        Environment.Exit(If(failures > 0, 1, 0))
    End Sub
End Module