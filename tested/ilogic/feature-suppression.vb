' Pattern: Feature Suppression in iLogic
' Verified: 2026-09-04 | Inventor 2026 | iLogic internal rule
' Source: Developed during ApplyFeatureConfiguration (addins/ApplyFeatureConfiguration/)

' --- Finding a feature by name ---
Dim targetFeature As PartFeature = Nothing
For Each f As PartFeature In compDef.Features
    If f.Name = "FeatureName" Then
        targetFeature = f
        Exit For
    End If
Next

' --- Check if feature was found ---
If targetFeature Is Nothing Then
    ' Handle missing feature
End If

' --- Suppress a feature ---
Try
    targetFeature.Suppressed = True
Catch ex As Exception
    ' Handle error (locked feature, invalid state, etc.)
End Try

' --- Activate a feature ---
Try
    targetFeature.Suppressed = False
Catch ex As Exception
    ' Handle error
End Try

' --- Check current suppression state ---
Dim state As String
Try
    state = If(targetFeature.Suppressed, "Suppressed", "Active")
Catch ex As Exception
    state = "Unknown"
End Try

' --- Update model after changing suppression ---
Try
    doc.Update()
Catch ex As Exception
    ' Handle error
End Try