#include <windows.h>
#include "cuda_wrap.h"

typedef CUresult(__stdcall *pcuGetErrorString)(CUresult error, const char **pStr);
typedef CUresult(__stdcall *pcuGetErrorName)(CUresult error, const char **pStr);
typedef CUresult(__stdcall *pcuInit)(unsigned int Flags);
typedef CUresult(__stdcall *pcuDriverGetVersion)(int *driverVersion);
typedef CUresult(__stdcall *pcuDeviceGet)(CUdevice *device, int ordinal);
typedef CUresult(__stdcall *pcuDeviceGetCount)(int *count);
typedef CUresult(__stdcall *pcuDeviceGetName)(char *name, int len, CUdevice dev);
typedef CUresult(__stdcall *pcuDeviceGetUuid)(CUuuid *uuid, CUdevice dev);
typedef CUresult(__stdcall *pcuDeviceGetLuid)(char *luid, unsigned int *deviceNodeMask, CUdevice dev);
typedef CUresult(__stdcall *pcuDeviceTotalMem_v2)(size_t *bytes, CUdevice dev);
typedef CUresult(__stdcall *pcuDeviceGetAttribute)(int *pi, CUdevice_attribute attrib, CUdevice dev);
typedef CUresult(__stdcall *pcuDeviceGetProperties)(CUdevprop *prop, CUdevice dev);
typedef CUresult(__stdcall *pcuDeviceComputeCapability)(int *major, int *minor, CUdevice dev);
typedef CUresult(__stdcall *pcuDevicePrimaryCtxRetain)(CUcontext *pctx, CUdevice dev);
typedef CUresult(__stdcall *pcuDevicePrimaryCtxRelease)(CUdevice dev);
typedef CUresult(__stdcall *pcuDevicePrimaryCtxSetFlags)(CUdevice dev, unsigned int flags);
typedef CUresult(__stdcall *pcuDevicePrimaryCtxGetState)(CUdevice dev, unsigned int *flags, int *active);
typedef CUresult(__stdcall *pcuDevicePrimaryCtxReset)(CUdevice dev);
typedef CUresult(__stdcall *pcuCtxCreate_v2)(CUcontext *pctx, unsigned int flags, CUdevice dev);
typedef CUresult(__stdcall *pcuCtxDestroy_v2)(CUcontext ctx);
typedef CUresult(__stdcall *pcuCtxPushCurrent_v2)(CUcontext ctx);
typedef CUresult(__stdcall *pcuCtxPopCurrent_v2)(CUcontext *pctx);
typedef CUresult(__stdcall *pcuCtxSetCurrent)(CUcontext ctx);
typedef CUresult(__stdcall *pcuCtxGetCurrent)(CUcontext *pctx);
typedef CUresult(__stdcall *pcuCtxGetDevice)(CUdevice *device);
typedef CUresult(__stdcall *pcuCtxGetFlags)(unsigned int *flags);
typedef CUresult(__stdcall *pcuCtxSynchronize)();
typedef CUresult(__stdcall *pcuCtxSetLimit)(CUlimit limit, size_t value);
typedef CUresult(__stdcall *pcuCtxGetLimit)(size_t *pvalue, CUlimit limit);
typedef CUresult(__stdcall *pcuCtxGetCacheConfig)(CUfunc_cache *pconfig);
typedef CUresult(__stdcall *pcuCtxSetCacheConfig)(CUfunc_cache config);
typedef CUresult(__stdcall *pcuCtxGetSharedMemConfig)(CUsharedconfig *pConfig);
typedef CUresult(__stdcall *pcuCtxSetSharedMemConfig)(CUsharedconfig config);
typedef CUresult(__stdcall *pcuCtxGetApiVersion)(CUcontext ctx, unsigned int *version);
typedef CUresult(__stdcall *pcuCtxGetStreamPriorityRange)(int *leastPriority, int *greatestPriority);
typedef CUresult(__stdcall *pcuCtxAttach)(CUcontext *pctx, unsigned int flags);
typedef CUresult(__stdcall *pcuCtxDetach)(CUcontext ctx);
typedef CUresult(__stdcall *pcuModuleLoad)(CUmodule *module, const char *fname);
typedef CUresult(__stdcall *pcuModuleLoadData)(CUmodule *module, const void *image);
typedef CUresult(__stdcall *pcuModuleLoadDataEx)(CUmodule *module, const void *image, unsigned int numOptions, CUjit_option *options, void **optionValues);
typedef CUresult(__stdcall *pcuModuleLoadFatBinary)(CUmodule *module, const void *fatCubin);
typedef CUresult(__stdcall *pcuModuleUnload)(CUmodule hmod);
typedef CUresult(__stdcall *pcuModuleGetFunction)(CUfunction *hfunc, CUmodule hmod, const char *name);
typedef CUresult(__stdcall *pcuModuleGetGlobal_v2)(CUdeviceptr *dptr, size_t *bytes, CUmodule hmod, const char *name);
typedef CUresult(__stdcall *pcuModuleGetTexRef)(CUtexref *pTexRef, CUmodule hmod, const char *name);
typedef CUresult(__stdcall *pcuModuleGetSurfRef)(CUsurfref *pSurfRef, CUmodule hmod, const char *name);
typedef CUresult(__stdcall *pcuLinkCreate_v2)(unsigned int numOptions, CUjit_option *options, void **optionValues, CUlinkState *stateOut);
typedef CUresult(__stdcall *pcuLinkAddData_v2)(CUlinkState state, CUjitInputType type, void *data, size_t size, const char *name, unsigned int numOptions, CUjit_option *options, void **optionValues);
typedef CUresult(__stdcall *pcuLinkAddFile_v2)(CUlinkState state, CUjitInputType type, const char *path, unsigned int numOptions, CUjit_option *options, void **optionValues);
typedef CUresult(__stdcall *pcuLinkComplete)(CUlinkState state, void **cubinOut, size_t *sizeOut);
typedef CUresult(__stdcall *pcuLinkDestroy)(CUlinkState state);
typedef CUresult(__stdcall *pcuMemGetInfo_v2)(size_t *free, size_t *total);
typedef CUresult(__stdcall *pcuMemAlloc_v2)(CUdeviceptr *dptr, size_t bytesize);
typedef CUresult(__stdcall *pcuMemAllocPitch_v2)(CUdeviceptr *dptr, size_t *pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes);
typedef CUresult(__stdcall *pcuMemFree_v2)(CUdeviceptr dptr);
typedef CUresult(__stdcall *pcuMemGetAddressRange_v2)(CUdeviceptr *pbase, size_t *psize, CUdeviceptr dptr);
typedef CUresult(__stdcall *pcuMemAllocHost_v2)(void **pp, size_t bytesize);
typedef CUresult(__stdcall *pcuMemFreeHost)(void *p);
typedef CUresult(__stdcall *pcuMemHostAlloc)(void **pp, size_t bytesize, unsigned int Flags);
typedef CUresult(__stdcall *pcuMemHostGetDevicePointer_v2)(CUdeviceptr *pdptr, void *p, unsigned int Flags);
typedef CUresult(__stdcall *pcuMemHostGetFlags)(unsigned int *pFlags, void *p);
typedef CUresult(__stdcall *pcuMemAllocManaged)(CUdeviceptr *dptr, size_t bytesize, unsigned int flags);
typedef CUresult(__stdcall *pcuDeviceGetByPCIBusId)(CUdevice *dev, const char *pciBusId);
typedef CUresult(__stdcall *pcuDeviceGetPCIBusId)(char *pciBusId, int len, CUdevice dev);
typedef CUresult(__stdcall *pcuIpcGetEventHandle)(CUipcEventHandle *pHandle, CUevent event);
typedef CUresult(__stdcall *pcuIpcOpenEventHandle)(CUevent *phEvent, CUipcEventHandle handle);
typedef CUresult(__stdcall *pcuIpcGetMemHandle)(CUipcMemHandle *pHandle, CUdeviceptr dptr);
typedef CUresult(__stdcall *pcuIpcOpenMemHandle)(CUdeviceptr *pdptr, CUipcMemHandle handle, unsigned int Flags);
typedef CUresult(__stdcall *pcuIpcCloseMemHandle)(CUdeviceptr dptr);
typedef CUresult(__stdcall *pcuMemHostRegister_v2)(void *p, size_t bytesize, unsigned int Flags);
typedef CUresult(__stdcall *pcuMemHostUnregister)(void *p);
typedef CUresult(__stdcall *pcuMemcpy)(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount);
typedef CUresult(__stdcall *pcuMemcpyPeer)(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount);
typedef CUresult(__stdcall *pcuMemcpyHtoD_v2)(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount);
typedef CUresult(__stdcall *pcuMemcpyDtoH_v2)(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount);
typedef CUresult(__stdcall *pcuMemcpyDtoD_v2)(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount);
typedef CUresult(__stdcall *pcuMemcpyDtoA_v2)(CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount);
typedef CUresult(__stdcall *pcuMemcpyAtoD_v2)(CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount);
typedef CUresult(__stdcall *pcuMemcpyHtoA_v2)(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount);
typedef CUresult(__stdcall *pcuMemcpyAtoH_v2)(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount);
typedef CUresult(__stdcall *pcuMemcpyAtoA_v2)(CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount);
typedef CUresult(__stdcall *pcuMemcpy2D_v2)(const CUDA_MEMCPY2D *pCopy);
typedef CUresult(__stdcall *pcuMemcpy2DUnaligned_v2)(const CUDA_MEMCPY2D *pCopy);
typedef CUresult(__stdcall *pcuMemcpy3D_v2)(const CUDA_MEMCPY3D *pCopy);
typedef CUresult(__stdcall *pcuMemcpy3DPeer)(const CUDA_MEMCPY3D_PEER *pCopy);
typedef CUresult(__stdcall *pcuMemcpyAsync)(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream);
typedef CUresult(__stdcall *pcuMemcpyPeerAsync)(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream);
typedef CUresult(__stdcall *pcuMemcpyHtoDAsync_v2)(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount, CUstream hStream);
typedef CUresult(__stdcall *pcuMemcpyDtoHAsync_v2)(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream);
typedef CUresult(__stdcall *pcuMemcpyDtoDAsync_v2)(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream);
typedef CUresult(__stdcall *pcuMemcpyHtoAAsync_v2)(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount, CUstream hStream);
typedef CUresult(__stdcall *pcuMemcpyAtoHAsync_v2)(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream);
typedef CUresult(__stdcall *pcuMemcpy2DAsync_v2)(const CUDA_MEMCPY2D *pCopy, CUstream hStream);
typedef CUresult(__stdcall *pcuMemcpy3DAsync_v2)(const CUDA_MEMCPY3D *pCopy, CUstream hStream);
typedef CUresult(__stdcall *pcuMemcpy3DPeerAsync)(const CUDA_MEMCPY3D_PEER *pCopy, CUstream hStream);
typedef CUresult(__stdcall *pcuMemsetD8_v2)(CUdeviceptr dstDevice, unsigned char uc, size_t N);
typedef CUresult(__stdcall *pcuMemsetD16_v2)(CUdeviceptr dstDevice, unsigned short us, size_t N);
typedef CUresult(__stdcall *pcuMemsetD32_v2)(CUdeviceptr dstDevice, unsigned int ui, size_t N);
typedef CUresult(__stdcall *pcuMemsetD2D8_v2)(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height);
typedef CUresult(__stdcall *pcuMemsetD2D16_v2)(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height);
typedef CUresult(__stdcall *pcuMemsetD2D32_v2)(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height);
typedef CUresult(__stdcall *pcuMemsetD8Async)(CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream);
typedef CUresult(__stdcall *pcuMemsetD16Async)(CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream);
typedef CUresult(__stdcall *pcuMemsetD32Async)(CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream);
typedef CUresult(__stdcall *pcuMemsetD2D8Async)(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream);
typedef CUresult(__stdcall *pcuMemsetD2D16Async)(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream);
typedef CUresult(__stdcall *pcuMemsetD2D32Async)(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream);
typedef CUresult(__stdcall *pcuArrayCreate_v2)(CUarray *pHandle, const CUDA_ARRAY_DESCRIPTOR *pAllocateArray);
typedef CUresult(__stdcall *pcuArrayGetDescriptor_v2)(CUDA_ARRAY_DESCRIPTOR *pArrayDescriptor, CUarray hArray);
typedef CUresult(__stdcall *pcuArrayDestroy)(CUarray hArray);
typedef CUresult(__stdcall *pcuArray3DCreate_v2)(CUarray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR *pAllocateArray);
typedef CUresult(__stdcall *pcuArray3DGetDescriptor_v2)(CUDA_ARRAY3D_DESCRIPTOR *pArrayDescriptor, CUarray hArray);
typedef CUresult(__stdcall *pcuMipmappedArrayCreate)(CUmipmappedArray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR *pMipmappedArrayDesc, unsigned int numMipmapLevels);
typedef CUresult(__stdcall *pcuMipmappedArrayGetLevel)(CUarray *pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level);
typedef CUresult(__stdcall *pcuMipmappedArrayDestroy)(CUmipmappedArray hMipmappedArray);
typedef CUresult(__stdcall *pcuPointerGetAttribute)(void *data, CUpointer_attribute attribute, CUdeviceptr ptr);
typedef CUresult(__stdcall *pcuMemPrefetchAsync)(CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream);
typedef CUresult(__stdcall *pcuMemAdvise)(CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device);
typedef CUresult(__stdcall *pcuMemRangeGetAttribute)(void *data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count);
typedef CUresult(__stdcall *pcuMemRangeGetAttributes)(void **data, size_t *dataSizes, CUmem_range_attribute *attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count);
typedef CUresult(__stdcall *pcuPointerSetAttribute)(const void *value, CUpointer_attribute attribute, CUdeviceptr ptr);
typedef CUresult(__stdcall *pcuPointerGetAttributes)(unsigned int numAttributes, CUpointer_attribute *attributes, void **data, CUdeviceptr ptr);
typedef CUresult(__stdcall *pcuStreamCreate)(CUstream *phStream, unsigned int Flags);
typedef CUresult(__stdcall *pcuStreamCreateWithPriority)(CUstream *phStream, unsigned int flags, int priority);
typedef CUresult(__stdcall *pcuStreamGetPriority)(CUstream hStream, int *priority);
typedef CUresult(__stdcall *pcuStreamGetFlags)(CUstream hStream, unsigned int *flags);
typedef CUresult(__stdcall *pcuStreamGetCtx)(CUstream hStream, CUcontext *pctx);
typedef CUresult(__stdcall *pcuStreamWaitEvent)(CUstream hStream, CUevent hEvent, unsigned int Flags);
typedef CUresult(__stdcall *pcuStreamAddCallback)(CUstream hStream, CUstreamCallback callback, void *userData, unsigned int flags);
typedef CUresult(__stdcall *pcuStreamBeginCapture)(CUstream hStream);
typedef CUresult(__stdcall *pcuStreamEndCapture)(CUstream hStream, CUgraph *phGraph);
typedef CUresult(__stdcall *pcuStreamIsCapturing)(CUstream hStream, CUstreamCaptureStatus *captureStatus);
typedef CUresult(__stdcall *pcuStreamAttachMemAsync)(CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags);
typedef CUresult(__stdcall *pcuStreamQuery)(CUstream hStream);
typedef CUresult(__stdcall *pcuStreamSynchronize)(CUstream hStream);
typedef CUresult(__stdcall *pcuStreamDestroy_v2)(CUstream hStream);
typedef CUresult(__stdcall *pcuEventCreate)(CUevent *phEvent, unsigned int Flags);
typedef CUresult(__stdcall *pcuEventRecord)(CUevent hEvent, CUstream hStream);
typedef CUresult(__stdcall *pcuEventQuery)(CUevent hEvent);
typedef CUresult(__stdcall *pcuEventSynchronize)(CUevent hEvent);
typedef CUresult(__stdcall *pcuEventDestroy_v2)(CUevent hEvent);
typedef CUresult(__stdcall *pcuEventElapsedTime)(float *pMilliseconds, CUevent hStart, CUevent hEnd);
typedef CUresult(__stdcall *pcuImportExternalMemory)(CUexternalMemory *extMem_out, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC *memHandleDesc);
typedef CUresult(__stdcall *pcuExternalMemoryGetMappedBuffer)(CUdeviceptr *devPtr, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC *bufferDesc);
typedef CUresult(__stdcall *pcuExternalMemoryGetMappedMipmappedArray)(CUmipmappedArray *mipmap, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC *mipmapDesc);
typedef CUresult(__stdcall *pcuDestroyExternalMemory)(CUexternalMemory extMem);
typedef CUresult(__stdcall *pcuImportExternalSemaphore)(CUexternalSemaphore *extSem_out, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC *semHandleDesc);
typedef CUresult(__stdcall *pcuSignalExternalSemaphoresAsync)(const CUexternalSemaphore *extSemArray, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS *paramsArray, unsigned int numExtSems, CUstream stream);
typedef CUresult(__stdcall *pcuWaitExternalSemaphoresAsync)(const CUexternalSemaphore *extSemArray, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS *paramsArray, unsigned int numExtSems, CUstream stream);
typedef CUresult(__stdcall *pcuDestroyExternalSemaphore)(CUexternalSemaphore extSem);
typedef CUresult(__stdcall *pcuStreamWaitValue32)(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags);
typedef CUresult(__stdcall *pcuStreamWaitValue64)(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags);
typedef CUresult(__stdcall *pcuStreamWriteValue32)(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags);
typedef CUresult(__stdcall *pcuStreamWriteValue64)(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags);
typedef CUresult(__stdcall *pcuStreamBatchMemOp)(CUstream stream, unsigned int count, CUstreamBatchMemOpParams *paramArray, unsigned int flags);
typedef CUresult(__stdcall *pcuFuncGetAttribute)(int *pi, CUfunction_attribute attrib, CUfunction hfunc);
typedef CUresult(__stdcall *pcuFuncSetAttribute)(CUfunction hfunc, CUfunction_attribute attrib, int value);
typedef CUresult(__stdcall *pcuFuncSetCacheConfig)(CUfunction hfunc, CUfunc_cache config);
typedef CUresult(__stdcall *pcuFuncSetSharedMemConfig)(CUfunction hfunc, CUsharedconfig config);
typedef CUresult(__stdcall *pcuLaunchKernel)(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void **kernelParams, void **extra);
typedef CUresult(__stdcall *pcuLaunchCooperativeKernel)(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void **kernelParams);
typedef CUresult(__stdcall *pcuLaunchCooperativeKernelMultiDevice)(CUDA_LAUNCH_PARAMS *launchParamsList, unsigned int numDevices, unsigned int flags);
typedef CUresult(__stdcall *pcuLaunchHostFunc)(CUstream hStream, CUhostFn fn, void *userData);
typedef CUresult(__stdcall *pcuFuncSetBlockShape)(CUfunction hfunc, int x, int y, int z);
typedef CUresult(__stdcall *pcuFuncSetSharedSize)(CUfunction hfunc, unsigned int bytes);
typedef CUresult(__stdcall *pcuParamSetSize)(CUfunction hfunc, unsigned int numbytes);
typedef CUresult(__stdcall *pcuParamSeti)(CUfunction hfunc, int offset, unsigned int value);
typedef CUresult(__stdcall *pcuParamSetf)(CUfunction hfunc, int offset, float value);
typedef CUresult(__stdcall *pcuParamSetv)(CUfunction hfunc, int offset, void *ptr, unsigned int numbytes);
typedef CUresult(__stdcall *pcuLaunch)(CUfunction f);
typedef CUresult(__stdcall *pcuLaunchGrid)(CUfunction f, int grid_width, int grid_height);
typedef CUresult(__stdcall *pcuLaunchGridAsync)(CUfunction f, int grid_width, int grid_height, CUstream hStream);
typedef CUresult(__stdcall *pcuParamSetTexRef)(CUfunction hfunc, int texunit, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuGraphCreate)(CUgraph *phGraph, unsigned int flags);
typedef CUresult(__stdcall *pcuGraphAddKernelNode)(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_KERNEL_NODE_PARAMS *nodeParams);
typedef CUresult(__stdcall *pcuGraphKernelNodeGetParams)(CUgraphNode hNode, CUDA_KERNEL_NODE_PARAMS *nodeParams);
typedef CUresult(__stdcall *pcuGraphKernelNodeSetParams)(CUgraphNode hNode, const CUDA_KERNEL_NODE_PARAMS *nodeParams);
typedef CUresult(__stdcall *pcuGraphAddMemcpyNode)(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_MEMCPY3D *copyParams, CUcontext ctx);
typedef CUresult(__stdcall *pcuGraphMemcpyNodeGetParams)(CUgraphNode hNode, CUDA_MEMCPY3D *nodeParams);
typedef CUresult(__stdcall *pcuGraphMemcpyNodeSetParams)(CUgraphNode hNode, const CUDA_MEMCPY3D *nodeParams);
typedef CUresult(__stdcall *pcuGraphAddMemsetNode)(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_MEMSET_NODE_PARAMS *memsetParams, CUcontext ctx);
typedef CUresult(__stdcall *pcuGraphMemsetNodeGetParams)(CUgraphNode hNode, CUDA_MEMSET_NODE_PARAMS *nodeParams);
typedef CUresult(__stdcall *pcuGraphMemsetNodeSetParams)(CUgraphNode hNode, const CUDA_MEMSET_NODE_PARAMS *nodeParams);
typedef CUresult(__stdcall *pcuGraphAddHostNode)(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_HOST_NODE_PARAMS *nodeParams);
typedef CUresult(__stdcall *pcuGraphHostNodeGetParams)(CUgraphNode hNode, CUDA_HOST_NODE_PARAMS *nodeParams);
typedef CUresult(__stdcall *pcuGraphHostNodeSetParams)(CUgraphNode hNode, const CUDA_HOST_NODE_PARAMS *nodeParams);
typedef CUresult(__stdcall *pcuGraphAddChildGraphNode)(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, CUgraph childGraph);
typedef CUresult(__stdcall *pcuGraphChildGraphNodeGetGraph)(CUgraphNode hNode, CUgraph *phGraph);
typedef CUresult(__stdcall *pcuGraphAddEmptyNode)(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies);
typedef CUresult(__stdcall *pcuGraphClone)(CUgraph *phGraphClone, CUgraph originalGraph);
typedef CUresult(__stdcall *pcuGraphNodeFindInClone)(CUgraphNode *phNode, CUgraphNode hOriginalNode, CUgraph hClonedGraph);
typedef CUresult(__stdcall *pcuGraphNodeGetType)(CUgraphNode hNode, CUgraphNodeType *type);
typedef CUresult(__stdcall *pcuGraphGetNodes)(CUgraph hGraph, CUgraphNode *nodes, size_t *numNodes);
typedef CUresult(__stdcall *pcuGraphGetRootNodes)(CUgraph hGraph, CUgraphNode *rootNodes, size_t *numRootNodes);
typedef CUresult(__stdcall *pcuGraphGetEdges)(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t *numEdges);
typedef CUresult(__stdcall *pcuGraphNodeGetDependencies)(CUgraphNode hNode, CUgraphNode *dependencies, size_t *numDependencies);
typedef CUresult(__stdcall *pcuGraphNodeGetDependentNodes)(CUgraphNode hNode, CUgraphNode *dependentNodes, size_t *numDependentNodes);
typedef CUresult(__stdcall *pcuGraphAddDependencies)(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t numDependencies);
typedef CUresult(__stdcall *pcuGraphRemoveDependencies)(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t numDependencies);
typedef CUresult(__stdcall *pcuGraphDestroyNode)(CUgraphNode hNode);
typedef CUresult(__stdcall *pcuGraphInstantiate)(CUgraphExec *phGraphExec, CUgraph hGraph, CUgraphNode *phErrorNode, char *logBuffer, size_t bufferSize);
typedef CUresult(__stdcall *pcuGraphLaunch)(CUgraphExec hGraphExec, CUstream hStream);
typedef CUresult(__stdcall *pcuGraphExecDestroy)(CUgraphExec hGraphExec);
typedef CUresult(__stdcall *pcuGraphDestroy)(CUgraph hGraph);
typedef CUresult(__stdcall *pcuOccupancyMaxActiveBlocksPerMultiprocessor)(int *numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize);
typedef CUresult(__stdcall *pcuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)(int *numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags);
typedef CUresult(__stdcall *pcuOccupancyMaxPotentialBlockSize)(int *minGridSize, int *blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit);
typedef CUresult(__stdcall *pcuOccupancyMaxPotentialBlockSizeWithFlags)(int *minGridSize, int *blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags);
typedef CUresult(__stdcall *pcuTexRefSetArray)(CUtexref hTexRef, CUarray hArray, unsigned int Flags);
typedef CUresult(__stdcall *pcuTexRefSetMipmappedArray)(CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags);
typedef CUresult(__stdcall *pcuTexRefSetAddress_v2)(size_t *ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes);
typedef CUresult(__stdcall *pcuTexRefSetAddress2D_v3)(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR *desc, CUdeviceptr dptr, size_t Pitch);
typedef CUresult(__stdcall *pcuTexRefSetFormat)(CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents);
typedef CUresult(__stdcall *pcuTexRefSetAddressMode)(CUtexref hTexRef, int dim, CUaddress_mode am);
typedef CUresult(__stdcall *pcuTexRefSetFilterMode)(CUtexref hTexRef, CUfilter_mode fm);
typedef CUresult(__stdcall *pcuTexRefSetMipmapFilterMode)(CUtexref hTexRef, CUfilter_mode fm);
typedef CUresult(__stdcall *pcuTexRefSetMipmapLevelBias)(CUtexref hTexRef, float bias);
typedef CUresult(__stdcall *pcuTexRefSetMipmapLevelClamp)(CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp);
typedef CUresult(__stdcall *pcuTexRefSetMaxAnisotropy)(CUtexref hTexRef, unsigned int maxAniso);
typedef CUresult(__stdcall *pcuTexRefSetBorderColor)(CUtexref hTexRef, float *pBorderColor);
typedef CUresult(__stdcall *pcuTexRefSetFlags)(CUtexref hTexRef, unsigned int Flags);
typedef CUresult(__stdcall *pcuTexRefGetAddress_v2)(CUdeviceptr *pdptr, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuTexRefGetArray)(CUarray *phArray, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuTexRefGetMipmappedArray)(CUmipmappedArray *phMipmappedArray, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuTexRefGetAddressMode)(CUaddress_mode *pam, CUtexref hTexRef, int dim);
typedef CUresult(__stdcall *pcuTexRefGetFilterMode)(CUfilter_mode *pfm, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuTexRefGetFormat)(CUarray_format *pFormat, int *pNumChannels, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuTexRefGetMipmapFilterMode)(CUfilter_mode *pfm, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuTexRefGetMipmapLevelBias)(float *pbias, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuTexRefGetMipmapLevelClamp)(float *pminMipmapLevelClamp, float *pmaxMipmapLevelClamp, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuTexRefGetMaxAnisotropy)(int *pmaxAniso, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuTexRefGetBorderColor)(float *pBorderColor, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuTexRefGetFlags)(unsigned int *pFlags, CUtexref hTexRef);
typedef CUresult(__stdcall *pcuTexRefCreate)(CUtexref *pTexRef);
typedef CUresult(__stdcall *pcuTexRefDestroy)(CUtexref hTexRef);
typedef CUresult(__stdcall *pcuSurfRefSetArray)(CUsurfref hSurfRef, CUarray hArray, unsigned int Flags);
typedef CUresult(__stdcall *pcuSurfRefGetArray)(CUarray *phArray, CUsurfref hSurfRef);
typedef CUresult(__stdcall *pcuTexObjectCreate)(CUtexObject *pTexObject, const CUDA_RESOURCE_DESC *pResDesc, const CUDA_TEXTURE_DESC *pTexDesc, const CUDA_RESOURCE_VIEW_DESC *pResViewDesc);
typedef CUresult(__stdcall *pcuTexObjectDestroy)(CUtexObject texObject);
typedef CUresult(__stdcall *pcuTexObjectGetResourceDesc)(CUDA_RESOURCE_DESC *pResDesc, CUtexObject texObject);
typedef CUresult(__stdcall *pcuTexObjectGetTextureDesc)(CUDA_TEXTURE_DESC *pTexDesc, CUtexObject texObject);
typedef CUresult(__stdcall *pcuTexObjectGetResourceViewDesc)(CUDA_RESOURCE_VIEW_DESC *pResViewDesc, CUtexObject texObject);
typedef CUresult(__stdcall *pcuSurfObjectCreate)(CUsurfObject *pSurfObject, const CUDA_RESOURCE_DESC *pResDesc);
typedef CUresult(__stdcall *pcuSurfObjectDestroy)(CUsurfObject surfObject);
typedef CUresult(__stdcall *pcuSurfObjectGetResourceDesc)(CUDA_RESOURCE_DESC *pResDesc, CUsurfObject surfObject);
typedef CUresult(__stdcall *pcuDeviceCanAccessPeer)(int *canAccessPeer, CUdevice dev, CUdevice peerDev);
typedef CUresult(__stdcall *pcuCtxEnablePeerAccess)(CUcontext peerContext, unsigned int Flags);
typedef CUresult(__stdcall *pcuCtxDisablePeerAccess)(CUcontext peerContext);
typedef CUresult(__stdcall *pcuDeviceGetP2PAttribute)(int* value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice);
typedef CUresult(__stdcall *pcuGraphicsUnregisterResource)(CUgraphicsResource resource);
typedef CUresult(__stdcall *pcuGraphicsSubResourceGetMappedArray)(CUarray *pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel);
typedef CUresult(__stdcall *pcuGraphicsResourceGetMappedMipmappedArray)(CUmipmappedArray *pMipmappedArray, CUgraphicsResource resource);
typedef CUresult(__stdcall *pcuGraphicsResourceGetMappedPointer_v2)(CUdeviceptr *pDevPtr, size_t *pSize, CUgraphicsResource resource);
typedef CUresult(__stdcall *pcuGraphicsResourceSetMapFlags_v2)(CUgraphicsResource resource, unsigned int flags);
typedef CUresult(__stdcall *pcuGraphicsMapResources)(unsigned int count, CUgraphicsResource *resources, CUstream hStream);
typedef CUresult(__stdcall *pcuGraphicsUnmapResources)(unsigned int count, CUgraphicsResource *resources, CUstream hStream);
typedef CUresult(__stdcall *pcuGetExportTable)(const void **ppExportTable, const CUuuid *pExportTableId);

class wrap
{
public:
pcuGetErrorString m_cuGetErrorString;
pcuGetErrorName m_cuGetErrorName;
pcuInit m_cuInit;
pcuDriverGetVersion m_cuDriverGetVersion;
pcuDeviceGet m_cuDeviceGet;
pcuDeviceGetCount m_cuDeviceGetCount;
pcuDeviceGetName m_cuDeviceGetName;
pcuDeviceGetUuid m_cuDeviceGetUuid;
pcuDeviceGetLuid m_cuDeviceGetLuid;
pcuDeviceTotalMem_v2 m_cuDeviceTotalMem_v2;
pcuDeviceGetAttribute m_cuDeviceGetAttribute;
pcuDeviceGetProperties m_cuDeviceGetProperties;
pcuDeviceComputeCapability m_cuDeviceComputeCapability;
pcuDevicePrimaryCtxRetain m_cuDevicePrimaryCtxRetain;
pcuDevicePrimaryCtxRelease m_cuDevicePrimaryCtxRelease;
pcuDevicePrimaryCtxSetFlags m_cuDevicePrimaryCtxSetFlags;
pcuDevicePrimaryCtxGetState m_cuDevicePrimaryCtxGetState;
pcuDevicePrimaryCtxReset m_cuDevicePrimaryCtxReset;
pcuCtxCreate_v2 m_cuCtxCreate_v2;
pcuCtxDestroy_v2 m_cuCtxDestroy_v2;
pcuCtxPushCurrent_v2 m_cuCtxPushCurrent_v2;
pcuCtxPopCurrent_v2 m_cuCtxPopCurrent_v2;
pcuCtxSetCurrent m_cuCtxSetCurrent;
pcuCtxGetCurrent m_cuCtxGetCurrent;
pcuCtxGetDevice m_cuCtxGetDevice;
pcuCtxGetFlags m_cuCtxGetFlags;
pcuCtxSynchronize m_cuCtxSynchronize;
pcuCtxSetLimit m_cuCtxSetLimit;
pcuCtxGetLimit m_cuCtxGetLimit;
pcuCtxGetCacheConfig m_cuCtxGetCacheConfig;
pcuCtxSetCacheConfig m_cuCtxSetCacheConfig;
pcuCtxGetSharedMemConfig m_cuCtxGetSharedMemConfig;
pcuCtxSetSharedMemConfig m_cuCtxSetSharedMemConfig;
pcuCtxGetApiVersion m_cuCtxGetApiVersion;
pcuCtxGetStreamPriorityRange m_cuCtxGetStreamPriorityRange;
pcuCtxAttach m_cuCtxAttach;
pcuCtxDetach m_cuCtxDetach;
pcuModuleLoad m_cuModuleLoad;
pcuModuleLoadData m_cuModuleLoadData;
pcuModuleLoadDataEx m_cuModuleLoadDataEx;
pcuModuleLoadFatBinary m_cuModuleLoadFatBinary;
pcuModuleUnload m_cuModuleUnload;
pcuModuleGetFunction m_cuModuleGetFunction;
pcuModuleGetGlobal_v2 m_cuModuleGetGlobal_v2;
pcuModuleGetTexRef m_cuModuleGetTexRef;
pcuModuleGetSurfRef m_cuModuleGetSurfRef;
pcuLinkCreate_v2 m_cuLinkCreate_v2;
pcuLinkAddData_v2 m_cuLinkAddData_v2;
pcuLinkAddFile_v2 m_cuLinkAddFile_v2;
pcuLinkComplete m_cuLinkComplete;
pcuLinkDestroy m_cuLinkDestroy;
pcuMemGetInfo_v2 m_cuMemGetInfo_v2;
pcuMemAlloc_v2 m_cuMemAlloc_v2;
pcuMemAllocPitch_v2 m_cuMemAllocPitch_v2;
pcuMemFree_v2 m_cuMemFree_v2;
pcuMemGetAddressRange_v2 m_cuMemGetAddressRange_v2;
pcuMemAllocHost_v2 m_cuMemAllocHost_v2;
pcuMemFreeHost m_cuMemFreeHost;
pcuMemHostAlloc m_cuMemHostAlloc;
pcuMemHostGetDevicePointer_v2 m_cuMemHostGetDevicePointer_v2;
pcuMemHostGetFlags m_cuMemHostGetFlags;
pcuMemAllocManaged m_cuMemAllocManaged;
pcuDeviceGetByPCIBusId m_cuDeviceGetByPCIBusId;
pcuDeviceGetPCIBusId m_cuDeviceGetPCIBusId;
pcuIpcGetEventHandle m_cuIpcGetEventHandle;
pcuIpcOpenEventHandle m_cuIpcOpenEventHandle;
pcuIpcGetMemHandle m_cuIpcGetMemHandle;
pcuIpcOpenMemHandle m_cuIpcOpenMemHandle;
pcuIpcCloseMemHandle m_cuIpcCloseMemHandle;
pcuMemHostRegister_v2 m_cuMemHostRegister_v2;
pcuMemHostUnregister m_cuMemHostUnregister;
pcuMemcpy m_cuMemcpy;
pcuMemcpyPeer m_cuMemcpyPeer;
pcuMemcpyHtoD_v2 m_cuMemcpyHtoD_v2;
pcuMemcpyDtoH_v2 m_cuMemcpyDtoH_v2;
pcuMemcpyDtoD_v2 m_cuMemcpyDtoD_v2;
pcuMemcpyDtoA_v2 m_cuMemcpyDtoA_v2;
pcuMemcpyAtoD_v2 m_cuMemcpyAtoD_v2;
pcuMemcpyHtoA_v2 m_cuMemcpyHtoA_v2;
pcuMemcpyAtoH_v2 m_cuMemcpyAtoH_v2;
pcuMemcpyAtoA_v2 m_cuMemcpyAtoA_v2;
pcuMemcpy2D_v2 m_cuMemcpy2D_v2;
pcuMemcpy2DUnaligned_v2 m_cuMemcpy2DUnaligned_v2;
pcuMemcpy3D_v2 m_cuMemcpy3D_v2;
pcuMemcpy3DPeer m_cuMemcpy3DPeer;
pcuMemcpyAsync m_cuMemcpyAsync;
pcuMemcpyPeerAsync m_cuMemcpyPeerAsync;
pcuMemcpyHtoDAsync_v2 m_cuMemcpyHtoDAsync_v2;
pcuMemcpyDtoHAsync_v2 m_cuMemcpyDtoHAsync_v2;
pcuMemcpyDtoDAsync_v2 m_cuMemcpyDtoDAsync_v2;
pcuMemcpyHtoAAsync_v2 m_cuMemcpyHtoAAsync_v2;
pcuMemcpyAtoHAsync_v2 m_cuMemcpyAtoHAsync_v2;
pcuMemcpy2DAsync_v2 m_cuMemcpy2DAsync_v2;
pcuMemcpy3DAsync_v2 m_cuMemcpy3DAsync_v2;
pcuMemcpy3DPeerAsync m_cuMemcpy3DPeerAsync;
pcuMemsetD8_v2 m_cuMemsetD8_v2;
pcuMemsetD16_v2 m_cuMemsetD16_v2;
pcuMemsetD32_v2 m_cuMemsetD32_v2;
pcuMemsetD2D8_v2 m_cuMemsetD2D8_v2;
pcuMemsetD2D16_v2 m_cuMemsetD2D16_v2;
pcuMemsetD2D32_v2 m_cuMemsetD2D32_v2;
pcuMemsetD8Async m_cuMemsetD8Async;
pcuMemsetD16Async m_cuMemsetD16Async;
pcuMemsetD32Async m_cuMemsetD32Async;
pcuMemsetD2D8Async m_cuMemsetD2D8Async;
pcuMemsetD2D16Async m_cuMemsetD2D16Async;
pcuMemsetD2D32Async m_cuMemsetD2D32Async;
pcuArrayCreate_v2 m_cuArrayCreate_v2;
pcuArrayGetDescriptor_v2 m_cuArrayGetDescriptor_v2;
pcuArrayDestroy m_cuArrayDestroy;
pcuArray3DCreate_v2 m_cuArray3DCreate_v2;
pcuArray3DGetDescriptor_v2 m_cuArray3DGetDescriptor_v2;
pcuMipmappedArrayCreate m_cuMipmappedArrayCreate;
pcuMipmappedArrayGetLevel m_cuMipmappedArrayGetLevel;
pcuMipmappedArrayDestroy m_cuMipmappedArrayDestroy;
pcuPointerGetAttribute m_cuPointerGetAttribute;
pcuMemPrefetchAsync m_cuMemPrefetchAsync;
pcuMemAdvise m_cuMemAdvise;
pcuMemRangeGetAttribute m_cuMemRangeGetAttribute;
pcuMemRangeGetAttributes m_cuMemRangeGetAttributes;
pcuPointerSetAttribute m_cuPointerSetAttribute;
pcuPointerGetAttributes m_cuPointerGetAttributes;
pcuStreamCreate m_cuStreamCreate;
pcuStreamCreateWithPriority m_cuStreamCreateWithPriority;
pcuStreamGetPriority m_cuStreamGetPriority;
pcuStreamGetFlags m_cuStreamGetFlags;
pcuStreamGetCtx m_cuStreamGetCtx;
pcuStreamWaitEvent m_cuStreamWaitEvent;
pcuStreamAddCallback m_cuStreamAddCallback;
pcuStreamBeginCapture m_cuStreamBeginCapture;
pcuStreamEndCapture m_cuStreamEndCapture;
pcuStreamIsCapturing m_cuStreamIsCapturing;
pcuStreamAttachMemAsync m_cuStreamAttachMemAsync;
pcuStreamQuery m_cuStreamQuery;
pcuStreamSynchronize m_cuStreamSynchronize;
pcuStreamDestroy_v2 m_cuStreamDestroy_v2;
pcuEventCreate m_cuEventCreate;
pcuEventRecord m_cuEventRecord;
pcuEventQuery m_cuEventQuery;
pcuEventSynchronize m_cuEventSynchronize;
pcuEventDestroy_v2 m_cuEventDestroy_v2;
pcuEventElapsedTime m_cuEventElapsedTime;
pcuImportExternalMemory m_cuImportExternalMemory;
pcuExternalMemoryGetMappedBuffer m_cuExternalMemoryGetMappedBuffer;
pcuExternalMemoryGetMappedMipmappedArray m_cuExternalMemoryGetMappedMipmappedArray;
pcuDestroyExternalMemory m_cuDestroyExternalMemory;
pcuImportExternalSemaphore m_cuImportExternalSemaphore;
pcuSignalExternalSemaphoresAsync m_cuSignalExternalSemaphoresAsync;
pcuWaitExternalSemaphoresAsync m_cuWaitExternalSemaphoresAsync;
pcuDestroyExternalSemaphore m_cuDestroyExternalSemaphore;
pcuStreamWaitValue32 m_cuStreamWaitValue32;
pcuStreamWaitValue64 m_cuStreamWaitValue64;
pcuStreamWriteValue32 m_cuStreamWriteValue32;
pcuStreamWriteValue64 m_cuStreamWriteValue64;
pcuStreamBatchMemOp m_cuStreamBatchMemOp;
pcuFuncGetAttribute m_cuFuncGetAttribute;
pcuFuncSetAttribute m_cuFuncSetAttribute;
pcuFuncSetCacheConfig m_cuFuncSetCacheConfig;
pcuFuncSetSharedMemConfig m_cuFuncSetSharedMemConfig;
pcuLaunchKernel m_cuLaunchKernel;
pcuLaunchCooperativeKernel m_cuLaunchCooperativeKernel;
pcuLaunchCooperativeKernelMultiDevice m_cuLaunchCooperativeKernelMultiDevice;
pcuLaunchHostFunc m_cuLaunchHostFunc;
pcuFuncSetBlockShape m_cuFuncSetBlockShape;
pcuFuncSetSharedSize m_cuFuncSetSharedSize;
pcuParamSetSize m_cuParamSetSize;
pcuParamSeti m_cuParamSeti;
pcuParamSetf m_cuParamSetf;
pcuParamSetv m_cuParamSetv;
pcuLaunch m_cuLaunch;
pcuLaunchGrid m_cuLaunchGrid;
pcuLaunchGridAsync m_cuLaunchGridAsync;
pcuParamSetTexRef m_cuParamSetTexRef;
pcuGraphCreate m_cuGraphCreate;
pcuGraphAddKernelNode m_cuGraphAddKernelNode;
pcuGraphKernelNodeGetParams m_cuGraphKernelNodeGetParams;
pcuGraphKernelNodeSetParams m_cuGraphKernelNodeSetParams;
pcuGraphAddMemcpyNode m_cuGraphAddMemcpyNode;
pcuGraphMemcpyNodeGetParams m_cuGraphMemcpyNodeGetParams;
pcuGraphMemcpyNodeSetParams m_cuGraphMemcpyNodeSetParams;
pcuGraphAddMemsetNode m_cuGraphAddMemsetNode;
pcuGraphMemsetNodeGetParams m_cuGraphMemsetNodeGetParams;
pcuGraphMemsetNodeSetParams m_cuGraphMemsetNodeSetParams;
pcuGraphAddHostNode m_cuGraphAddHostNode;
pcuGraphHostNodeGetParams m_cuGraphHostNodeGetParams;
pcuGraphHostNodeSetParams m_cuGraphHostNodeSetParams;
pcuGraphAddChildGraphNode m_cuGraphAddChildGraphNode;
pcuGraphChildGraphNodeGetGraph m_cuGraphChildGraphNodeGetGraph;
pcuGraphAddEmptyNode m_cuGraphAddEmptyNode;
pcuGraphClone m_cuGraphClone;
pcuGraphNodeFindInClone m_cuGraphNodeFindInClone;
pcuGraphNodeGetType m_cuGraphNodeGetType;
pcuGraphGetNodes m_cuGraphGetNodes;
pcuGraphGetRootNodes m_cuGraphGetRootNodes;
pcuGraphGetEdges m_cuGraphGetEdges;
pcuGraphNodeGetDependencies m_cuGraphNodeGetDependencies;
pcuGraphNodeGetDependentNodes m_cuGraphNodeGetDependentNodes;
pcuGraphAddDependencies m_cuGraphAddDependencies;
pcuGraphRemoveDependencies m_cuGraphRemoveDependencies;
pcuGraphDestroyNode m_cuGraphDestroyNode;
pcuGraphInstantiate m_cuGraphInstantiate;
pcuGraphLaunch m_cuGraphLaunch;
pcuGraphExecDestroy m_cuGraphExecDestroy;
pcuGraphDestroy m_cuGraphDestroy;
pcuOccupancyMaxActiveBlocksPerMultiprocessor m_cuOccupancyMaxActiveBlocksPerMultiprocessor;
pcuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags m_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags;
pcuOccupancyMaxPotentialBlockSize m_cuOccupancyMaxPotentialBlockSize;
pcuOccupancyMaxPotentialBlockSizeWithFlags m_cuOccupancyMaxPotentialBlockSizeWithFlags;
pcuTexRefSetArray m_cuTexRefSetArray;
pcuTexRefSetMipmappedArray m_cuTexRefSetMipmappedArray;
pcuTexRefSetAddress_v2 m_cuTexRefSetAddress_v2;
pcuTexRefSetAddress2D_v3 m_cuTexRefSetAddress2D_v3;
pcuTexRefSetFormat m_cuTexRefSetFormat;
pcuTexRefSetAddressMode m_cuTexRefSetAddressMode;
pcuTexRefSetFilterMode m_cuTexRefSetFilterMode;
pcuTexRefSetMipmapFilterMode m_cuTexRefSetMipmapFilterMode;
pcuTexRefSetMipmapLevelBias m_cuTexRefSetMipmapLevelBias;
pcuTexRefSetMipmapLevelClamp m_cuTexRefSetMipmapLevelClamp;
pcuTexRefSetMaxAnisotropy m_cuTexRefSetMaxAnisotropy;
pcuTexRefSetBorderColor m_cuTexRefSetBorderColor;
pcuTexRefSetFlags m_cuTexRefSetFlags;
pcuTexRefGetAddress_v2 m_cuTexRefGetAddress_v2;
pcuTexRefGetArray m_cuTexRefGetArray;
pcuTexRefGetMipmappedArray m_cuTexRefGetMipmappedArray;
pcuTexRefGetAddressMode m_cuTexRefGetAddressMode;
pcuTexRefGetFilterMode m_cuTexRefGetFilterMode;
pcuTexRefGetFormat m_cuTexRefGetFormat;
pcuTexRefGetMipmapFilterMode m_cuTexRefGetMipmapFilterMode;
pcuTexRefGetMipmapLevelBias m_cuTexRefGetMipmapLevelBias;
pcuTexRefGetMipmapLevelClamp m_cuTexRefGetMipmapLevelClamp;
pcuTexRefGetMaxAnisotropy m_cuTexRefGetMaxAnisotropy;
pcuTexRefGetBorderColor m_cuTexRefGetBorderColor;
pcuTexRefGetFlags m_cuTexRefGetFlags;
pcuTexRefCreate m_cuTexRefCreate;
pcuTexRefDestroy m_cuTexRefDestroy;
pcuSurfRefSetArray m_cuSurfRefSetArray;
pcuSurfRefGetArray m_cuSurfRefGetArray;
pcuTexObjectCreate m_cuTexObjectCreate;
pcuTexObjectDestroy m_cuTexObjectDestroy;
pcuTexObjectGetResourceDesc m_cuTexObjectGetResourceDesc;
pcuTexObjectGetTextureDesc m_cuTexObjectGetTextureDesc;
pcuTexObjectGetResourceViewDesc m_cuTexObjectGetResourceViewDesc;
pcuSurfObjectCreate m_cuSurfObjectCreate;
pcuSurfObjectDestroy m_cuSurfObjectDestroy;
pcuSurfObjectGetResourceDesc m_cuSurfObjectGetResourceDesc;
pcuDeviceCanAccessPeer m_cuDeviceCanAccessPeer;
pcuCtxEnablePeerAccess m_cuCtxEnablePeerAccess;
pcuCtxDisablePeerAccess m_cuCtxDisablePeerAccess;
pcuDeviceGetP2PAttribute m_cuDeviceGetP2PAttribute;
pcuGraphicsUnregisterResource m_cuGraphicsUnregisterResource;
pcuGraphicsSubResourceGetMappedArray m_cuGraphicsSubResourceGetMappedArray;
pcuGraphicsResourceGetMappedMipmappedArray m_cuGraphicsResourceGetMappedMipmappedArray;
pcuGraphicsResourceGetMappedPointer_v2 m_cuGraphicsResourceGetMappedPointer_v2;
pcuGraphicsResourceSetMapFlags_v2 m_cuGraphicsResourceSetMapFlags_v2;
pcuGraphicsMapResources m_cuGraphicsMapResources;
pcuGraphicsUnmapResources m_cuGraphicsUnmapResources;
pcuGetExportTable m_cuGetExportTable;

    wrap()
    {
        HMODULE h = LoadLibrary("nvcuda.dll");
m_cuGetErrorString = (pcuGetErrorString)GetProcAddress(h, "cuGetErrorString");
m_cuGetErrorName = (pcuGetErrorName)GetProcAddress(h, "cuGetErrorName");
m_cuInit = (pcuInit)GetProcAddress(h, "cuInit");
m_cuDriverGetVersion = (pcuDriverGetVersion)GetProcAddress(h, "cuDriverGetVersion");
m_cuDeviceGet = (pcuDeviceGet)GetProcAddress(h, "cuDeviceGet");
m_cuDeviceGetCount = (pcuDeviceGetCount)GetProcAddress(h, "cuDeviceGetCount");
m_cuDeviceGetName = (pcuDeviceGetName)GetProcAddress(h, "cuDeviceGetName");
m_cuDeviceGetUuid = (pcuDeviceGetUuid)GetProcAddress(h, "cuDeviceGetUuid");
m_cuDeviceGetLuid = (pcuDeviceGetLuid)GetProcAddress(h, "cuDeviceGetLuid");
m_cuDeviceTotalMem_v2 = (pcuDeviceTotalMem_v2)GetProcAddress(h, "cuDeviceTotalMem_v2");
m_cuDeviceGetAttribute = (pcuDeviceGetAttribute)GetProcAddress(h, "cuDeviceGetAttribute");
m_cuDeviceGetProperties = (pcuDeviceGetProperties)GetProcAddress(h, "cuDeviceGetProperties");
m_cuDeviceComputeCapability = (pcuDeviceComputeCapability)GetProcAddress(h, "cuDeviceComputeCapability");
m_cuDevicePrimaryCtxRetain = (pcuDevicePrimaryCtxRetain)GetProcAddress(h, "cuDevicePrimaryCtxRetain");
m_cuDevicePrimaryCtxRelease = (pcuDevicePrimaryCtxRelease)GetProcAddress(h, "cuDevicePrimaryCtxRelease");
m_cuDevicePrimaryCtxSetFlags = (pcuDevicePrimaryCtxSetFlags)GetProcAddress(h, "cuDevicePrimaryCtxSetFlags");
m_cuDevicePrimaryCtxGetState = (pcuDevicePrimaryCtxGetState)GetProcAddress(h, "cuDevicePrimaryCtxGetState");
m_cuDevicePrimaryCtxReset = (pcuDevicePrimaryCtxReset)GetProcAddress(h, "cuDevicePrimaryCtxReset");
m_cuCtxCreate_v2 = (pcuCtxCreate_v2)GetProcAddress(h, "cuCtxCreate_v2");
m_cuCtxDestroy_v2 = (pcuCtxDestroy_v2)GetProcAddress(h, "cuCtxDestroy_v2");
m_cuCtxPushCurrent_v2 = (pcuCtxPushCurrent_v2)GetProcAddress(h, "cuCtxPushCurrent_v2");
m_cuCtxPopCurrent_v2 = (pcuCtxPopCurrent_v2)GetProcAddress(h, "cuCtxPopCurrent_v2");
m_cuCtxSetCurrent = (pcuCtxSetCurrent)GetProcAddress(h, "cuCtxSetCurrent");
m_cuCtxGetCurrent = (pcuCtxGetCurrent)GetProcAddress(h, "cuCtxGetCurrent");
m_cuCtxGetDevice = (pcuCtxGetDevice)GetProcAddress(h, "cuCtxGetDevice");
m_cuCtxGetFlags = (pcuCtxGetFlags)GetProcAddress(h, "cuCtxGetFlags");
m_cuCtxSynchronize = (pcuCtxSynchronize)GetProcAddress(h, "cuCtxSynchronize");
m_cuCtxSetLimit = (pcuCtxSetLimit)GetProcAddress(h, "cuCtxSetLimit");
m_cuCtxGetLimit = (pcuCtxGetLimit)GetProcAddress(h, "cuCtxGetLimit");
m_cuCtxGetCacheConfig = (pcuCtxGetCacheConfig)GetProcAddress(h, "cuCtxGetCacheConfig");
m_cuCtxSetCacheConfig = (pcuCtxSetCacheConfig)GetProcAddress(h, "cuCtxSetCacheConfig");
m_cuCtxGetSharedMemConfig = (pcuCtxGetSharedMemConfig)GetProcAddress(h, "cuCtxGetSharedMemConfig");
m_cuCtxSetSharedMemConfig = (pcuCtxSetSharedMemConfig)GetProcAddress(h, "cuCtxSetSharedMemConfig");
m_cuCtxGetApiVersion = (pcuCtxGetApiVersion)GetProcAddress(h, "cuCtxGetApiVersion");
m_cuCtxGetStreamPriorityRange = (pcuCtxGetStreamPriorityRange)GetProcAddress(h, "cuCtxGetStreamPriorityRange");
m_cuCtxAttach = (pcuCtxAttach)GetProcAddress(h, "cuCtxAttach");
m_cuCtxDetach = (pcuCtxDetach)GetProcAddress(h, "cuCtxDetach");
m_cuModuleLoad = (pcuModuleLoad)GetProcAddress(h, "cuModuleLoad");
m_cuModuleLoadData = (pcuModuleLoadData)GetProcAddress(h, "cuModuleLoadData");
m_cuModuleLoadDataEx = (pcuModuleLoadDataEx)GetProcAddress(h, "cuModuleLoadDataEx");
m_cuModuleLoadFatBinary = (pcuModuleLoadFatBinary)GetProcAddress(h, "cuModuleLoadFatBinary");
m_cuModuleUnload = (pcuModuleUnload)GetProcAddress(h, "cuModuleUnload");
m_cuModuleGetFunction = (pcuModuleGetFunction)GetProcAddress(h, "cuModuleGetFunction");
m_cuModuleGetGlobal_v2 = (pcuModuleGetGlobal_v2)GetProcAddress(h, "cuModuleGetGlobal_v2");
m_cuModuleGetTexRef = (pcuModuleGetTexRef)GetProcAddress(h, "cuModuleGetTexRef");
m_cuModuleGetSurfRef = (pcuModuleGetSurfRef)GetProcAddress(h, "cuModuleGetSurfRef");
m_cuLinkCreate_v2 = (pcuLinkCreate_v2)GetProcAddress(h, "cuLinkCreate_v2");
m_cuLinkAddData_v2 = (pcuLinkAddData_v2)GetProcAddress(h, "cuLinkAddData_v2");
m_cuLinkAddFile_v2 = (pcuLinkAddFile_v2)GetProcAddress(h, "cuLinkAddFile_v2");
m_cuLinkComplete = (pcuLinkComplete)GetProcAddress(h, "cuLinkComplete");
m_cuLinkDestroy = (pcuLinkDestroy)GetProcAddress(h, "cuLinkDestroy");
m_cuMemGetInfo_v2 = (pcuMemGetInfo_v2)GetProcAddress(h, "cuMemGetInfo_v2");
m_cuMemAlloc_v2 = (pcuMemAlloc_v2)GetProcAddress(h, "cuMemAlloc_v2");
m_cuMemAllocPitch_v2 = (pcuMemAllocPitch_v2)GetProcAddress(h, "cuMemAllocPitch_v2");
m_cuMemFree_v2 = (pcuMemFree_v2)GetProcAddress(h, "cuMemFree_v2");
m_cuMemGetAddressRange_v2 = (pcuMemGetAddressRange_v2)GetProcAddress(h, "cuMemGetAddressRange_v2");
m_cuMemAllocHost_v2 = (pcuMemAllocHost_v2)GetProcAddress(h, "cuMemAllocHost_v2");
m_cuMemFreeHost = (pcuMemFreeHost)GetProcAddress(h, "cuMemFreeHost");
m_cuMemHostAlloc = (pcuMemHostAlloc)GetProcAddress(h, "cuMemHostAlloc");
m_cuMemHostGetDevicePointer_v2 = (pcuMemHostGetDevicePointer_v2)GetProcAddress(h, "cuMemHostGetDevicePointer_v2");
m_cuMemHostGetFlags = (pcuMemHostGetFlags)GetProcAddress(h, "cuMemHostGetFlags");
m_cuMemAllocManaged = (pcuMemAllocManaged)GetProcAddress(h, "cuMemAllocManaged");
m_cuDeviceGetByPCIBusId = (pcuDeviceGetByPCIBusId)GetProcAddress(h, "cuDeviceGetByPCIBusId");
m_cuDeviceGetPCIBusId = (pcuDeviceGetPCIBusId)GetProcAddress(h, "cuDeviceGetPCIBusId");
m_cuIpcGetEventHandle = (pcuIpcGetEventHandle)GetProcAddress(h, "cuIpcGetEventHandle");
m_cuIpcOpenEventHandle = (pcuIpcOpenEventHandle)GetProcAddress(h, "cuIpcOpenEventHandle");
m_cuIpcGetMemHandle = (pcuIpcGetMemHandle)GetProcAddress(h, "cuIpcGetMemHandle");
m_cuIpcOpenMemHandle = (pcuIpcOpenMemHandle)GetProcAddress(h, "cuIpcOpenMemHandle");
m_cuIpcCloseMemHandle = (pcuIpcCloseMemHandle)GetProcAddress(h, "cuIpcCloseMemHandle");
m_cuMemHostRegister_v2 = (pcuMemHostRegister_v2)GetProcAddress(h, "cuMemHostRegister_v2");
m_cuMemHostUnregister = (pcuMemHostUnregister)GetProcAddress(h, "cuMemHostUnregister");
m_cuMemcpy = (pcuMemcpy)GetProcAddress(h, "cuMemcpy");
m_cuMemcpyPeer = (pcuMemcpyPeer)GetProcAddress(h, "cuMemcpyPeer");
m_cuMemcpyHtoD_v2 = (pcuMemcpyHtoD_v2)GetProcAddress(h, "cuMemcpyHtoD_v2");
m_cuMemcpyDtoH_v2 = (pcuMemcpyDtoH_v2)GetProcAddress(h, "cuMemcpyDtoH_v2");
m_cuMemcpyDtoD_v2 = (pcuMemcpyDtoD_v2)GetProcAddress(h, "cuMemcpyDtoD_v2");
m_cuMemcpyDtoA_v2 = (pcuMemcpyDtoA_v2)GetProcAddress(h, "cuMemcpyDtoA_v2");
m_cuMemcpyAtoD_v2 = (pcuMemcpyAtoD_v2)GetProcAddress(h, "cuMemcpyAtoD_v2");
m_cuMemcpyHtoA_v2 = (pcuMemcpyHtoA_v2)GetProcAddress(h, "cuMemcpyHtoA_v2");
m_cuMemcpyAtoH_v2 = (pcuMemcpyAtoH_v2)GetProcAddress(h, "cuMemcpyAtoH_v2");
m_cuMemcpyAtoA_v2 = (pcuMemcpyAtoA_v2)GetProcAddress(h, "cuMemcpyAtoA_v2");
m_cuMemcpy2D_v2 = (pcuMemcpy2D_v2)GetProcAddress(h, "cuMemcpy2D_v2");
m_cuMemcpy2DUnaligned_v2 = (pcuMemcpy2DUnaligned_v2)GetProcAddress(h, "cuMemcpy2DUnaligned_v2");
m_cuMemcpy3D_v2 = (pcuMemcpy3D_v2)GetProcAddress(h, "cuMemcpy3D_v2");
m_cuMemcpy3DPeer = (pcuMemcpy3DPeer)GetProcAddress(h, "cuMemcpy3DPeer");
m_cuMemcpyAsync = (pcuMemcpyAsync)GetProcAddress(h, "cuMemcpyAsync");
m_cuMemcpyPeerAsync = (pcuMemcpyPeerAsync)GetProcAddress(h, "cuMemcpyPeerAsync");
m_cuMemcpyHtoDAsync_v2 = (pcuMemcpyHtoDAsync_v2)GetProcAddress(h, "cuMemcpyHtoDAsync_v2");
m_cuMemcpyDtoHAsync_v2 = (pcuMemcpyDtoHAsync_v2)GetProcAddress(h, "cuMemcpyDtoHAsync_v2");
m_cuMemcpyDtoDAsync_v2 = (pcuMemcpyDtoDAsync_v2)GetProcAddress(h, "cuMemcpyDtoDAsync_v2");
m_cuMemcpyHtoAAsync_v2 = (pcuMemcpyHtoAAsync_v2)GetProcAddress(h, "cuMemcpyHtoAAsync_v2");
m_cuMemcpyAtoHAsync_v2 = (pcuMemcpyAtoHAsync_v2)GetProcAddress(h, "cuMemcpyAtoHAsync_v2");
m_cuMemcpy2DAsync_v2 = (pcuMemcpy2DAsync_v2)GetProcAddress(h, "cuMemcpy2DAsync_v2");
m_cuMemcpy3DAsync_v2 = (pcuMemcpy3DAsync_v2)GetProcAddress(h, "cuMemcpy3DAsync_v2");
m_cuMemcpy3DPeerAsync = (pcuMemcpy3DPeerAsync)GetProcAddress(h, "cuMemcpy3DPeerAsync");
m_cuMemsetD8_v2 = (pcuMemsetD8_v2)GetProcAddress(h, "cuMemsetD8_v2");
m_cuMemsetD16_v2 = (pcuMemsetD16_v2)GetProcAddress(h, "cuMemsetD16_v2");
m_cuMemsetD32_v2 = (pcuMemsetD32_v2)GetProcAddress(h, "cuMemsetD32_v2");
m_cuMemsetD2D8_v2 = (pcuMemsetD2D8_v2)GetProcAddress(h, "cuMemsetD2D8_v2");
m_cuMemsetD2D16_v2 = (pcuMemsetD2D16_v2)GetProcAddress(h, "cuMemsetD2D16_v2");
m_cuMemsetD2D32_v2 = (pcuMemsetD2D32_v2)GetProcAddress(h, "cuMemsetD2D32_v2");
m_cuMemsetD8Async = (pcuMemsetD8Async)GetProcAddress(h, "cuMemsetD8Async");
m_cuMemsetD16Async = (pcuMemsetD16Async)GetProcAddress(h, "cuMemsetD16Async");
m_cuMemsetD32Async = (pcuMemsetD32Async)GetProcAddress(h, "cuMemsetD32Async");
m_cuMemsetD2D8Async = (pcuMemsetD2D8Async)GetProcAddress(h, "cuMemsetD2D8Async");
m_cuMemsetD2D16Async = (pcuMemsetD2D16Async)GetProcAddress(h, "cuMemsetD2D16Async");
m_cuMemsetD2D32Async = (pcuMemsetD2D32Async)GetProcAddress(h, "cuMemsetD2D32Async");
m_cuArrayCreate_v2 = (pcuArrayCreate_v2)GetProcAddress(h, "cuArrayCreate_v2");
m_cuArrayGetDescriptor_v2 = (pcuArrayGetDescriptor_v2)GetProcAddress(h, "cuArrayGetDescriptor_v2");
m_cuArrayDestroy = (pcuArrayDestroy)GetProcAddress(h, "cuArrayDestroy");
m_cuArray3DCreate_v2 = (pcuArray3DCreate_v2)GetProcAddress(h, "cuArray3DCreate_v2");
m_cuArray3DGetDescriptor_v2 = (pcuArray3DGetDescriptor_v2)GetProcAddress(h, "cuArray3DGetDescriptor_v2");
m_cuMipmappedArrayCreate = (pcuMipmappedArrayCreate)GetProcAddress(h, "cuMipmappedArrayCreate");
m_cuMipmappedArrayGetLevel = (pcuMipmappedArrayGetLevel)GetProcAddress(h, "cuMipmappedArrayGetLevel");
m_cuMipmappedArrayDestroy = (pcuMipmappedArrayDestroy)GetProcAddress(h, "cuMipmappedArrayDestroy");
m_cuPointerGetAttribute = (pcuPointerGetAttribute)GetProcAddress(h, "cuPointerGetAttribute");
m_cuMemPrefetchAsync = (pcuMemPrefetchAsync)GetProcAddress(h, "cuMemPrefetchAsync");
m_cuMemAdvise = (pcuMemAdvise)GetProcAddress(h, "cuMemAdvise");
m_cuMemRangeGetAttribute = (pcuMemRangeGetAttribute)GetProcAddress(h, "cuMemRangeGetAttribute");
m_cuMemRangeGetAttributes = (pcuMemRangeGetAttributes)GetProcAddress(h, "cuMemRangeGetAttributes");
m_cuPointerSetAttribute = (pcuPointerSetAttribute)GetProcAddress(h, "cuPointerSetAttribute");
m_cuPointerGetAttributes = (pcuPointerGetAttributes)GetProcAddress(h, "cuPointerGetAttributes");
m_cuStreamCreate = (pcuStreamCreate)GetProcAddress(h, "cuStreamCreate");
m_cuStreamCreateWithPriority = (pcuStreamCreateWithPriority)GetProcAddress(h, "cuStreamCreateWithPriority");
m_cuStreamGetPriority = (pcuStreamGetPriority)GetProcAddress(h, "cuStreamGetPriority");
m_cuStreamGetFlags = (pcuStreamGetFlags)GetProcAddress(h, "cuStreamGetFlags");
m_cuStreamGetCtx = (pcuStreamGetCtx)GetProcAddress(h, "cuStreamGetCtx");
m_cuStreamWaitEvent = (pcuStreamWaitEvent)GetProcAddress(h, "cuStreamWaitEvent");
m_cuStreamAddCallback = (pcuStreamAddCallback)GetProcAddress(h, "cuStreamAddCallback");
m_cuStreamBeginCapture = (pcuStreamBeginCapture)GetProcAddress(h, "cuStreamBeginCapture");
m_cuStreamEndCapture = (pcuStreamEndCapture)GetProcAddress(h, "cuStreamEndCapture");
m_cuStreamIsCapturing = (pcuStreamIsCapturing)GetProcAddress(h, "cuStreamIsCapturing");
m_cuStreamAttachMemAsync = (pcuStreamAttachMemAsync)GetProcAddress(h, "cuStreamAttachMemAsync");
m_cuStreamQuery = (pcuStreamQuery)GetProcAddress(h, "cuStreamQuery");
m_cuStreamSynchronize = (pcuStreamSynchronize)GetProcAddress(h, "cuStreamSynchronize");
m_cuStreamDestroy_v2 = (pcuStreamDestroy_v2)GetProcAddress(h, "cuStreamDestroy_v2");
m_cuEventCreate = (pcuEventCreate)GetProcAddress(h, "cuEventCreate");
m_cuEventRecord = (pcuEventRecord)GetProcAddress(h, "cuEventRecord");
m_cuEventQuery = (pcuEventQuery)GetProcAddress(h, "cuEventQuery");
m_cuEventSynchronize = (pcuEventSynchronize)GetProcAddress(h, "cuEventSynchronize");
m_cuEventDestroy_v2 = (pcuEventDestroy_v2)GetProcAddress(h, "cuEventDestroy_v2");
m_cuEventElapsedTime = (pcuEventElapsedTime)GetProcAddress(h, "cuEventElapsedTime");
m_cuImportExternalMemory = (pcuImportExternalMemory)GetProcAddress(h, "cuImportExternalMemory");
m_cuExternalMemoryGetMappedBuffer = (pcuExternalMemoryGetMappedBuffer)GetProcAddress(h, "cuExternalMemoryGetMappedBuffer");
m_cuExternalMemoryGetMappedMipmappedArray = (pcuExternalMemoryGetMappedMipmappedArray)GetProcAddress(h, "cuExternalMemoryGetMappedMipmappedArray");
m_cuDestroyExternalMemory = (pcuDestroyExternalMemory)GetProcAddress(h, "cuDestroyExternalMemory");
m_cuImportExternalSemaphore = (pcuImportExternalSemaphore)GetProcAddress(h, "cuImportExternalSemaphore");
m_cuSignalExternalSemaphoresAsync = (pcuSignalExternalSemaphoresAsync)GetProcAddress(h, "cuSignalExternalSemaphoresAsync");
m_cuWaitExternalSemaphoresAsync = (pcuWaitExternalSemaphoresAsync)GetProcAddress(h, "cuWaitExternalSemaphoresAsync");
m_cuDestroyExternalSemaphore = (pcuDestroyExternalSemaphore)GetProcAddress(h, "cuDestroyExternalSemaphore");
m_cuStreamWaitValue32 = (pcuStreamWaitValue32)GetProcAddress(h, "cuStreamWaitValue32");
m_cuStreamWaitValue64 = (pcuStreamWaitValue64)GetProcAddress(h, "cuStreamWaitValue64");
m_cuStreamWriteValue32 = (pcuStreamWriteValue32)GetProcAddress(h, "cuStreamWriteValue32");
m_cuStreamWriteValue64 = (pcuStreamWriteValue64)GetProcAddress(h, "cuStreamWriteValue64");
m_cuStreamBatchMemOp = (pcuStreamBatchMemOp)GetProcAddress(h, "cuStreamBatchMemOp");
m_cuFuncGetAttribute = (pcuFuncGetAttribute)GetProcAddress(h, "cuFuncGetAttribute");
m_cuFuncSetAttribute = (pcuFuncSetAttribute)GetProcAddress(h, "cuFuncSetAttribute");
m_cuFuncSetCacheConfig = (pcuFuncSetCacheConfig)GetProcAddress(h, "cuFuncSetCacheConfig");
m_cuFuncSetSharedMemConfig = (pcuFuncSetSharedMemConfig)GetProcAddress(h, "cuFuncSetSharedMemConfig");
m_cuLaunchKernel = (pcuLaunchKernel)GetProcAddress(h, "cuLaunchKernel");
m_cuLaunchCooperativeKernel = (pcuLaunchCooperativeKernel)GetProcAddress(h, "cuLaunchCooperativeKernel");
m_cuLaunchCooperativeKernelMultiDevice = (pcuLaunchCooperativeKernelMultiDevice)GetProcAddress(h, "cuLaunchCooperativeKernelMultiDevice");
m_cuLaunchHostFunc = (pcuLaunchHostFunc)GetProcAddress(h, "cuLaunchHostFunc");
m_cuFuncSetBlockShape = (pcuFuncSetBlockShape)GetProcAddress(h, "cuFuncSetBlockShape");
m_cuFuncSetSharedSize = (pcuFuncSetSharedSize)GetProcAddress(h, "cuFuncSetSharedSize");
m_cuParamSetSize = (pcuParamSetSize)GetProcAddress(h, "cuParamSetSize");
m_cuParamSeti = (pcuParamSeti)GetProcAddress(h, "cuParamSeti");
m_cuParamSetf = (pcuParamSetf)GetProcAddress(h, "cuParamSetf");
m_cuParamSetv = (pcuParamSetv)GetProcAddress(h, "cuParamSetv");
m_cuLaunch = (pcuLaunch)GetProcAddress(h, "cuLaunch");
m_cuLaunchGrid = (pcuLaunchGrid)GetProcAddress(h, "cuLaunchGrid");
m_cuLaunchGridAsync = (pcuLaunchGridAsync)GetProcAddress(h, "cuLaunchGridAsync");
m_cuParamSetTexRef = (pcuParamSetTexRef)GetProcAddress(h, "cuParamSetTexRef");
m_cuGraphCreate = (pcuGraphCreate)GetProcAddress(h, "cuGraphCreate");
m_cuGraphAddKernelNode = (pcuGraphAddKernelNode)GetProcAddress(h, "cuGraphAddKernelNode");
m_cuGraphKernelNodeGetParams = (pcuGraphKernelNodeGetParams)GetProcAddress(h, "cuGraphKernelNodeGetParams");
m_cuGraphKernelNodeSetParams = (pcuGraphKernelNodeSetParams)GetProcAddress(h, "cuGraphKernelNodeSetParams");
m_cuGraphAddMemcpyNode = (pcuGraphAddMemcpyNode)GetProcAddress(h, "cuGraphAddMemcpyNode");
m_cuGraphMemcpyNodeGetParams = (pcuGraphMemcpyNodeGetParams)GetProcAddress(h, "cuGraphMemcpyNodeGetParams");
m_cuGraphMemcpyNodeSetParams = (pcuGraphMemcpyNodeSetParams)GetProcAddress(h, "cuGraphMemcpyNodeSetParams");
m_cuGraphAddMemsetNode = (pcuGraphAddMemsetNode)GetProcAddress(h, "cuGraphAddMemsetNode");
m_cuGraphMemsetNodeGetParams = (pcuGraphMemsetNodeGetParams)GetProcAddress(h, "cuGraphMemsetNodeGetParams");
m_cuGraphMemsetNodeSetParams = (pcuGraphMemsetNodeSetParams)GetProcAddress(h, "cuGraphMemsetNodeSetParams");
m_cuGraphAddHostNode = (pcuGraphAddHostNode)GetProcAddress(h, "cuGraphAddHostNode");
m_cuGraphHostNodeGetParams = (pcuGraphHostNodeGetParams)GetProcAddress(h, "cuGraphHostNodeGetParams");
m_cuGraphHostNodeSetParams = (pcuGraphHostNodeSetParams)GetProcAddress(h, "cuGraphHostNodeSetParams");
m_cuGraphAddChildGraphNode = (pcuGraphAddChildGraphNode)GetProcAddress(h, "cuGraphAddChildGraphNode");
m_cuGraphChildGraphNodeGetGraph = (pcuGraphChildGraphNodeGetGraph)GetProcAddress(h, "cuGraphChildGraphNodeGetGraph");
m_cuGraphAddEmptyNode = (pcuGraphAddEmptyNode)GetProcAddress(h, "cuGraphAddEmptyNode");
m_cuGraphClone = (pcuGraphClone)GetProcAddress(h, "cuGraphClone");
m_cuGraphNodeFindInClone = (pcuGraphNodeFindInClone)GetProcAddress(h, "cuGraphNodeFindInClone");
m_cuGraphNodeGetType = (pcuGraphNodeGetType)GetProcAddress(h, "cuGraphNodeGetType");
m_cuGraphGetNodes = (pcuGraphGetNodes)GetProcAddress(h, "cuGraphGetNodes");
m_cuGraphGetRootNodes = (pcuGraphGetRootNodes)GetProcAddress(h, "cuGraphGetRootNodes");
m_cuGraphGetEdges = (pcuGraphGetEdges)GetProcAddress(h, "cuGraphGetEdges");
m_cuGraphNodeGetDependencies = (pcuGraphNodeGetDependencies)GetProcAddress(h, "cuGraphNodeGetDependencies");
m_cuGraphNodeGetDependentNodes = (pcuGraphNodeGetDependentNodes)GetProcAddress(h, "cuGraphNodeGetDependentNodes");
m_cuGraphAddDependencies = (pcuGraphAddDependencies)GetProcAddress(h, "cuGraphAddDependencies");
m_cuGraphRemoveDependencies = (pcuGraphRemoveDependencies)GetProcAddress(h, "cuGraphRemoveDependencies");
m_cuGraphDestroyNode = (pcuGraphDestroyNode)GetProcAddress(h, "cuGraphDestroyNode");
m_cuGraphInstantiate = (pcuGraphInstantiate)GetProcAddress(h, "cuGraphInstantiate");
m_cuGraphLaunch = (pcuGraphLaunch)GetProcAddress(h, "cuGraphLaunch");
m_cuGraphExecDestroy = (pcuGraphExecDestroy)GetProcAddress(h, "cuGraphExecDestroy");
m_cuGraphDestroy = (pcuGraphDestroy)GetProcAddress(h, "cuGraphDestroy");
m_cuOccupancyMaxActiveBlocksPerMultiprocessor = (pcuOccupancyMaxActiveBlocksPerMultiprocessor)GetProcAddress(h, "cuOccupancyMaxActiveBlocksPerMultiprocessor");
m_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags = (pcuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)GetProcAddress(h, "cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags");
m_cuOccupancyMaxPotentialBlockSize = (pcuOccupancyMaxPotentialBlockSize)GetProcAddress(h, "cuOccupancyMaxPotentialBlockSize");
m_cuOccupancyMaxPotentialBlockSizeWithFlags = (pcuOccupancyMaxPotentialBlockSizeWithFlags)GetProcAddress(h, "cuOccupancyMaxPotentialBlockSizeWithFlags");
m_cuTexRefSetArray = (pcuTexRefSetArray)GetProcAddress(h, "cuTexRefSetArray");
m_cuTexRefSetMipmappedArray = (pcuTexRefSetMipmappedArray)GetProcAddress(h, "cuTexRefSetMipmappedArray");
m_cuTexRefSetAddress_v2 = (pcuTexRefSetAddress_v2)GetProcAddress(h, "cuTexRefSetAddress_v2");
m_cuTexRefSetAddress2D_v3 = (pcuTexRefSetAddress2D_v3)GetProcAddress(h, "cuTexRefSetAddress2D_v3");
m_cuTexRefSetFormat = (pcuTexRefSetFormat)GetProcAddress(h, "cuTexRefSetFormat");
m_cuTexRefSetAddressMode = (pcuTexRefSetAddressMode)GetProcAddress(h, "cuTexRefSetAddressMode");
m_cuTexRefSetFilterMode = (pcuTexRefSetFilterMode)GetProcAddress(h, "cuTexRefSetFilterMode");
m_cuTexRefSetMipmapFilterMode = (pcuTexRefSetMipmapFilterMode)GetProcAddress(h, "cuTexRefSetMipmapFilterMode");
m_cuTexRefSetMipmapLevelBias = (pcuTexRefSetMipmapLevelBias)GetProcAddress(h, "cuTexRefSetMipmapLevelBias");
m_cuTexRefSetMipmapLevelClamp = (pcuTexRefSetMipmapLevelClamp)GetProcAddress(h, "cuTexRefSetMipmapLevelClamp");
m_cuTexRefSetMaxAnisotropy = (pcuTexRefSetMaxAnisotropy)GetProcAddress(h, "cuTexRefSetMaxAnisotropy");
m_cuTexRefSetBorderColor = (pcuTexRefSetBorderColor)GetProcAddress(h, "cuTexRefSetBorderColor");
m_cuTexRefSetFlags = (pcuTexRefSetFlags)GetProcAddress(h, "cuTexRefSetFlags");
m_cuTexRefGetAddress_v2 = (pcuTexRefGetAddress_v2)GetProcAddress(h, "cuTexRefGetAddress_v2");
m_cuTexRefGetArray = (pcuTexRefGetArray)GetProcAddress(h, "cuTexRefGetArray");
m_cuTexRefGetMipmappedArray = (pcuTexRefGetMipmappedArray)GetProcAddress(h, "cuTexRefGetMipmappedArray");
m_cuTexRefGetAddressMode = (pcuTexRefGetAddressMode)GetProcAddress(h, "cuTexRefGetAddressMode");
m_cuTexRefGetFilterMode = (pcuTexRefGetFilterMode)GetProcAddress(h, "cuTexRefGetFilterMode");
m_cuTexRefGetFormat = (pcuTexRefGetFormat)GetProcAddress(h, "cuTexRefGetFormat");
m_cuTexRefGetMipmapFilterMode = (pcuTexRefGetMipmapFilterMode)GetProcAddress(h, "cuTexRefGetMipmapFilterMode");
m_cuTexRefGetMipmapLevelBias = (pcuTexRefGetMipmapLevelBias)GetProcAddress(h, "cuTexRefGetMipmapLevelBias");
m_cuTexRefGetMipmapLevelClamp = (pcuTexRefGetMipmapLevelClamp)GetProcAddress(h, "cuTexRefGetMipmapLevelClamp");
m_cuTexRefGetMaxAnisotropy = (pcuTexRefGetMaxAnisotropy)GetProcAddress(h, "cuTexRefGetMaxAnisotropy");
m_cuTexRefGetBorderColor = (pcuTexRefGetBorderColor)GetProcAddress(h, "cuTexRefGetBorderColor");
m_cuTexRefGetFlags = (pcuTexRefGetFlags)GetProcAddress(h, "cuTexRefGetFlags");
m_cuTexRefCreate = (pcuTexRefCreate)GetProcAddress(h, "cuTexRefCreate");
m_cuTexRefDestroy = (pcuTexRefDestroy)GetProcAddress(h, "cuTexRefDestroy");
m_cuSurfRefSetArray = (pcuSurfRefSetArray)GetProcAddress(h, "cuSurfRefSetArray");
m_cuSurfRefGetArray = (pcuSurfRefGetArray)GetProcAddress(h, "cuSurfRefGetArray");
m_cuTexObjectCreate = (pcuTexObjectCreate)GetProcAddress(h, "cuTexObjectCreate");
m_cuTexObjectDestroy = (pcuTexObjectDestroy)GetProcAddress(h, "cuTexObjectDestroy");
m_cuTexObjectGetResourceDesc = (pcuTexObjectGetResourceDesc)GetProcAddress(h, "cuTexObjectGetResourceDesc");
m_cuTexObjectGetTextureDesc = (pcuTexObjectGetTextureDesc)GetProcAddress(h, "cuTexObjectGetTextureDesc");
m_cuTexObjectGetResourceViewDesc = (pcuTexObjectGetResourceViewDesc)GetProcAddress(h, "cuTexObjectGetResourceViewDesc");
m_cuSurfObjectCreate = (pcuSurfObjectCreate)GetProcAddress(h, "cuSurfObjectCreate");
m_cuSurfObjectDestroy = (pcuSurfObjectDestroy)GetProcAddress(h, "cuSurfObjectDestroy");
m_cuSurfObjectGetResourceDesc = (pcuSurfObjectGetResourceDesc)GetProcAddress(h, "cuSurfObjectGetResourceDesc");
m_cuDeviceCanAccessPeer = (pcuDeviceCanAccessPeer)GetProcAddress(h, "cuDeviceCanAccessPeer");
m_cuCtxEnablePeerAccess = (pcuCtxEnablePeerAccess)GetProcAddress(h, "cuCtxEnablePeerAccess");
m_cuCtxDisablePeerAccess = (pcuCtxDisablePeerAccess)GetProcAddress(h, "cuCtxDisablePeerAccess");
m_cuDeviceGetP2PAttribute = (pcuDeviceGetP2PAttribute)GetProcAddress(h, "cuDeviceGetP2PAttribute");
m_cuGraphicsUnregisterResource = (pcuGraphicsUnregisterResource)GetProcAddress(h, "cuGraphicsUnregisterResource");
m_cuGraphicsSubResourceGetMappedArray = (pcuGraphicsSubResourceGetMappedArray)GetProcAddress(h, "cuGraphicsSubResourceGetMappedArray");
m_cuGraphicsResourceGetMappedMipmappedArray = (pcuGraphicsResourceGetMappedMipmappedArray)GetProcAddress(h, "cuGraphicsResourceGetMappedMipmappedArray");
m_cuGraphicsResourceGetMappedPointer_v2 = (pcuGraphicsResourceGetMappedPointer_v2)GetProcAddress(h, "cuGraphicsResourceGetMappedPointer_v2");
m_cuGraphicsResourceSetMapFlags_v2 = (pcuGraphicsResourceSetMapFlags_v2)GetProcAddress(h, "cuGraphicsResourceSetMapFlags_v2");
m_cuGraphicsMapResources = (pcuGraphicsMapResources)GetProcAddress(h, "cuGraphicsMapResources");
m_cuGraphicsUnmapResources = (pcuGraphicsUnmapResources)GetProcAddress(h, "cuGraphicsUnmapResources");
m_cuGetExportTable = (pcuGetExportTable)GetProcAddress(h, "cuGetExportTable");
    }
};

static wrap g;

CUresult __stdcall cuGetErrorString(CUresult error, const char **pStr)
{
    CUresult ret;
    ret = g.m_cuGetErrorString(error,pStr);
    return ret;
}

CUresult __stdcall cuGetErrorName(CUresult error, const char **pStr)
{
    CUresult ret;
    ret = g.m_cuGetErrorName(error,pStr);
    return ret;
}

CUresult __stdcall cuInit(unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuInit(Flags);
    return ret;
}

CUresult __stdcall cuDriverGetVersion(int *driverVersion)
{
    CUresult ret;
    ret = g.m_cuDriverGetVersion(driverVersion);
    return ret;
}

CUresult __stdcall cuDeviceGet(CUdevice *device, int ordinal)
{
    CUresult ret;
    ret = g.m_cuDeviceGet(device,ordinal);
    return ret;
}

CUresult __stdcall cuDeviceGetCount(int *count)
{
    CUresult ret;
    ret = g.m_cuDeviceGetCount(count);
    return ret;
}

CUresult __stdcall cuDeviceGetName(char *name, int len, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetName(name,len,dev);
    return ret;
}

CUresult __stdcall cuDeviceGetUuid(CUuuid *uuid, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetUuid(uuid,dev);
    return ret;
}

CUresult __stdcall cuDeviceGetLuid(char *luid, unsigned int *deviceNodeMask, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetLuid(luid,deviceNodeMask,dev);
    return ret;
}

CUresult __stdcall cuDeviceTotalMem_v2(size_t *bytes, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceTotalMem_v2(bytes,dev);
    return ret;
}

CUresult __stdcall cuDeviceGetAttribute(int *pi, CUdevice_attribute attrib, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetAttribute(pi,attrib,dev);
    return ret;
}

CUresult __stdcall cuDeviceGetProperties(CUdevprop *prop, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetProperties(prop,dev);
    return ret;
}

CUresult __stdcall cuDeviceComputeCapability(int *major, int *minor, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceComputeCapability(major,minor,dev);
    return ret;
}

CUresult __stdcall cuDevicePrimaryCtxRetain(CUcontext *pctx, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDevicePrimaryCtxRetain(pctx,dev);
    return ret;
}

CUresult __stdcall cuDevicePrimaryCtxRelease(CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDevicePrimaryCtxRelease(dev);
    return ret;
}

CUresult __stdcall cuDevicePrimaryCtxSetFlags(CUdevice dev, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuDevicePrimaryCtxSetFlags(dev,flags);
    return ret;
}

CUresult __stdcall cuDevicePrimaryCtxGetState(CUdevice dev, unsigned int *flags, int *active)
{
    CUresult ret;
    ret = g.m_cuDevicePrimaryCtxGetState(dev,flags,active);
    return ret;
}

CUresult __stdcall cuDevicePrimaryCtxReset(CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDevicePrimaryCtxReset(dev);
    return ret;
}

CUresult __stdcall cuCtxCreate_v2(CUcontext *pctx, unsigned int flags, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuCtxCreate_v2(pctx,flags,dev);
    return ret;
}

CUresult __stdcall cuCtxDestroy_v2(CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuCtxDestroy_v2(ctx);
    return ret;
}

CUresult __stdcall cuCtxPushCurrent_v2(CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuCtxPushCurrent_v2(ctx);
    return ret;
}

CUresult __stdcall cuCtxPopCurrent_v2(CUcontext *pctx)
{
    CUresult ret;
    ret = g.m_cuCtxPopCurrent_v2(pctx);
    return ret;
}

CUresult __stdcall cuCtxSetCurrent(CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuCtxSetCurrent(ctx);
    return ret;
}

CUresult __stdcall cuCtxGetCurrent(CUcontext *pctx)
{
    CUresult ret;
    ret = g.m_cuCtxGetCurrent(pctx);
    return ret;
}

CUresult __stdcall cuCtxGetDevice(CUdevice *device)
{
    CUresult ret;
    ret = g.m_cuCtxGetDevice(device);
    return ret;
}

CUresult __stdcall cuCtxGetFlags(unsigned int *flags)
{
    CUresult ret;
    ret = g.m_cuCtxGetFlags(flags);
    return ret;
}

CUresult __stdcall cuCtxSynchronize()
{
    CUresult ret;
    ret = g.m_cuCtxSynchronize();
    return ret;
}

CUresult __stdcall cuCtxSetLimit(CUlimit limit, size_t value)
{
    CUresult ret;
    ret = g.m_cuCtxSetLimit(limit,value);
    return ret;
}

CUresult __stdcall cuCtxGetLimit(size_t *pvalue, CUlimit limit)
{
    CUresult ret;
    ret = g.m_cuCtxGetLimit(pvalue,limit);
    return ret;
}

CUresult __stdcall cuCtxGetCacheConfig(CUfunc_cache *pconfig)
{
    CUresult ret;
    ret = g.m_cuCtxGetCacheConfig(pconfig);
    return ret;
}

CUresult __stdcall cuCtxSetCacheConfig(CUfunc_cache config)
{
    CUresult ret;
    ret = g.m_cuCtxSetCacheConfig(config);
    return ret;
}

CUresult __stdcall cuCtxGetSharedMemConfig(CUsharedconfig *pConfig)
{
    CUresult ret;
    ret = g.m_cuCtxGetSharedMemConfig(pConfig);
    return ret;
}

CUresult __stdcall cuCtxSetSharedMemConfig(CUsharedconfig config)
{
    CUresult ret;
    ret = g.m_cuCtxSetSharedMemConfig(config);
    return ret;
}

CUresult __stdcall cuCtxGetApiVersion(CUcontext ctx, unsigned int *version)
{
    CUresult ret;
    ret = g.m_cuCtxGetApiVersion(ctx,version);
    return ret;
}

CUresult __stdcall cuCtxGetStreamPriorityRange(int *leastPriority, int *greatestPriority)
{
    CUresult ret;
    ret = g.m_cuCtxGetStreamPriorityRange(leastPriority,greatestPriority);
    return ret;
}

CUresult __stdcall cuCtxAttach(CUcontext *pctx, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuCtxAttach(pctx,flags);
    return ret;
}

CUresult __stdcall cuCtxDetach(CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuCtxDetach(ctx);
    return ret;
}

CUresult __stdcall cuModuleLoad(CUmodule *module, const char *fname)
{
    CUresult ret;
    ret = g.m_cuModuleLoad(module,fname);
    return ret;
}

CUresult __stdcall cuModuleLoadData(CUmodule *module, const void *image)
{
    CUresult ret;
    ret = g.m_cuModuleLoadData(module,image);
    return ret;
}

CUresult __stdcall cuModuleLoadDataEx(CUmodule *module, const void *image, unsigned int numOptions, CUjit_option *options, void **optionValues)
{
    CUresult ret;
    ret = g.m_cuModuleLoadDataEx(module,image,numOptions,options,optionValues);
    return ret;
}

CUresult __stdcall cuModuleLoadFatBinary(CUmodule *module, const void *fatCubin)
{
    CUresult ret;
    ret = g.m_cuModuleLoadFatBinary(module,fatCubin);
    return ret;
}

CUresult __stdcall cuModuleUnload(CUmodule hmod)
{
    CUresult ret;
    ret = g.m_cuModuleUnload(hmod);
    return ret;
}

CUresult __stdcall cuModuleGetFunction(CUfunction *hfunc, CUmodule hmod, const char *name)
{
    CUresult ret;
    ret = g.m_cuModuleGetFunction(hfunc,hmod,name);
    return ret;
}

CUresult __stdcall cuModuleGetGlobal_v2(CUdeviceptr *dptr, size_t *bytes, CUmodule hmod, const char *name)
{
    CUresult ret;
    ret = g.m_cuModuleGetGlobal_v2(dptr,bytes,hmod,name);
    return ret;
}

CUresult __stdcall cuModuleGetTexRef(CUtexref *pTexRef, CUmodule hmod, const char *name)
{
    CUresult ret;
    ret = g.m_cuModuleGetTexRef(pTexRef,hmod,name);
    return ret;
}

CUresult __stdcall cuModuleGetSurfRef(CUsurfref *pSurfRef, CUmodule hmod, const char *name)
{
    CUresult ret;
    ret = g.m_cuModuleGetSurfRef(pSurfRef,hmod,name);
    return ret;
}

CUresult __stdcall cuLinkCreate_v2(unsigned int numOptions, CUjit_option *options, void **optionValues, CUlinkState *stateOut)
{
    CUresult ret;
    ret = g.m_cuLinkCreate_v2(numOptions,options,optionValues,stateOut);
    return ret;
}

CUresult __stdcall cuLinkAddData_v2(CUlinkState state, CUjitInputType type, void *data, size_t size, const char *name, unsigned int numOptions, CUjit_option *options, void **optionValues)
{
    CUresult ret;
    ret = g.m_cuLinkAddData_v2(state,type,data,size,name,numOptions,options,optionValues);
    return ret;
}

CUresult __stdcall cuLinkAddFile_v2(CUlinkState state, CUjitInputType type, const char *path, unsigned int numOptions, CUjit_option *options, void **optionValues)
{
    CUresult ret;
    ret = g.m_cuLinkAddFile_v2(state,type,path,numOptions,options,optionValues);
    return ret;
}

CUresult __stdcall cuLinkComplete(CUlinkState state, void **cubinOut, size_t *sizeOut)
{
    CUresult ret;
    ret = g.m_cuLinkComplete(state,cubinOut,sizeOut);
    return ret;
}

CUresult __stdcall cuLinkDestroy(CUlinkState state)
{
    CUresult ret;
    ret = g.m_cuLinkDestroy(state);
    return ret;
}

CUresult __stdcall cuMemGetInfo_v2(size_t *free, size_t *total)
{
    CUresult ret;
    ret = g.m_cuMemGetInfo_v2(free,total);
    return ret;
}

CUresult __stdcall cuMemAlloc_v2(CUdeviceptr *dptr, size_t bytesize)
{
    CUresult ret;
    ret = g.m_cuMemAlloc_v2(dptr,bytesize);
    return ret;
}

CUresult __stdcall cuMemAllocPitch_v2(CUdeviceptr *dptr, size_t *pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes)
{
    CUresult ret;
    ret = g.m_cuMemAllocPitch_v2(dptr,pPitch,WidthInBytes,Height,ElementSizeBytes);
    return ret;
}

CUresult __stdcall cuMemFree_v2(CUdeviceptr dptr)
{
    CUresult ret;
    ret = g.m_cuMemFree_v2(dptr);
    return ret;
}

CUresult __stdcall cuMemGetAddressRange_v2(CUdeviceptr *pbase, size_t *psize, CUdeviceptr dptr)
{
    CUresult ret;
    ret = g.m_cuMemGetAddressRange_v2(pbase,psize,dptr);
    return ret;
}

CUresult __stdcall cuMemAllocHost_v2(void **pp, size_t bytesize)
{
    CUresult ret;
    ret = g.m_cuMemAllocHost_v2(pp,bytesize);
    return ret;
}

CUresult __stdcall cuMemFreeHost(void *p)
{
    CUresult ret;
    ret = g.m_cuMemFreeHost(p);
    return ret;
}

CUresult __stdcall cuMemHostAlloc(void **pp, size_t bytesize, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuMemHostAlloc(pp,bytesize,Flags);
    return ret;
}

CUresult __stdcall cuMemHostGetDevicePointer_v2(CUdeviceptr *pdptr, void *p, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuMemHostGetDevicePointer_v2(pdptr,p,Flags);
    return ret;
}

CUresult __stdcall cuMemHostGetFlags(unsigned int *pFlags, void *p)
{
    CUresult ret;
    ret = g.m_cuMemHostGetFlags(pFlags,p);
    return ret;
}

CUresult __stdcall cuMemAllocManaged(CUdeviceptr *dptr, size_t bytesize, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuMemAllocManaged(dptr,bytesize,flags);
    return ret;
}

CUresult __stdcall cuDeviceGetByPCIBusId(CUdevice *dev, const char *pciBusId)
{
    CUresult ret;
    ret = g.m_cuDeviceGetByPCIBusId(dev,pciBusId);
    return ret;
}

CUresult __stdcall cuDeviceGetPCIBusId(char *pciBusId, int len, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetPCIBusId(pciBusId,len,dev);
    return ret;
}

CUresult __stdcall cuIpcGetEventHandle(CUipcEventHandle *pHandle, CUevent event)
{
    CUresult ret;
    ret = g.m_cuIpcGetEventHandle(pHandle,event);
    return ret;
}

CUresult __stdcall cuIpcOpenEventHandle(CUevent *phEvent, CUipcEventHandle handle)
{
    CUresult ret;
    ret = g.m_cuIpcOpenEventHandle(phEvent,handle);
    return ret;
}

CUresult __stdcall cuIpcGetMemHandle(CUipcMemHandle *pHandle, CUdeviceptr dptr)
{
    CUresult ret;
    ret = g.m_cuIpcGetMemHandle(pHandle,dptr);
    return ret;
}

CUresult __stdcall cuIpcOpenMemHandle(CUdeviceptr *pdptr, CUipcMemHandle handle, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuIpcOpenMemHandle(pdptr,handle,Flags);
    return ret;
}

CUresult __stdcall cuIpcCloseMemHandle(CUdeviceptr dptr)
{
    CUresult ret;
    ret = g.m_cuIpcCloseMemHandle(dptr);
    return ret;
}

CUresult __stdcall cuMemHostRegister_v2(void *p, size_t bytesize, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuMemHostRegister_v2(p,bytesize,Flags);
    return ret;
}

CUresult __stdcall cuMemHostUnregister(void *p)
{
    CUresult ret;
    ret = g.m_cuMemHostUnregister(p);
    return ret;
}

CUresult __stdcall cuMemcpy(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpy(dst,src,ByteCount);
    return ret;
}

CUresult __stdcall cuMemcpyPeer(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyPeer(dstDevice,dstContext,srcDevice,srcContext,ByteCount);
    return ret;
}

CUresult __stdcall cuMemcpyHtoD_v2(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyHtoD_v2(dstDevice,srcHost,ByteCount);
    return ret;
}

CUresult __stdcall cuMemcpyDtoH_v2(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyDtoH_v2(dstHost,srcDevice,ByteCount);
    return ret;
}

CUresult __stdcall cuMemcpyDtoD_v2(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyDtoD_v2(dstDevice,srcDevice,ByteCount);
    return ret;
}

CUresult __stdcall cuMemcpyDtoA_v2(CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyDtoA_v2(dstArray,dstOffset,srcDevice,ByteCount);
    return ret;
}

CUresult __stdcall cuMemcpyAtoD_v2(CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyAtoD_v2(dstDevice,srcArray,srcOffset,ByteCount);
    return ret;
}

CUresult __stdcall cuMemcpyHtoA_v2(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyHtoA_v2(dstArray,dstOffset,srcHost,ByteCount);
    return ret;
}

CUresult __stdcall cuMemcpyAtoH_v2(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyAtoH_v2(dstHost,srcArray,srcOffset,ByteCount);
    return ret;
}

CUresult __stdcall cuMemcpyAtoA_v2(CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyAtoA_v2(dstArray,dstOffset,srcArray,srcOffset,ByteCount);
    return ret;
}

CUresult __stdcall cuMemcpy2D_v2(const CUDA_MEMCPY2D *pCopy)
{
    CUresult ret;
    ret = g.m_cuMemcpy2D_v2(pCopy);
    return ret;
}

CUresult __stdcall cuMemcpy2DUnaligned_v2(const CUDA_MEMCPY2D *pCopy)
{
    CUresult ret;
    ret = g.m_cuMemcpy2DUnaligned_v2(pCopy);
    return ret;
}

CUresult __stdcall cuMemcpy3D_v2(const CUDA_MEMCPY3D *pCopy)
{
    CUresult ret;
    ret = g.m_cuMemcpy3D_v2(pCopy);
    return ret;
}

CUresult __stdcall cuMemcpy3DPeer(const CUDA_MEMCPY3D_PEER *pCopy)
{
    CUresult ret;
    ret = g.m_cuMemcpy3DPeer(pCopy);
    return ret;
}

CUresult __stdcall cuMemcpyAsync(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyAsync(dst,src,ByteCount,hStream);
    return ret;
}

CUresult __stdcall cuMemcpyPeerAsync(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyPeerAsync(dstDevice,dstContext,srcDevice,srcContext,ByteCount,hStream);
    return ret;
}

CUresult __stdcall cuMemcpyHtoDAsync_v2(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyHtoDAsync_v2(dstDevice,srcHost,ByteCount,hStream);
    return ret;
}

CUresult __stdcall cuMemcpyDtoHAsync_v2(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyDtoHAsync_v2(dstHost,srcDevice,ByteCount,hStream);
    return ret;
}

CUresult __stdcall cuMemcpyDtoDAsync_v2(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyDtoDAsync_v2(dstDevice,srcDevice,ByteCount,hStream);
    return ret;
}

CUresult __stdcall cuMemcpyHtoAAsync_v2(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyHtoAAsync_v2(dstArray,dstOffset,srcHost,ByteCount,hStream);
    return ret;
}

CUresult __stdcall cuMemcpyAtoHAsync_v2(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyAtoHAsync_v2(dstHost,srcArray,srcOffset,ByteCount,hStream);
    return ret;
}

CUresult __stdcall cuMemcpy2DAsync_v2(const CUDA_MEMCPY2D *pCopy, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpy2DAsync_v2(pCopy,hStream);
    return ret;
}

CUresult __stdcall cuMemcpy3DAsync_v2(const CUDA_MEMCPY3D *pCopy, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpy3DAsync_v2(pCopy,hStream);
    return ret;
}

CUresult __stdcall cuMemcpy3DPeerAsync(const CUDA_MEMCPY3D_PEER *pCopy, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpy3DPeerAsync(pCopy,hStream);
    return ret;
}

CUresult __stdcall cuMemsetD8_v2(CUdeviceptr dstDevice, unsigned char uc, size_t N)
{
    CUresult ret;
    ret = g.m_cuMemsetD8_v2(dstDevice,uc,N);
    return ret;
}

CUresult __stdcall cuMemsetD16_v2(CUdeviceptr dstDevice, unsigned short us, size_t N)
{
    CUresult ret;
    ret = g.m_cuMemsetD16_v2(dstDevice,us,N);
    return ret;
}

CUresult __stdcall cuMemsetD32_v2(CUdeviceptr dstDevice, unsigned int ui, size_t N)
{
    CUresult ret;
    ret = g.m_cuMemsetD32_v2(dstDevice,ui,N);
    return ret;
}

CUresult __stdcall cuMemsetD2D8_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D8_v2(dstDevice,dstPitch,uc,Width,Height);
    return ret;
}

CUresult __stdcall cuMemsetD2D16_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D16_v2(dstDevice,dstPitch,us,Width,Height);
    return ret;
}

CUresult __stdcall cuMemsetD2D32_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D32_v2(dstDevice,dstPitch,ui,Width,Height);
    return ret;
}

CUresult __stdcall cuMemsetD8Async(CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD8Async(dstDevice,uc,N,hStream);
    return ret;
}

CUresult __stdcall cuMemsetD16Async(CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD16Async(dstDevice,us,N,hStream);
    return ret;
}

CUresult __stdcall cuMemsetD32Async(CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD32Async(dstDevice,ui,N,hStream);
    return ret;
}

CUresult __stdcall cuMemsetD2D8Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D8Async(dstDevice,dstPitch,uc,Width,Height,hStream);
    return ret;
}

CUresult __stdcall cuMemsetD2D16Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D16Async(dstDevice,dstPitch,us,Width,Height,hStream);
    return ret;
}

CUresult __stdcall cuMemsetD2D32Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D32Async(dstDevice,dstPitch,ui,Width,Height,hStream);
    return ret;
}

CUresult __stdcall cuArrayCreate_v2(CUarray *pHandle, const CUDA_ARRAY_DESCRIPTOR *pAllocateArray)
{
    CUresult ret;
    ret = g.m_cuArrayCreate_v2(pHandle,pAllocateArray);
    return ret;
}

CUresult __stdcall cuArrayGetDescriptor_v2(CUDA_ARRAY_DESCRIPTOR *pArrayDescriptor, CUarray hArray)
{
    CUresult ret;
    ret = g.m_cuArrayGetDescriptor_v2(pArrayDescriptor,hArray);
    return ret;
}

CUresult __stdcall cuArrayDestroy(CUarray hArray)
{
    CUresult ret;
    ret = g.m_cuArrayDestroy(hArray);
    return ret;
}

CUresult __stdcall cuArray3DCreate_v2(CUarray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR *pAllocateArray)
{
    CUresult ret;
    ret = g.m_cuArray3DCreate_v2(pHandle,pAllocateArray);
    return ret;
}

CUresult __stdcall cuArray3DGetDescriptor_v2(CUDA_ARRAY3D_DESCRIPTOR *pArrayDescriptor, CUarray hArray)
{
    CUresult ret;
    ret = g.m_cuArray3DGetDescriptor_v2(pArrayDescriptor,hArray);
    return ret;
}

CUresult __stdcall cuMipmappedArrayCreate(CUmipmappedArray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR *pMipmappedArrayDesc, unsigned int numMipmapLevels)
{
    CUresult ret;
    ret = g.m_cuMipmappedArrayCreate(pHandle,pMipmappedArrayDesc,numMipmapLevels);
    return ret;
}

CUresult __stdcall cuMipmappedArrayGetLevel(CUarray *pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level)
{
    CUresult ret;
    ret = g.m_cuMipmappedArrayGetLevel(pLevelArray,hMipmappedArray,level);
    return ret;
}

CUresult __stdcall cuMipmappedArrayDestroy(CUmipmappedArray hMipmappedArray)
{
    CUresult ret;
    ret = g.m_cuMipmappedArrayDestroy(hMipmappedArray);
    return ret;
}

CUresult __stdcall cuPointerGetAttribute(void *data, CUpointer_attribute attribute, CUdeviceptr ptr)
{
    CUresult ret;
    ret = g.m_cuPointerGetAttribute(data,attribute,ptr);
    return ret;
}

CUresult __stdcall cuMemPrefetchAsync(CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemPrefetchAsync(devPtr,count,dstDevice,hStream);
    return ret;
}

CUresult __stdcall cuMemAdvise(CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device)
{
    CUresult ret;
    ret = g.m_cuMemAdvise(devPtr,count,advice,device);
    return ret;
}

CUresult __stdcall cuMemRangeGetAttribute(void *data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count)
{
    CUresult ret;
    ret = g.m_cuMemRangeGetAttribute(data,dataSize,attribute,devPtr,count);
    return ret;
}

CUresult __stdcall cuMemRangeGetAttributes(void **data, size_t *dataSizes, CUmem_range_attribute *attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count)
{
    CUresult ret;
    ret = g.m_cuMemRangeGetAttributes(data,dataSizes,attributes,numAttributes,devPtr,count);
    return ret;
}

CUresult __stdcall cuPointerSetAttribute(const void *value, CUpointer_attribute attribute, CUdeviceptr ptr)
{
    CUresult ret;
    ret = g.m_cuPointerSetAttribute(value,attribute,ptr);
    return ret;
}

CUresult __stdcall cuPointerGetAttributes(unsigned int numAttributes, CUpointer_attribute *attributes, void **data, CUdeviceptr ptr)
{
    CUresult ret;
    ret = g.m_cuPointerGetAttributes(numAttributes,attributes,data,ptr);
    return ret;
}

CUresult __stdcall cuStreamCreate(CUstream *phStream, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuStreamCreate(phStream,Flags);
    return ret;
}

CUresult __stdcall cuStreamCreateWithPriority(CUstream *phStream, unsigned int flags, int priority)
{
    CUresult ret;
    ret = g.m_cuStreamCreateWithPriority(phStream,flags,priority);
    return ret;
}

CUresult __stdcall cuStreamGetPriority(CUstream hStream, int *priority)
{
    CUresult ret;
    ret = g.m_cuStreamGetPriority(hStream,priority);
    return ret;
}

CUresult __stdcall cuStreamGetFlags(CUstream hStream, unsigned int *flags)
{
    CUresult ret;
    ret = g.m_cuStreamGetFlags(hStream,flags);
    return ret;
}

CUresult __stdcall cuStreamGetCtx(CUstream hStream, CUcontext *pctx)
{
    CUresult ret;
    ret = g.m_cuStreamGetCtx(hStream,pctx);
    return ret;
}

CUresult __stdcall cuStreamWaitEvent(CUstream hStream, CUevent hEvent, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuStreamWaitEvent(hStream,hEvent,Flags);
    return ret;
}

CUresult __stdcall cuStreamAddCallback(CUstream hStream, CUstreamCallback callback, void *userData, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamAddCallback(hStream,callback,userData,flags);
    return ret;
}

CUresult __stdcall cuStreamBeginCapture(CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuStreamBeginCapture(hStream);
    return ret;
}

CUresult __stdcall cuStreamEndCapture(CUstream hStream, CUgraph *phGraph)
{
    CUresult ret;
    ret = g.m_cuStreamEndCapture(hStream,phGraph);
    return ret;
}

CUresult __stdcall cuStreamIsCapturing(CUstream hStream, CUstreamCaptureStatus *captureStatus)
{
    CUresult ret;
    ret = g.m_cuStreamIsCapturing(hStream,captureStatus);
    return ret;
}

CUresult __stdcall cuStreamAttachMemAsync(CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamAttachMemAsync(hStream,dptr,length,flags);
    return ret;
}

CUresult __stdcall cuStreamQuery(CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuStreamQuery(hStream);
    return ret;
}

CUresult __stdcall cuStreamSynchronize(CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuStreamSynchronize(hStream);
    return ret;
}

CUresult __stdcall cuStreamDestroy_v2(CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuStreamDestroy_v2(hStream);
    return ret;
}

CUresult __stdcall cuEventCreate(CUevent *phEvent, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuEventCreate(phEvent,Flags);
    return ret;
}

CUresult __stdcall cuEventRecord(CUevent hEvent, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuEventRecord(hEvent,hStream);
    return ret;
}

CUresult __stdcall cuEventQuery(CUevent hEvent)
{
    CUresult ret;
    ret = g.m_cuEventQuery(hEvent);
    return ret;
}

CUresult __stdcall cuEventSynchronize(CUevent hEvent)
{
    CUresult ret;
    ret = g.m_cuEventSynchronize(hEvent);
    return ret;
}

CUresult __stdcall cuEventDestroy_v2(CUevent hEvent)
{
    CUresult ret;
    ret = g.m_cuEventDestroy_v2(hEvent);
    return ret;
}

CUresult __stdcall cuEventElapsedTime(float *pMilliseconds, CUevent hStart, CUevent hEnd)
{
    CUresult ret;
    ret = g.m_cuEventElapsedTime(pMilliseconds,hStart,hEnd);
    return ret;
}

CUresult __stdcall cuImportExternalMemory(CUexternalMemory *extMem_out, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC *memHandleDesc)
{
    CUresult ret;
    ret = g.m_cuImportExternalMemory(extMem_out,memHandleDesc);
    return ret;
}

CUresult __stdcall cuExternalMemoryGetMappedBuffer(CUdeviceptr *devPtr, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC *bufferDesc)
{
    CUresult ret;
    ret = g.m_cuExternalMemoryGetMappedBuffer(devPtr,extMem,bufferDesc);
    return ret;
}

CUresult __stdcall cuExternalMemoryGetMappedMipmappedArray(CUmipmappedArray *mipmap, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC *mipmapDesc)
{
    CUresult ret;
    ret = g.m_cuExternalMemoryGetMappedMipmappedArray(mipmap,extMem,mipmapDesc);
    return ret;
}

CUresult __stdcall cuDestroyExternalMemory(CUexternalMemory extMem)
{
    CUresult ret;
    ret = g.m_cuDestroyExternalMemory(extMem);
    return ret;
}

CUresult __stdcall cuImportExternalSemaphore(CUexternalSemaphore *extSem_out, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC *semHandleDesc)
{
    CUresult ret;
    ret = g.m_cuImportExternalSemaphore(extSem_out,semHandleDesc);
    return ret;
}

CUresult __stdcall cuSignalExternalSemaphoresAsync(const CUexternalSemaphore *extSemArray, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS *paramsArray, unsigned int numExtSems, CUstream stream)
{
    CUresult ret;
    ret = g.m_cuSignalExternalSemaphoresAsync(extSemArray,paramsArray,numExtSems,stream);
    return ret;
}

CUresult __stdcall cuWaitExternalSemaphoresAsync(const CUexternalSemaphore *extSemArray, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS *paramsArray, unsigned int numExtSems, CUstream stream)
{
    CUresult ret;
    ret = g.m_cuWaitExternalSemaphoresAsync(extSemArray,paramsArray,numExtSems,stream);
    return ret;
}

CUresult __stdcall cuDestroyExternalSemaphore(CUexternalSemaphore extSem)
{
    CUresult ret;
    ret = g.m_cuDestroyExternalSemaphore(extSem);
    return ret;
}

CUresult __stdcall cuStreamWaitValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamWaitValue32(stream,addr,value,flags);
    return ret;
}

CUresult __stdcall cuStreamWaitValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamWaitValue64(stream,addr,value,flags);
    return ret;
}

CUresult __stdcall cuStreamWriteValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamWriteValue32(stream,addr,value,flags);
    return ret;
}

CUresult __stdcall cuStreamWriteValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamWriteValue64(stream,addr,value,flags);
    return ret;
}

CUresult __stdcall cuStreamBatchMemOp(CUstream stream, unsigned int count, CUstreamBatchMemOpParams *paramArray, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamBatchMemOp(stream,count,paramArray,flags);
    return ret;
}

CUresult __stdcall cuFuncGetAttribute(int *pi, CUfunction_attribute attrib, CUfunction hfunc)
{
    CUresult ret;
    ret = g.m_cuFuncGetAttribute(pi,attrib,hfunc);
    return ret;
}

CUresult __stdcall cuFuncSetAttribute(CUfunction hfunc, CUfunction_attribute attrib, int value)
{
    CUresult ret;
    ret = g.m_cuFuncSetAttribute(hfunc,attrib,value);
    return ret;
}

CUresult __stdcall cuFuncSetCacheConfig(CUfunction hfunc, CUfunc_cache config)
{
    CUresult ret;
    ret = g.m_cuFuncSetCacheConfig(hfunc,config);
    return ret;
}

CUresult __stdcall cuFuncSetSharedMemConfig(CUfunction hfunc, CUsharedconfig config)
{
    CUresult ret;
    ret = g.m_cuFuncSetSharedMemConfig(hfunc,config);
    return ret;
}

CUresult __stdcall cuLaunchKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void **kernelParams, void **extra)
{
    CUresult ret;
    ret = g.m_cuLaunchKernel(f,gridDimX,gridDimY,gridDimZ,blockDimX,blockDimY,blockDimZ,sharedMemBytes,hStream,kernelParams,extra);
    return ret;
}

CUresult __stdcall cuLaunchCooperativeKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void **kernelParams)
{
    CUresult ret;
    ret = g.m_cuLaunchCooperativeKernel(f,gridDimX,gridDimY,gridDimZ,blockDimX,blockDimY,blockDimZ,sharedMemBytes,hStream,kernelParams);
    return ret;
}

CUresult __stdcall cuLaunchCooperativeKernelMultiDevice(CUDA_LAUNCH_PARAMS *launchParamsList, unsigned int numDevices, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuLaunchCooperativeKernelMultiDevice(launchParamsList,numDevices,flags);
    return ret;
}

CUresult __stdcall cuLaunchHostFunc(CUstream hStream, CUhostFn fn, void *userData)
{
    CUresult ret;
    ret = g.m_cuLaunchHostFunc(hStream,fn,userData);
    return ret;
}

CUresult __stdcall cuFuncSetBlockShape(CUfunction hfunc, int x, int y, int z)
{
    CUresult ret;
    ret = g.m_cuFuncSetBlockShape(hfunc,x,y,z);
    return ret;
}

CUresult __stdcall cuFuncSetSharedSize(CUfunction hfunc, unsigned int bytes)
{
    CUresult ret;
    ret = g.m_cuFuncSetSharedSize(hfunc,bytes);
    return ret;
}

CUresult __stdcall cuParamSetSize(CUfunction hfunc, unsigned int numbytes)
{
    CUresult ret;
    ret = g.m_cuParamSetSize(hfunc,numbytes);
    return ret;
}

CUresult __stdcall cuParamSeti(CUfunction hfunc, int offset, unsigned int value)
{
    CUresult ret;
    ret = g.m_cuParamSeti(hfunc,offset,value);
    return ret;
}

CUresult __stdcall cuParamSetf(CUfunction hfunc, int offset, float value)
{
    CUresult ret;
    ret = g.m_cuParamSetf(hfunc,offset,value);
    return ret;
}

CUresult __stdcall cuParamSetv(CUfunction hfunc, int offset, void *ptr, unsigned int numbytes)
{
    CUresult ret;
    ret = g.m_cuParamSetv(hfunc,offset,ptr,numbytes);
    return ret;
}

CUresult __stdcall cuLaunch(CUfunction f)
{
    CUresult ret;
    ret = g.m_cuLaunch(f);
    return ret;
}

CUresult __stdcall cuLaunchGrid(CUfunction f, int grid_width, int grid_height)
{
    CUresult ret;
    ret = g.m_cuLaunchGrid(f,grid_width,grid_height);
    return ret;
}

CUresult __stdcall cuLaunchGridAsync(CUfunction f, int grid_width, int grid_height, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuLaunchGridAsync(f,grid_width,grid_height,hStream);
    return ret;
}

CUresult __stdcall cuParamSetTexRef(CUfunction hfunc, int texunit, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuParamSetTexRef(hfunc,texunit,hTexRef);
    return ret;
}

CUresult __stdcall cuGraphCreate(CUgraph *phGraph, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuGraphCreate(phGraph,flags);
    return ret;
}

CUresult __stdcall cuGraphAddKernelNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_KERNEL_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphAddKernelNode(phGraphNode,hGraph,dependencies,numDependencies,nodeParams);
    return ret;
}

CUresult __stdcall cuGraphKernelNodeGetParams(CUgraphNode hNode, CUDA_KERNEL_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphKernelNodeGetParams(hNode,nodeParams);
    return ret;
}

CUresult __stdcall cuGraphKernelNodeSetParams(CUgraphNode hNode, const CUDA_KERNEL_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphKernelNodeSetParams(hNode,nodeParams);
    return ret;
}

CUresult __stdcall cuGraphAddMemcpyNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_MEMCPY3D *copyParams, CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuGraphAddMemcpyNode(phGraphNode,hGraph,dependencies,numDependencies,copyParams,ctx);
    return ret;
}

CUresult __stdcall cuGraphMemcpyNodeGetParams(CUgraphNode hNode, CUDA_MEMCPY3D *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphMemcpyNodeGetParams(hNode,nodeParams);
    return ret;
}

CUresult __stdcall cuGraphMemcpyNodeSetParams(CUgraphNode hNode, const CUDA_MEMCPY3D *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphMemcpyNodeSetParams(hNode,nodeParams);
    return ret;
}

CUresult __stdcall cuGraphAddMemsetNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_MEMSET_NODE_PARAMS *memsetParams, CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuGraphAddMemsetNode(phGraphNode,hGraph,dependencies,numDependencies,memsetParams,ctx);
    return ret;
}

CUresult __stdcall cuGraphMemsetNodeGetParams(CUgraphNode hNode, CUDA_MEMSET_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphMemsetNodeGetParams(hNode,nodeParams);
    return ret;
}

CUresult __stdcall cuGraphMemsetNodeSetParams(CUgraphNode hNode, const CUDA_MEMSET_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphMemsetNodeSetParams(hNode,nodeParams);
    return ret;
}

CUresult __stdcall cuGraphAddHostNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_HOST_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphAddHostNode(phGraphNode,hGraph,dependencies,numDependencies,nodeParams);
    return ret;
}

CUresult __stdcall cuGraphHostNodeGetParams(CUgraphNode hNode, CUDA_HOST_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphHostNodeGetParams(hNode,nodeParams);
    return ret;
}

CUresult __stdcall cuGraphHostNodeSetParams(CUgraphNode hNode, const CUDA_HOST_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphHostNodeSetParams(hNode,nodeParams);
    return ret;
}

CUresult __stdcall cuGraphAddChildGraphNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, CUgraph childGraph)
{
    CUresult ret;
    ret = g.m_cuGraphAddChildGraphNode(phGraphNode,hGraph,dependencies,numDependencies,childGraph);
    return ret;
}

CUresult __stdcall cuGraphChildGraphNodeGetGraph(CUgraphNode hNode, CUgraph *phGraph)
{
    CUresult ret;
    ret = g.m_cuGraphChildGraphNodeGetGraph(hNode,phGraph);
    return ret;
}

CUresult __stdcall cuGraphAddEmptyNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies)
{
    CUresult ret;
    ret = g.m_cuGraphAddEmptyNode(phGraphNode,hGraph,dependencies,numDependencies);
    return ret;
}

CUresult __stdcall cuGraphClone(CUgraph *phGraphClone, CUgraph originalGraph)
{
    CUresult ret;
    ret = g.m_cuGraphClone(phGraphClone,originalGraph);
    return ret;
}

CUresult __stdcall cuGraphNodeFindInClone(CUgraphNode *phNode, CUgraphNode hOriginalNode, CUgraph hClonedGraph)
{
    CUresult ret;
    ret = g.m_cuGraphNodeFindInClone(phNode,hOriginalNode,hClonedGraph);
    return ret;
}

CUresult __stdcall cuGraphNodeGetType(CUgraphNode hNode, CUgraphNodeType *type)
{
    CUresult ret;
    ret = g.m_cuGraphNodeGetType(hNode,type);
    return ret;
}

CUresult __stdcall cuGraphGetNodes(CUgraph hGraph, CUgraphNode *nodes, size_t *numNodes)
{
    CUresult ret;
    ret = g.m_cuGraphGetNodes(hGraph,nodes,numNodes);
    return ret;
}

CUresult __stdcall cuGraphGetRootNodes(CUgraph hGraph, CUgraphNode *rootNodes, size_t *numRootNodes)
{
    CUresult ret;
    ret = g.m_cuGraphGetRootNodes(hGraph,rootNodes,numRootNodes);
    return ret;
}

CUresult __stdcall cuGraphGetEdges(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t *numEdges)
{
    CUresult ret;
    ret = g.m_cuGraphGetEdges(hGraph,from,to,numEdges);
    return ret;
}

CUresult __stdcall cuGraphNodeGetDependencies(CUgraphNode hNode, CUgraphNode *dependencies, size_t *numDependencies)
{
    CUresult ret;
    ret = g.m_cuGraphNodeGetDependencies(hNode,dependencies,numDependencies);
    return ret;
}

CUresult __stdcall cuGraphNodeGetDependentNodes(CUgraphNode hNode, CUgraphNode *dependentNodes, size_t *numDependentNodes)
{
    CUresult ret;
    ret = g.m_cuGraphNodeGetDependentNodes(hNode,dependentNodes,numDependentNodes);
    return ret;
}

CUresult __stdcall cuGraphAddDependencies(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t numDependencies)
{
    CUresult ret;
    ret = g.m_cuGraphAddDependencies(hGraph,from,to,numDependencies);
    return ret;
}

CUresult __stdcall cuGraphRemoveDependencies(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t numDependencies)
{
    CUresult ret;
    ret = g.m_cuGraphRemoveDependencies(hGraph,from,to,numDependencies);
    return ret;
}

CUresult __stdcall cuGraphDestroyNode(CUgraphNode hNode)
{
    CUresult ret;
    ret = g.m_cuGraphDestroyNode(hNode);
    return ret;
}

CUresult __stdcall cuGraphInstantiate(CUgraphExec *phGraphExec, CUgraph hGraph, CUgraphNode *phErrorNode, char *logBuffer, size_t bufferSize)
{
    CUresult ret;
    ret = g.m_cuGraphInstantiate(phGraphExec,hGraph,phErrorNode,logBuffer,bufferSize);
    return ret;
}

CUresult __stdcall cuGraphLaunch(CUgraphExec hGraphExec, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuGraphLaunch(hGraphExec,hStream);
    return ret;
}

CUresult __stdcall cuGraphExecDestroy(CUgraphExec hGraphExec)
{
    CUresult ret;
    ret = g.m_cuGraphExecDestroy(hGraphExec);
    return ret;
}

CUresult __stdcall cuGraphDestroy(CUgraph hGraph)
{
    CUresult ret;
    ret = g.m_cuGraphDestroy(hGraph);
    return ret;
}

CUresult __stdcall cuOccupancyMaxActiveBlocksPerMultiprocessor(int *numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize)
{
    CUresult ret;
    ret = g.m_cuOccupancyMaxActiveBlocksPerMultiprocessor(numBlocks,func,blockSize,dynamicSMemSize);
    return ret;
}

CUresult __stdcall cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int *numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(numBlocks,func,blockSize,dynamicSMemSize,flags);
    return ret;
}

CUresult __stdcall cuOccupancyMaxPotentialBlockSize(int *minGridSize, int *blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit)
{
    CUresult ret;
    ret = g.m_cuOccupancyMaxPotentialBlockSize(minGridSize,blockSize,func,blockSizeToDynamicSMemSize,dynamicSMemSize,blockSizeLimit);
    return ret;
}

CUresult __stdcall cuOccupancyMaxPotentialBlockSizeWithFlags(int *minGridSize, int *blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuOccupancyMaxPotentialBlockSizeWithFlags(minGridSize,blockSize,func,blockSizeToDynamicSMemSize,dynamicSMemSize,blockSizeLimit,flags);
    return ret;
}

CUresult __stdcall cuTexRefSetArray(CUtexref hTexRef, CUarray hArray, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuTexRefSetArray(hTexRef,hArray,Flags);
    return ret;
}

CUresult __stdcall cuTexRefSetMipmappedArray(CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuTexRefSetMipmappedArray(hTexRef,hMipmappedArray,Flags);
    return ret;
}

CUresult __stdcall cuTexRefSetAddress_v2(size_t *ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes)
{
    CUresult ret;
    ret = g.m_cuTexRefSetAddress_v2(ByteOffset,hTexRef,dptr,bytes);
    return ret;
}

CUresult __stdcall cuTexRefSetAddress2D_v3(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR *desc, CUdeviceptr dptr, size_t Pitch)
{
    CUresult ret;
    ret = g.m_cuTexRefSetAddress2D_v3(hTexRef,desc,dptr,Pitch);
    return ret;
}

CUresult __stdcall cuTexRefSetFormat(CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents)
{
    CUresult ret;
    ret = g.m_cuTexRefSetFormat(hTexRef,fmt,NumPackedComponents);
    return ret;
}

CUresult __stdcall cuTexRefSetAddressMode(CUtexref hTexRef, int dim, CUaddress_mode am)
{
    CUresult ret;
    ret = g.m_cuTexRefSetAddressMode(hTexRef,dim,am);
    return ret;
}

CUresult __stdcall cuTexRefSetFilterMode(CUtexref hTexRef, CUfilter_mode fm)
{
    CUresult ret;
    ret = g.m_cuTexRefSetFilterMode(hTexRef,fm);
    return ret;
}

CUresult __stdcall cuTexRefSetMipmapFilterMode(CUtexref hTexRef, CUfilter_mode fm)
{
    CUresult ret;
    ret = g.m_cuTexRefSetMipmapFilterMode(hTexRef,fm);
    return ret;
}

CUresult __stdcall cuTexRefSetMipmapLevelBias(CUtexref hTexRef, float bias)
{
    CUresult ret;
    ret = g.m_cuTexRefSetMipmapLevelBias(hTexRef,bias);
    return ret;
}

CUresult __stdcall cuTexRefSetMipmapLevelClamp(CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp)
{
    CUresult ret;
    ret = g.m_cuTexRefSetMipmapLevelClamp(hTexRef,minMipmapLevelClamp,maxMipmapLevelClamp);
    return ret;
}

CUresult __stdcall cuTexRefSetMaxAnisotropy(CUtexref hTexRef, unsigned int maxAniso)
{
    CUresult ret;
    ret = g.m_cuTexRefSetMaxAnisotropy(hTexRef,maxAniso);
    return ret;
}

CUresult __stdcall cuTexRefSetBorderColor(CUtexref hTexRef, float *pBorderColor)
{
    CUresult ret;
    ret = g.m_cuTexRefSetBorderColor(hTexRef,pBorderColor);
    return ret;
}

CUresult __stdcall cuTexRefSetFlags(CUtexref hTexRef, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuTexRefSetFlags(hTexRef,Flags);
    return ret;
}

CUresult __stdcall cuTexRefGetAddress_v2(CUdeviceptr *pdptr, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetAddress_v2(pdptr,hTexRef);
    return ret;
}

CUresult __stdcall cuTexRefGetArray(CUarray *phArray, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetArray(phArray,hTexRef);
    return ret;
}

CUresult __stdcall cuTexRefGetMipmappedArray(CUmipmappedArray *phMipmappedArray, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetMipmappedArray(phMipmappedArray,hTexRef);
    return ret;
}

CUresult __stdcall cuTexRefGetAddressMode(CUaddress_mode *pam, CUtexref hTexRef, int dim)
{
    CUresult ret;
    ret = g.m_cuTexRefGetAddressMode(pam,hTexRef,dim);
    return ret;
}

CUresult __stdcall cuTexRefGetFilterMode(CUfilter_mode *pfm, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetFilterMode(pfm,hTexRef);
    return ret;
}

CUresult __stdcall cuTexRefGetFormat(CUarray_format *pFormat, int *pNumChannels, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetFormat(pFormat,pNumChannels,hTexRef);
    return ret;
}

CUresult __stdcall cuTexRefGetMipmapFilterMode(CUfilter_mode *pfm, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetMipmapFilterMode(pfm,hTexRef);
    return ret;
}

CUresult __stdcall cuTexRefGetMipmapLevelBias(float *pbias, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetMipmapLevelBias(pbias,hTexRef);
    return ret;
}

CUresult __stdcall cuTexRefGetMipmapLevelClamp(float *pminMipmapLevelClamp, float *pmaxMipmapLevelClamp, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetMipmapLevelClamp(pminMipmapLevelClamp,pmaxMipmapLevelClamp,hTexRef);
    return ret;
}

CUresult __stdcall cuTexRefGetMaxAnisotropy(int *pmaxAniso, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetMaxAnisotropy(pmaxAniso,hTexRef);
    return ret;
}

CUresult __stdcall cuTexRefGetBorderColor(float *pBorderColor, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetBorderColor(pBorderColor,hTexRef);
    return ret;
}

CUresult __stdcall cuTexRefGetFlags(unsigned int *pFlags, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetFlags(pFlags,hTexRef);
    return ret;
}

CUresult __stdcall cuTexRefCreate(CUtexref *pTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefCreate(pTexRef);
    return ret;
}

CUresult __stdcall cuTexRefDestroy(CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefDestroy(hTexRef);
    return ret;
}

CUresult __stdcall cuSurfRefSetArray(CUsurfref hSurfRef, CUarray hArray, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuSurfRefSetArray(hSurfRef,hArray,Flags);
    return ret;
}

CUresult __stdcall cuSurfRefGetArray(CUarray *phArray, CUsurfref hSurfRef)
{
    CUresult ret;
    ret = g.m_cuSurfRefGetArray(phArray,hSurfRef);
    return ret;
}

CUresult __stdcall cuTexObjectCreate(CUtexObject *pTexObject, const CUDA_RESOURCE_DESC *pResDesc, const CUDA_TEXTURE_DESC *pTexDesc, const CUDA_RESOURCE_VIEW_DESC *pResViewDesc)
{
    CUresult ret;
    ret = g.m_cuTexObjectCreate(pTexObject,pResDesc,pTexDesc,pResViewDesc);
    return ret;
}

CUresult __stdcall cuTexObjectDestroy(CUtexObject texObject)
{
    CUresult ret;
    ret = g.m_cuTexObjectDestroy(texObject);
    return ret;
}

CUresult __stdcall cuTexObjectGetResourceDesc(CUDA_RESOURCE_DESC *pResDesc, CUtexObject texObject)
{
    CUresult ret;
    ret = g.m_cuTexObjectGetResourceDesc(pResDesc,texObject);
    return ret;
}

CUresult __stdcall cuTexObjectGetTextureDesc(CUDA_TEXTURE_DESC *pTexDesc, CUtexObject texObject)
{
    CUresult ret;
    ret = g.m_cuTexObjectGetTextureDesc(pTexDesc,texObject);
    return ret;
}

CUresult __stdcall cuTexObjectGetResourceViewDesc(CUDA_RESOURCE_VIEW_DESC *pResViewDesc, CUtexObject texObject)
{
    CUresult ret;
    ret = g.m_cuTexObjectGetResourceViewDesc(pResViewDesc,texObject);
    return ret;
}

CUresult __stdcall cuSurfObjectCreate(CUsurfObject *pSurfObject, const CUDA_RESOURCE_DESC *pResDesc)
{
    CUresult ret;
    ret = g.m_cuSurfObjectCreate(pSurfObject,pResDesc);
    return ret;
}

CUresult __stdcall cuSurfObjectDestroy(CUsurfObject surfObject)
{
    CUresult ret;
    ret = g.m_cuSurfObjectDestroy(surfObject);
    return ret;
}

CUresult __stdcall cuSurfObjectGetResourceDesc(CUDA_RESOURCE_DESC *pResDesc, CUsurfObject surfObject)
{
    CUresult ret;
    ret = g.m_cuSurfObjectGetResourceDesc(pResDesc,surfObject);
    return ret;
}

CUresult __stdcall cuDeviceCanAccessPeer(int *canAccessPeer, CUdevice dev, CUdevice peerDev)
{
    CUresult ret;
    ret = g.m_cuDeviceCanAccessPeer(canAccessPeer,dev,peerDev);
    return ret;
}

CUresult __stdcall cuCtxEnablePeerAccess(CUcontext peerContext, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuCtxEnablePeerAccess(peerContext,Flags);
    return ret;
}

CUresult __stdcall cuCtxDisablePeerAccess(CUcontext peerContext)
{
    CUresult ret;
    ret = g.m_cuCtxDisablePeerAccess(peerContext);
    return ret;
}

CUresult __stdcall cuDeviceGetP2PAttribute(int* value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice)
{
    CUresult ret;
    ret = g.m_cuDeviceGetP2PAttribute(value,attrib,srcDevice,dstDevice);
    return ret;
}

CUresult __stdcall cuGraphicsUnregisterResource(CUgraphicsResource resource)
{
    CUresult ret;
    ret = g.m_cuGraphicsUnregisterResource(resource);
    return ret;
}

CUresult __stdcall cuGraphicsSubResourceGetMappedArray(CUarray *pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel)
{
    CUresult ret;
    ret = g.m_cuGraphicsSubResourceGetMappedArray(pArray,resource,arrayIndex,mipLevel);
    return ret;
}

CUresult __stdcall cuGraphicsResourceGetMappedMipmappedArray(CUmipmappedArray *pMipmappedArray, CUgraphicsResource resource)
{
    CUresult ret;
    ret = g.m_cuGraphicsResourceGetMappedMipmappedArray(pMipmappedArray,resource);
    return ret;
}

CUresult __stdcall cuGraphicsResourceGetMappedPointer_v2(CUdeviceptr *pDevPtr, size_t *pSize, CUgraphicsResource resource)
{
    CUresult ret;
    ret = g.m_cuGraphicsResourceGetMappedPointer_v2(pDevPtr,pSize,resource);
    return ret;
}

CUresult __stdcall cuGraphicsResourceSetMapFlags_v2(CUgraphicsResource resource, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuGraphicsResourceSetMapFlags_v2(resource,flags);
    return ret;
}

CUresult __stdcall cuGraphicsMapResources(unsigned int count, CUgraphicsResource *resources, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuGraphicsMapResources(count,resources,hStream);
    return ret;
}

CUresult __stdcall cuGraphicsUnmapResources(unsigned int count, CUgraphicsResource *resources, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuGraphicsUnmapResources(count,resources,hStream);
    return ret;
}

CUresult __stdcall cuGetExportTable(const void **ppExportTable, const CUuuid *pExportTableId)
{
    CUresult ret;
    ret = g.m_cuGetExportTable(ppExportTable,pExportTableId);
    return ret;
}

