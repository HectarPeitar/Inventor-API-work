Imports System
Module DstvProfileWrapper
Function GetDstvProfileCode( _
	ByVal sFamilyOrDesc As String) As String

	Dim s As String = _
		sFamilyOrDesc.ToUpper()


	Dim reHE As New System.Text.RegularExpressions.Regex( _
		"^HE\s*\d+\s*[ABM]\b")


	Dim reL As New System.Text.RegularExpressions.Regex( _
				"^L\s*\d")

	Dim rePL As New System.Text.RegularExpressions.Regex( _
		"^PL\b")

	Dim reC As New System.Text.RegularExpressions.Regex( _
		"^C\s*\d")

	Dim reT As New System.Text.RegularExpressions.Regex( _
		"^T\s*\d")

	Dim reRU As New System.Text.RegularExpressions.Regex( _
		"^R\s*\d")


	If reHE.IsMatch(s) OrElse _
		s.Contains("HEA") OrElse _
		s.Contains("HEB") OrElse _
		s.Contains("HEM") OrElse _
		s.Contains("IPE") Then

		Return "I"


	ElseIf reL.IsMatch(s) OrElse _
		s.Contains("HOEK") OrElse _
		s.Contains("EQUAL ANGLE") OrElse _
		s.Contains("UNEQUAL ANGLE") Then

		Return "L"


	ElseIf s.Contains("UNP") OrElse _
		s.Contains("UPN") OrElse _
		s.Contains("UPE") Then

		Return "U"


	ElseIf rePL.IsMatch(s) OrElse _
		s.Contains("PLATE") OrElse _
		s.Contains("SHEET") OrElse _
		s.Contains("BLECH") Then
		Return "B"


	ElseIf s.Contains("ROHR") OrElse _
		s.Contains("ROUND TUBE") OrElse _
		s.Contains("CHS") OrElse _
		s.Contains("BUIS") Then
		Return "RO"


	ElseIf reRU.IsMatch(s) OrElse _
		s.Contains("RND") OrElse _
		s.Contains("RUND") OrElse _
		s.Contains("ROUND") OrElse _
		s.Contains("CIRCLE") Then
		Return "RU"


	ElseIf s.Contains("RHS") OrElse _
		s.Contains("SHS") OrElse _
		s.Contains("KOK") OrElse _
		s.Contains("RECTANGULAR") OrElse _
		s.Contains("RECTANGLE") OrElse _
		s.Contains("SQUARE") Then
		Return "M"


	ElseIf reC.IsMatch(s) Then
		Return "C"


	ElseIf reT.IsMatch(s) Then
		Return "T"


	Else

		Return "SO"

	End If

End Function
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