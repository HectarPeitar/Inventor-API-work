//-----------------------------------------------------------------------------
//----- (c) 2005-2015 Autodesk, Inc.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
function OnFinish (selProj, selObj) {
	try {
		var strProjectPath =wizard.FindSymbol ('PROJECT_PATH') ;
		var strProjectName =wizard.FindSymbol ('PROJECT_NAME') ;
		wizard.AddSymbol ("UPPER_CASE_PROJECT_NAME", strProjectName.toUpperCase ()) ;

		//- WIZARDS_VERSION
		wizard.AddSymbol ("WIZARDS_VERSION", "18.0.0.0") ;

		//Add read me file.
		AddReadMeFile(strProjectPath);
	        //Add Autodesk.XXX.Inventor.addin manifest file    
		var strManifestFile = AddCustomManifestFile(strProjectPath, strProjectName);			
		
		selProj =CreateCustomProject (strProjectName, strProjectPath) ;
		AddConfig (selProj, strProjectName, strManifestFile) ;
		AddFilters(selProj);
		
		var InfFile =CreateCustomInfFile () ;
		AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
		PchSettings (selProj) ;
		InfFile.Delete () ;
		
		selProj.Object.Save () ;
	} catch (e) {
		if ( e.description.length != 0 )
			SetErrorInfo (e) ;
		return (e.number) ;
	}
}

//-----------------------------------------------------------------------------
function CreateCustomProject (strProjectName, strProjectPath) {
	try {
		var strProjTemplatePath =wizard.FindSymbol ('PROJECT_TEMPLATE_PATH') ;
		var strProjTemplate =strProjTemplatePath + '\\default.vcxproj' ;

		var Solution =dte.Solution ;
		var strSolutionName ='' ;
		if ( wizard.FindSymbol ('CLOSE_SOLUTION') ) {
			Solution.Close () ;
			strSolutionName =wizard.FindSymbol ('VS_SOLUTION_NAME') ;
			if ( strSolutionName.length ) {
				var strSolutionPath =strProjectPath.substr (0, strProjectPath.length - strProjectName.length) ;
				Solution.Create (strSolutionPath, strSolutionName) ;
			}
		}

		var strProjectNameWithExt ='' ;
		strProjectNameWithExt =strProjectName + '.vcxproj' ;

		var oTarget =wizard.FindSymbol ('TARGET') ;
		var prj ;
		if ( wizard.FindSymbol ('WIZARD_TYPE') == vsWizardAddSubProject ) { //----- vsWizardAddSubProject
			var prjItem =oTarget.AddFromTemplate (strProjTemplate, strProjectNameWithExt) ;
			prj =prjItem.SubProject ;
		} else {
			prj =oTarget.AddFromTemplate (strProjTemplate, strProjectPath, strProjectNameWithExt) ;
		}
		return (prj) ;
	} catch (e) {
		throw e ;
	}
}

//-----------------------------------------------------------------------------
function AddFilters (proj) {
	try 	{
		//----- Add the folders to your project
		var group =proj.Object.AddFilter ('Source Files') ;
		group.Filter ='cpp;c;cc;cxx;def;idl;odl' ;
		
		group =proj.Object.AddFilter ('Include Files') ;
		group.Filter ='h;hh;hxx' ;
		
		group =proj.Object.AddFilter ('Resource Files') ;
		group.Filter ='rc;ico;bmp;cur;jpg;gif' ;

		group =proj.Object.AddFilter ('Miscellaneous Files') ;
		group.Filter ='reg;rgs;mak;clw;vsdir;vsz;css;inf;vcxproj;csproj' ;
	} catch (e) {
		throw e ;
	}
}

//-----------------------------------------------------------------------------
function AddConfig (proj, strProjectName, strManifestFile) {
	var strSPitManifestFile = strManifestFile.split('\\');
	var strMaifestFileShortName = strSPitManifestFile[strSPitManifestFile.length-1]
	
	try {
		var szRds =wizard.FindSymbol ('RDS_SYMB') ;
		var bUseMfc =wizard.FindSymbol ('USE_MFC') ;
		var bUseAtl =wizard.FindSymbol ('USE_ATL') ;
		var szUprProjectName =strProjectName.toUpperCase () ;
	
		//Win32 configurations
		//- Debug
		var config =proj.Object.Configurations ('Debug') ;
		config.ConfigurationType =typeDynamicLibrary ;
		config.IntermediateDirectory ='Debug' ;
		config.OutputDirectory ='Debug' ;
		config.CharacterSet =charSetUnicode ;

		if ( bUseMfc )
			config.useOfMfc =useMfcDynamic ;
		else
			config.useOfMfc =useMfcStdWin ;
		if ( bUseAtl )
			config.useOfAtl =useATLDynamic ;
			
		//- Searching Inventor EXE
		var regkey =new ActiveXObject ('WScript.Shell') ;
		var strInventor ='' ;
		var strInventorBinPath ='' ;
		var strInventorSDKIncludePath = '';	
		try {
			strInventor =regkey.RegRead ('HKEY_CURRENT_USER\\Software\\Autodesk\\Inventor\\Current Version\\Executable') ;
			strInventorBinPath =strInventor.substr (0, strInventor.lastIndexOf ("\\")) ;
		} catch (e) {
			strInventorBinPath ='r:\\lib\debug' ;
		}

		try {
			strInventorSDKIncludePath =regkey.RegRead ('HKEY_CURRENT_USER\\Software\\Autodesk\\Inventor Developer Tools\\18.0\\InstallPath') ;
			strInventorSDKIncludePath +='DeveloperTools\\Include' ;
		} catch (e) {
			strInventorSDKIncludePath ='C:\\Program Files\\Autodesk\\Inventor 2026\\SDK\\DeveloperTools\\Include' + ';' ;
			strInventorSDKIncludePath +='C:\\Users\\Public\\Documents\\Autodesk\\Inventor 2026\\SDK\\DeveloperTools\\Include' ;
		}


		var strInventorAddinsPath = '';
		// Inventor Version Dependent: "Addins" folder in installation all users area:
		// The presence of a manifest file in the following locations indicates that the add-in should be loaded in a specific
		// version of Inventor.  The values of the "SupportedSoftwareVersionXXX" settings in the manifest file are ignored, if present.
		//  Windows XP:
		//  C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor [Version]\Addins\
		//  Windows7/Vista:
		//  C:\ProgramData\Autodesk\Inventor [Version]\Addins		
		var strInventorVersionDependentAddinsPath = '';
		// Inventor Version Independent: "Inventor Addins" folder in all users area
		// The presence of a manifest file in the following locations indicates that the add-in should be loaded in
		// multiple versions of Inventor based on the values of the "SupportedSoftwareVersionXXX" settings in the manifest file.
		//  Windows XP:
		//  C:\Documents and Settings\All Users\Application Data\Autodesk\Inventor Addins\
		//  Windows7/Vista:
		//  C:\ProgramData\Autodesk\Inventor Addins
		var strInventorVersionUndependentAddinsPath = '';
		
		try {
		    if(strInventor.substr(0, 1) == 'R' || strInventor.substr(0, 1) == 'r') {
		        strInventorAddinsPath = strInventorBinPath + '\\Addins\\';
		    }
		    else {
		        var objShell = new ActiveXObject("Shell.Application");
		        var ssfCommonAppdata = 35;
		        var strCommonDataPath = objShell.Namespace(ssfCommonAppdata);
		        strCommonDataPath = strCommonDataPath.items();
		        strCommonDataPath = strCommonDataPath.item();
		        strCommonDataPath = strCommonDataPath.Path;
		        strInventorVersionDependentAddinsPath = strCommonDataPath + '\\Autodesk\\Inventor 2026\\Addins\\';
		        strInventorVersionUndependentAddinsPath = strCommonDataPath + '\\Autodesk\\Inventor Addins\\'
		        strInventorAddinsPath = strInventorVersionUndependentAddinsPath;
		    }
		} catch (e) {
		        strInventorAddinsPath = strInventorBinPath + '\\Addins\\';
		}
		
		var CLTool =config.Tools ('VCCLCompilerTool') ;
		CLTool.DebugInformationFormat =debugEditAndContinue ;
		CLTool.WarningLevel =warningLevel_1 ;
		CLTool.Detect64BitPortabilityProblems =false ;
		CLTool.Optimization =optimizeDisabled ;
		CLTool.MinimalRebuild =true ;
		CLTool.StringPooling =false ;
		CLTool.BasicRuntimeChecks =runtimeBasicCheckAll/*runtimeBasicCheckNone*/ ;
		CLTool.BufferSecurityCheck =true ;
		CLTool.RuntimeLibrary =rtMultiThreadedDebugDLL ;
		CLTool.RuntimeTypeInfo =true ;
		CLTool.UsePrecompiledHeader =pchUseUsingSpecific ;
		//CLTool.PrecompiledHeaderFile ="StdAfx.h" ;
		CLTool.PreprocessorDefinitions ='WIN32;_WINDOWS;_DEBUG;' + szUprProjectName + '_MODULE' ;
        CLTool.PreprocessorDefinitions +=';_UNICODE;UNICODE' ;
		if ( bUseMfc )
			CLTool.PreprocessorDefinitions +=';_AFXDLL;_USRDLL' ;
		CLTool.AdditionalIncludeDirectories +=strInventorBinPath + ';' + strInventorSDKIncludePath ;
		//- Linker
		var LinkTool =config.Tools ('VCLinkerTool') ;
		LinkTool.LinkIncremental =linkIncrementalYes ;

		LinkTool.OutputFile ='$(outdir)/' + szRds + strProjectName + '.dll' ;
		LinkTool.LinkDLL = true;
		
		LinkTool.EnableUAC = false;
		LinkTool.SubSystem =subSystemWindows ;
		LinkTool.GenerateDebugInformation =true ;
		LinkTool.ProgramDatabaseFile ='$(OutDir)/' + szRds + strProjectName + '.pdb' ;
		LinkTool.ImportLibrary ='$(OutDir)/' + szRds + strProjectName + '.lib' ;
		LinkTool.TargetMachine =machineX86 ;
		//- Midl
		var MidlTool =config.Tools ("VCMidlTool") ;
		MidlTool.MkTypLibCompatible =false ;
		MidlTool.TargetEnvironment =midlTargetWin32 ;
		MidlTool.PreprocessorDefinitions ='_DEBUG' ;
		MidlTool.HeaderFileName =strProjectName + '.h'  ;
		MidlTool.InterfaceIdentifierFileName =strProjectName + '_i.c' ;
		MidlTool.ProxyFileName =strProjectName + '_p.c' ;
		MidlTool.GenerateStublessProxies =true ;
		MidlTool.GenerateTypeLibrary  =true ;
		MidlTool.TypeLibraryName ='$(IntDir)/' + szRds + strProjectName + '.tlb' ;
		MidlTool.DLLDataFileName ='' ;
		//- Post Build action
		
		var PostBuildTool =config.Tools ('VCPostBuildEventTool') ;
		PostBuildTool.Description = 'Copy OutputFile and ManifestFile';

		var strCommandLine = 'if not exist \"' + strInventorAddinsPath +'\" md \"' + strInventorAddinsPath +'\"';
		strCommandLine = strCommandLine + '\r\ncopy /Y \"' + '$(ProjectDir)' + strMaifestFileShortName + '\" \"' + strInventorAddinsPath + '\"';
		PostBuildTool.CommandLine = strCommandLine;
		// Resources
		var RCTool =config.Tools ('VCResourceCompilerTool') ;
		RCTool.Culture =rcEnglishUS ;
		RCTool.AdditionalIncludeDirectories ='$(IntDir)' ;
		RCTool.PreprocessorDefinitions ='_DEBUG' ;
		//- Debugger
		var DebugTool =config.DebugSettings
		DebugTool.Command =strInventor ;
		
		//----- Pseudo Debug

		proj.Object.AddConfiguration('PseudoDebug');
		var debugConfig = config;
		config = proj.Object.Configurations('PseudoDebug');
		debugConfig.CopyTo(config);
		config.IntermediateDirectory = 'PseudoDebug';
		config.OutputDirectory = 'PseudoDebug';

		CLTool = config.Tools('VCCLCompilerTool');
		CLTool.RuntimeLibrary = rtMultiThreadedDLL;
		CLTool.PreprocessorDefinitions += ';PSEUDO_DEBUG';
		
		//----- Release
		config =proj.Object.Configurations ('Release') ;

		config.ConfigurationType =typeDynamicLibrary ;

		config.IntermediateDirectory ='Release' ;
		config.OutputDirectory ='Release' ;

		config.CharacterSet =charSetUnicode ;

		if ( bUseMfc )
			config.useOfMfc =useMfcDynamic ;
		else
			config.useOfMfc =useMfcStdWin ;
		if ( bUseAtl )
			config.useOfAtl =useATLDynamic ;
		//- Compiler
		CLTool =config.Tools('VCCLCompilerTool') ;
		CLTool.DebugInformationFormat =debugDisabled ;
		CLTool.WarningLevel =warningLevel_1 ;
		CLTool.Detect64BitPortabilityProblems =false ;
		CLTool.Optimization =optimizeMaxSpeed/*optimizeFull*//*optimizeDisabled*/ ;
		CLTool.MinimalRebuild =false ;
		CLTool.StringPooling =true ;
		CLTool.BasicRuntimeChecks =/*runtimeBasicCheckAll*/runtimeBasicCheckNone ;
		CLTool.BufferSecurityCheck =false ;
		CLTool.RuntimeLibrary =rtMultiThreadedDLL ;
		CLTool.RuntimeTypeInfo =true ;
		CLTool.UsePrecompiledHeader =pchUseUsingSpecific ;
		//CLTool.PrecompiledHeaderFile ="StdAfx.h" ;
		CLTool.PreprocessorDefinitions ='WIN32;_WINDOWS;NDEBUG;' + szUprProjectName + '_MODULE' ;

		CLTool.PreprocessorDefinitions +=';_UNICODE;UNICODE' ;
		if ( bUseMfc )
			CLTool.PreprocessorDefinitions +=';_AFXDLL;_USRDLL' ;
		CLTool.AdditionalIncludeDirectories +=strInventorBinPath + ';' + strInventorSDKIncludePath ;
		//- Linker
		LinkTool =config.Tools ('VCLinkerTool') ;
		LinkTool.LinkIncremental =linkIncrementalYes ;

		LinkTool.OutputFile = '$(outdir)/' + szRds + strProjectName + '.dll';
		LinkTool.LinkDLL = true;

		LinkTool.EnableUAC = false;
		LinkTool.SubSystem =subSystemWindows ;
		LinkTool.GenerateDebugInformation =false ;
		LinkTool.ProgramDatabaseFile ='' ;
		LinkTool.ImportLibrary ='$(OutDir)/' + szRds + strProjectName + '.lib' ;
		LinkTool.TargetMachine =machineX86 ;
		//- Midl
		MidlTool =config.Tools ('VCMidlTool') ;
		MidlTool.MkTypLibCompatible =false ;
		MidlTool.TargetEnvironment =midlTargetWin32 ;
		MidlTool.PreprocessorDefinitions ='NDEBUG' ;
		MidlTool.HeaderFileName =strProjectName + '.h' ;
		MidlTool.InterfaceIdentifierFileName =strProjectName + '_i.c' ;
		MidlTool.ProxyFileName =strProjectName + '_p.c' ;
		MidlTool.GenerateStublessProxies =true ;
		MidlTool.GenerateTypeLibrary  =true ;
		MidlTool.TypeLibraryName ='$(IntDir)/' + szRds + strProjectName + '.tlb' ;
		MidlTool.DLLDataFileName ='' ;
		//- Post Build action
		PostBuildTool = config.Tools('VCPostBuildEventTool');
		PostBuildTool.Description = 'Copy OutputFile and ManifestFile';

		PostBuildTool.CommandLine = strCommandLine;
		//- Resources
		RCTool =config.Tools ('VCResourceCompilerTool') ;
		RCTool.Culture =rcEnglishUS ;
		RCTool.AdditionalIncludeDirectories ='$(IntDir)' ;
		RCTool.PreprocessorDefinitions ='NDEBUG' ;
		//- Debugger
		DebugTool =config.DebugSettings ;
		DebugTool.Command =strInventor ;

		//x64 configurations
		proj.Object.AddPlatform('x64');

		config = proj.Object.Configurations('Debug|x64');
	
		// Inherit the x64 project settings from Win32 so that
		// we don't have to set every property manually
		proj.Object.Configurations('Debug|Win32').CopyTo(config);

		//- Compiler
		CLTool =config.Tools('VCCLCompilerTool') ;
		CLTool.PreprocessorDefinitions ='_WIN64;_WINDOWS;_DEBUG;' + szUprProjectName + '_MODULE' ;

		CLTool.PreprocessorDefinitions +=';_UNICODE;UNICODE' ;
		if ( bUseMfc )
			CLTool.PreprocessorDefinitions +=';_AFXDLL;_USRDLL' ;
	
		//- Linker
		LinkTool =config.Tools ('VCLinkerTool') ;
		LinkTool.TargetMachine =machineAMD64 ;
		//- Midl
		MidlTool =config.Tools ('VCMidlTool') ;
		MidlTool.TargetEnvironment =midlTargetAMD64 ;

		config.ConfigurationType =typeDynamicLibrary ;

		//--------Release|x64

		config = proj.Object.Configurations('Release|x64');
	
		// Inherit the x64 project settings from Win32 so that
		// we don't have to set every property manually
		proj.Object.Configurations('Release|Win32').CopyTo(config);

		//- Compiler
		CLTool =config.Tools('VCCLCompilerTool') ;
		CLTool.PreprocessorDefinitions ='_WIN64;_WINDOWS;NDEBUG;' + szUprProjectName + '_MODULE' ;

		CLTool.PreprocessorDefinitions +=';_UNICODE;UNICODE' ;
		if ( bUseMfc )
			CLTool.PreprocessorDefinitions +=';_AFXDLL;_USRDLL' ;
	
		//- Linker
		LinkTool =config.Tools ('VCLinkerTool') ;
		LinkTool.TargetMachine =machineAMD64 ;
		//- Midl
		MidlTool =config.Tools ('VCMidlTool') ;
		MidlTool.TargetEnvironment =midlTargetAMD64 ;

		config.ConfigurationType =typeDynamicLibrary ;

	} catch (e) {
		throw e ;
	}
}

//-----------------------------------------------------------------------------
function PchSettings (proj) {
	try {
			//- Win32
			var FileTool =GetFileTool (proj, 'Debug|Win32', 'StdAfx.cpp') ;
			FileTool.UsePrecompiledHeader =pchCreateUsingSpecific ;
			FileTool =GetFileTool (proj, 'Release|Win32', 'StdAfx.cpp') ;
			FileTool.UsePrecompiledHeader =pchCreateUsingSpecific ;
			//- x64
			var FileTool =GetFileTool (proj, 'Debug|x64', 'StdAfx.cpp') ;
   			if ( FileTool != null )
				FileTool.UsePrecompiledHeader =pchCreateUsingSpecific ;
			FileTool =GetFileTool (proj, 'Release|x64', 'StdAfx.cpp') ;
            if ( FileTool != null )
				FileTool.UsePrecompiledHeader =pchCreateUsingSpecific ;
	} catch (e) {
		throw e ;
	}
}

//-----------------------------------------------------------------------------
function DelFile (fso, strWizTempFile) {
	try {
		if ( fso.FileExists (strWizTempFile) ) {
			var tmpFile =fso.GetFile (strWizTempFile) ;
			tmpFile.Delete () ;
		}
	} catch (e) {
		throw e ;
	}
}

//-----------------------------------------------------------------------------
function CreateCustomInfFile () {
	try {
		var fso, TemplatesFolder, TemplateFiles, strTemplate ;
		fso =new ActiveXObject ('Scripting.FileSystemObject') ;

		var TemporaryFolder =2 ;
		var tfolder =fso.GetSpecialFolder (TemporaryFolder) ;
		var strTempFolder =tfolder.Drive + '\\' + tfolder.Name ;

		var strWizTempFile =strTempFolder + '\\' + fso.GetTempName () ;

		var strTemplatePath =wizard.FindSymbol ('TEMPLATES_PATH') ;
		var strInfFile =strTemplatePath + '\\Templates.inf' ;
		wizard.RenderTemplate (strInfFile, strWizTempFile) ;

		var WizTempFile =fso.GetFile (strWizTempFile) ;
		return (WizTempFile) ;
	} catch (e) {
		throw e ;
	}
}

//-----------------------------------------------------------------------------
function AddCustomManifestFile(strProjectPath, strProjectName) {
    var strWizManifestFile = strProjectPath + '\\' + 'Autodesk.' + strProjectName + '.Inventor.addin';
    var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
    var strManifestFile = strTemplatePath + '\\Autodesk.root.Inventor.addin';
    wizard.RenderTemplate(strManifestFile, strWizManifestFile);
    return strWizManifestFile;
}

//-----------------------------------------------------------------------------
function AddReadMeFile(strProjectPath) {
    var strReadMeFile= strProjectPath + '\\' + 'Readme.txt';
    var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
    var strReadMeTemplate= strTemplatePath + '\\Readme.txt';
    wizard.RenderTemplate(strReadMeTemplate, strReadMeFile );
}


//-----------------------------------------------------------------------------
function GetTargetName (strName, strProjectName) {
	try {
		//----- Set the name of the rendered file based on the template filename
		var strTarget =strName ;

		if ( strName.substr (0, 4) == 'root' )
			strTarget =strProjectName + strName.substr (4, strName.length - 4) ;
			
		if ( strName.substr (0, 11) == 'AddInServer' ) {
			var i =strName.indexOf ('.') ;
			strTarget =wizard.FindSymbol ('ADDIN_NAME') + strName.substr (i);
		}

		return (strTarget) ;
	} catch (e) {
		throw e ;
	}
}

//-----------------------------------------------------------------------------
function AddFilesToCustomProj (proj, strProjectName, strProjectPath, InfFile) {
	try {
		var projItems =proj.ProjectItems ;

		var strTemplatePath =wizard.FindSymbol ('TEMPLATES_PATH') ;

		var strTpl ='' ;
		var strName ='' ;

		var strTextStream =InfFile.OpenAsTextStream (1, -2) ;
		while ( !strTextStream.AtEndOfStream ) {
			strTpl =strTextStream.ReadLine () ;
			if ( strTpl != '' ) {
				strName =strTpl ;
				var strTarget =GetTargetName(strName, strProjectName) ;
				var strTemplate =strTemplatePath + '\\' + strTpl ;
				var strFile =strProjectPath + '\\' + strTarget ;

				var bCopyOnly =false ;  //----- "true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
				var strExt =strName.substr (strName.lastIndexOf ('.')) ;
				if ( strExt == '.bmp' || strExt==".ico" || strExt=='.gif' || strExt=='.rtf' || strExt=='.css' )
					bCopyOnly =true ;
				wizard.RenderTemplate (strTemplate, strFile, bCopyOnly) ;
				proj.Object.AddFile (strFile) ;
			}
		}
		strTextStream.Close () ;
	} catch (e) {
		throw e ;
	}
}

function RemoveFileFromProject (proj, FileName) {
	try {
		var col =proj.Object.Files ;
		var file =col.Item (FileName) ;
		if ( file != null )
			proj.Object.RemoveFile (file) ;
	} catch (e) {
		throw e ;
	}
}

function GetFileTool (proj, Config, FileName) {
	try {
		var col =proj.Object.Files ;
		var file =col.Item (FileName) ;
		var config =file.FileConfigurations.Item (Config) ;
		if ( config == null )
		    return (null) ;
		var tool =config.Tool
		return (tool)
	} catch (e) {
		throw e ;
		return (null) ;
	}
}