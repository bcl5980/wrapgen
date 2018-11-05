#include <windows.h>
#include <fstream>
#include <map>
#include <string>
#include "cuda_wrap.h"

using std::ofstream;
using std::map;
using std::string;

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
typedef CUresult(__stdcall *pcuDeviceGetP2PAttribute)(int *value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice);
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

    map<int, string> m_mapESCUipcMem_flags;
    map<int, string> m_mapESCUmemAttach_flags;
    map<int, string> m_mapESCUctx_flags;
    map<int, string> m_mapESCUstream_flags;
    map<int, string> m_mapESCUevent_flags;
    map<int, string> m_mapESCUstreamWaitValue_flags;
    map<int, string> m_mapESCUstreamWriteValue_flags;
    map<int, string> m_mapESCUstreamBatchMemOpType;
    map<int, string> m_mapESCUoccupancy_flags;
    map<int, string> m_mapESCUarray_format;
    map<int, string> m_mapESCUaddress_mode;
    map<int, string> m_mapESCUfilter_mode;
    map<int, string> m_mapESCUdevice_attribute;
    map<int, string> m_mapESCUpointer_attribute;
    map<int, string> m_mapESCUfunction_attribute;
    map<int, string> m_mapESCUfunc_cache;
    map<int, string> m_mapESCUsharedconfig;
    map<int, string> m_mapESCUshared_carveout;
    map<int, string> m_mapESCUmemorytype;
    map<int, string> m_mapESCUcomputemode;
    map<int, string> m_mapESCUmem_advise;
    map<int, string> m_mapESCUmem_range_attribute;
    map<int, string> m_mapESCUjit_option;
    map<int, string> m_mapESCUjit_target;
    map<int, string> m_mapESCUjit_fallback;
    map<int, string> m_mapESCUjit_cacheMode;
    map<int, string> m_mapESCUjitInputType;
    map<int, string> m_mapESCUgraphicsRegisterFlags;
    map<int, string> m_mapESCUgraphicsMapResourceFlags;
    map<int, string> m_mapESCUarray_cubemap_face;
    map<int, string> m_mapESCUlimit;
    map<int, string> m_mapESCUresourcetype;
    map<int, string> m_mapESCUgraphNodeType;
    map<int, string> m_mapESCUstreamCaptureStatus;
    map<int, string> m_mapESCUresult;
    map<int, string> m_mapESCUdevice_P2PAttribute;
    map<int, string> m_mapESCUresourceViewFormat;
    map<int, string> m_mapESCUexternalMemoryHandleType;
    map<int, string> m_mapESCUexternalSemaphoreHandleType;

    wrap()
    {
        HMODULE h = LoadLibrary("nvcuda_orig.dll");
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

        m_mapESCUipcMem_flags[1] = "CU_IPC_MEM_LAZY_ENABLE_PEER_ACCESS";

        m_mapESCUmemAttach_flags[1] = "CU_MEM_ATTACH_GLOBAL";
        m_mapESCUmemAttach_flags[2] = "CU_MEM_ATTACH_HOST";
        m_mapESCUmemAttach_flags[4] = "CU_MEM_ATTACH_SINGLE";

        m_mapESCUctx_flags[0] = "CU_CTX_SCHED_AUTO";
        m_mapESCUctx_flags[1] = "CU_CTX_SCHED_SPIN";
        m_mapESCUctx_flags[2] = "CU_CTX_SCHED_YIELD";
        m_mapESCUctx_flags[4] = "CU_CTX_BLOCKING_SYNC";
        m_mapESCUctx_flags[7] = "CU_CTX_SCHED_MASK";
        m_mapESCUctx_flags[8] = "CU_CTX_MAP_HOST";
        m_mapESCUctx_flags[16] = "CU_CTX_LMEM_RESIZE_TO_MAX";
        m_mapESCUctx_flags[31] = "CU_CTX_FLAGS_MASK";

        m_mapESCUstream_flags[0] = "CU_STREAM_DEFAULT";
        m_mapESCUstream_flags[1] = "CU_STREAM_NON_BLOCKING";

        m_mapESCUevent_flags[0] = "CU_EVENT_DEFAULT";
        m_mapESCUevent_flags[1] = "CU_EVENT_BLOCKING_SYNC";
        m_mapESCUevent_flags[2] = "CU_EVENT_DISABLE_TIMING";
        m_mapESCUevent_flags[4] = "CU_EVENT_INTERPROCESS";

        m_mapESCUstreamWaitValue_flags[0] = "CU_STREAM_WAIT_VALUE_GEQ";
        m_mapESCUstreamWaitValue_flags[1] = "CU_STREAM_WAIT_VALUE_EQ";
        m_mapESCUstreamWaitValue_flags[2] = "CU_STREAM_WAIT_VALUE_AND";
        m_mapESCUstreamWaitValue_flags[3] = "CU_STREAM_WAIT_VALUE_NOR";
        m_mapESCUstreamWaitValue_flags[1073741824] = "CU_STREAM_WAIT_VALUE_FLUSH";

        m_mapESCUstreamWriteValue_flags[0] = "CU_STREAM_WRITE_VALUE_DEFAULT";
        m_mapESCUstreamWriteValue_flags[1] = "CU_STREAM_WRITE_VALUE_NO_MEMORY_BARRIER";

        m_mapESCUstreamBatchMemOpType[1] = "CU_STREAM_MEM_OP_WAIT_VALUE_32";
        m_mapESCUstreamBatchMemOpType[2] = "CU_STREAM_MEM_OP_WRITE_VALUE_32";
        m_mapESCUstreamBatchMemOpType[4] = "CU_STREAM_MEM_OP_WAIT_VALUE_64";
        m_mapESCUstreamBatchMemOpType[5] = "CU_STREAM_MEM_OP_WRITE_VALUE_64";
        m_mapESCUstreamBatchMemOpType[3] = "CU_STREAM_MEM_OP_FLUSH_REMOTE_WRITES";

        m_mapESCUoccupancy_flags[0] = "CU_OCCUPANCY_DEFAULT";
        m_mapESCUoccupancy_flags[1] = "CU_OCCUPANCY_DISABLE_CACHING_OVERRIDE";

        m_mapESCUarray_format[1] = "CU_AD_FORMAT_UNSIGNED_INT8";
        m_mapESCUarray_format[2] = "CU_AD_FORMAT_UNSIGNED_INT16";
        m_mapESCUarray_format[3] = "CU_AD_FORMAT_UNSIGNED_INT32";
        m_mapESCUarray_format[8] = "CU_AD_FORMAT_SIGNED_INT8";
        m_mapESCUarray_format[9] = "CU_AD_FORMAT_SIGNED_INT16";
        m_mapESCUarray_format[10] = "CU_AD_FORMAT_SIGNED_INT32";
        m_mapESCUarray_format[16] = "CU_AD_FORMAT_HALF";
        m_mapESCUarray_format[32] = "CU_AD_FORMAT_FLOAT";

        m_mapESCUaddress_mode[0] = "CU_TR_ADDRESS_MODE_WRAP";
        m_mapESCUaddress_mode[1] = "CU_TR_ADDRESS_MODE_CLAMP";
        m_mapESCUaddress_mode[2] = "CU_TR_ADDRESS_MODE_MIRROR";
        m_mapESCUaddress_mode[3] = "CU_TR_ADDRESS_MODE_BORDER";

        m_mapESCUfilter_mode[0] = "CU_TR_FILTER_MODE_POINT";
        m_mapESCUfilter_mode[1] = "CU_TR_FILTER_MODE_LINEAR";

        m_mapESCUdevice_attribute[1] = "CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK";
        m_mapESCUdevice_attribute[2] = "CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X";
        m_mapESCUdevice_attribute[3] = "CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Y";
        m_mapESCUdevice_attribute[4] = "CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Z";
        m_mapESCUdevice_attribute[5] = "CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_X";
        m_mapESCUdevice_attribute[6] = "CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Y";
        m_mapESCUdevice_attribute[7] = "CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Z";
        m_mapESCUdevice_attribute[8] = "CU_DEVICE_ATTRIBUTE_SHARED_MEMORY_PER_BLOCK";
        m_mapESCUdevice_attribute[9] = "CU_DEVICE_ATTRIBUTE_TOTAL_CONSTANT_MEMORY";
        m_mapESCUdevice_attribute[10] = "CU_DEVICE_ATTRIBUTE_WARP_SIZE";
        m_mapESCUdevice_attribute[11] = "CU_DEVICE_ATTRIBUTE_MAX_PITCH";
        m_mapESCUdevice_attribute[12] = "CU_DEVICE_ATTRIBUTE_REGISTERS_PER_BLOCK";
        m_mapESCUdevice_attribute[13] = "CU_DEVICE_ATTRIBUTE_CLOCK_RATE";
        m_mapESCUdevice_attribute[14] = "CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT";
        m_mapESCUdevice_attribute[15] = "CU_DEVICE_ATTRIBUTE_GPU_OVERLAP";
        m_mapESCUdevice_attribute[16] = "CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT";
        m_mapESCUdevice_attribute[17] = "CU_DEVICE_ATTRIBUTE_KERNEL_EXEC_TIMEOUT";
        m_mapESCUdevice_attribute[18] = "CU_DEVICE_ATTRIBUTE_INTEGRATED";
        m_mapESCUdevice_attribute[19] = "CU_DEVICE_ATTRIBUTE_CAN_MAP_HOST_MEMORY";
        m_mapESCUdevice_attribute[20] = "CU_DEVICE_ATTRIBUTE_COMPUTE_MODE";
        m_mapESCUdevice_attribute[21] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_WIDTH";
        m_mapESCUdevice_attribute[22] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_WIDTH";
        m_mapESCUdevice_attribute[23] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_HEIGHT";
        m_mapESCUdevice_attribute[24] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH";
        m_mapESCUdevice_attribute[25] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT";
        m_mapESCUdevice_attribute[26] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH";
        m_mapESCUdevice_attribute[27] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_WIDTH";
        m_mapESCUdevice_attribute[28] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_HEIGHT";
        m_mapESCUdevice_attribute[29] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_NUMSLICES";
        m_mapESCUdevice_attribute[30] = "CU_DEVICE_ATTRIBUTE_SURFACE_ALIGNMENT";
        m_mapESCUdevice_attribute[31] = "CU_DEVICE_ATTRIBUTE_CONCURRENT_KERNELS";
        m_mapESCUdevice_attribute[32] = "CU_DEVICE_ATTRIBUTE_ECC_ENABLED";
        m_mapESCUdevice_attribute[33] = "CU_DEVICE_ATTRIBUTE_PCI_BUS_ID";
        m_mapESCUdevice_attribute[34] = "CU_DEVICE_ATTRIBUTE_PCI_DEVICE_ID";
        m_mapESCUdevice_attribute[35] = "CU_DEVICE_ATTRIBUTE_TCC_DRIVER";
        m_mapESCUdevice_attribute[36] = "CU_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE";
        m_mapESCUdevice_attribute[37] = "CU_DEVICE_ATTRIBUTE_GLOBAL_MEMORY_BUS_WIDTH";
        m_mapESCUdevice_attribute[38] = "CU_DEVICE_ATTRIBUTE_L2_CACHE_SIZE";
        m_mapESCUdevice_attribute[39] = "CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_MULTIPROCESSOR";
        m_mapESCUdevice_attribute[40] = "CU_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT";
        m_mapESCUdevice_attribute[41] = "CU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING";
        m_mapESCUdevice_attribute[42] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_WIDTH";
        m_mapESCUdevice_attribute[43] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_LAYERS";
        m_mapESCUdevice_attribute[44] = "CU_DEVICE_ATTRIBUTE_CAN_TEX2D_GATHER";
        m_mapESCUdevice_attribute[45] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_WIDTH";
        m_mapESCUdevice_attribute[46] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_HEIGHT";
        m_mapESCUdevice_attribute[47] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH_ALTERNATE";
        m_mapESCUdevice_attribute[48] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT_ALTERNATE";
        m_mapESCUdevice_attribute[49] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH_ALTERNATE";
        m_mapESCUdevice_attribute[50] = "CU_DEVICE_ATTRIBUTE_PCI_DOMAIN_ID";
        m_mapESCUdevice_attribute[51] = "CU_DEVICE_ATTRIBUTE_TEXTURE_PITCH_ALIGNMENT";
        m_mapESCUdevice_attribute[52] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_WIDTH";
        m_mapESCUdevice_attribute[53] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_WIDTH";
        m_mapESCUdevice_attribute[54] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_LAYERS";
        m_mapESCUdevice_attribute[55] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_WIDTH";
        m_mapESCUdevice_attribute[56] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_WIDTH";
        m_mapESCUdevice_attribute[57] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_HEIGHT";
        m_mapESCUdevice_attribute[58] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_WIDTH";
        m_mapESCUdevice_attribute[59] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_HEIGHT";
        m_mapESCUdevice_attribute[60] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_DEPTH";
        m_mapESCUdevice_attribute[61] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_WIDTH";
        m_mapESCUdevice_attribute[62] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_LAYERS";
        m_mapESCUdevice_attribute[63] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_WIDTH";
        m_mapESCUdevice_attribute[64] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_HEIGHT";
        m_mapESCUdevice_attribute[65] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_LAYERS";
        m_mapESCUdevice_attribute[66] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_WIDTH";
        m_mapESCUdevice_attribute[67] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_WIDTH";
        m_mapESCUdevice_attribute[68] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_LAYERS";
        m_mapESCUdevice_attribute[69] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LINEAR_WIDTH";
        m_mapESCUdevice_attribute[70] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_WIDTH";
        m_mapESCUdevice_attribute[71] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_HEIGHT";
        m_mapESCUdevice_attribute[72] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_PITCH";
        m_mapESCUdevice_attribute[73] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_WIDTH";
        m_mapESCUdevice_attribute[74] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_HEIGHT";
        m_mapESCUdevice_attribute[75] = "CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MAJOR";
        m_mapESCUdevice_attribute[76] = "CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MINOR";
        m_mapESCUdevice_attribute[77] = "CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_MIPMAPPED_WIDTH";
        m_mapESCUdevice_attribute[78] = "CU_DEVICE_ATTRIBUTE_STREAM_PRIORITIES_SUPPORTED";
        m_mapESCUdevice_attribute[79] = "CU_DEVICE_ATTRIBUTE_GLOBAL_L1_CACHE_SUPPORTED";
        m_mapESCUdevice_attribute[80] = "CU_DEVICE_ATTRIBUTE_LOCAL_L1_CACHE_SUPPORTED";
        m_mapESCUdevice_attribute[81] = "CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_MULTIPROCESSOR";
        m_mapESCUdevice_attribute[82] = "CU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_MULTIPROCESSOR";
        m_mapESCUdevice_attribute[83] = "CU_DEVICE_ATTRIBUTE_MANAGED_MEMORY";
        m_mapESCUdevice_attribute[84] = "CU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD";
        m_mapESCUdevice_attribute[85] = "CU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD_GROUP_ID";
        m_mapESCUdevice_attribute[86] = "CU_DEVICE_ATTRIBUTE_HOST_NATIVE_ATOMIC_SUPPORTED";
        m_mapESCUdevice_attribute[87] = "CU_DEVICE_ATTRIBUTE_SINGLE_TO_DOUBLE_PRECISION_PERF_RATIO";
        m_mapESCUdevice_attribute[88] = "CU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS";
        m_mapESCUdevice_attribute[89] = "CU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS";
        m_mapESCUdevice_attribute[90] = "CU_DEVICE_ATTRIBUTE_COMPUTE_PREEMPTION_SUPPORTED";
        m_mapESCUdevice_attribute[91] = "CU_DEVICE_ATTRIBUTE_CAN_USE_HOST_POINTER_FOR_REGISTERED_MEM";
        m_mapESCUdevice_attribute[92] = "CU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_MEM_OPS";
        m_mapESCUdevice_attribute[93] = "CU_DEVICE_ATTRIBUTE_CAN_USE_64_BIT_STREAM_MEM_OPS";
        m_mapESCUdevice_attribute[94] = "CU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_WAIT_VALUE_NOR";
        m_mapESCUdevice_attribute[95] = "CU_DEVICE_ATTRIBUTE_COOPERATIVE_LAUNCH";
        m_mapESCUdevice_attribute[96] = "CU_DEVICE_ATTRIBUTE_COOPERATIVE_MULTI_DEVICE_LAUNCH";
        m_mapESCUdevice_attribute[97] = "CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK_OPTIN";
        m_mapESCUdevice_attribute[98] = "CU_DEVICE_ATTRIBUTE_CAN_FLUSH_REMOTE_WRITES";
        m_mapESCUdevice_attribute[99] = "CU_DEVICE_ATTRIBUTE_HOST_REGISTER_SUPPORTED";
        m_mapESCUdevice_attribute[100] = "CU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS_USES_HOST_PAGE_TABLES";
        m_mapESCUdevice_attribute[101] = "CU_DEVICE_ATTRIBUTE_DIRECT_MANAGED_MEM_ACCESS_FROM_HOST";
        m_mapESCUdevice_attribute[102] = "CU_DEVICE_ATTRIBUTE_MAX";

        m_mapESCUpointer_attribute[1] = "CU_POINTER_ATTRIBUTE_CONTEXT";
        m_mapESCUpointer_attribute[2] = "CU_POINTER_ATTRIBUTE_MEMORY_TYPE";
        m_mapESCUpointer_attribute[3] = "CU_POINTER_ATTRIBUTE_DEVICE_POINTER";
        m_mapESCUpointer_attribute[4] = "CU_POINTER_ATTRIBUTE_HOST_POINTER";
        m_mapESCUpointer_attribute[5] = "CU_POINTER_ATTRIBUTE_P2P_TOKENS";
        m_mapESCUpointer_attribute[6] = "CU_POINTER_ATTRIBUTE_SYNC_MEMOPS";
        m_mapESCUpointer_attribute[7] = "CU_POINTER_ATTRIBUTE_BUFFER_ID";
        m_mapESCUpointer_attribute[8] = "CU_POINTER_ATTRIBUTE_IS_MANAGED";
        m_mapESCUpointer_attribute[9] = "CU_POINTER_ATTRIBUTE_DEVICE_ORDINAL";

        m_mapESCUfunction_attribute[0] = "CU_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK";
        m_mapESCUfunction_attribute[1] = "CU_FUNC_ATTRIBUTE_SHARED_SIZE_BYTES";
        m_mapESCUfunction_attribute[2] = "CU_FUNC_ATTRIBUTE_CONST_SIZE_BYTES";
        m_mapESCUfunction_attribute[3] = "CU_FUNC_ATTRIBUTE_LOCAL_SIZE_BYTES";
        m_mapESCUfunction_attribute[4] = "CU_FUNC_ATTRIBUTE_NUM_REGS";
        m_mapESCUfunction_attribute[5] = "CU_FUNC_ATTRIBUTE_PTX_VERSION";
        m_mapESCUfunction_attribute[6] = "CU_FUNC_ATTRIBUTE_BINARY_VERSION";
        m_mapESCUfunction_attribute[7] = "CU_FUNC_ATTRIBUTE_CACHE_MODE_CA";
        m_mapESCUfunction_attribute[8] = "CU_FUNC_ATTRIBUTE_MAX_DYNAMIC_SHARED_SIZE_BYTES";
        m_mapESCUfunction_attribute[9] = "CU_FUNC_ATTRIBUTE_PREFERRED_SHARED_MEMORY_CARVEOUT";
        m_mapESCUfunction_attribute[10] = "CU_FUNC_ATTRIBUTE_MAX";

        m_mapESCUfunc_cache[0] = "CU_FUNC_CACHE_PREFER_NONE";
        m_mapESCUfunc_cache[1] = "CU_FUNC_CACHE_PREFER_SHARED";
        m_mapESCUfunc_cache[2] = "CU_FUNC_CACHE_PREFER_L1";
        m_mapESCUfunc_cache[3] = "CU_FUNC_CACHE_PREFER_EQUAL";

        m_mapESCUsharedconfig[0] = "CU_SHARED_MEM_CONFIG_DEFAULT_BANK_SIZE";
        m_mapESCUsharedconfig[1] = "CU_SHARED_MEM_CONFIG_FOUR_BYTE_BANK_SIZE";
        m_mapESCUsharedconfig[2] = "CU_SHARED_MEM_CONFIG_EIGHT_BYTE_BANK_SIZE";

        m_mapESCUshared_carveout[-1] = "CU_SHAREDMEM_CARVEOUT_DEFAULT";
        m_mapESCUshared_carveout[100] = "CU_SHAREDMEM_CARVEOUT_MAX_SHARED";
        m_mapESCUshared_carveout[0] = "CU_SHAREDMEM_CARVEOUT_MAX_L1";

        m_mapESCUmemorytype[1] = "CU_MEMORYTYPE_HOST";
        m_mapESCUmemorytype[2] = "CU_MEMORYTYPE_DEVICE";
        m_mapESCUmemorytype[3] = "CU_MEMORYTYPE_ARRAY";
        m_mapESCUmemorytype[4] = "CU_MEMORYTYPE_UNIFIED";

        m_mapESCUcomputemode[0] = "CU_COMPUTEMODE_DEFAULT";
        m_mapESCUcomputemode[2] = "CU_COMPUTEMODE_PROHIBITED";
        m_mapESCUcomputemode[3] = "CU_COMPUTEMODE_EXCLUSIVE_PROCESS";

        m_mapESCUmem_advise[1] = "CU_MEM_ADVISE_SET_READ_MOSTLY";
        m_mapESCUmem_advise[2] = "CU_MEM_ADVISE_UNSET_READ_MOSTLY";
        m_mapESCUmem_advise[3] = "CU_MEM_ADVISE_SET_PREFERRED_LOCATION";
        m_mapESCUmem_advise[4] = "CU_MEM_ADVISE_UNSET_PREFERRED_LOCATION";
        m_mapESCUmem_advise[5] = "CU_MEM_ADVISE_SET_ACCESSED_BY";
        m_mapESCUmem_advise[6] = "CU_MEM_ADVISE_UNSET_ACCESSED_BY";

        m_mapESCUmem_range_attribute[1] = "CU_MEM_RANGE_ATTRIBUTE_READ_MOSTLY";
        m_mapESCUmem_range_attribute[2] = "CU_MEM_RANGE_ATTRIBUTE_PREFERRED_LOCATION";
        m_mapESCUmem_range_attribute[3] = "CU_MEM_RANGE_ATTRIBUTE_ACCESSED_BY";
        m_mapESCUmem_range_attribute[4] = "CU_MEM_RANGE_ATTRIBUTE_LAST_PREFETCH_LOCATION";

        m_mapESCUjit_option[0] = "CU_JIT_MAX_REGISTERS";
        m_mapESCUjit_option[1] = "CU_JIT_THREADS_PER_BLOCK";
        m_mapESCUjit_option[2] = "CU_JIT_WALL_TIME";
        m_mapESCUjit_option[3] = "CU_JIT_INFO_LOG_BUFFER";
        m_mapESCUjit_option[4] = "CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES";
        m_mapESCUjit_option[5] = "CU_JIT_ERROR_LOG_BUFFER";
        m_mapESCUjit_option[6] = "CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES";
        m_mapESCUjit_option[7] = "CU_JIT_OPTIMIZATION_LEVEL";
        m_mapESCUjit_option[8] = "CU_JIT_TARGET_FROM_CUCONTEXT";
        m_mapESCUjit_option[9] = "CU_JIT_TARGET";
        m_mapESCUjit_option[10] = "CU_JIT_FALLBACK_STRATEGY";
        m_mapESCUjit_option[11] = "CU_JIT_GENERATE_DEBUG_INFO";
        m_mapESCUjit_option[12] = "CU_JIT_LOG_VERBOSE";
        m_mapESCUjit_option[13] = "CU_JIT_GENERATE_LINE_INFO";
        m_mapESCUjit_option[14] = "CU_JIT_CACHE_MODE";
        m_mapESCUjit_option[15] = "CU_JIT_NEW_SM3X_OPT";
        m_mapESCUjit_option[16] = "CU_JIT_FAST_COMPILE";
        m_mapESCUjit_option[17] = "CU_JIT_GLOBAL_SYMBOL_NAMES";
        m_mapESCUjit_option[18] = "CU_JIT_GLOBAL_SYMBOL_ADDRESSES";
        m_mapESCUjit_option[19] = "CU_JIT_GLOBAL_SYMBOL_COUNT";
        m_mapESCUjit_option[20] = "CU_JIT_NUM_OPTIONS";

        m_mapESCUjit_target[20] = "CU_TARGET_COMPUTE_20";
        m_mapESCUjit_target[21] = "CU_TARGET_COMPUTE_21";
        m_mapESCUjit_target[30] = "CU_TARGET_COMPUTE_30";
        m_mapESCUjit_target[32] = "CU_TARGET_COMPUTE_32";
        m_mapESCUjit_target[35] = "CU_TARGET_COMPUTE_35";
        m_mapESCUjit_target[37] = "CU_TARGET_COMPUTE_37";
        m_mapESCUjit_target[50] = "CU_TARGET_COMPUTE_50";
        m_mapESCUjit_target[52] = "CU_TARGET_COMPUTE_52";
        m_mapESCUjit_target[53] = "CU_TARGET_COMPUTE_53";
        m_mapESCUjit_target[60] = "CU_TARGET_COMPUTE_60";
        m_mapESCUjit_target[61] = "CU_TARGET_COMPUTE_61";
        m_mapESCUjit_target[62] = "CU_TARGET_COMPUTE_62";
        m_mapESCUjit_target[70] = "CU_TARGET_COMPUTE_70";
        m_mapESCUjit_target[75] = "CU_TARGET_COMPUTE_75";

        m_mapESCUjit_fallback[0] = "CU_PREFER_PTX";
        m_mapESCUjit_fallback[1] = "CU_PREFER_BINARY";

        m_mapESCUjit_cacheMode[0] = "CU_JIT_CACHE_OPTION_NONE";
        m_mapESCUjit_cacheMode[1] = "CU_JIT_CACHE_OPTION_CG";
        m_mapESCUjit_cacheMode[2] = "CU_JIT_CACHE_OPTION_CA";

        m_mapESCUjitInputType[0] = "CU_JIT_INPUT_CUBIN";
        m_mapESCUjitInputType[1] = "CU_JIT_INPUT_PTX";
        m_mapESCUjitInputType[2] = "CU_JIT_INPUT_FATBINARY";
        m_mapESCUjitInputType[3] = "CU_JIT_INPUT_OBJECT";
        m_mapESCUjitInputType[4] = "CU_JIT_INPUT_LIBRARY";
        m_mapESCUjitInputType[5] = "CU_JIT_NUM_INPUT_TYPES";

        m_mapESCUgraphicsRegisterFlags[0] = "CU_GRAPHICS_REGISTER_FLAGS_NONE";
        m_mapESCUgraphicsRegisterFlags[1] = "CU_GRAPHICS_REGISTER_FLAGS_READ_ONLY";
        m_mapESCUgraphicsRegisterFlags[2] = "CU_GRAPHICS_REGISTER_FLAGS_WRITE_DISCARD";
        m_mapESCUgraphicsRegisterFlags[4] = "CU_GRAPHICS_REGISTER_FLAGS_SURFACE_LDST";
        m_mapESCUgraphicsRegisterFlags[8] = "CU_GRAPHICS_REGISTER_FLAGS_TEXTURE_GATHER";

        m_mapESCUgraphicsMapResourceFlags[0] = "CU_GRAPHICS_MAP_RESOURCE_FLAGS_NONE";
        m_mapESCUgraphicsMapResourceFlags[1] = "CU_GRAPHICS_MAP_RESOURCE_FLAGS_READ_ONLY";
        m_mapESCUgraphicsMapResourceFlags[2] = "CU_GRAPHICS_MAP_RESOURCE_FLAGS_WRITE_DISCARD";

        m_mapESCUarray_cubemap_face[0] = "CU_CUBEMAP_FACE_POSITIVE_X";
        m_mapESCUarray_cubemap_face[1] = "CU_CUBEMAP_FACE_NEGATIVE_X";
        m_mapESCUarray_cubemap_face[2] = "CU_CUBEMAP_FACE_POSITIVE_Y";
        m_mapESCUarray_cubemap_face[3] = "CU_CUBEMAP_FACE_NEGATIVE_Y";
        m_mapESCUarray_cubemap_face[4] = "CU_CUBEMAP_FACE_POSITIVE_Z";
        m_mapESCUarray_cubemap_face[5] = "CU_CUBEMAP_FACE_NEGATIVE_Z";

        m_mapESCUlimit[0] = "CU_LIMIT_STACK_SIZE";
        m_mapESCUlimit[1] = "CU_LIMIT_PRINTF_FIFO_SIZE";
        m_mapESCUlimit[2] = "CU_LIMIT_MALLOC_HEAP_SIZE";
        m_mapESCUlimit[3] = "CU_LIMIT_DEV_RUNTIME_SYNC_DEPTH";
        m_mapESCUlimit[4] = "CU_LIMIT_DEV_RUNTIME_PENDING_LAUNCH_COUNT";
        m_mapESCUlimit[5] = "CU_LIMIT_MAX_L2_FETCH_GRANULARITY";
        m_mapESCUlimit[6] = "CU_LIMIT_MAX";

        m_mapESCUresourcetype[0] = "CU_RESOURCE_TYPE_ARRAY";
        m_mapESCUresourcetype[1] = "CU_RESOURCE_TYPE_MIPMAPPED_ARRAY";
        m_mapESCUresourcetype[2] = "CU_RESOURCE_TYPE_LINEAR";
        m_mapESCUresourcetype[3] = "CU_RESOURCE_TYPE_PITCH2D";

        m_mapESCUgraphNodeType[0] = "CU_GRAPH_NODE_TYPE_KERNEL";
        m_mapESCUgraphNodeType[1] = "CU_GRAPH_NODE_TYPE_MEMCPY";
        m_mapESCUgraphNodeType[2] = "CU_GRAPH_NODE_TYPE_MEMSET";
        m_mapESCUgraphNodeType[3] = "CU_GRAPH_NODE_TYPE_HOST";
        m_mapESCUgraphNodeType[4] = "CU_GRAPH_NODE_TYPE_GRAPH";
        m_mapESCUgraphNodeType[5] = "CU_GRAPH_NODE_TYPE_EMPTY";
        m_mapESCUgraphNodeType[6] = "CU_GRAPH_NODE_TYPE_COUNT";

        m_mapESCUstreamCaptureStatus[0] = "CU_STREAM_CAPTURE_STATUS_NONE";
        m_mapESCUstreamCaptureStatus[1] = "CU_STREAM_CAPTURE_STATUS_ACTIVE";
        m_mapESCUstreamCaptureStatus[2] = "CU_STREAM_CAPTURE_STATUS_INVALIDATED";

        m_mapESCUresult[0] = "CUDA_SUCCESS";
        m_mapESCUresult[1] = "CUDA_ERROR_INVALID_VALUE";
        m_mapESCUresult[2] = "CUDA_ERROR_OUT_OF_MEMORY";
        m_mapESCUresult[3] = "CUDA_ERROR_NOT_INITIALIZED";
        m_mapESCUresult[4] = "CUDA_ERROR_DEINITIALIZED";
        m_mapESCUresult[5] = "CUDA_ERROR_PROFILER_DISABLED";
        m_mapESCUresult[6] = "CUDA_ERROR_PROFILER_NOT_INITIALIZED";
        m_mapESCUresult[7] = "CUDA_ERROR_PROFILER_ALREADY_STARTED";
        m_mapESCUresult[8] = "CUDA_ERROR_PROFILER_ALREADY_STOPPED";
        m_mapESCUresult[100] = "CUDA_ERROR_NO_DEVICE";
        m_mapESCUresult[101] = "CUDA_ERROR_INVALID_DEVICE";
        m_mapESCUresult[200] = "CUDA_ERROR_INVALID_IMAGE";
        m_mapESCUresult[201] = "CUDA_ERROR_INVALID_CONTEXT";
        m_mapESCUresult[202] = "CUDA_ERROR_CONTEXT_ALREADY_CURRENT";
        m_mapESCUresult[205] = "CUDA_ERROR_MAP_FAILED";
        m_mapESCUresult[206] = "CUDA_ERROR_UNMAP_FAILED";
        m_mapESCUresult[207] = "CUDA_ERROR_ARRAY_IS_MAPPED";
        m_mapESCUresult[208] = "CUDA_ERROR_ALREADY_MAPPED";
        m_mapESCUresult[209] = "CUDA_ERROR_NO_BINARY_FOR_GPU";
        m_mapESCUresult[210] = "CUDA_ERROR_ALREADY_ACQUIRED";
        m_mapESCUresult[211] = "CUDA_ERROR_NOT_MAPPED";
        m_mapESCUresult[212] = "CUDA_ERROR_NOT_MAPPED_AS_ARRAY";
        m_mapESCUresult[213] = "CUDA_ERROR_NOT_MAPPED_AS_POINTER";
        m_mapESCUresult[214] = "CUDA_ERROR_ECC_UNCORRECTABLE";
        m_mapESCUresult[215] = "CUDA_ERROR_UNSUPPORTED_LIMIT";
        m_mapESCUresult[216] = "CUDA_ERROR_CONTEXT_ALREADY_IN_USE";
        m_mapESCUresult[217] = "CUDA_ERROR_PEER_ACCESS_UNSUPPORTED";
        m_mapESCUresult[218] = "CUDA_ERROR_INVALID_PTX";
        m_mapESCUresult[219] = "CUDA_ERROR_INVALID_GRAPHICS_CONTEXT";
        m_mapESCUresult[220] = "CUDA_ERROR_NVLINK_UNCORRECTABLE";
        m_mapESCUresult[221] = "CUDA_ERROR_JIT_COMPILER_NOT_FOUND";
        m_mapESCUresult[300] = "CUDA_ERROR_INVALID_SOURCE";
        m_mapESCUresult[301] = "CUDA_ERROR_FILE_NOT_FOUND";
        m_mapESCUresult[302] = "CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND";
        m_mapESCUresult[303] = "CUDA_ERROR_SHARED_OBJECT_INIT_FAILED";
        m_mapESCUresult[304] = "CUDA_ERROR_OPERATING_SYSTEM";
        m_mapESCUresult[400] = "CUDA_ERROR_INVALID_HANDLE";
        m_mapESCUresult[401] = "CUDA_ERROR_ILLEGAL_STATE";
        m_mapESCUresult[500] = "CUDA_ERROR_NOT_FOUND";
        m_mapESCUresult[600] = "CUDA_ERROR_NOT_READY";
        m_mapESCUresult[700] = "CUDA_ERROR_ILLEGAL_ADDRESS";
        m_mapESCUresult[701] = "CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES";
        m_mapESCUresult[702] = "CUDA_ERROR_LAUNCH_TIMEOUT";
        m_mapESCUresult[703] = "CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING";
        m_mapESCUresult[704] = "CUDA_ERROR_PEER_ACCESS_ALREADY_ENABLED";
        m_mapESCUresult[705] = "CUDA_ERROR_PEER_ACCESS_NOT_ENABLED";
        m_mapESCUresult[708] = "CUDA_ERROR_PRIMARY_CONTEXT_ACTIVE";
        m_mapESCUresult[709] = "CUDA_ERROR_CONTEXT_IS_DESTROYED";
        m_mapESCUresult[710] = "CUDA_ERROR_ASSERT";
        m_mapESCUresult[711] = "CUDA_ERROR_TOO_MANY_PEERS";
        m_mapESCUresult[712] = "CUDA_ERROR_HOST_MEMORY_ALREADY_REGISTERED";
        m_mapESCUresult[713] = "CUDA_ERROR_HOST_MEMORY_NOT_REGISTERED";
        m_mapESCUresult[714] = "CUDA_ERROR_HARDWARE_STACK_ERROR";
        m_mapESCUresult[715] = "CUDA_ERROR_ILLEGAL_INSTRUCTION";
        m_mapESCUresult[716] = "CUDA_ERROR_MISALIGNED_ADDRESS";
        m_mapESCUresult[717] = "CUDA_ERROR_INVALID_ADDRESS_SPACE";
        m_mapESCUresult[718] = "CUDA_ERROR_INVALID_PC";
        m_mapESCUresult[719] = "CUDA_ERROR_LAUNCH_FAILED";
        m_mapESCUresult[720] = "CUDA_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE";
        m_mapESCUresult[800] = "CUDA_ERROR_NOT_PERMITTED";
        m_mapESCUresult[801] = "CUDA_ERROR_NOT_SUPPORTED";
        m_mapESCUresult[802] = "CUDA_ERROR_SYSTEM_NOT_READY";
        m_mapESCUresult[900] = "CUDA_ERROR_STREAM_CAPTURE_UNSUPPORTED";
        m_mapESCUresult[901] = "CUDA_ERROR_STREAM_CAPTURE_INVALIDATED";
        m_mapESCUresult[902] = "CUDA_ERROR_STREAM_CAPTURE_MERGE";
        m_mapESCUresult[903] = "CUDA_ERROR_STREAM_CAPTURE_UNMATCHED";
        m_mapESCUresult[904] = "CUDA_ERROR_STREAM_CAPTURE_UNJOINED";
        m_mapESCUresult[905] = "CUDA_ERROR_STREAM_CAPTURE_ISOLATION";
        m_mapESCUresult[906] = "CUDA_ERROR_STREAM_CAPTURE_IMPLICIT";
        m_mapESCUresult[907] = "CUDA_ERROR_CAPTURED_EVENT";
        m_mapESCUresult[999] = "CUDA_ERROR_UNKNOWN";

        m_mapESCUdevice_P2PAttribute[1] = "CU_DEVICE_P2P_ATTRIBUTE_PERFORMANCE_RANK";
        m_mapESCUdevice_P2PAttribute[2] = "CU_DEVICE_P2P_ATTRIBUTE_ACCESS_SUPPORTED";
        m_mapESCUdevice_P2PAttribute[3] = "CU_DEVICE_P2P_ATTRIBUTE_NATIVE_ATOMIC_SUPPORTED";
        m_mapESCUdevice_P2PAttribute[4] = "CU_DEVICE_P2P_ATTRIBUTE_CUDA_ARRAY_ACCESS_SUPPORTED";

        m_mapESCUresourceViewFormat[0] = "CU_RES_VIEW_FORMAT_NONE";
        m_mapESCUresourceViewFormat[1] = "CU_RES_VIEW_FORMAT_UINT_1X8";
        m_mapESCUresourceViewFormat[2] = "CU_RES_VIEW_FORMAT_UINT_2X8";
        m_mapESCUresourceViewFormat[3] = "CU_RES_VIEW_FORMAT_UINT_4X8";
        m_mapESCUresourceViewFormat[4] = "CU_RES_VIEW_FORMAT_SINT_1X8";
        m_mapESCUresourceViewFormat[5] = "CU_RES_VIEW_FORMAT_SINT_2X8";
        m_mapESCUresourceViewFormat[6] = "CU_RES_VIEW_FORMAT_SINT_4X8";
        m_mapESCUresourceViewFormat[7] = "CU_RES_VIEW_FORMAT_UINT_1X16";
        m_mapESCUresourceViewFormat[8] = "CU_RES_VIEW_FORMAT_UINT_2X16";
        m_mapESCUresourceViewFormat[9] = "CU_RES_VIEW_FORMAT_UINT_4X16";
        m_mapESCUresourceViewFormat[10] = "CU_RES_VIEW_FORMAT_SINT_1X16";
        m_mapESCUresourceViewFormat[11] = "CU_RES_VIEW_FORMAT_SINT_2X16";
        m_mapESCUresourceViewFormat[12] = "CU_RES_VIEW_FORMAT_SINT_4X16";
        m_mapESCUresourceViewFormat[13] = "CU_RES_VIEW_FORMAT_UINT_1X32";
        m_mapESCUresourceViewFormat[14] = "CU_RES_VIEW_FORMAT_UINT_2X32";
        m_mapESCUresourceViewFormat[15] = "CU_RES_VIEW_FORMAT_UINT_4X32";
        m_mapESCUresourceViewFormat[16] = "CU_RES_VIEW_FORMAT_SINT_1X32";
        m_mapESCUresourceViewFormat[17] = "CU_RES_VIEW_FORMAT_SINT_2X32";
        m_mapESCUresourceViewFormat[18] = "CU_RES_VIEW_FORMAT_SINT_4X32";
        m_mapESCUresourceViewFormat[19] = "CU_RES_VIEW_FORMAT_FLOAT_1X16";
        m_mapESCUresourceViewFormat[20] = "CU_RES_VIEW_FORMAT_FLOAT_2X16";
        m_mapESCUresourceViewFormat[21] = "CU_RES_VIEW_FORMAT_FLOAT_4X16";
        m_mapESCUresourceViewFormat[22] = "CU_RES_VIEW_FORMAT_FLOAT_1X32";
        m_mapESCUresourceViewFormat[23] = "CU_RES_VIEW_FORMAT_FLOAT_2X32";
        m_mapESCUresourceViewFormat[24] = "CU_RES_VIEW_FORMAT_FLOAT_4X32";
        m_mapESCUresourceViewFormat[25] = "CU_RES_VIEW_FORMAT_UNSIGNED_BC1";
        m_mapESCUresourceViewFormat[26] = "CU_RES_VIEW_FORMAT_UNSIGNED_BC2";
        m_mapESCUresourceViewFormat[27] = "CU_RES_VIEW_FORMAT_UNSIGNED_BC3";
        m_mapESCUresourceViewFormat[28] = "CU_RES_VIEW_FORMAT_UNSIGNED_BC4";
        m_mapESCUresourceViewFormat[29] = "CU_RES_VIEW_FORMAT_SIGNED_BC4";
        m_mapESCUresourceViewFormat[30] = "CU_RES_VIEW_FORMAT_UNSIGNED_BC5";
        m_mapESCUresourceViewFormat[31] = "CU_RES_VIEW_FORMAT_SIGNED_BC5";
        m_mapESCUresourceViewFormat[32] = "CU_RES_VIEW_FORMAT_UNSIGNED_BC6H";
        m_mapESCUresourceViewFormat[33] = "CU_RES_VIEW_FORMAT_SIGNED_BC6H";
        m_mapESCUresourceViewFormat[34] = "CU_RES_VIEW_FORMAT_UNSIGNED_BC7";

        m_mapESCUexternalMemoryHandleType[1] = "CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD";
        m_mapESCUexternalMemoryHandleType[2] = "CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32";
        m_mapESCUexternalMemoryHandleType[3] = "CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT";
        m_mapESCUexternalMemoryHandleType[4] = "CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP";
        m_mapESCUexternalMemoryHandleType[5] = "CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE";

        m_mapESCUexternalSemaphoreHandleType[1] = "CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD";
        m_mapESCUexternalSemaphoreHandleType[2] = "CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32";
        m_mapESCUexternalSemaphoreHandleType[3] = "CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT";
        m_mapESCUexternalSemaphoreHandleType[4] = "CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE";

    }

    ~wrap()
    {

    }
};

static wrap g;
static ofstream oflog("log.txt");

CUresult __stdcall cuGetErrorString(CUresult error, const char **pStr)
{
    CUresult ret;
    ret = g.m_cuGetErrorString(error, pStr);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "error:" << g.m_mapESCUresult[error] << error << '\n';
    oflog << "*pStr:" << (pStr ? *pStr : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGetErrorName(CUresult error, const char **pStr)
{
    CUresult ret;
    ret = g.m_cuGetErrorName(error, pStr);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "error:" << g.m_mapESCUresult[error] << error << '\n';
    oflog << "*pStr:" << (pStr ? *pStr : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuInit(unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuInit(Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDriverGetVersion(int *driverVersion)
{
    CUresult ret;
    ret = g.m_cuDriverGetVersion(driverVersion);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*driverVersion:" << (driverVersion ? *driverVersion : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceGet(CUdevice *device, int ordinal)
{
    CUresult ret;
    ret = g.m_cuDeviceGet(device, ordinal);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*device:" << (device ? *device : 0) << '\n';
    oflog << "ordinal:" << ordinal << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceGetCount(int *count)
{
    CUresult ret;
    ret = g.m_cuDeviceGetCount(count);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*count:" << (count ? *count : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceGetName(char *name, int len, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetName(name, len, dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "name:" << name << '\n';
    oflog << "len:" << len << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceGetUuid(CUuuid *uuid, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetUuid(uuid, dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "uuid->bytes:" << uuid->bytes << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceGetLuid(char *luid, unsigned int *deviceNodeMask, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetLuid(luid, deviceNodeMask, dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "luid:" << luid << '\n';
    oflog << "*deviceNodeMask:" << (deviceNodeMask ? *deviceNodeMask : 0) << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceTotalMem_v2(size_t *bytes, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceTotalMem_v2(bytes, dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*bytes:" << (bytes ? *bytes : 0) << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceGetAttribute(int *pi, CUdevice_attribute attrib, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetAttribute(pi, attrib, dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pi:" << (pi ? *pi : 0) << '\n';
    oflog << "attrib:" << g.m_mapESCUdevice_attribute[attrib] << attrib << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceGetProperties(CUdevprop *prop, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetProperties(prop, dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "prop->maxThreadsPerBlock:" << prop->maxThreadsPerBlock << '\n'
        << "prop->maxThreadsDim:" << prop->maxThreadsDim[0] << '\n'
        << "prop->maxThreadsDim:" << prop->maxThreadsDim[1] << '\n'
        << "prop->maxThreadsDim:" << prop->maxThreadsDim[2] << '\n'
        << "prop->maxGridSize:" << prop->maxGridSize[0] << '\n'
        << "prop->maxGridSize:" << prop->maxGridSize[1] << '\n'
        << "prop->maxGridSize:" << prop->maxGridSize[2] << '\n'
        << "prop->sharedMemPerBlock:" << prop->sharedMemPerBlock << '\n'
        << "prop->totalConstantMemory:" << prop->totalConstantMemory << '\n'
        << "prop->SIMDWidth:" << prop->SIMDWidth << '\n'
        << "prop->memPitch:" << prop->memPitch << '\n'
        << "prop->regsPerBlock:" << prop->regsPerBlock << '\n'
        << "prop->clockRate:" << prop->clockRate << '\n'
        << "prop->textureAlign:" << prop->textureAlign << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceComputeCapability(int *major, int *minor, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceComputeCapability(major, minor, dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*major:" << (major ? *major : 0) << '\n';
    oflog << "*minor:" << (minor ? *minor : 0) << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDevicePrimaryCtxRetain(CUcontext *pctx, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDevicePrimaryCtxRetain(pctx, dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pctx:" << pctx << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDevicePrimaryCtxRelease(CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDevicePrimaryCtxRelease(dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDevicePrimaryCtxSetFlags(CUdevice dev, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuDevicePrimaryCtxSetFlags(dev, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDevicePrimaryCtxGetState(CUdevice dev, unsigned int *flags, int *active)
{
    CUresult ret;
    ret = g.m_cuDevicePrimaryCtxGetState(dev, flags, active);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << "*flags:" << (flags ? *flags : 0) << '\n';
    oflog << "*active:" << (active ? *active : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDevicePrimaryCtxReset(CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDevicePrimaryCtxReset(dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxCreate_v2(CUcontext *pctx, unsigned int flags, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuCtxCreate_v2(pctx, flags, dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pctx:" << pctx << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxDestroy_v2(CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuCtxDestroy_v2(ctx);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "ctx:" << ctx << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxPushCurrent_v2(CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuCtxPushCurrent_v2(ctx);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "ctx:" << ctx << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxPopCurrent_v2(CUcontext *pctx)
{
    CUresult ret;
    ret = g.m_cuCtxPopCurrent_v2(pctx);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pctx:" << pctx << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxSetCurrent(CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuCtxSetCurrent(ctx);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "ctx:" << ctx << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxGetCurrent(CUcontext *pctx)
{
    CUresult ret;
    ret = g.m_cuCtxGetCurrent(pctx);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pctx:" << pctx << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxGetDevice(CUdevice *device)
{
    CUresult ret;
    ret = g.m_cuCtxGetDevice(device);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*device:" << (device ? *device : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxGetFlags(unsigned int *flags)
{
    CUresult ret;
    ret = g.m_cuCtxGetFlags(flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*flags:" << (flags ? *flags : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxSynchronize()
{
    CUresult ret;
    ret = g.m_cuCtxSynchronize();
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxSetLimit(CUlimit limit, size_t value)
{
    CUresult ret;
    ret = g.m_cuCtxSetLimit(limit, value);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "limit:" << g.m_mapESCUlimit[limit] << limit << '\n';
    oflog << "value:" << value << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxGetLimit(size_t *pvalue, CUlimit limit)
{
    CUresult ret;
    ret = g.m_cuCtxGetLimit(pvalue, limit);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pvalue:" << (pvalue ? *pvalue : 0) << '\n';
    oflog << "limit:" << g.m_mapESCUlimit[limit] << limit << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxGetCacheConfig(CUfunc_cache *pconfig)
{
    CUresult ret;
    ret = g.m_cuCtxGetCacheConfig(pconfig);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pconfig:" << g.m_mapESCUfunc_cache[*pconfig] << pconfig << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxSetCacheConfig(CUfunc_cache config)
{
    CUresult ret;
    ret = g.m_cuCtxSetCacheConfig(config);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "config:" << g.m_mapESCUfunc_cache[config] << config << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxGetSharedMemConfig(CUsharedconfig *pConfig)
{
    CUresult ret;
    ret = g.m_cuCtxGetSharedMemConfig(pConfig);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pConfig:" << g.m_mapESCUsharedconfig[*pConfig] << pConfig << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxSetSharedMemConfig(CUsharedconfig config)
{
    CUresult ret;
    ret = g.m_cuCtxSetSharedMemConfig(config);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "config:" << g.m_mapESCUsharedconfig[config] << config << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxGetApiVersion(CUcontext ctx, unsigned int *version)
{
    CUresult ret;
    ret = g.m_cuCtxGetApiVersion(ctx, version);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "ctx:" << ctx << '\n';
    oflog << "*version:" << (version ? *version : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxGetStreamPriorityRange(int *leastPriority, int *greatestPriority)
{
    CUresult ret;
    ret = g.m_cuCtxGetStreamPriorityRange(leastPriority, greatestPriority);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*leastPriority:" << (leastPriority ? *leastPriority : 0) << '\n';
    oflog << "*greatestPriority:" << (greatestPriority ? *greatestPriority : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxAttach(CUcontext *pctx, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuCtxAttach(pctx, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pctx:" << pctx << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxDetach(CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuCtxDetach(ctx);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "ctx:" << ctx << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuModuleLoad(CUmodule *module, const char *fname)
{
    CUresult ret;
    ret = g.m_cuModuleLoad(module, fname);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "module:" << module << '\n';
    oflog << "fname:" << fname << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuModuleLoadData(CUmodule *module, const void *image)
{
    CUresult ret;
    ret = g.m_cuModuleLoadData(module, image);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "module:" << module << '\n';
    oflog << "image:" << image << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuModuleLoadDataEx(CUmodule *module, const void *image, unsigned int numOptions, CUjit_option *options, void **optionValues)
{
    CUresult ret;
    ret = g.m_cuModuleLoadDataEx(module, image, numOptions, options, optionValues);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "module:" << module << '\n';
    oflog << "image:" << image << '\n';
    oflog << "numOptions:" << numOptions << '\n';
    oflog << "*options:" << g.m_mapESCUjit_option[*options] << options << '\n';
    oflog << "*optionValues:" << (optionValues ? *optionValues : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuModuleLoadFatBinary(CUmodule *module, const void *fatCubin)
{
    CUresult ret;
    ret = g.m_cuModuleLoadFatBinary(module, fatCubin);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "module:" << module << '\n';
    oflog << "fatCubin:" << fatCubin << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuModuleUnload(CUmodule hmod)
{
    CUresult ret;
    ret = g.m_cuModuleUnload(hmod);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hmod:" << hmod << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuModuleGetFunction(CUfunction *hfunc, CUmodule hmod, const char *name)
{
    CUresult ret;
    ret = g.m_cuModuleGetFunction(hfunc, hmod, name);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << "hmod:" << hmod << '\n';
    oflog << "name:" << name << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuModuleGetGlobal_v2(CUdeviceptr *dptr, size_t *bytes, CUmodule hmod, const char *name)
{
    CUresult ret;
    ret = g.m_cuModuleGetGlobal_v2(dptr, bytes, hmod, name);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*dptr:" << (dptr ? *dptr : 0) << '\n';
    oflog << "*bytes:" << (bytes ? *bytes : 0) << '\n';
    oflog << "hmod:" << hmod << '\n';
    oflog << "name:" << name << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuModuleGetTexRef(CUtexref *pTexRef, CUmodule hmod, const char *name)
{
    CUresult ret;
    ret = g.m_cuModuleGetTexRef(pTexRef, hmod, name);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pTexRef:" << pTexRef << '\n';
    oflog << "hmod:" << hmod << '\n';
    oflog << "name:" << name << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuModuleGetSurfRef(CUsurfref *pSurfRef, CUmodule hmod, const char *name)
{
    CUresult ret;
    ret = g.m_cuModuleGetSurfRef(pSurfRef, hmod, name);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pSurfRef:" << pSurfRef << '\n';
    oflog << "hmod:" << hmod << '\n';
    oflog << "name:" << name << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLinkCreate_v2(unsigned int numOptions, CUjit_option *options, void **optionValues, CUlinkState *stateOut)
{
    CUresult ret;
    ret = g.m_cuLinkCreate_v2(numOptions, options, optionValues, stateOut);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "numOptions:" << numOptions << '\n';
    oflog << "*options:" << g.m_mapESCUjit_option[*options] << options << '\n';
    oflog << "*optionValues:" << (optionValues ? *optionValues : 0) << '\n';
    oflog << "stateOut:" << stateOut << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLinkAddData_v2(CUlinkState state, CUjitInputType type, void *data, size_t size, const char *name, unsigned int numOptions, CUjit_option *options, void **optionValues)
{
    CUresult ret;
    ret = g.m_cuLinkAddData_v2(state, type, data, size, name, numOptions, options, optionValues);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "state:" << state << '\n';
    oflog << "type:" << g.m_mapESCUjitInputType[type] << type << '\n';
    oflog << "data:" << data << '\n';
    oflog << "size:" << size << '\n';
    oflog << "name:" << name << '\n';
    oflog << "numOptions:" << numOptions << '\n';
    oflog << "*options:" << g.m_mapESCUjit_option[*options] << options << '\n';
    oflog << "*optionValues:" << (optionValues ? *optionValues : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLinkAddFile_v2(CUlinkState state, CUjitInputType type, const char *path, unsigned int numOptions, CUjit_option *options, void **optionValues)
{
    CUresult ret;
    ret = g.m_cuLinkAddFile_v2(state, type, path, numOptions, options, optionValues);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "state:" << state << '\n';
    oflog << "type:" << g.m_mapESCUjitInputType[type] << type << '\n';
    oflog << "path:" << path << '\n';
    oflog << "numOptions:" << numOptions << '\n';
    oflog << "*options:" << g.m_mapESCUjit_option[*options] << options << '\n';
    oflog << "*optionValues:" << (optionValues ? *optionValues : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLinkComplete(CUlinkState state, void **cubinOut, size_t *sizeOut)
{
    CUresult ret;
    ret = g.m_cuLinkComplete(state, cubinOut, sizeOut);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "state:" << state << '\n';
    oflog << "*cubinOut:" << (cubinOut ? *cubinOut : 0) << '\n';
    oflog << "*sizeOut:" << (sizeOut ? *sizeOut : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLinkDestroy(CUlinkState state)
{
    CUresult ret;
    ret = g.m_cuLinkDestroy(state);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "state:" << state << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemGetInfo_v2(size_t *free, size_t *total)
{
    CUresult ret;
    ret = g.m_cuMemGetInfo_v2(free, total);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*free:" << (free ? *free : 0) << '\n';
    oflog << "*total:" << (total ? *total : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemAlloc_v2(CUdeviceptr *dptr, size_t bytesize)
{
    CUresult ret;
    ret = g.m_cuMemAlloc_v2(dptr, bytesize);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*dptr:" << (dptr ? *dptr : 0) << '\n';
    oflog << "bytesize:" << bytesize << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemAllocPitch_v2(CUdeviceptr *dptr, size_t *pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes)
{
    CUresult ret;
    ret = g.m_cuMemAllocPitch_v2(dptr, pPitch, WidthInBytes, Height, ElementSizeBytes);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*dptr:" << (dptr ? *dptr : 0) << '\n';
    oflog << "*pPitch:" << (pPitch ? *pPitch : 0) << '\n';
    oflog << "WidthInBytes:" << WidthInBytes << '\n';
    oflog << "Height:" << Height << '\n';
    oflog << "ElementSizeBytes:" << ElementSizeBytes << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemFree_v2(CUdeviceptr dptr)
{
    CUresult ret;
    ret = g.m_cuMemFree_v2(dptr);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dptr:" << dptr << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemGetAddressRange_v2(CUdeviceptr *pbase, size_t *psize, CUdeviceptr dptr)
{
    CUresult ret;
    ret = g.m_cuMemGetAddressRange_v2(pbase, psize, dptr);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pbase:" << (pbase ? *pbase : 0) << '\n';
    oflog << "*psize:" << (psize ? *psize : 0) << '\n';
    oflog << "dptr:" << dptr << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemAllocHost_v2(void **pp, size_t bytesize)
{
    CUresult ret;
    ret = g.m_cuMemAllocHost_v2(pp, bytesize);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pp:" << (pp ? *pp : 0) << '\n';
    oflog << "bytesize:" << bytesize << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemFreeHost(void *p)
{
    CUresult ret;
    ret = g.m_cuMemFreeHost(p);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "p:" << p << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemHostAlloc(void **pp, size_t bytesize, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuMemHostAlloc(pp, bytesize, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pp:" << (pp ? *pp : 0) << '\n';
    oflog << "bytesize:" << bytesize << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemHostGetDevicePointer_v2(CUdeviceptr *pdptr, void *p, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuMemHostGetDevicePointer_v2(pdptr, p, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pdptr:" << (pdptr ? *pdptr : 0) << '\n';
    oflog << "p:" << p << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemHostGetFlags(unsigned int *pFlags, void *p)
{
    CUresult ret;
    ret = g.m_cuMemHostGetFlags(pFlags, p);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pFlags:" << (pFlags ? *pFlags : 0) << '\n';
    oflog << "p:" << p << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemAllocManaged(CUdeviceptr *dptr, size_t bytesize, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuMemAllocManaged(dptr, bytesize, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*dptr:" << (dptr ? *dptr : 0) << '\n';
    oflog << "bytesize:" << bytesize << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceGetByPCIBusId(CUdevice *dev, const char *pciBusId)
{
    CUresult ret;
    ret = g.m_cuDeviceGetByPCIBusId(dev, pciBusId);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*dev:" << (dev ? *dev : 0) << '\n';
    oflog << "pciBusId:" << pciBusId << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceGetPCIBusId(char *pciBusId, int len, CUdevice dev)
{
    CUresult ret;
    ret = g.m_cuDeviceGetPCIBusId(pciBusId, len, dev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pciBusId:" << pciBusId << '\n';
    oflog << "len:" << len << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuIpcGetEventHandle(CUipcEventHandle *pHandle, CUevent event)
{
    CUresult ret;
    ret = g.m_cuIpcGetEventHandle(pHandle, event);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "event:" << event << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuIpcOpenEventHandle(CUevent *phEvent, CUipcEventHandle handle)
{
    CUresult ret;
    ret = g.m_cuIpcOpenEventHandle(phEvent, handle);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phEvent:" << phEvent << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuIpcGetMemHandle(CUipcMemHandle *pHandle, CUdeviceptr dptr)
{
    CUresult ret;
    ret = g.m_cuIpcGetMemHandle(pHandle, dptr);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dptr:" << dptr << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuIpcOpenMemHandle(CUdeviceptr *pdptr, CUipcMemHandle handle, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuIpcOpenMemHandle(pdptr, handle, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pdptr:" << (pdptr ? *pdptr : 0) << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuIpcCloseMemHandle(CUdeviceptr dptr)
{
    CUresult ret;
    ret = g.m_cuIpcCloseMemHandle(dptr);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dptr:" << dptr << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemHostRegister_v2(void *p, size_t bytesize, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuMemHostRegister_v2(p, bytesize, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "p:" << p << '\n';
    oflog << "bytesize:" << bytesize << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemHostUnregister(void *p)
{
    CUresult ret;
    ret = g.m_cuMemHostUnregister(p);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "p:" << p << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpy(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpy(dst, src, ByteCount);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dst:" << dst << '\n';
    oflog << "src:" << src << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyPeer(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyPeer(dstDevice, dstContext, srcDevice, srcContext, ByteCount);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "dstContext:" << dstContext << '\n';
    oflog << "srcDevice:" << srcDevice << '\n';
    oflog << "srcContext:" << srcContext << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyHtoD_v2(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyHtoD_v2(dstDevice, srcHost, ByteCount);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "srcHost:" << srcHost << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyDtoH_v2(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyDtoH_v2(dstHost, srcDevice, ByteCount);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstHost:" << dstHost << '\n';
    oflog << "srcDevice:" << srcDevice << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyDtoD_v2(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyDtoD_v2(dstDevice, srcDevice, ByteCount);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "srcDevice:" << srcDevice << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyDtoA_v2(CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyDtoA_v2(dstArray, dstOffset, srcDevice, ByteCount);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstArray:" << dstArray << '\n';
    oflog << "dstOffset:" << dstOffset << '\n';
    oflog << "srcDevice:" << srcDevice << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyAtoD_v2(CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyAtoD_v2(dstDevice, srcArray, srcOffset, ByteCount);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "srcArray:" << srcArray << '\n';
    oflog << "srcOffset:" << srcOffset << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyHtoA_v2(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyHtoA_v2(dstArray, dstOffset, srcHost, ByteCount);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstArray:" << dstArray << '\n';
    oflog << "dstOffset:" << dstOffset << '\n';
    oflog << "srcHost:" << srcHost << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyAtoH_v2(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyAtoH_v2(dstHost, srcArray, srcOffset, ByteCount);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstHost:" << dstHost << '\n';
    oflog << "srcArray:" << srcArray << '\n';
    oflog << "srcOffset:" << srcOffset << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyAtoA_v2(CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount)
{
    CUresult ret;
    ret = g.m_cuMemcpyAtoA_v2(dstArray, dstOffset, srcArray, srcOffset, ByteCount);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstArray:" << dstArray << '\n';
    oflog << "dstOffset:" << dstOffset << '\n';
    oflog << "srcArray:" << srcArray << '\n';
    oflog << "srcOffset:" << srcOffset << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpy2D_v2(const CUDA_MEMCPY2D *pCopy)
{
    CUresult ret;
    ret = g.m_cuMemcpy2D_v2(pCopy);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pCopy->srcXInBytes:" << pCopy->srcXInBytes << '\n'
        << "pCopy->srcY:" << pCopy->srcY << '\n'
        << "pCopy->srcMemoryType:" << g.m_mapESCUmemorytype[pCopy->srcMemoryType] << pCopy->srcMemoryType << '\n'
        << "pCopy->srcHost:" << pCopy->srcHost << '\n'
        << "pCopy->srcDevice:" << pCopy->srcDevice << '\n'
        << "pCopy->srcArray:" << pCopy->srcArray << '\n'
        << "pCopy->srcPitch:" << pCopy->srcPitch << '\n'
        << "pCopy->dstXInBytes:" << pCopy->dstXInBytes << '\n'
        << "pCopy->dstY:" << pCopy->dstY << '\n'
        << "pCopy->dstMemoryType:" << g.m_mapESCUmemorytype[pCopy->dstMemoryType] << pCopy->dstMemoryType << '\n'
        << "pCopy->dstHost:" << pCopy->dstHost << '\n'
        << "pCopy->dstDevice:" << pCopy->dstDevice << '\n'
        << "pCopy->dstArray:" << pCopy->dstArray << '\n'
        << "pCopy->dstPitch:" << pCopy->dstPitch << '\n'
        << "pCopy->WidthInBytes:" << pCopy->WidthInBytes << '\n'
        << "pCopy->Height:" << pCopy->Height << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpy2DUnaligned_v2(const CUDA_MEMCPY2D *pCopy)
{
    CUresult ret;
    ret = g.m_cuMemcpy2DUnaligned_v2(pCopy);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pCopy->srcXInBytes:" << pCopy->srcXInBytes << '\n'
        << "pCopy->srcY:" << pCopy->srcY << '\n'
        << "pCopy->srcMemoryType:" << g.m_mapESCUmemorytype[pCopy->srcMemoryType] << pCopy->srcMemoryType << '\n'
        << "pCopy->srcHost:" << pCopy->srcHost << '\n'
        << "pCopy->srcDevice:" << pCopy->srcDevice << '\n'
        << "pCopy->srcArray:" << pCopy->srcArray << '\n'
        << "pCopy->srcPitch:" << pCopy->srcPitch << '\n'
        << "pCopy->dstXInBytes:" << pCopy->dstXInBytes << '\n'
        << "pCopy->dstY:" << pCopy->dstY << '\n'
        << "pCopy->dstMemoryType:" << g.m_mapESCUmemorytype[pCopy->dstMemoryType] << pCopy->dstMemoryType << '\n'
        << "pCopy->dstHost:" << pCopy->dstHost << '\n'
        << "pCopy->dstDevice:" << pCopy->dstDevice << '\n'
        << "pCopy->dstArray:" << pCopy->dstArray << '\n'
        << "pCopy->dstPitch:" << pCopy->dstPitch << '\n'
        << "pCopy->WidthInBytes:" << pCopy->WidthInBytes << '\n'
        << "pCopy->Height:" << pCopy->Height << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpy3D_v2(const CUDA_MEMCPY3D *pCopy)
{
    CUresult ret;
    ret = g.m_cuMemcpy3D_v2(pCopy);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pCopy->srcXInBytes:" << pCopy->srcXInBytes << '\n'
        << "pCopy->srcY:" << pCopy->srcY << '\n'
        << "pCopy->srcZ:" << pCopy->srcZ << '\n'
        << "pCopy->srcLOD:" << pCopy->srcLOD << '\n'
        << "pCopy->srcMemoryType:" << g.m_mapESCUmemorytype[pCopy->srcMemoryType] << pCopy->srcMemoryType << '\n'
        << "pCopy->srcHost:" << pCopy->srcHost << '\n'
        << "pCopy->srcDevice:" << pCopy->srcDevice << '\n'
        << "pCopy->srcArray:" << pCopy->srcArray << '\n'
        << "pCopy->srcPitch:" << pCopy->srcPitch << '\n'
        << "pCopy->srcHeight:" << pCopy->srcHeight << '\n'
        << "pCopy->dstXInBytes:" << pCopy->dstXInBytes << '\n'
        << "pCopy->dstY:" << pCopy->dstY << '\n'
        << "pCopy->dstZ:" << pCopy->dstZ << '\n'
        << "pCopy->dstLOD:" << pCopy->dstLOD << '\n'
        << "pCopy->dstMemoryType:" << g.m_mapESCUmemorytype[pCopy->dstMemoryType] << pCopy->dstMemoryType << '\n'
        << "pCopy->dstHost:" << pCopy->dstHost << '\n'
        << "pCopy->dstDevice:" << pCopy->dstDevice << '\n'
        << "pCopy->dstArray:" << pCopy->dstArray << '\n'
        << "pCopy->dstPitch:" << pCopy->dstPitch << '\n'
        << "pCopy->dstHeight:" << pCopy->dstHeight << '\n'
        << "pCopy->WidthInBytes:" << pCopy->WidthInBytes << '\n'
        << "pCopy->Height:" << pCopy->Height << '\n'
        << "pCopy->Depth:" << pCopy->Depth << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpy3DPeer(const CUDA_MEMCPY3D_PEER *pCopy)
{
    CUresult ret;
    ret = g.m_cuMemcpy3DPeer(pCopy);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pCopy->srcXInBytes:" << pCopy->srcXInBytes << '\n'
        << "pCopy->srcY:" << pCopy->srcY << '\n'
        << "pCopy->srcZ:" << pCopy->srcZ << '\n'
        << "pCopy->srcLOD:" << pCopy->srcLOD << '\n'
        << "pCopy->srcMemoryType:" << g.m_mapESCUmemorytype[pCopy->srcMemoryType] << pCopy->srcMemoryType << '\n'
        << "pCopy->srcHost:" << pCopy->srcHost << '\n'
        << "pCopy->srcDevice:" << pCopy->srcDevice << '\n'
        << "pCopy->srcArray:" << pCopy->srcArray << '\n'
        << "pCopy->srcContext:" << pCopy->srcContext << '\n'
        << "pCopy->srcPitch:" << pCopy->srcPitch << '\n'
        << "pCopy->srcHeight:" << pCopy->srcHeight << '\n'
        << "pCopy->dstXInBytes:" << pCopy->dstXInBytes << '\n'
        << "pCopy->dstY:" << pCopy->dstY << '\n'
        << "pCopy->dstZ:" << pCopy->dstZ << '\n'
        << "pCopy->dstLOD:" << pCopy->dstLOD << '\n'
        << "pCopy->dstMemoryType:" << g.m_mapESCUmemorytype[pCopy->dstMemoryType] << pCopy->dstMemoryType << '\n'
        << "pCopy->dstHost:" << pCopy->dstHost << '\n'
        << "pCopy->dstDevice:" << pCopy->dstDevice << '\n'
        << "pCopy->dstArray:" << pCopy->dstArray << '\n'
        << "pCopy->dstContext:" << pCopy->dstContext << '\n'
        << "pCopy->dstPitch:" << pCopy->dstPitch << '\n'
        << "pCopy->dstHeight:" << pCopy->dstHeight << '\n'
        << "pCopy->WidthInBytes:" << pCopy->WidthInBytes << '\n'
        << "pCopy->Height:" << pCopy->Height << '\n'
        << "pCopy->Depth:" << pCopy->Depth << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyAsync(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyAsync(dst, src, ByteCount, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dst:" << dst << '\n';
    oflog << "src:" << src << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyPeerAsync(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyPeerAsync(dstDevice, dstContext, srcDevice, srcContext, ByteCount, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "dstContext:" << dstContext << '\n';
    oflog << "srcDevice:" << srcDevice << '\n';
    oflog << "srcContext:" << srcContext << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyHtoDAsync_v2(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyHtoDAsync_v2(dstDevice, srcHost, ByteCount, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "srcHost:" << srcHost << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyDtoHAsync_v2(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyDtoHAsync_v2(dstHost, srcDevice, ByteCount, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstHost:" << dstHost << '\n';
    oflog << "srcDevice:" << srcDevice << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyDtoDAsync_v2(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyDtoDAsync_v2(dstDevice, srcDevice, ByteCount, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "srcDevice:" << srcDevice << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyHtoAAsync_v2(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyHtoAAsync_v2(dstArray, dstOffset, srcHost, ByteCount, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstArray:" << dstArray << '\n';
    oflog << "dstOffset:" << dstOffset << '\n';
    oflog << "srcHost:" << srcHost << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpyAtoHAsync_v2(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpyAtoHAsync_v2(dstHost, srcArray, srcOffset, ByteCount, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstHost:" << dstHost << '\n';
    oflog << "srcArray:" << srcArray << '\n';
    oflog << "srcOffset:" << srcOffset << '\n';
    oflog << "ByteCount:" << ByteCount << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpy2DAsync_v2(const CUDA_MEMCPY2D *pCopy, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpy2DAsync_v2(pCopy, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pCopy->srcXInBytes:" << pCopy->srcXInBytes << '\n'
        << "pCopy->srcY:" << pCopy->srcY << '\n'
        << "pCopy->srcMemoryType:" << g.m_mapESCUmemorytype[pCopy->srcMemoryType] << pCopy->srcMemoryType << '\n'
        << "pCopy->srcHost:" << pCopy->srcHost << '\n'
        << "pCopy->srcDevice:" << pCopy->srcDevice << '\n'
        << "pCopy->srcArray:" << pCopy->srcArray << '\n'
        << "pCopy->srcPitch:" << pCopy->srcPitch << '\n'
        << "pCopy->dstXInBytes:" << pCopy->dstXInBytes << '\n'
        << "pCopy->dstY:" << pCopy->dstY << '\n'
        << "pCopy->dstMemoryType:" << g.m_mapESCUmemorytype[pCopy->dstMemoryType] << pCopy->dstMemoryType << '\n'
        << "pCopy->dstHost:" << pCopy->dstHost << '\n'
        << "pCopy->dstDevice:" << pCopy->dstDevice << '\n'
        << "pCopy->dstArray:" << pCopy->dstArray << '\n'
        << "pCopy->dstPitch:" << pCopy->dstPitch << '\n'
        << "pCopy->WidthInBytes:" << pCopy->WidthInBytes << '\n'
        << "pCopy->Height:" << pCopy->Height << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpy3DAsync_v2(const CUDA_MEMCPY3D *pCopy, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpy3DAsync_v2(pCopy, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pCopy->srcXInBytes:" << pCopy->srcXInBytes << '\n'
        << "pCopy->srcY:" << pCopy->srcY << '\n'
        << "pCopy->srcZ:" << pCopy->srcZ << '\n'
        << "pCopy->srcLOD:" << pCopy->srcLOD << '\n'
        << "pCopy->srcMemoryType:" << g.m_mapESCUmemorytype[pCopy->srcMemoryType] << pCopy->srcMemoryType << '\n'
        << "pCopy->srcHost:" << pCopy->srcHost << '\n'
        << "pCopy->srcDevice:" << pCopy->srcDevice << '\n'
        << "pCopy->srcArray:" << pCopy->srcArray << '\n'
        << "pCopy->srcPitch:" << pCopy->srcPitch << '\n'
        << "pCopy->srcHeight:" << pCopy->srcHeight << '\n'
        << "pCopy->dstXInBytes:" << pCopy->dstXInBytes << '\n'
        << "pCopy->dstY:" << pCopy->dstY << '\n'
        << "pCopy->dstZ:" << pCopy->dstZ << '\n'
        << "pCopy->dstLOD:" << pCopy->dstLOD << '\n'
        << "pCopy->dstMemoryType:" << g.m_mapESCUmemorytype[pCopy->dstMemoryType] << pCopy->dstMemoryType << '\n'
        << "pCopy->dstHost:" << pCopy->dstHost << '\n'
        << "pCopy->dstDevice:" << pCopy->dstDevice << '\n'
        << "pCopy->dstArray:" << pCopy->dstArray << '\n'
        << "pCopy->dstPitch:" << pCopy->dstPitch << '\n'
        << "pCopy->dstHeight:" << pCopy->dstHeight << '\n'
        << "pCopy->WidthInBytes:" << pCopy->WidthInBytes << '\n'
        << "pCopy->Height:" << pCopy->Height << '\n'
        << "pCopy->Depth:" << pCopy->Depth << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemcpy3DPeerAsync(const CUDA_MEMCPY3D_PEER *pCopy, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemcpy3DPeerAsync(pCopy, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pCopy->srcXInBytes:" << pCopy->srcXInBytes << '\n'
        << "pCopy->srcY:" << pCopy->srcY << '\n'
        << "pCopy->srcZ:" << pCopy->srcZ << '\n'
        << "pCopy->srcLOD:" << pCopy->srcLOD << '\n'
        << "pCopy->srcMemoryType:" << g.m_mapESCUmemorytype[pCopy->srcMemoryType] << pCopy->srcMemoryType << '\n'
        << "pCopy->srcHost:" << pCopy->srcHost << '\n'
        << "pCopy->srcDevice:" << pCopy->srcDevice << '\n'
        << "pCopy->srcArray:" << pCopy->srcArray << '\n'
        << "pCopy->srcContext:" << pCopy->srcContext << '\n'
        << "pCopy->srcPitch:" << pCopy->srcPitch << '\n'
        << "pCopy->srcHeight:" << pCopy->srcHeight << '\n'
        << "pCopy->dstXInBytes:" << pCopy->dstXInBytes << '\n'
        << "pCopy->dstY:" << pCopy->dstY << '\n'
        << "pCopy->dstZ:" << pCopy->dstZ << '\n'
        << "pCopy->dstLOD:" << pCopy->dstLOD << '\n'
        << "pCopy->dstMemoryType:" << g.m_mapESCUmemorytype[pCopy->dstMemoryType] << pCopy->dstMemoryType << '\n'
        << "pCopy->dstHost:" << pCopy->dstHost << '\n'
        << "pCopy->dstDevice:" << pCopy->dstDevice << '\n'
        << "pCopy->dstArray:" << pCopy->dstArray << '\n'
        << "pCopy->dstContext:" << pCopy->dstContext << '\n'
        << "pCopy->dstPitch:" << pCopy->dstPitch << '\n'
        << "pCopy->dstHeight:" << pCopy->dstHeight << '\n'
        << "pCopy->WidthInBytes:" << pCopy->WidthInBytes << '\n'
        << "pCopy->Height:" << pCopy->Height << '\n'
        << "pCopy->Depth:" << pCopy->Depth << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD8_v2(CUdeviceptr dstDevice, unsigned char uc, size_t N)
{
    CUresult ret;
    ret = g.m_cuMemsetD8_v2(dstDevice, uc, N);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "uc:" << uc << '\n';
    oflog << "N:" << N << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD16_v2(CUdeviceptr dstDevice, unsigned short us, size_t N)
{
    CUresult ret;
    ret = g.m_cuMemsetD16_v2(dstDevice, us, N);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "us:" << us << '\n';
    oflog << "N:" << N << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD32_v2(CUdeviceptr dstDevice, unsigned int ui, size_t N)
{
    CUresult ret;
    ret = g.m_cuMemsetD32_v2(dstDevice, ui, N);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "ui:" << ui << '\n';
    oflog << "N:" << N << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD2D8_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D8_v2(dstDevice, dstPitch, uc, Width, Height);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "dstPitch:" << dstPitch << '\n';
    oflog << "uc:" << uc << '\n';
    oflog << "Width:" << Width << '\n';
    oflog << "Height:" << Height << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD2D16_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D16_v2(dstDevice, dstPitch, us, Width, Height);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "dstPitch:" << dstPitch << '\n';
    oflog << "us:" << us << '\n';
    oflog << "Width:" << Width << '\n';
    oflog << "Height:" << Height << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD2D32_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D32_v2(dstDevice, dstPitch, ui, Width, Height);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "dstPitch:" << dstPitch << '\n';
    oflog << "ui:" << ui << '\n';
    oflog << "Width:" << Width << '\n';
    oflog << "Height:" << Height << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD8Async(CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD8Async(dstDevice, uc, N, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "uc:" << uc << '\n';
    oflog << "N:" << N << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD16Async(CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD16Async(dstDevice, us, N, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "us:" << us << '\n';
    oflog << "N:" << N << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD32Async(CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD32Async(dstDevice, ui, N, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "ui:" << ui << '\n';
    oflog << "N:" << N << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD2D8Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D8Async(dstDevice, dstPitch, uc, Width, Height, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "dstPitch:" << dstPitch << '\n';
    oflog << "uc:" << uc << '\n';
    oflog << "Width:" << Width << '\n';
    oflog << "Height:" << Height << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD2D16Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D16Async(dstDevice, dstPitch, us, Width, Height, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "dstPitch:" << dstPitch << '\n';
    oflog << "us:" << us << '\n';
    oflog << "Width:" << Width << '\n';
    oflog << "Height:" << Height << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemsetD2D32Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemsetD2D32Async(dstDevice, dstPitch, ui, Width, Height, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "dstPitch:" << dstPitch << '\n';
    oflog << "ui:" << ui << '\n';
    oflog << "Width:" << Width << '\n';
    oflog << "Height:" << Height << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuArrayCreate_v2(CUarray *pHandle, const CUDA_ARRAY_DESCRIPTOR *pAllocateArray)
{
    CUresult ret;
    ret = g.m_cuArrayCreate_v2(pHandle, pAllocateArray);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pHandle:" << pHandle << '\n';
    oflog << "pAllocateArray->Width:" << pAllocateArray->Width << '\n'
        << "pAllocateArray->Height:" << pAllocateArray->Height << '\n'
        << "pAllocateArray->Format:" << g.m_mapESCUarray_format[pAllocateArray->Format] << pAllocateArray->Format << '\n'
        << "pAllocateArray->NumChannels:" << pAllocateArray->NumChannels << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuArrayGetDescriptor_v2(CUDA_ARRAY_DESCRIPTOR *pArrayDescriptor, CUarray hArray)
{
    CUresult ret;
    ret = g.m_cuArrayGetDescriptor_v2(pArrayDescriptor, hArray);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pArrayDescriptor->Width:" << pArrayDescriptor->Width << '\n'
        << "pArrayDescriptor->Height:" << pArrayDescriptor->Height << '\n'
        << "pArrayDescriptor->Format:" << g.m_mapESCUarray_format[pArrayDescriptor->Format] << pArrayDescriptor->Format << '\n'
        << "pArrayDescriptor->NumChannels:" << pArrayDescriptor->NumChannels << '\n';
    oflog << "hArray:" << hArray << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuArrayDestroy(CUarray hArray)
{
    CUresult ret;
    ret = g.m_cuArrayDestroy(hArray);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hArray:" << hArray << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuArray3DCreate_v2(CUarray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR *pAllocateArray)
{
    CUresult ret;
    ret = g.m_cuArray3DCreate_v2(pHandle, pAllocateArray);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pHandle:" << pHandle << '\n';
    oflog << "pAllocateArray->Width:" << pAllocateArray->Width << '\n'
        << "pAllocateArray->Height:" << pAllocateArray->Height << '\n'
        << "pAllocateArray->Depth:" << pAllocateArray->Depth << '\n'
        << "pAllocateArray->Format:" << g.m_mapESCUarray_format[pAllocateArray->Format] << pAllocateArray->Format << '\n'
        << "pAllocateArray->NumChannels:" << pAllocateArray->NumChannels << '\n'
        << "pAllocateArray->Flags:" << pAllocateArray->Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuArray3DGetDescriptor_v2(CUDA_ARRAY3D_DESCRIPTOR *pArrayDescriptor, CUarray hArray)
{
    CUresult ret;
    ret = g.m_cuArray3DGetDescriptor_v2(pArrayDescriptor, hArray);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pArrayDescriptor->Width:" << pArrayDescriptor->Width << '\n'
        << "pArrayDescriptor->Height:" << pArrayDescriptor->Height << '\n'
        << "pArrayDescriptor->Depth:" << pArrayDescriptor->Depth << '\n'
        << "pArrayDescriptor->Format:" << g.m_mapESCUarray_format[pArrayDescriptor->Format] << pArrayDescriptor->Format << '\n'
        << "pArrayDescriptor->NumChannels:" << pArrayDescriptor->NumChannels << '\n'
        << "pArrayDescriptor->Flags:" << pArrayDescriptor->Flags << '\n';
    oflog << "hArray:" << hArray << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMipmappedArrayCreate(CUmipmappedArray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR *pMipmappedArrayDesc, unsigned int numMipmapLevels)
{
    CUresult ret;
    ret = g.m_cuMipmappedArrayCreate(pHandle, pMipmappedArrayDesc, numMipmapLevels);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pHandle:" << pHandle << '\n';
    oflog << "pMipmappedArrayDesc->Width:" << pMipmappedArrayDesc->Width << '\n'
        << "pMipmappedArrayDesc->Height:" << pMipmappedArrayDesc->Height << '\n'
        << "pMipmappedArrayDesc->Depth:" << pMipmappedArrayDesc->Depth << '\n'
        << "pMipmappedArrayDesc->Format:" << g.m_mapESCUarray_format[pMipmappedArrayDesc->Format] << pMipmappedArrayDesc->Format << '\n'
        << "pMipmappedArrayDesc->NumChannels:" << pMipmappedArrayDesc->NumChannels << '\n'
        << "pMipmappedArrayDesc->Flags:" << pMipmappedArrayDesc->Flags << '\n';
    oflog << "numMipmapLevels:" << numMipmapLevels << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMipmappedArrayGetLevel(CUarray *pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level)
{
    CUresult ret;
    ret = g.m_cuMipmappedArrayGetLevel(pLevelArray, hMipmappedArray, level);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pLevelArray:" << pLevelArray << '\n';
    oflog << "hMipmappedArray:" << hMipmappedArray << '\n';
    oflog << "level:" << level << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMipmappedArrayDestroy(CUmipmappedArray hMipmappedArray)
{
    CUresult ret;
    ret = g.m_cuMipmappedArrayDestroy(hMipmappedArray);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hMipmappedArray:" << hMipmappedArray << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuPointerGetAttribute(void *data, CUpointer_attribute attribute, CUdeviceptr ptr)
{
    CUresult ret;
    ret = g.m_cuPointerGetAttribute(data, attribute, ptr);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "data:" << data << '\n';
    oflog << "attribute:" << g.m_mapESCUpointer_attribute[attribute] << attribute << '\n';
    oflog << "ptr:" << ptr << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemPrefetchAsync(CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuMemPrefetchAsync(devPtr, count, dstDevice, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "devPtr:" << devPtr << '\n';
    oflog << "count:" << count << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemAdvise(CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device)
{
    CUresult ret;
    ret = g.m_cuMemAdvise(devPtr, count, advice, device);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "devPtr:" << devPtr << '\n';
    oflog << "count:" << count << '\n';
    oflog << "advice:" << g.m_mapESCUmem_advise[advice] << advice << '\n';
    oflog << "device:" << device << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemRangeGetAttribute(void *data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count)
{
    CUresult ret;
    ret = g.m_cuMemRangeGetAttribute(data, dataSize, attribute, devPtr, count);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "data:" << data << '\n';
    oflog << "dataSize:" << dataSize << '\n';
    oflog << "attribute:" << g.m_mapESCUmem_range_attribute[attribute] << attribute << '\n';
    oflog << "devPtr:" << devPtr << '\n';
    oflog << "count:" << count << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuMemRangeGetAttributes(void **data, size_t *dataSizes, CUmem_range_attribute *attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count)
{
    CUresult ret;
    ret = g.m_cuMemRangeGetAttributes(data, dataSizes, attributes, numAttributes, devPtr, count);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*data:" << (data ? *data : 0) << '\n';
    oflog << "*dataSizes:" << (dataSizes ? *dataSizes : 0) << '\n';
    oflog << "*attributes:" << g.m_mapESCUmem_range_attribute[*attributes] << attributes << '\n';
    oflog << "numAttributes:" << numAttributes << '\n';
    oflog << "devPtr:" << devPtr << '\n';
    oflog << "count:" << count << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuPointerSetAttribute(const void *value, CUpointer_attribute attribute, CUdeviceptr ptr)
{
    CUresult ret;
    ret = g.m_cuPointerSetAttribute(value, attribute, ptr);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "value:" << value << '\n';
    oflog << "attribute:" << g.m_mapESCUpointer_attribute[attribute] << attribute << '\n';
    oflog << "ptr:" << ptr << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuPointerGetAttributes(unsigned int numAttributes, CUpointer_attribute *attributes, void **data, CUdeviceptr ptr)
{
    CUresult ret;
    ret = g.m_cuPointerGetAttributes(numAttributes, attributes, data, ptr);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "numAttributes:" << numAttributes << '\n';
    oflog << "*attributes:" << g.m_mapESCUpointer_attribute[*attributes] << attributes << '\n';
    oflog << "*data:" << (data ? *data : 0) << '\n';
    oflog << "ptr:" << ptr << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamCreate(CUstream *phStream, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuStreamCreate(phStream, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phStream:" << phStream << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamCreateWithPriority(CUstream *phStream, unsigned int flags, int priority)
{
    CUresult ret;
    ret = g.m_cuStreamCreateWithPriority(phStream, flags, priority);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phStream:" << phStream << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << "priority:" << priority << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamGetPriority(CUstream hStream, int *priority)
{
    CUresult ret;
    ret = g.m_cuStreamGetPriority(hStream, priority);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << "*priority:" << (priority ? *priority : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamGetFlags(CUstream hStream, unsigned int *flags)
{
    CUresult ret;
    ret = g.m_cuStreamGetFlags(hStream, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << "*flags:" << (flags ? *flags : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamGetCtx(CUstream hStream, CUcontext *pctx)
{
    CUresult ret;
    ret = g.m_cuStreamGetCtx(hStream, pctx);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << "pctx:" << pctx << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamWaitEvent(CUstream hStream, CUevent hEvent, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuStreamWaitEvent(hStream, hEvent, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << "hEvent:" << hEvent << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamAddCallback(CUstream hStream, CUstreamCallback callback, void *userData, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamAddCallback(hStream, callback, userData, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << "callback:" << callback << '\n';
    oflog << "userData:" << userData << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamBeginCapture(CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuStreamBeginCapture(hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamEndCapture(CUstream hStream, CUgraph *phGraph)
{
    CUresult ret;
    ret = g.m_cuStreamEndCapture(hStream, phGraph);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << "phGraph:" << phGraph << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamIsCapturing(CUstream hStream, CUstreamCaptureStatus *captureStatus)
{
    CUresult ret;
    ret = g.m_cuStreamIsCapturing(hStream, captureStatus);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << "*captureStatus:" << g.m_mapESCUstreamCaptureStatus[*captureStatus] << captureStatus << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamAttachMemAsync(CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamAttachMemAsync(hStream, dptr, length, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << "dptr:" << dptr << '\n';
    oflog << "length:" << length << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamQuery(CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuStreamQuery(hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamSynchronize(CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuStreamSynchronize(hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamDestroy_v2(CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuStreamDestroy_v2(hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuEventCreate(CUevent *phEvent, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuEventCreate(phEvent, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phEvent:" << phEvent << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuEventRecord(CUevent hEvent, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuEventRecord(hEvent, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hEvent:" << hEvent << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuEventQuery(CUevent hEvent)
{
    CUresult ret;
    ret = g.m_cuEventQuery(hEvent);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hEvent:" << hEvent << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuEventSynchronize(CUevent hEvent)
{
    CUresult ret;
    ret = g.m_cuEventSynchronize(hEvent);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hEvent:" << hEvent << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuEventDestroy_v2(CUevent hEvent)
{
    CUresult ret;
    ret = g.m_cuEventDestroy_v2(hEvent);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hEvent:" << hEvent << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuEventElapsedTime(float *pMilliseconds, CUevent hStart, CUevent hEnd)
{
    CUresult ret;
    ret = g.m_cuEventElapsedTime(pMilliseconds, hStart, hEnd);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pMilliseconds:" << (pMilliseconds ? *pMilliseconds : 0) << '\n';
    oflog << "hStart:" << hStart << '\n';
    oflog << "hEnd:" << hEnd << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuImportExternalMemory(CUexternalMemory *extMem_out, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC *memHandleDesc)
{
    CUresult ret;
    ret = g.m_cuImportExternalMemory(extMem_out, memHandleDesc);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "extMem_out:" << extMem_out << '\n';
    oflog << "memHandleDesc->type:" << g.m_mapESCUexternalMemoryHandleType[memHandleDesc->type] << memHandleDesc->type << '\n'
        << "memHandleDesc->handle.fd:" << memHandleDesc->handle.fd << '\n'
        << "memHandleDesc->handle.win32.handle:" << memHandleDesc->handle.win32.handle << '\n'
        << "memHandleDesc->handle.win32.name:" << memHandleDesc->handle.win32.name << '\n'
        << "memHandleDesc->size:" << memHandleDesc->size << '\n'
        << "memHandleDesc->flags:" << memHandleDesc->flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuExternalMemoryGetMappedBuffer(CUdeviceptr *devPtr, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC *bufferDesc)
{
    CUresult ret;
    ret = g.m_cuExternalMemoryGetMappedBuffer(devPtr, extMem, bufferDesc);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*devPtr:" << (devPtr ? *devPtr : 0) << '\n';
    oflog << "extMem:" << extMem << '\n';
    oflog << "bufferDesc->offset:" << bufferDesc->offset << '\n'
        << "bufferDesc->size:" << bufferDesc->size << '\n'
        << "bufferDesc->flags:" << bufferDesc->flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuExternalMemoryGetMappedMipmappedArray(CUmipmappedArray *mipmap, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC *mipmapDesc)
{
    CUresult ret;
    ret = g.m_cuExternalMemoryGetMappedMipmappedArray(mipmap, extMem, mipmapDesc);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "mipmap:" << mipmap << '\n';
    oflog << "extMem:" << extMem << '\n';
    oflog << "mipmapDesc->offset:" << mipmapDesc->offset << '\n'
        << "mipmapDesc->arrayDesc.Width:" << mipmapDesc->arrayDesc.Width << '\n'
        << "mipmapDesc->arrayDesc.Height:" << mipmapDesc->arrayDesc.Height << '\n'
        << "mipmapDesc->arrayDesc.Depth:" << mipmapDesc->arrayDesc.Depth << '\n'
        << "mipmapDesc->arrayDesc.Format:" << g.m_mapESCUarray_format[mipmapDesc->arrayDesc.Format] << mipmapDesc->arrayDesc.Format << '\n'
        << "mipmapDesc->arrayDesc.NumChannels:" << mipmapDesc->arrayDesc.NumChannels << '\n'
        << "mipmapDesc->arrayDesc.Flags:" << mipmapDesc->arrayDesc.Flags << '\n'
        << "mipmapDesc->numLevels:" << mipmapDesc->numLevels << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDestroyExternalMemory(CUexternalMemory extMem)
{
    CUresult ret;
    ret = g.m_cuDestroyExternalMemory(extMem);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "extMem:" << extMem << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuImportExternalSemaphore(CUexternalSemaphore *extSem_out, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC *semHandleDesc)
{
    CUresult ret;
    ret = g.m_cuImportExternalSemaphore(extSem_out, semHandleDesc);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "extSem_out:" << extSem_out << '\n';
    oflog << "semHandleDesc->type:" << g.m_mapESCUexternalSemaphoreHandleType[semHandleDesc->type] << semHandleDesc->type << '\n'
        << "semHandleDesc->handle.fd:" << semHandleDesc->handle.fd << '\n'
        << "semHandleDesc->handle.win32.handle:" << semHandleDesc->handle.win32.handle << '\n'
        << "semHandleDesc->handle.win32.name:" << semHandleDesc->handle.win32.name << '\n'
        << "semHandleDesc->flags:" << semHandleDesc->flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuSignalExternalSemaphoresAsync(const CUexternalSemaphore *extSemArray, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS *paramsArray, unsigned int numExtSems, CUstream stream)
{
    CUresult ret;
    ret = g.m_cuSignalExternalSemaphoresAsync(extSemArray, paramsArray, numExtSems, stream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "extSemArray:" << extSemArray << '\n';
    oflog << "paramsArray->params.fence.value:" << paramsArray->params.fence.value << '\n'
        << "paramsArray->flags:" << paramsArray->flags << '\n';
    oflog << "numExtSems:" << numExtSems << '\n';
    oflog << "stream:" << stream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuWaitExternalSemaphoresAsync(const CUexternalSemaphore *extSemArray, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS *paramsArray, unsigned int numExtSems, CUstream stream)
{
    CUresult ret;
    ret = g.m_cuWaitExternalSemaphoresAsync(extSemArray, paramsArray, numExtSems, stream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "extSemArray:" << extSemArray << '\n';
    oflog << "paramsArray->params.fence.value:" << paramsArray->params.fence.value << '\n'
        << "paramsArray->flags:" << paramsArray->flags << '\n';
    oflog << "numExtSems:" << numExtSems << '\n';
    oflog << "stream:" << stream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDestroyExternalSemaphore(CUexternalSemaphore extSem)
{
    CUresult ret;
    ret = g.m_cuDestroyExternalSemaphore(extSem);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "extSem:" << extSem << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamWaitValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamWaitValue32(stream, addr, value, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "stream:" << stream << '\n';
    oflog << "addr:" << addr << '\n';
    oflog << "value:" << value << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamWaitValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamWaitValue64(stream, addr, value, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "stream:" << stream << '\n';
    oflog << "addr:" << addr << '\n';
    oflog << "value:" << value << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamWriteValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamWriteValue32(stream, addr, value, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "stream:" << stream << '\n';
    oflog << "addr:" << addr << '\n';
    oflog << "value:" << value << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamWriteValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamWriteValue64(stream, addr, value, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "stream:" << stream << '\n';
    oflog << "addr:" << addr << '\n';
    oflog << "value:" << value << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuStreamBatchMemOp(CUstream stream, unsigned int count, CUstreamBatchMemOpParams *paramArray, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuStreamBatchMemOp(stream, count, paramArray, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "stream:" << stream << '\n';
    oflog << "count:" << count << '\n';
    oflog << "paramArray->operation:" << g.m_mapESCUstreamBatchMemOpType[paramArray->operation] << paramArray->operation << '\n'
        << "paramArray->waitValue.operation:" << g.m_mapESCUstreamBatchMemOpType[paramArray->waitValue.operation] << paramArray->waitValue.operation << '\n'
        << "paramArray->waitValue.address:" << paramArray->waitValue.address << '\n'
        << "paramArray->waitValue.flags:" << paramArray->waitValue.flags << '\n'
        << "paramArray->waitValue.alias:" << paramArray->waitValue.alias << '\n'
        << "paramArray->writeValue.operation:" << g.m_mapESCUstreamBatchMemOpType[paramArray->writeValue.operation] << paramArray->writeValue.operation << '\n'
        << "paramArray->writeValue.address:" << paramArray->writeValue.address << '\n'
        << "paramArray->writeValue.flags:" << paramArray->writeValue.flags << '\n'
        << "paramArray->writeValue.alias:" << paramArray->writeValue.alias << '\n'
        << "paramArray->flushRemoteWrites.operation:" << g.m_mapESCUstreamBatchMemOpType[paramArray->flushRemoteWrites.operation] << paramArray->flushRemoteWrites.operation << '\n'
        << "paramArray->flushRemoteWrites.flags:" << paramArray->flushRemoteWrites.flags << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuFuncGetAttribute(int *pi, CUfunction_attribute attrib, CUfunction hfunc)
{
    CUresult ret;
    ret = g.m_cuFuncGetAttribute(pi, attrib, hfunc);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pi:" << (pi ? *pi : 0) << '\n';
    oflog << "attrib:" << g.m_mapESCUfunction_attribute[attrib] << attrib << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuFuncSetAttribute(CUfunction hfunc, CUfunction_attribute attrib, int value)
{
    CUresult ret;
    ret = g.m_cuFuncSetAttribute(hfunc, attrib, value);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << "attrib:" << g.m_mapESCUfunction_attribute[attrib] << attrib << '\n';
    oflog << "value:" << value << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuFuncSetCacheConfig(CUfunction hfunc, CUfunc_cache config)
{
    CUresult ret;
    ret = g.m_cuFuncSetCacheConfig(hfunc, config);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << "config:" << g.m_mapESCUfunc_cache[config] << config << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuFuncSetSharedMemConfig(CUfunction hfunc, CUsharedconfig config)
{
    CUresult ret;
    ret = g.m_cuFuncSetSharedMemConfig(hfunc, config);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << "config:" << g.m_mapESCUsharedconfig[config] << config << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLaunchKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void **kernelParams, void **extra)
{
    CUresult ret;
    ret = g.m_cuLaunchKernel(f, gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ, sharedMemBytes, hStream, kernelParams, extra);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "f:" << f << '\n';
    oflog << "gridDimX:" << gridDimX << '\n';
    oflog << "gridDimY:" << gridDimY << '\n';
    oflog << "gridDimZ:" << gridDimZ << '\n';
    oflog << "blockDimX:" << blockDimX << '\n';
    oflog << "blockDimY:" << blockDimY << '\n';
    oflog << "blockDimZ:" << blockDimZ << '\n';
    oflog << "sharedMemBytes:" << sharedMemBytes << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << "*kernelParams:" << (kernelParams ? *kernelParams : 0) << '\n';
    oflog << "*extra:" << (extra ? *extra : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLaunchCooperativeKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void **kernelParams)
{
    CUresult ret;
    ret = g.m_cuLaunchCooperativeKernel(f, gridDimX, gridDimY, gridDimZ, blockDimX, blockDimY, blockDimZ, sharedMemBytes, hStream, kernelParams);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "f:" << f << '\n';
    oflog << "gridDimX:" << gridDimX << '\n';
    oflog << "gridDimY:" << gridDimY << '\n';
    oflog << "gridDimZ:" << gridDimZ << '\n';
    oflog << "blockDimX:" << blockDimX << '\n';
    oflog << "blockDimY:" << blockDimY << '\n';
    oflog << "blockDimZ:" << blockDimZ << '\n';
    oflog << "sharedMemBytes:" << sharedMemBytes << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << "*kernelParams:" << (kernelParams ? *kernelParams : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLaunchCooperativeKernelMultiDevice(CUDA_LAUNCH_PARAMS *launchParamsList, unsigned int numDevices, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuLaunchCooperativeKernelMultiDevice(launchParamsList, numDevices, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "launchParamsList->function:" << launchParamsList->function << '\n'
        << "launchParamsList->gridDimX:" << launchParamsList->gridDimX << '\n'
        << "launchParamsList->gridDimY:" << launchParamsList->gridDimY << '\n'
        << "launchParamsList->gridDimZ:" << launchParamsList->gridDimZ << '\n'
        << "launchParamsList->blockDimX:" << launchParamsList->blockDimX << '\n'
        << "launchParamsList->blockDimY:" << launchParamsList->blockDimY << '\n'
        << "launchParamsList->blockDimZ:" << launchParamsList->blockDimZ << '\n'
        << "launchParamsList->sharedMemBytes:" << launchParamsList->sharedMemBytes << '\n'
        << "launchParamsList->hStream:" << launchParamsList->hStream << '\n'
        << "*launchParamsList->kernelParams:" << (launchParamsList->kernelParams ? *launchParamsList->kernelParams : 0) << '\n';
    oflog << "numDevices:" << numDevices << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLaunchHostFunc(CUstream hStream, CUhostFn fn, void *userData)
{
    CUresult ret;
    ret = g.m_cuLaunchHostFunc(hStream, fn, userData);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << "fn:" << fn << '\n';
    oflog << "userData:" << userData << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuFuncSetBlockShape(CUfunction hfunc, int x, int y, int z)
{
    CUresult ret;
    ret = g.m_cuFuncSetBlockShape(hfunc, x, y, z);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << "x:" << x << '\n';
    oflog << "y:" << y << '\n';
    oflog << "z:" << z << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuFuncSetSharedSize(CUfunction hfunc, unsigned int bytes)
{
    CUresult ret;
    ret = g.m_cuFuncSetSharedSize(hfunc, bytes);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << "bytes:" << bytes << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuParamSetSize(CUfunction hfunc, unsigned int numbytes)
{
    CUresult ret;
    ret = g.m_cuParamSetSize(hfunc, numbytes);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << "numbytes:" << numbytes << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuParamSeti(CUfunction hfunc, int offset, unsigned int value)
{
    CUresult ret;
    ret = g.m_cuParamSeti(hfunc, offset, value);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << "offset:" << offset << '\n';
    oflog << "value:" << value << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuParamSetf(CUfunction hfunc, int offset, float value)
{
    CUresult ret;
    ret = g.m_cuParamSetf(hfunc, offset, value);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << "offset:" << offset << '\n';
    oflog << "value:" << value << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuParamSetv(CUfunction hfunc, int offset, void *ptr, unsigned int numbytes)
{
    CUresult ret;
    ret = g.m_cuParamSetv(hfunc, offset, ptr, numbytes);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << "offset:" << offset << '\n';
    oflog << "ptr:" << ptr << '\n';
    oflog << "numbytes:" << numbytes << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLaunch(CUfunction f)
{
    CUresult ret;
    ret = g.m_cuLaunch(f);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "f:" << f << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLaunchGrid(CUfunction f, int grid_width, int grid_height)
{
    CUresult ret;
    ret = g.m_cuLaunchGrid(f, grid_width, grid_height);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "f:" << f << '\n';
    oflog << "grid_width:" << grid_width << '\n';
    oflog << "grid_height:" << grid_height << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuLaunchGridAsync(CUfunction f, int grid_width, int grid_height, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuLaunchGridAsync(f, grid_width, grid_height, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "f:" << f << '\n';
    oflog << "grid_width:" << grid_width << '\n';
    oflog << "grid_height:" << grid_height << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuParamSetTexRef(CUfunction hfunc, int texunit, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuParamSetTexRef(hfunc, texunit, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hfunc:" << hfunc << '\n';
    oflog << "texunit:" << texunit << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphCreate(CUgraph *phGraph, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuGraphCreate(phGraph, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phGraph:" << phGraph << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphAddKernelNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_KERNEL_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphAddKernelNode(phGraphNode, hGraph, dependencies, numDependencies, nodeParams);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phGraphNode:" << phGraphNode << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "dependencies:" << dependencies << '\n';
    oflog << "numDependencies:" << numDependencies << '\n';
    oflog << "nodeParams->func:" << nodeParams->func << '\n'
        << "nodeParams->gridDimX:" << nodeParams->gridDimX << '\n'
        << "nodeParams->gridDimY:" << nodeParams->gridDimY << '\n'
        << "nodeParams->gridDimZ:" << nodeParams->gridDimZ << '\n'
        << "nodeParams->blockDimX:" << nodeParams->blockDimX << '\n'
        << "nodeParams->blockDimY:" << nodeParams->blockDimY << '\n'
        << "nodeParams->blockDimZ:" << nodeParams->blockDimZ << '\n'
        << "nodeParams->sharedMemBytes:" << nodeParams->sharedMemBytes << '\n'
        << "*nodeParams->kernelParams:" << (nodeParams->kernelParams ? *nodeParams->kernelParams : 0) << '\n'
        << "*nodeParams->extra:" << (nodeParams->extra ? *nodeParams->extra : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphKernelNodeGetParams(CUgraphNode hNode, CUDA_KERNEL_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphKernelNodeGetParams(hNode, nodeParams);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "nodeParams->func:" << nodeParams->func << '\n'
        << "nodeParams->gridDimX:" << nodeParams->gridDimX << '\n'
        << "nodeParams->gridDimY:" << nodeParams->gridDimY << '\n'
        << "nodeParams->gridDimZ:" << nodeParams->gridDimZ << '\n'
        << "nodeParams->blockDimX:" << nodeParams->blockDimX << '\n'
        << "nodeParams->blockDimY:" << nodeParams->blockDimY << '\n'
        << "nodeParams->blockDimZ:" << nodeParams->blockDimZ << '\n'
        << "nodeParams->sharedMemBytes:" << nodeParams->sharedMemBytes << '\n'
        << "*nodeParams->kernelParams:" << (nodeParams->kernelParams ? *nodeParams->kernelParams : 0) << '\n'
        << "*nodeParams->extra:" << (nodeParams->extra ? *nodeParams->extra : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphKernelNodeSetParams(CUgraphNode hNode, const CUDA_KERNEL_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphKernelNodeSetParams(hNode, nodeParams);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "nodeParams->func:" << nodeParams->func << '\n'
        << "nodeParams->gridDimX:" << nodeParams->gridDimX << '\n'
        << "nodeParams->gridDimY:" << nodeParams->gridDimY << '\n'
        << "nodeParams->gridDimZ:" << nodeParams->gridDimZ << '\n'
        << "nodeParams->blockDimX:" << nodeParams->blockDimX << '\n'
        << "nodeParams->blockDimY:" << nodeParams->blockDimY << '\n'
        << "nodeParams->blockDimZ:" << nodeParams->blockDimZ << '\n'
        << "nodeParams->sharedMemBytes:" << nodeParams->sharedMemBytes << '\n'
        << "*nodeParams->kernelParams:" << (nodeParams->kernelParams ? *nodeParams->kernelParams : 0) << '\n'
        << "*nodeParams->extra:" << (nodeParams->extra ? *nodeParams->extra : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphAddMemcpyNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_MEMCPY3D *copyParams, CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuGraphAddMemcpyNode(phGraphNode, hGraph, dependencies, numDependencies, copyParams, ctx);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phGraphNode:" << phGraphNode << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "dependencies:" << dependencies << '\n';
    oflog << "numDependencies:" << numDependencies << '\n';
    oflog << "copyParams->srcXInBytes:" << copyParams->srcXInBytes << '\n'
        << "copyParams->srcY:" << copyParams->srcY << '\n'
        << "copyParams->srcZ:" << copyParams->srcZ << '\n'
        << "copyParams->srcLOD:" << copyParams->srcLOD << '\n'
        << "copyParams->srcMemoryType:" << g.m_mapESCUmemorytype[copyParams->srcMemoryType] << copyParams->srcMemoryType << '\n'
        << "copyParams->srcHost:" << copyParams->srcHost << '\n'
        << "copyParams->srcDevice:" << copyParams->srcDevice << '\n'
        << "copyParams->srcArray:" << copyParams->srcArray << '\n'
        << "copyParams->srcPitch:" << copyParams->srcPitch << '\n'
        << "copyParams->srcHeight:" << copyParams->srcHeight << '\n'
        << "copyParams->dstXInBytes:" << copyParams->dstXInBytes << '\n'
        << "copyParams->dstY:" << copyParams->dstY << '\n'
        << "copyParams->dstZ:" << copyParams->dstZ << '\n'
        << "copyParams->dstLOD:" << copyParams->dstLOD << '\n'
        << "copyParams->dstMemoryType:" << g.m_mapESCUmemorytype[copyParams->dstMemoryType] << copyParams->dstMemoryType << '\n'
        << "copyParams->dstHost:" << copyParams->dstHost << '\n'
        << "copyParams->dstDevice:" << copyParams->dstDevice << '\n'
        << "copyParams->dstArray:" << copyParams->dstArray << '\n'
        << "copyParams->dstPitch:" << copyParams->dstPitch << '\n'
        << "copyParams->dstHeight:" << copyParams->dstHeight << '\n'
        << "copyParams->WidthInBytes:" << copyParams->WidthInBytes << '\n'
        << "copyParams->Height:" << copyParams->Height << '\n'
        << "copyParams->Depth:" << copyParams->Depth << '\n';
    oflog << "ctx:" << ctx << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphMemcpyNodeGetParams(CUgraphNode hNode, CUDA_MEMCPY3D *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphMemcpyNodeGetParams(hNode, nodeParams);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "nodeParams->srcXInBytes:" << nodeParams->srcXInBytes << '\n'
        << "nodeParams->srcY:" << nodeParams->srcY << '\n'
        << "nodeParams->srcZ:" << nodeParams->srcZ << '\n'
        << "nodeParams->srcLOD:" << nodeParams->srcLOD << '\n'
        << "nodeParams->srcMemoryType:" << g.m_mapESCUmemorytype[nodeParams->srcMemoryType] << nodeParams->srcMemoryType << '\n'
        << "nodeParams->srcHost:" << nodeParams->srcHost << '\n'
        << "nodeParams->srcDevice:" << nodeParams->srcDevice << '\n'
        << "nodeParams->srcArray:" << nodeParams->srcArray << '\n'
        << "nodeParams->srcPitch:" << nodeParams->srcPitch << '\n'
        << "nodeParams->srcHeight:" << nodeParams->srcHeight << '\n'
        << "nodeParams->dstXInBytes:" << nodeParams->dstXInBytes << '\n'
        << "nodeParams->dstY:" << nodeParams->dstY << '\n'
        << "nodeParams->dstZ:" << nodeParams->dstZ << '\n'
        << "nodeParams->dstLOD:" << nodeParams->dstLOD << '\n'
        << "nodeParams->dstMemoryType:" << g.m_mapESCUmemorytype[nodeParams->dstMemoryType] << nodeParams->dstMemoryType << '\n'
        << "nodeParams->dstHost:" << nodeParams->dstHost << '\n'
        << "nodeParams->dstDevice:" << nodeParams->dstDevice << '\n'
        << "nodeParams->dstArray:" << nodeParams->dstArray << '\n'
        << "nodeParams->dstPitch:" << nodeParams->dstPitch << '\n'
        << "nodeParams->dstHeight:" << nodeParams->dstHeight << '\n'
        << "nodeParams->WidthInBytes:" << nodeParams->WidthInBytes << '\n'
        << "nodeParams->Height:" << nodeParams->Height << '\n'
        << "nodeParams->Depth:" << nodeParams->Depth << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphMemcpyNodeSetParams(CUgraphNode hNode, const CUDA_MEMCPY3D *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphMemcpyNodeSetParams(hNode, nodeParams);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "nodeParams->srcXInBytes:" << nodeParams->srcXInBytes << '\n'
        << "nodeParams->srcY:" << nodeParams->srcY << '\n'
        << "nodeParams->srcZ:" << nodeParams->srcZ << '\n'
        << "nodeParams->srcLOD:" << nodeParams->srcLOD << '\n'
        << "nodeParams->srcMemoryType:" << g.m_mapESCUmemorytype[nodeParams->srcMemoryType] << nodeParams->srcMemoryType << '\n'
        << "nodeParams->srcHost:" << nodeParams->srcHost << '\n'
        << "nodeParams->srcDevice:" << nodeParams->srcDevice << '\n'
        << "nodeParams->srcArray:" << nodeParams->srcArray << '\n'
        << "nodeParams->srcPitch:" << nodeParams->srcPitch << '\n'
        << "nodeParams->srcHeight:" << nodeParams->srcHeight << '\n'
        << "nodeParams->dstXInBytes:" << nodeParams->dstXInBytes << '\n'
        << "nodeParams->dstY:" << nodeParams->dstY << '\n'
        << "nodeParams->dstZ:" << nodeParams->dstZ << '\n'
        << "nodeParams->dstLOD:" << nodeParams->dstLOD << '\n'
        << "nodeParams->dstMemoryType:" << g.m_mapESCUmemorytype[nodeParams->dstMemoryType] << nodeParams->dstMemoryType << '\n'
        << "nodeParams->dstHost:" << nodeParams->dstHost << '\n'
        << "nodeParams->dstDevice:" << nodeParams->dstDevice << '\n'
        << "nodeParams->dstArray:" << nodeParams->dstArray << '\n'
        << "nodeParams->dstPitch:" << nodeParams->dstPitch << '\n'
        << "nodeParams->dstHeight:" << nodeParams->dstHeight << '\n'
        << "nodeParams->WidthInBytes:" << nodeParams->WidthInBytes << '\n'
        << "nodeParams->Height:" << nodeParams->Height << '\n'
        << "nodeParams->Depth:" << nodeParams->Depth << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphAddMemsetNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_MEMSET_NODE_PARAMS *memsetParams, CUcontext ctx)
{
    CUresult ret;
    ret = g.m_cuGraphAddMemsetNode(phGraphNode, hGraph, dependencies, numDependencies, memsetParams, ctx);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phGraphNode:" << phGraphNode << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "dependencies:" << dependencies << '\n';
    oflog << "numDependencies:" << numDependencies << '\n';
    oflog << "memsetParams->dst:" << memsetParams->dst << '\n'
        << "memsetParams->pitch:" << memsetParams->pitch << '\n'
        << "memsetParams->value:" << memsetParams->value << '\n'
        << "memsetParams->elementSize:" << memsetParams->elementSize << '\n'
        << "memsetParams->width:" << memsetParams->width << '\n'
        << "memsetParams->height:" << memsetParams->height << '\n';
    oflog << "ctx:" << ctx << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphMemsetNodeGetParams(CUgraphNode hNode, CUDA_MEMSET_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphMemsetNodeGetParams(hNode, nodeParams);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "nodeParams->dst:" << nodeParams->dst << '\n'
        << "nodeParams->pitch:" << nodeParams->pitch << '\n'
        << "nodeParams->value:" << nodeParams->value << '\n'
        << "nodeParams->elementSize:" << nodeParams->elementSize << '\n'
        << "nodeParams->width:" << nodeParams->width << '\n'
        << "nodeParams->height:" << nodeParams->height << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphMemsetNodeSetParams(CUgraphNode hNode, const CUDA_MEMSET_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphMemsetNodeSetParams(hNode, nodeParams);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "nodeParams->dst:" << nodeParams->dst << '\n'
        << "nodeParams->pitch:" << nodeParams->pitch << '\n'
        << "nodeParams->value:" << nodeParams->value << '\n'
        << "nodeParams->elementSize:" << nodeParams->elementSize << '\n'
        << "nodeParams->width:" << nodeParams->width << '\n'
        << "nodeParams->height:" << nodeParams->height << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphAddHostNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_HOST_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphAddHostNode(phGraphNode, hGraph, dependencies, numDependencies, nodeParams);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phGraphNode:" << phGraphNode << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "dependencies:" << dependencies << '\n';
    oflog << "numDependencies:" << numDependencies << '\n';
    oflog << "nodeParams->fn:" << nodeParams->fn << '\n'
        << "nodeParams->userData:" << nodeParams->userData << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphHostNodeGetParams(CUgraphNode hNode, CUDA_HOST_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphHostNodeGetParams(hNode, nodeParams);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "nodeParams->fn:" << nodeParams->fn << '\n'
        << "nodeParams->userData:" << nodeParams->userData << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphHostNodeSetParams(CUgraphNode hNode, const CUDA_HOST_NODE_PARAMS *nodeParams)
{
    CUresult ret;
    ret = g.m_cuGraphHostNodeSetParams(hNode, nodeParams);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "nodeParams->fn:" << nodeParams->fn << '\n'
        << "nodeParams->userData:" << nodeParams->userData << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphAddChildGraphNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, CUgraph childGraph)
{
    CUresult ret;
    ret = g.m_cuGraphAddChildGraphNode(phGraphNode, hGraph, dependencies, numDependencies, childGraph);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phGraphNode:" << phGraphNode << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "dependencies:" << dependencies << '\n';
    oflog << "numDependencies:" << numDependencies << '\n';
    oflog << "childGraph:" << childGraph << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphChildGraphNodeGetGraph(CUgraphNode hNode, CUgraph *phGraph)
{
    CUresult ret;
    ret = g.m_cuGraphChildGraphNodeGetGraph(hNode, phGraph);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "phGraph:" << phGraph << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphAddEmptyNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies)
{
    CUresult ret;
    ret = g.m_cuGraphAddEmptyNode(phGraphNode, hGraph, dependencies, numDependencies);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phGraphNode:" << phGraphNode << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "dependencies:" << dependencies << '\n';
    oflog << "numDependencies:" << numDependencies << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphClone(CUgraph *phGraphClone, CUgraph originalGraph)
{
    CUresult ret;
    ret = g.m_cuGraphClone(phGraphClone, originalGraph);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phGraphClone:" << phGraphClone << '\n';
    oflog << "originalGraph:" << originalGraph << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphNodeFindInClone(CUgraphNode *phNode, CUgraphNode hOriginalNode, CUgraph hClonedGraph)
{
    CUresult ret;
    ret = g.m_cuGraphNodeFindInClone(phNode, hOriginalNode, hClonedGraph);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phNode:" << phNode << '\n';
    oflog << "hOriginalNode:" << hOriginalNode << '\n';
    oflog << "hClonedGraph:" << hClonedGraph << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphNodeGetType(CUgraphNode hNode, CUgraphNodeType *type)
{
    CUresult ret;
    ret = g.m_cuGraphNodeGetType(hNode, type);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "*type:" << g.m_mapESCUgraphNodeType[*type] << type << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphGetNodes(CUgraph hGraph, CUgraphNode *nodes, size_t *numNodes)
{
    CUresult ret;
    ret = g.m_cuGraphGetNodes(hGraph, nodes, numNodes);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "nodes:" << nodes << '\n';
    oflog << "*numNodes:" << (numNodes ? *numNodes : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphGetRootNodes(CUgraph hGraph, CUgraphNode *rootNodes, size_t *numRootNodes)
{
    CUresult ret;
    ret = g.m_cuGraphGetRootNodes(hGraph, rootNodes, numRootNodes);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "rootNodes:" << rootNodes << '\n';
    oflog << "*numRootNodes:" << (numRootNodes ? *numRootNodes : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphGetEdges(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t *numEdges)
{
    CUresult ret;
    ret = g.m_cuGraphGetEdges(hGraph, from, to, numEdges);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "from:" << from << '\n';
    oflog << "to:" << to << '\n';
    oflog << "*numEdges:" << (numEdges ? *numEdges : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphNodeGetDependencies(CUgraphNode hNode, CUgraphNode *dependencies, size_t *numDependencies)
{
    CUresult ret;
    ret = g.m_cuGraphNodeGetDependencies(hNode, dependencies, numDependencies);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "dependencies:" << dependencies << '\n';
    oflog << "*numDependencies:" << (numDependencies ? *numDependencies : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphNodeGetDependentNodes(CUgraphNode hNode, CUgraphNode *dependentNodes, size_t *numDependentNodes)
{
    CUresult ret;
    ret = g.m_cuGraphNodeGetDependentNodes(hNode, dependentNodes, numDependentNodes);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << "dependentNodes:" << dependentNodes << '\n';
    oflog << "*numDependentNodes:" << (numDependentNodes ? *numDependentNodes : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphAddDependencies(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t numDependencies)
{
    CUresult ret;
    ret = g.m_cuGraphAddDependencies(hGraph, from, to, numDependencies);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "from:" << from << '\n';
    oflog << "to:" << to << '\n';
    oflog << "numDependencies:" << numDependencies << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphRemoveDependencies(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t numDependencies)
{
    CUresult ret;
    ret = g.m_cuGraphRemoveDependencies(hGraph, from, to, numDependencies);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "from:" << from << '\n';
    oflog << "to:" << to << '\n';
    oflog << "numDependencies:" << numDependencies << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphDestroyNode(CUgraphNode hNode)
{
    CUresult ret;
    ret = g.m_cuGraphDestroyNode(hNode);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hNode:" << hNode << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphInstantiate(CUgraphExec *phGraphExec, CUgraph hGraph, CUgraphNode *phErrorNode, char *logBuffer, size_t bufferSize)
{
    CUresult ret;
    ret = g.m_cuGraphInstantiate(phGraphExec, hGraph, phErrorNode, logBuffer, bufferSize);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phGraphExec:" << phGraphExec << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << "phErrorNode:" << phErrorNode << '\n';
    oflog << "logBuffer:" << logBuffer << '\n';
    oflog << "bufferSize:" << bufferSize << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphLaunch(CUgraphExec hGraphExec, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuGraphLaunch(hGraphExec, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hGraphExec:" << hGraphExec << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphExecDestroy(CUgraphExec hGraphExec)
{
    CUresult ret;
    ret = g.m_cuGraphExecDestroy(hGraphExec);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hGraphExec:" << hGraphExec << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphDestroy(CUgraph hGraph)
{
    CUresult ret;
    ret = g.m_cuGraphDestroy(hGraph);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hGraph:" << hGraph << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuOccupancyMaxActiveBlocksPerMultiprocessor(int *numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize)
{
    CUresult ret;
    ret = g.m_cuOccupancyMaxActiveBlocksPerMultiprocessor(numBlocks, func, blockSize, dynamicSMemSize);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*numBlocks:" << (numBlocks ? *numBlocks : 0) << '\n';
    oflog << "func:" << func << '\n';
    oflog << "blockSize:" << blockSize << '\n';
    oflog << "dynamicSMemSize:" << dynamicSMemSize << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int *numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(numBlocks, func, blockSize, dynamicSMemSize, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*numBlocks:" << (numBlocks ? *numBlocks : 0) << '\n';
    oflog << "func:" << func << '\n';
    oflog << "blockSize:" << blockSize << '\n';
    oflog << "dynamicSMemSize:" << dynamicSMemSize << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuOccupancyMaxPotentialBlockSize(int *minGridSize, int *blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit)
{
    CUresult ret;
    ret = g.m_cuOccupancyMaxPotentialBlockSize(minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*minGridSize:" << (minGridSize ? *minGridSize : 0) << '\n';
    oflog << "*blockSize:" << (blockSize ? *blockSize : 0) << '\n';
    oflog << "func:" << func << '\n';
    oflog << "blockSizeToDynamicSMemSize:" << blockSizeToDynamicSMemSize << '\n';
    oflog << "dynamicSMemSize:" << dynamicSMemSize << '\n';
    oflog << "blockSizeLimit:" << blockSizeLimit << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuOccupancyMaxPotentialBlockSizeWithFlags(int *minGridSize, int *blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuOccupancyMaxPotentialBlockSizeWithFlags(minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*minGridSize:" << (minGridSize ? *minGridSize : 0) << '\n';
    oflog << "*blockSize:" << (blockSize ? *blockSize : 0) << '\n';
    oflog << "func:" << func << '\n';
    oflog << "blockSizeToDynamicSMemSize:" << blockSizeToDynamicSMemSize << '\n';
    oflog << "dynamicSMemSize:" << dynamicSMemSize << '\n';
    oflog << "blockSizeLimit:" << blockSizeLimit << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetArray(CUtexref hTexRef, CUarray hArray, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuTexRefSetArray(hTexRef, hArray, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "hArray:" << hArray << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetMipmappedArray(CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuTexRefSetMipmappedArray(hTexRef, hMipmappedArray, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "hMipmappedArray:" << hMipmappedArray << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetAddress_v2(size_t *ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes)
{
    CUresult ret;
    ret = g.m_cuTexRefSetAddress_v2(ByteOffset, hTexRef, dptr, bytes);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*ByteOffset:" << (ByteOffset ? *ByteOffset : 0) << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "dptr:" << dptr << '\n';
    oflog << "bytes:" << bytes << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetAddress2D_v3(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR *desc, CUdeviceptr dptr, size_t Pitch)
{
    CUresult ret;
    ret = g.m_cuTexRefSetAddress2D_v3(hTexRef, desc, dptr, Pitch);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "desc->Width:" << desc->Width << '\n'
        << "desc->Height:" << desc->Height << '\n'
        << "desc->Format:" << g.m_mapESCUarray_format[desc->Format] << desc->Format << '\n'
        << "desc->NumChannels:" << desc->NumChannels << '\n';
    oflog << "dptr:" << dptr << '\n';
    oflog << "Pitch:" << Pitch << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetFormat(CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents)
{
    CUresult ret;
    ret = g.m_cuTexRefSetFormat(hTexRef, fmt, NumPackedComponents);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "fmt:" << g.m_mapESCUarray_format[fmt] << fmt << '\n';
    oflog << "NumPackedComponents:" << NumPackedComponents << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetAddressMode(CUtexref hTexRef, int dim, CUaddress_mode am)
{
    CUresult ret;
    ret = g.m_cuTexRefSetAddressMode(hTexRef, dim, am);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "dim:" << dim << '\n';
    oflog << "am:" << g.m_mapESCUaddress_mode[am] << am << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetFilterMode(CUtexref hTexRef, CUfilter_mode fm)
{
    CUresult ret;
    ret = g.m_cuTexRefSetFilterMode(hTexRef, fm);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "fm:" << g.m_mapESCUfilter_mode[fm] << fm << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetMipmapFilterMode(CUtexref hTexRef, CUfilter_mode fm)
{
    CUresult ret;
    ret = g.m_cuTexRefSetMipmapFilterMode(hTexRef, fm);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "fm:" << g.m_mapESCUfilter_mode[fm] << fm << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetMipmapLevelBias(CUtexref hTexRef, float bias)
{
    CUresult ret;
    ret = g.m_cuTexRefSetMipmapLevelBias(hTexRef, bias);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "bias:" << bias << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetMipmapLevelClamp(CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp)
{
    CUresult ret;
    ret = g.m_cuTexRefSetMipmapLevelClamp(hTexRef, minMipmapLevelClamp, maxMipmapLevelClamp);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "minMipmapLevelClamp:" << minMipmapLevelClamp << '\n';
    oflog << "maxMipmapLevelClamp:" << maxMipmapLevelClamp << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetMaxAnisotropy(CUtexref hTexRef, unsigned int maxAniso)
{
    CUresult ret;
    ret = g.m_cuTexRefSetMaxAnisotropy(hTexRef, maxAniso);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "maxAniso:" << maxAniso << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetBorderColor(CUtexref hTexRef, float *pBorderColor)
{
    CUresult ret;
    ret = g.m_cuTexRefSetBorderColor(hTexRef, pBorderColor);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "*pBorderColor:" << (pBorderColor ? *pBorderColor : 0) << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefSetFlags(CUtexref hTexRef, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuTexRefSetFlags(hTexRef, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetAddress_v2(CUdeviceptr *pdptr, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetAddress_v2(pdptr, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pdptr:" << (pdptr ? *pdptr : 0) << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetArray(CUarray *phArray, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetArray(phArray, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phArray:" << phArray << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetMipmappedArray(CUmipmappedArray *phMipmappedArray, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetMipmappedArray(phMipmappedArray, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phMipmappedArray:" << phMipmappedArray << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetAddressMode(CUaddress_mode *pam, CUtexref hTexRef, int dim)
{
    CUresult ret;
    ret = g.m_cuTexRefGetAddressMode(pam, hTexRef, dim);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pam:" << g.m_mapESCUaddress_mode[*pam] << pam << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << "dim:" << dim << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetFilterMode(CUfilter_mode *pfm, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetFilterMode(pfm, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pfm:" << g.m_mapESCUfilter_mode[*pfm] << pfm << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetFormat(CUarray_format *pFormat, int *pNumChannels, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetFormat(pFormat, pNumChannels, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pFormat:" << g.m_mapESCUarray_format[*pFormat] << pFormat << '\n';
    oflog << "*pNumChannels:" << (pNumChannels ? *pNumChannels : 0) << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetMipmapFilterMode(CUfilter_mode *pfm, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetMipmapFilterMode(pfm, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pfm:" << g.m_mapESCUfilter_mode[*pfm] << pfm << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetMipmapLevelBias(float *pbias, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetMipmapLevelBias(pbias, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pbias:" << (pbias ? *pbias : 0) << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetMipmapLevelClamp(float *pminMipmapLevelClamp, float *pmaxMipmapLevelClamp, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetMipmapLevelClamp(pminMipmapLevelClamp, pmaxMipmapLevelClamp, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pminMipmapLevelClamp:" << (pminMipmapLevelClamp ? *pminMipmapLevelClamp : 0) << '\n';
    oflog << "*pmaxMipmapLevelClamp:" << (pmaxMipmapLevelClamp ? *pmaxMipmapLevelClamp : 0) << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetMaxAnisotropy(int *pmaxAniso, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetMaxAnisotropy(pmaxAniso, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pmaxAniso:" << (pmaxAniso ? *pmaxAniso : 0) << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetBorderColor(float *pBorderColor, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetBorderColor(pBorderColor, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pBorderColor:" << (pBorderColor ? *pBorderColor : 0) << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefGetFlags(unsigned int *pFlags, CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefGetFlags(pFlags, hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pFlags:" << (pFlags ? *pFlags : 0) << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefCreate(CUtexref *pTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefCreate(pTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pTexRef:" << pTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexRefDestroy(CUtexref hTexRef)
{
    CUresult ret;
    ret = g.m_cuTexRefDestroy(hTexRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hTexRef:" << hTexRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuSurfRefSetArray(CUsurfref hSurfRef, CUarray hArray, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuSurfRefSetArray(hSurfRef, hArray, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "hSurfRef:" << hSurfRef << '\n';
    oflog << "hArray:" << hArray << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuSurfRefGetArray(CUarray *phArray, CUsurfref hSurfRef)
{
    CUresult ret;
    ret = g.m_cuSurfRefGetArray(phArray, hSurfRef);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "phArray:" << phArray << '\n';
    oflog << "hSurfRef:" << hSurfRef << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexObjectCreate(CUtexObject *pTexObject, const CUDA_RESOURCE_DESC *pResDesc, const CUDA_TEXTURE_DESC *pTexDesc, const CUDA_RESOURCE_VIEW_DESC *pResViewDesc)
{
    CUresult ret;
    ret = g.m_cuTexObjectCreate(pTexObject, pResDesc, pTexDesc, pResViewDesc);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pTexObject:" << (pTexObject ? *pTexObject : 0) << '\n';
    oflog << "pResDesc->resType:" << g.m_mapESCUresourcetype[pResDesc->resType] << pResDesc->resType << '\n'
        << "pResDesc->res.array.hArray:" << pResDesc->res.array.hArray << '\n'
        << "pResDesc->res.mipmap.hMipmappedArray:" << pResDesc->res.mipmap.hMipmappedArray << '\n'
        << "pResDesc->res.linear.devPtr:" << pResDesc->res.linear.devPtr << '\n'
        << "pResDesc->res.linear.format:" << g.m_mapESCUarray_format[pResDesc->res.linear.format] << pResDesc->res.linear.format << '\n'
        << "pResDesc->res.linear.numChannels:" << pResDesc->res.linear.numChannels << '\n'
        << "pResDesc->res.linear.sizeInBytes:" << pResDesc->res.linear.sizeInBytes << '\n'
        << "pResDesc->res.pitch2D.devPtr:" << pResDesc->res.pitch2D.devPtr << '\n'
        << "pResDesc->res.pitch2D.format:" << g.m_mapESCUarray_format[pResDesc->res.pitch2D.format] << pResDesc->res.pitch2D.format << '\n'
        << "pResDesc->res.pitch2D.numChannels:" << pResDesc->res.pitch2D.numChannels << '\n'
        << "pResDesc->res.pitch2D.width:" << pResDesc->res.pitch2D.width << '\n'
        << "pResDesc->res.pitch2D.height:" << pResDesc->res.pitch2D.height << '\n'
        << "pResDesc->res.pitch2D.pitchInBytes:" << pResDesc->res.pitch2D.pitchInBytes << '\n'
        << "pResDesc->flags:" << pResDesc->flags << '\n';
    oflog << "pTexDesc->addressMode[0]:" << g.m_mapESCUaddress_mode[pTexDesc->addressMode[0]] << pTexDesc->addressMode[0] << '\n'
        << "pTexDesc->addressMode[1]:" << g.m_mapESCUaddress_mode[pTexDesc->addressMode[1]] << pTexDesc->addressMode[1] << '\n'
        << "pTexDesc->addressMode[2]:" << g.m_mapESCUaddress_mode[pTexDesc->addressMode[2]] << pTexDesc->addressMode[2] << '\n'
        << "pTexDesc->filterMode:" << g.m_mapESCUfilter_mode[pTexDesc->filterMode] << pTexDesc->filterMode << '\n'
        << "pTexDesc->flags:" << pTexDesc->flags << '\n'
        << "pTexDesc->maxAnisotropy:" << pTexDesc->maxAnisotropy << '\n'
        << "pTexDesc->mipmapFilterMode:" << g.m_mapESCUfilter_mode[pTexDesc->mipmapFilterMode] << pTexDesc->mipmapFilterMode << '\n'
        << "pTexDesc->mipmapLevelBias:" << pTexDesc->mipmapLevelBias << '\n'
        << "pTexDesc->minMipmapLevelClamp:" << pTexDesc->minMipmapLevelClamp << '\n'
        << "pTexDesc->maxMipmapLevelClamp:" << pTexDesc->maxMipmapLevelClamp << '\n'
        << "pTexDesc->borderColor:" << pTexDesc->borderColor[0] << '\n'
        << "pTexDesc->borderColor:" << pTexDesc->borderColor[1] << '\n'
        << "pTexDesc->borderColor:" << pTexDesc->borderColor[2] << '\n'
        << "pTexDesc->borderColor:" << pTexDesc->borderColor[3] << '\n';
    oflog << "pResViewDesc->format:" << g.m_mapESCUresourceViewFormat[pResViewDesc->format] << pResViewDesc->format << '\n'
        << "pResViewDesc->width:" << pResViewDesc->width << '\n'
        << "pResViewDesc->height:" << pResViewDesc->height << '\n'
        << "pResViewDesc->depth:" << pResViewDesc->depth << '\n'
        << "pResViewDesc->firstMipmapLevel:" << pResViewDesc->firstMipmapLevel << '\n'
        << "pResViewDesc->lastMipmapLevel:" << pResViewDesc->lastMipmapLevel << '\n'
        << "pResViewDesc->firstLayer:" << pResViewDesc->firstLayer << '\n'
        << "pResViewDesc->lastLayer:" << pResViewDesc->lastLayer << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexObjectDestroy(CUtexObject texObject)
{
    CUresult ret;
    ret = g.m_cuTexObjectDestroy(texObject);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "texObject:" << texObject << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexObjectGetResourceDesc(CUDA_RESOURCE_DESC *pResDesc, CUtexObject texObject)
{
    CUresult ret;
    ret = g.m_cuTexObjectGetResourceDesc(pResDesc, texObject);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pResDesc->resType:" << g.m_mapESCUresourcetype[pResDesc->resType] << pResDesc->resType << '\n'
        << "pResDesc->res.array.hArray:" << pResDesc->res.array.hArray << '\n'
        << "pResDesc->res.mipmap.hMipmappedArray:" << pResDesc->res.mipmap.hMipmappedArray << '\n'
        << "pResDesc->res.linear.devPtr:" << pResDesc->res.linear.devPtr << '\n'
        << "pResDesc->res.linear.format:" << g.m_mapESCUarray_format[pResDesc->res.linear.format] << pResDesc->res.linear.format << '\n'
        << "pResDesc->res.linear.numChannels:" << pResDesc->res.linear.numChannels << '\n'
        << "pResDesc->res.linear.sizeInBytes:" << pResDesc->res.linear.sizeInBytes << '\n'
        << "pResDesc->res.pitch2D.devPtr:" << pResDesc->res.pitch2D.devPtr << '\n'
        << "pResDesc->res.pitch2D.format:" << g.m_mapESCUarray_format[pResDesc->res.pitch2D.format] << pResDesc->res.pitch2D.format << '\n'
        << "pResDesc->res.pitch2D.numChannels:" << pResDesc->res.pitch2D.numChannels << '\n'
        << "pResDesc->res.pitch2D.width:" << pResDesc->res.pitch2D.width << '\n'
        << "pResDesc->res.pitch2D.height:" << pResDesc->res.pitch2D.height << '\n'
        << "pResDesc->res.pitch2D.pitchInBytes:" << pResDesc->res.pitch2D.pitchInBytes << '\n'
        << "pResDesc->flags:" << pResDesc->flags << '\n';
    oflog << "texObject:" << texObject << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexObjectGetTextureDesc(CUDA_TEXTURE_DESC *pTexDesc, CUtexObject texObject)
{
    CUresult ret;
    ret = g.m_cuTexObjectGetTextureDesc(pTexDesc, texObject);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pTexDesc->addressMode[0]:" << g.m_mapESCUaddress_mode[pTexDesc->addressMode[0]] << pTexDesc->addressMode[0] << '\n'
        << "pTexDesc->addressMode[1]:" << g.m_mapESCUaddress_mode[pTexDesc->addressMode[1]] << pTexDesc->addressMode[1] << '\n'
        << "pTexDesc->addressMode[2]:" << g.m_mapESCUaddress_mode[pTexDesc->addressMode[2]] << pTexDesc->addressMode[2] << '\n'
        << "pTexDesc->filterMode:" << g.m_mapESCUfilter_mode[pTexDesc->filterMode] << pTexDesc->filterMode << '\n'
        << "pTexDesc->flags:" << pTexDesc->flags << '\n'
        << "pTexDesc->maxAnisotropy:" << pTexDesc->maxAnisotropy << '\n'
        << "pTexDesc->mipmapFilterMode:" << g.m_mapESCUfilter_mode[pTexDesc->mipmapFilterMode] << pTexDesc->mipmapFilterMode << '\n'
        << "pTexDesc->mipmapLevelBias:" << pTexDesc->mipmapLevelBias << '\n'
        << "pTexDesc->minMipmapLevelClamp:" << pTexDesc->minMipmapLevelClamp << '\n'
        << "pTexDesc->maxMipmapLevelClamp:" << pTexDesc->maxMipmapLevelClamp << '\n'
        << "pTexDesc->borderColor:" << pTexDesc->borderColor[0] << '\n'
        << "pTexDesc->borderColor:" << pTexDesc->borderColor[1] << '\n'
        << "pTexDesc->borderColor:" << pTexDesc->borderColor[2] << '\n'
        << "pTexDesc->borderColor:" << pTexDesc->borderColor[3] << '\n';
    oflog << "texObject:" << texObject << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuTexObjectGetResourceViewDesc(CUDA_RESOURCE_VIEW_DESC *pResViewDesc, CUtexObject texObject)
{
    CUresult ret;
    ret = g.m_cuTexObjectGetResourceViewDesc(pResViewDesc, texObject);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pResViewDesc->format:" << g.m_mapESCUresourceViewFormat[pResViewDesc->format] << pResViewDesc->format << '\n'
        << "pResViewDesc->width:" << pResViewDesc->width << '\n'
        << "pResViewDesc->height:" << pResViewDesc->height << '\n'
        << "pResViewDesc->depth:" << pResViewDesc->depth << '\n'
        << "pResViewDesc->firstMipmapLevel:" << pResViewDesc->firstMipmapLevel << '\n'
        << "pResViewDesc->lastMipmapLevel:" << pResViewDesc->lastMipmapLevel << '\n'
        << "pResViewDesc->firstLayer:" << pResViewDesc->firstLayer << '\n'
        << "pResViewDesc->lastLayer:" << pResViewDesc->lastLayer << '\n';
    oflog << "texObject:" << texObject << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuSurfObjectCreate(CUsurfObject *pSurfObject, const CUDA_RESOURCE_DESC *pResDesc)
{
    CUresult ret;
    ret = g.m_cuSurfObjectCreate(pSurfObject, pResDesc);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pSurfObject:" << (pSurfObject ? *pSurfObject : 0) << '\n';
    oflog << "pResDesc->resType:" << g.m_mapESCUresourcetype[pResDesc->resType] << pResDesc->resType << '\n'
        << "pResDesc->res.array.hArray:" << pResDesc->res.array.hArray << '\n'
        << "pResDesc->res.mipmap.hMipmappedArray:" << pResDesc->res.mipmap.hMipmappedArray << '\n'
        << "pResDesc->res.linear.devPtr:" << pResDesc->res.linear.devPtr << '\n'
        << "pResDesc->res.linear.format:" << g.m_mapESCUarray_format[pResDesc->res.linear.format] << pResDesc->res.linear.format << '\n'
        << "pResDesc->res.linear.numChannels:" << pResDesc->res.linear.numChannels << '\n'
        << "pResDesc->res.linear.sizeInBytes:" << pResDesc->res.linear.sizeInBytes << '\n'
        << "pResDesc->res.pitch2D.devPtr:" << pResDesc->res.pitch2D.devPtr << '\n'
        << "pResDesc->res.pitch2D.format:" << g.m_mapESCUarray_format[pResDesc->res.pitch2D.format] << pResDesc->res.pitch2D.format << '\n'
        << "pResDesc->res.pitch2D.numChannels:" << pResDesc->res.pitch2D.numChannels << '\n'
        << "pResDesc->res.pitch2D.width:" << pResDesc->res.pitch2D.width << '\n'
        << "pResDesc->res.pitch2D.height:" << pResDesc->res.pitch2D.height << '\n'
        << "pResDesc->res.pitch2D.pitchInBytes:" << pResDesc->res.pitch2D.pitchInBytes << '\n'
        << "pResDesc->flags:" << pResDesc->flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuSurfObjectDestroy(CUsurfObject surfObject)
{
    CUresult ret;
    ret = g.m_cuSurfObjectDestroy(surfObject);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "surfObject:" << surfObject << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuSurfObjectGetResourceDesc(CUDA_RESOURCE_DESC *pResDesc, CUsurfObject surfObject)
{
    CUresult ret;
    ret = g.m_cuSurfObjectGetResourceDesc(pResDesc, surfObject);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pResDesc->resType:" << g.m_mapESCUresourcetype[pResDesc->resType] << pResDesc->resType << '\n'
        << "pResDesc->res.array.hArray:" << pResDesc->res.array.hArray << '\n'
        << "pResDesc->res.mipmap.hMipmappedArray:" << pResDesc->res.mipmap.hMipmappedArray << '\n'
        << "pResDesc->res.linear.devPtr:" << pResDesc->res.linear.devPtr << '\n'
        << "pResDesc->res.linear.format:" << g.m_mapESCUarray_format[pResDesc->res.linear.format] << pResDesc->res.linear.format << '\n'
        << "pResDesc->res.linear.numChannels:" << pResDesc->res.linear.numChannels << '\n'
        << "pResDesc->res.linear.sizeInBytes:" << pResDesc->res.linear.sizeInBytes << '\n'
        << "pResDesc->res.pitch2D.devPtr:" << pResDesc->res.pitch2D.devPtr << '\n'
        << "pResDesc->res.pitch2D.format:" << g.m_mapESCUarray_format[pResDesc->res.pitch2D.format] << pResDesc->res.pitch2D.format << '\n'
        << "pResDesc->res.pitch2D.numChannels:" << pResDesc->res.pitch2D.numChannels << '\n'
        << "pResDesc->res.pitch2D.width:" << pResDesc->res.pitch2D.width << '\n'
        << "pResDesc->res.pitch2D.height:" << pResDesc->res.pitch2D.height << '\n'
        << "pResDesc->res.pitch2D.pitchInBytes:" << pResDesc->res.pitch2D.pitchInBytes << '\n'
        << "pResDesc->flags:" << pResDesc->flags << '\n';
    oflog << "surfObject:" << surfObject << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceCanAccessPeer(int *canAccessPeer, CUdevice dev, CUdevice peerDev)
{
    CUresult ret;
    ret = g.m_cuDeviceCanAccessPeer(canAccessPeer, dev, peerDev);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*canAccessPeer:" << (canAccessPeer ? *canAccessPeer : 0) << '\n';
    oflog << "dev:" << dev << '\n';
    oflog << "peerDev:" << peerDev << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxEnablePeerAccess(CUcontext peerContext, unsigned int Flags)
{
    CUresult ret;
    ret = g.m_cuCtxEnablePeerAccess(peerContext, Flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "peerContext:" << peerContext << '\n';
    oflog << "Flags:" << Flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuCtxDisablePeerAccess(CUcontext peerContext)
{
    CUresult ret;
    ret = g.m_cuCtxDisablePeerAccess(peerContext);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "peerContext:" << peerContext << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuDeviceGetP2PAttribute(int *value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice)
{
    CUresult ret;
    ret = g.m_cuDeviceGetP2PAttribute(value, attrib, srcDevice, dstDevice);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*value:" << (value ? *value : 0) << '\n';
    oflog << "attrib:" << g.m_mapESCUdevice_P2PAttribute[attrib] << attrib << '\n';
    oflog << "srcDevice:" << srcDevice << '\n';
    oflog << "dstDevice:" << dstDevice << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphicsUnregisterResource(CUgraphicsResource resource)
{
    CUresult ret;
    ret = g.m_cuGraphicsUnregisterResource(resource);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "resource:" << resource << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphicsSubResourceGetMappedArray(CUarray *pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel)
{
    CUresult ret;
    ret = g.m_cuGraphicsSubResourceGetMappedArray(pArray, resource, arrayIndex, mipLevel);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pArray:" << pArray << '\n';
    oflog << "resource:" << resource << '\n';
    oflog << "arrayIndex:" << arrayIndex << '\n';
    oflog << "mipLevel:" << mipLevel << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphicsResourceGetMappedMipmappedArray(CUmipmappedArray *pMipmappedArray, CUgraphicsResource resource)
{
    CUresult ret;
    ret = g.m_cuGraphicsResourceGetMappedMipmappedArray(pMipmappedArray, resource);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "pMipmappedArray:" << pMipmappedArray << '\n';
    oflog << "resource:" << resource << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphicsResourceGetMappedPointer_v2(CUdeviceptr *pDevPtr, size_t *pSize, CUgraphicsResource resource)
{
    CUresult ret;
    ret = g.m_cuGraphicsResourceGetMappedPointer_v2(pDevPtr, pSize, resource);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*pDevPtr:" << (pDevPtr ? *pDevPtr : 0) << '\n';
    oflog << "*pSize:" << (pSize ? *pSize : 0) << '\n';
    oflog << "resource:" << resource << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphicsResourceSetMapFlags_v2(CUgraphicsResource resource, unsigned int flags)
{
    CUresult ret;
    ret = g.m_cuGraphicsResourceSetMapFlags_v2(resource, flags);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "resource:" << resource << '\n';
    oflog << "flags:" << flags << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphicsMapResources(unsigned int count, CUgraphicsResource *resources, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuGraphicsMapResources(count, resources, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "count:" << count << '\n';
    oflog << "resources:" << resources << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGraphicsUnmapResources(unsigned int count, CUgraphicsResource *resources, CUstream hStream)
{
    CUresult ret;
    ret = g.m_cuGraphicsUnmapResources(count, resources, hStream);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "count:" << count << '\n';
    oflog << "resources:" << resources << '\n';
    oflog << "hStream:" << hStream << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


CUresult __stdcall cuGetExportTable(const void **ppExportTable, const CUuuid *pExportTableId)
{
    CUresult ret;
    ret = g.m_cuGetExportTable(ppExportTable, pExportTableId);
    oflog << __FUNCTION__ << " start:\n";
    oflog << "CUresult:" << g.m_mapESCUresult[ret] << '\n';
    oflog << "*ppExportTable:" << (ppExportTable ? *ppExportTable : 0) << '\n';
    oflog << "pExportTableId->bytes:" << pExportTableId->bytes << '\n';
    oflog << __FUNCTION__ << " end:\n\n";
    return ret;
}


