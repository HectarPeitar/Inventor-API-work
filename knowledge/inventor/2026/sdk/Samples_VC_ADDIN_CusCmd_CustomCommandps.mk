
CustomCommandps.dll: dlldata.obj CustomCommand_p.obj CustomCommand_i.obj
	link /dll /out:CustomCommandps.dll /def:CustomCommandps.def /entry:DllMain dlldata.obj CustomCommand_p.obj CustomCommand_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del CustomCommandps.dll
	@del CustomCommandps.lib
	@del CustomCommandps.exp
	@del dlldata.obj
	@del CustomCommand_p.obj
	@del CustomCommand_i.obj
