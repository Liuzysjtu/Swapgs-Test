#include<ntifs.h>
#include<ntddk.h>

EXTERN_C void my_swapgs(UINT64* gs_base, UINT64* kernerl_gs_base);

VOID Unload(PDRIVER_OBJECT pDriverObject) {
	UNREFERENCED_PARAMETER(pDriverObject);
}

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath) {

	UNREFERENCED_PARAMETER(pRegistryPath);
	pDriverObject->DriverUnload = Unload;

	UINT64 old_kernel_gs_base = 0, old_gs_base = 0, new_kernel_gs_base = 0, new_gs_base = 0;
	my_swapgs(&old_gs_base, &old_kernel_gs_base);
	my_swapgs(&new_gs_base, &new_kernel_gs_base);

	DbgPrint("Old GS Base: %p, Old Kernel GS Base: %p\n", old_gs_base, old_kernel_gs_base);
	DbgPrint("New GS Base: %p, New Kernel GS Base: %p\n", new_gs_base, new_kernel_gs_base);

	return STATUS_SUCCESS;
}