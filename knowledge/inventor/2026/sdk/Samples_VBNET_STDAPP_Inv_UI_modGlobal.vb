Option Strict Off
Option Explicit On
Module modGlobal
	
	Public oInventorApp As Inventor.Application
	
	Public Structure utdNameValue
		Dim Name As String
		Dim Value As Integer
	End Structure
	
    Public Filters() As utdNameValue = {}
	Public FiltersSize As Short
	Public KeyConstants() As utdNameValue
	
	'form properties
	Public Const SWP_NOMOVE As Short = 2
	Public Const SWP_NOSIZE As Short = 1
	Public Const FLAGS As Boolean = SWP_NOMOVE Or SWP_NOSIZE
	Public Const HWND_TOPMOST As Short = -1
	
	'SetWindowPos declaration
	Public Declare Function SetWindowPos Lib "user32" (ByVal hwnd As Integer, ByVal hWndInsertAfter As Integer, ByVal x As Integer, ByVal y As Integer, ByVal cx As Integer, ByVal cy As Integer, ByVal wFlags As Integer) As Integer
	
	
    Public Sub LoadKeyConstants()
        ReDim KeyConstants(100)
        KeyConstants(1).Name = "Key0"
        KeyConstants(1).Value = 48
        KeyConstants(2).Name = "Key1"
        KeyConstants(2).Value = 49
        KeyConstants(3).Name = "Key2"
        KeyConstants(3).Value = 50
        KeyConstants(4).Name = "Key3"
        KeyConstants(4).Value = 51
        KeyConstants(5).Name = "Key4"
        KeyConstants(5).Value = 52
        KeyConstants(6).Name = "Key5"
        KeyConstants(6).Value = 53
        KeyConstants(7).Name = "Key6"
        KeyConstants(7).Value = 54
        KeyConstants(8).Name = "Key7"
        KeyConstants(8).Value = 55
        KeyConstants(9).Name = "Key8"
        KeyConstants(9).Value = 56
        KeyConstants(10).Name = "Key9"
        KeyConstants(10).Value = 57
        KeyConstants(11).Name = "KeyA"
        KeyConstants(11).Value = 65
        KeyConstants(12).Name = "KeyAdd"
        KeyConstants(12).Value = 107
        KeyConstants(13).Name = "KeyB"
        KeyConstants(13).Value = 66
        KeyConstants(14).Name = "KeyBack"
        KeyConstants(14).Value = 8
        KeyConstants(15).Name = "KeyC"
        KeyConstants(15).Value = 67
        KeyConstants(16).Name = "KeyCancel"
        KeyConstants(16).Value = 3
        KeyConstants(17).Name = "KeyCapital"
        KeyConstants(17).Value = 20
        KeyConstants(18).Name = "KeyClear"
        KeyConstants(18).Value = 12
        KeyConstants(19).Name = "KeyControl"
        KeyConstants(19).Value = 17
        KeyConstants(20).Name = "KeyD"
        KeyConstants(20).Value = 68
        KeyConstants(21).Name = "KeyDecimal"
        KeyConstants(21).Value = 110
        KeyConstants(22).Name = "KeyDelete"
        KeyConstants(22).Value = 46
        KeyConstants(23).Name = "KeyDivide"
        KeyConstants(23).Value = 111
        KeyConstants(24).Name = "KeyDown"
        KeyConstants(24).Value = 40
        KeyConstants(25).Name = "KeyE"
        KeyConstants(25).Value = 69
        KeyConstants(26).Name = "KeyEnd"
        KeyConstants(26).Value = 35
        KeyConstants(27).Name = "KeyEscape"
        KeyConstants(27).Value = 27
        KeyConstants(28).Name = "KeyExecute"
        KeyConstants(28).Value = 43
        KeyConstants(29).Name = "KeyF"
        KeyConstants(29).Value = 70
        KeyConstants(30).Name = "KeyF1"
        KeyConstants(30).Value = 112
        KeyConstants(31).Name = "KeyF10"
        KeyConstants(31).Value = 121
        KeyConstants(32).Name = "KeyF11"
        KeyConstants(32).Value = 122
        KeyConstants(33).Name = "KeyF12"
        KeyConstants(33).Value = 123
        KeyConstants(34).Name = "KeyF13"
        KeyConstants(34).Value = 124
        KeyConstants(35).Name = "KeyF14"
        KeyConstants(35).Value = 125
        KeyConstants(36).Name = "KeyF15"
        KeyConstants(36).Value = 126
        KeyConstants(37).Name = "KeyF16"
        KeyConstants(37).Value = 127
        KeyConstants(38).Name = "KeyF2"
        KeyConstants(38).Value = 113
        KeyConstants(39).Name = "KeyF3"
        KeyConstants(39).Value = 114
        KeyConstants(40).Name = "KeyF4"
        KeyConstants(40).Value = 115
        KeyConstants(41).Name = "KeyF5"
        KeyConstants(41).Value = 116
        KeyConstants(42).Name = "KeyF6"
        KeyConstants(42).Value = 117
        KeyConstants(43).Name = "KeyF7"
        KeyConstants(43).Value = 118
        KeyConstants(44).Name = "KeyF8"
        KeyConstants(44).Value = 119
        KeyConstants(45).Name = "KeyF9"
        KeyConstants(45).Value = 120
        KeyConstants(46).Name = "KeyG"
        KeyConstants(46).Value = 71
        KeyConstants(47).Name = "KeyH"
        KeyConstants(47).Value = 72
        KeyConstants(48).Name = "KeyHelp"
        KeyConstants(48).Value = 47
        KeyConstants(49).Name = "KeyHome"
        KeyConstants(49).Value = 36
        KeyConstants(50).Name = "KeyI"
        KeyConstants(50).Value = 73
        KeyConstants(51).Name = "KeyInsert"
        KeyConstants(51).Value = 45
        KeyConstants(52).Name = "KeyJ"
        KeyConstants(52).Value = 74
        KeyConstants(53).Name = "KeyK"
        KeyConstants(53).Value = 75
        KeyConstants(54).Name = "KeyL"
        KeyConstants(54).Value = 76
        KeyConstants(55).Name = "KeyLButton"
        KeyConstants(55).Value = 1
        KeyConstants(56).Name = "KeyLeft"
        KeyConstants(56).Value = 37
        KeyConstants(57).Name = "KeyM"
        KeyConstants(57).Value = 77
        KeyConstants(58).Name = "KeyMButton"
        KeyConstants(58).Value = 4
        KeyConstants(59).Name = "KeyMenu"
        KeyConstants(59).Value = 18
        KeyConstants(60).Name = "KeyMultiply"
        KeyConstants(60).Value = 106
        KeyConstants(61).Name = "KeyN"
        KeyConstants(61).Value = 78
        KeyConstants(62).Name = "KeyNumlock"
        KeyConstants(62).Value = 144
        KeyConstants(63).Name = "KeyNumpad0"
        KeyConstants(63).Value = 96
        KeyConstants(64).Name = "KeyNumpad1"
        KeyConstants(64).Value = 97
        KeyConstants(65).Name = "KeyNumpad2"
        KeyConstants(65).Value = 98
        KeyConstants(66).Name = "KeyNumpad3"
        KeyConstants(66).Value = 99
        KeyConstants(67).Name = "KeyNumpad4"
        KeyConstants(67).Value = 100
        KeyConstants(68).Name = "KeyNumpad5"
        KeyConstants(68).Value = 101
        KeyConstants(69).Name = "KeyNumpad6"
        KeyConstants(69).Value = 102
        KeyConstants(70).Name = "KeyNumpad7"
        KeyConstants(70).Value = 103
        KeyConstants(71).Name = "KeyNumpad8"
        KeyConstants(71).Value = 104
        KeyConstants(72).Name = "KeyNumpad9"
        KeyConstants(72).Value = 105
        KeyConstants(73).Name = "KeyO"
        KeyConstants(73).Value = 79
        KeyConstants(74).Name = "KeyP"
        KeyConstants(74).Value = 80
        KeyConstants(75).Name = "KeyPageDown"
        KeyConstants(75).Value = 34
        KeyConstants(76).Name = "KeyPageUp"
        KeyConstants(76).Value = 33
        KeyConstants(77).Name = "KeyPause"
        KeyConstants(77).Value = 19
        KeyConstants(78).Name = "KeyPrint"
        KeyConstants(78).Value = 42
        KeyConstants(79).Name = "KeyQ"
        KeyConstants(79).Value = 81
        KeyConstants(80).Name = "KeyR"
        KeyConstants(80).Value = 82
        KeyConstants(81).Name = "KeyRButton"
        KeyConstants(81).Value = 2
        KeyConstants(82).Name = "KeyReturn"
        KeyConstants(82).Value = 13
        KeyConstants(83).Name = "KeyRight"
        KeyConstants(83).Value = 39
        KeyConstants(84).Name = "KeyS"
        KeyConstants(84).Value = 83
        KeyConstants(85).Name = "KeyScrollLock"
        KeyConstants(85).Value = 145
        KeyConstants(86).Name = "KeySelect"
        KeyConstants(86).Value = 41
        KeyConstants(87).Name = "KeySeparator"
        KeyConstants(87).Value = 108
        KeyConstants(88).Name = "KeyShift"
        KeyConstants(88).Value = 16
        KeyConstants(89).Name = "KeySnapshot"
        KeyConstants(89).Value = 44
        KeyConstants(90).Name = "KeySpace"
        KeyConstants(90).Value = 32
        KeyConstants(91).Name = "KeySubtract"
        KeyConstants(91).Value = 109
        KeyConstants(92).Name = "KeyT"
        KeyConstants(92).Value = 84
        KeyConstants(93).Name = "KeyTab"
        KeyConstants(93).Value = 9
        KeyConstants(94).Name = "KeyU"
        KeyConstants(94).Value = 85
        KeyConstants(95).Name = "KeyUp"
        KeyConstants(95).Value = 38
        KeyConstants(96).Name = "KeyV"
        KeyConstants(96).Value = 86
        KeyConstants(97).Name = "KeyW"
        KeyConstants(97).Value = 87
        KeyConstants(98).Name = "KeyX"
        KeyConstants(98).Value = 88
        KeyConstants(99).Name = "KeyY"
        KeyConstants(99).Value = 89
        KeyConstants(100).Name = "KeyZ"
        KeyConstants(100).Value = 90
    End Sub


    Private Sub AddFilter(ByVal Name As String, ByVal Value As Integer, ByRef FilterList() As utdNameValue)
        ReDim Preserve FilterList(FilterList.Length)
        FilterList(FilterList.Length - 1).Name = Name
        FilterList(FilterList.Length - 1).Value = Value
    End Sub


	' Load Assembly filters
    Public Sub LoadFilterListEnums()
        AddFilter("kAllCircularEntities", 18435, Filters)
        AddFilter("kAllCustomGraphicsFilter", 18436, Filters)
        AddFilter("kAllEntitiesFilter", 18439, Filters)
        AddFilter("kAllLinearEntities", 18433, Filters)
        AddFilter("kAllPlanarEntities", 18432, Filters)
        AddFilter("kAllPointEntities", 18434, Filters)
        AddFilter("kAssemblyFeatureFilter", 16646, Filters)
        AddFilter("kAssemblyLeafOccurrenceFilter", 16643, Filters)
        AddFilter("kAssemblyOccurrenceFilter", 16640, Filters)
        AddFilter("kAssemblyOccurrencePatternElementFilter", 16645, Filters)
        AddFilter("kAssemblyOccurrencePatternFilter", 16644, Filters)
        AddFilter("kCustomBrowserNodeFilter", 18437, Filters)
        AddFilter("kDrawingAutoCADBlockDefinitionFilter", 16923, Filters)
        AddFilter("kDrawingAutoCADBlockFilter", 16922, Filters)
        AddFilter("kDrawingBalloonFilter", 16906, Filters)
        AddFilter("kDrawingBorderDefinitionFilter", 16909, Filters)
        AddFilter("kDrawingBorderFilter", 16913, Filters)
        AddFilter("kDrawingCenterlineFilter", 16915, Filters)
        AddFilter("kDrawingCentermarkFilter", 16916, Filters)
        AddFilter("kDrawingCurveSegmentFilter", 16914, Filters)
        AddFilter("kDrawingCustomTableFilter", 16905, Filters)
        AddFilter("kDrawingDefaultFilter", 16896, Filters)
        AddFilter("kDrawingDimensionFilter", 16900, Filters)
        AddFilter("kDrawingFeatureControlFrameFilter", 16918, Filters)
        AddFilter("kDrawingHoleTableFilter", 16902, Filters)
        AddFilter("kDrawingHoleTagFilter", 16903, Filters)
        AddFilter("kDrawingNoteFilter", 16899, Filters)
        AddFilter("kDrawingOriginIndicatorFilter", 16920, Filters)
        AddFilter("kDrawingPartsListFilter", 16901, Filters)
        AddFilter("kDrawingRevisionTableFilter", 16904, Filters)
        AddFilter("kDrawingSheetFilter", 16897, Filters)
        AddFilter("kDrawingSheetFormatFilter", 16917, Filters)
        AddFilter("kDrawingSketchedSymbolDefinitionFilter", 16908, Filters)
        AddFilter("kDrawingSketchedSymbolFilter", 16907, Filters)
        AddFilter("kDrawingSurfaceTextureSymbolFilter", 16919, Filters)
        AddFilter("kDrawingTitleBlockDefinitionFilter", 16910, Filters)
        AddFilter("kDrawingTitleBlockFilter", 16912, Filters)
        AddFilter("kDrawingViewFilter", 16898, Filters)
        AddFilter("kDrawingViewLabelFilter", 16921, Filters)
        AddFilter("kFeatureDimensionFilter", 18438, Filters)
        AddFilter("kPartBodyFilter", 15890, Filters)
        AddFilter("kPartDefaultFilter", 15886, Filters)
        AddFilter("kPartEdgeCircularFilter", 15874, Filters)
        AddFilter("kPartEdgeFilter", 15873, Filters)
        AddFilter("kPartEdgeLinearFilter", 15875, Filters)
        AddFilter("kPartEdgeMidpointFilter", 15876, Filters)
        AddFilter("kPartFaceConicalFilter", 15880, Filters)
        AddFilter("kPartFaceCylindricalFilter", 15879, Filters)
        AddFilter("kPartFaceFilter", 15877, Filters)
        AddFilter("kPartFacePlanarFilter", 15878, Filters)
        AddFilter("kPartFaceSphericalFilter", 15882, Filters)
        AddFilter("kPartFaceToroidalFilter", 15881, Filters)
        AddFilter("kPartFeatureFilter", 15884, Filters)
        AddFilter("kPartSurfaceFeatureFilter", 15885, Filters)
        AddFilter("kPartVertexFilter", 15883, Filters)
        AddFilter("kPointCloudFilter", 15891, Filters)
        AddFilter("kPointCloudPointFilter", 15892, Filters)
        AddFilter("kSketch3DCurveCircularFilter", 17666, Filters)
        AddFilter("kSketch3DCurveEllipseFilter", 17667, Filters)
        AddFilter("kSketch3DCurveFilter", 17664, Filters)
        AddFilter("kSketch3DCurveLinearFilter", 17665, Filters)
        AddFilter("kSketch3DCurveSplineFilter", 17668, Filters)
        AddFilter("kSketch3DDefaultFilter", 17670, Filters)
        AddFilter("kSketch3DDimConstraintFilter ", 17672, Filters)
        AddFilter("kSketch3DObjectFilter", 17671, Filters)
        AddFilter("kSketch3DPointFilter", 17669, Filters)
        AddFilter("kSketch3DProfileFilter", 17673, Filters)
        AddFilter("kSketchBlockDefinitionFilter", 16141, Filters)
        AddFilter("kSketchBlockFilter", 16142, Filters)
        AddFilter("kSketchCurveCircularFilter", 16131, Filters)
        AddFilter("kSketchCurveEllipseFilter", 16132, Filters)
        AddFilter("kSketchCurveFilter", 16129, Filters)
        AddFilter("kSketchCurveLinearFilter", 16130, Filters)
        AddFilter("kSketchCurveSplineFilter", 16133, Filters)
        AddFilter("kSketchDefaultFilter", 16135, Filters)
        AddFilter("kSketchDimConstraintFilter", 16128, Filters)
        AddFilter("kSketchImageFilter", 16137, Filters)
        AddFilter("kSketchObjectFilter", 16136, Filters)
        AddFilter("kSketchPointFilter", 16134, Filters)
        AddFilter("kSketchProfileFilter", 16139, Filters)
        AddFilter("kSketchProjectedCutFilter", 16140, Filters)
        AddFilter("kSketchTextBoxFilter", 16138, Filters)
        AddFilter("kUserCoordinateSystemFilter", 16387, Filters)
        AddFilter("kWorkAxisFilter", 16384, Filters)
        AddFilter("kWorkPlaneFilter", 16385, Filters)
        AddFilter("kWorkPointFilter", 16386, Filters)
    End Sub
End Module