
TextClientGraphps.dll: dlldata.obj TextClientGraph_p.obj TextClientGraph_i.obj
	link /dll /out:TextClientGraphps.dll /def:TextClientGraphps.def /entry:DllMain dlldata.obj TextClientGraph_p.obj TextClientGraph_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del TextClientGraphps.dll
	@del TextClientGraphps.lib
	@del TextClientGraphps.exp
	@del dlldata.obj
	@del TextClientGraph_p.obj
	@del TextClientGraph_i.obj
