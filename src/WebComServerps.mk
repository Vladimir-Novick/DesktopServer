
WebComServerps.dll: dlldata.obj WebComServer_p.obj WebComServer_i.obj
	link /dll /out:WebComServerps.dll /def:WebComServerps.def /entry:DllMain dlldata.obj WebComServer_p.obj WebComServer_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del WebComServerps.dll
	@del WebComServerps.lib
	@del WebComServerps.exp
	@del dlldata.obj
	@del WebComServer_p.obj
	@del WebComServer_i.obj
