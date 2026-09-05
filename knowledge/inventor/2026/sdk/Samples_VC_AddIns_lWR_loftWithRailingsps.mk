
loftWithRailingsps.dll: dlldata.obj loftWithRailings_p.obj loftWithRailings_i.obj
	link /dll /out:loftWithRailingsps.dll /def:loftWithRailingsps.def /entry:DllMain dlldata.obj loftWithRailings_p.obj loftWithRailings_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del loftWithRailingsps.dll
	@del loftWithRailingsps.lib
	@del loftWithRailingsps.exp
	@del dlldata.obj
	@del loftWithRailings_p.obj
	@del loftWithRailings_i.obj
