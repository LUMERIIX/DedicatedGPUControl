//
// Getting Nvidia GPU Usage
//
// Reference: Open Hardware Monitor (http://code.google.com/p/open-hardware-monitor)
//

#include <windows.h>
#include <iostream>
#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <string>

// magic numbers, do not change them
#define NVAPI_MAX_PHYSICAL_GPUS   64
#define NVAPI_MAX_USAGES_PER_GPU  34
#define UsageThreshold 60

// function pointer types
typedef int *(*NvAPI_QueryInterface_t)(unsigned int offset);
typedef int (*NvAPI_Initialize_t)();
typedef int (*NvAPI_EnumPhysicalGPUs_t)(int **handles, int *count);
typedef int (*NvAPI_GPU_GetUsages_t)(int *handle, unsigned int *usages);

void enableGPU()
{
    system("start powershell.exe C:\\data\Scripts\DedicatedGPUControl\src\En!En_DedicatedGPU.ps1 1");
    system("cls");
}

void disableGPU()
{
    system("start powershell.exe C:\\data\Scripts\DedicatedGPUControl\src\En!En_DedicatedGPU.ps1 0");
    system("cls");
}

int main()
{
//    HMODULE hmod = LoadLibraryA("nvapi.dll");
    HMODULE hmod = LoadLibraryA("nvapi.dll");
    if (hmod == NULL)
    {
        std::cerr << "Couldn't find nvapi.lib" << std::endl;
        return 1;
    }

    // nvapi.lib internal function pointers
    NvAPI_QueryInterface_t      NvAPI_QueryInterface     = NULL;
    NvAPI_Initialize_t          NvAPI_Initialize         = NULL;
    NvAPI_EnumPhysicalGPUs_t    NvAPI_EnumPhysicalGPUs   = NULL;
    NvAPI_GPU_GetUsages_t       NvAPI_GPU_GetUsages      = NULL;

    // nvapi_QueryInterface is a function used to retrieve other internal functions in nvapi.lib
    NvAPI_QueryInterface = (NvAPI_QueryInterface_t) GetProcAddress(hmod, "nvapi_QueryInterface");

    // some useful internal functions that aren't exported by nvapi.lib
    NvAPI_Initialize = (NvAPI_Initialize_t) (*NvAPI_QueryInterface)(0x0150E828);
    NvAPI_EnumPhysicalGPUs = (NvAPI_EnumPhysicalGPUs_t) (*NvAPI_QueryInterface)(0xE5AC921F);
    NvAPI_GPU_GetUsages = (NvAPI_GPU_GetUsages_t) (*NvAPI_QueryInterface)(0x189A1FDF);

    if (NvAPI_Initialize == NULL || NvAPI_EnumPhysicalGPUs == NULL ||
        NvAPI_EnumPhysicalGPUs == NULL || NvAPI_GPU_GetUsages == NULL)
    {
        std::cerr << "Couldn't get functions in nvapi.lib" << std::endl;
        return 2;
    }

    // initialize NvAPI library, call it once before calling any other NvAPI functions
    (*NvAPI_Initialize)();

    int          gpuCount = 0;
    int         *gpuHandles[NVAPI_MAX_PHYSICAL_GPUS] = { NULL };
    unsigned int gpuUsages[NVAPI_MAX_USAGES_PER_GPU] = { 0 };

    // gpuUsages[0] must be this value, otherwise NvAPI_GPU_GetUsages won't work
    gpuUsages[0] = (NVAPI_MAX_USAGES_PER_GPU * 4) | 0x10000;

    (*NvAPI_EnumPhysicalGPUs)(gpuHandles, &gpuCount);

    // print GPU usage every second
	int usages[NVAPI_MAX_PHYSICAL_GPUS];
	bool enabled[NVAPI_MAX_PHYSICAL_GPUS] = {false};

	system("start powershell.exe Set-ExecutionPolicy RemoteSigned \n"); //set PS Policy

	while(1) //in Background
	{
		for(int j=1; j < gpuCount; j++) ///Device 0 shouldn't be disabled
		{
			(*NvAPI_GPU_GetUsages)(gpuHandles[j], gpuUsages);
			usages[j] = gpuUsages[3];
//			std::cout << "GPU Usage" << j << ": " << usages[j] << std::endl;
			if(usages[j] < UsageThreshold && enabled[j])
            {
//                disableGPU();
                enabled[j] = false;
            }

            else if(!enabled[j])
            {
//                enableGPU();
                enabled[j] = true;
            }
		}
	Sleep(1000);    ///decrease log speed to reduce system load of script in Background
	}

    return 0;
}
